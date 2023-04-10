#include "stdafx.h"
#include "NetUdpIocp.h"


namespace NetCore {

	CNetUdpIocp::CNetUdpIocp(VOID)
		: m_OnIoRecvPacket(NULL)
	{
	}

	CNetUdpIocp::~CNetUdpIocp(VOID)
	{
		End();
	}

	BOOL CNetUdpIocp::Begin(ADDR_PORT port, int nRecvUdpPoolCnt, int nSendUdpPoolCnt, void* owner, void* callback_OnIoRecvPacket)
	{
		CIocp::SetOwner(owner);
		m_OnIoRecvPacket = (func_OnIoRecvUdpPacket)callback_OnIoRecvPacket;

		if (!CIocp::Begin())
		{
			LOGEVENT("Session_Base_Error", _T("failed CIocp::Begin"));
			End();
			return FALSE;
		}

		//if (!UdpSession_.Begin(0, MAX_CLIENT_RECV_UDP_QUEUE_COUNT))
		if (!UdpSession_.Begin(0, nRecvUdpPoolCnt))
		{
			LOGEVENT("Session_Base_Error", _T("failed UdpSession_.Begin"));
			End();
			return FALSE;
		}

		//if (!UdpSession_.UdpBind(port, MAX_SEND_QUEUE_COUNT))
		if (!UdpSession_.UdpBind(port, nSendUdpPoolCnt))
		{
			LOGEVENT("Session_Base_Error", _T("failed UdpSession_.UdpBind"));
			End();
			return FALSE;
		}

		if (!CIocp::RegisterSocketToIocp(UdpSession_.GetSocket(), (ULONG_PTR)&UdpSession_))
		{
			LOGEVENT("Session_Base_Error", _T("failed CIocp::RegisterSocketToIocp"));
			End();
			return FALSE;
		}

		if (!UdpSession_.InitializeRecvFromForIocp())
		{
			LOGEVENT("Session_Base_Error", _T("failed UdpSession_.InitializeRecvFromForIocp"));
			End();
			return FALSE;
		}

		//if (!UdpSession_.InitializeRecvFromForEventSelect())
		//{
		//	LOGEVENT("Session_Base_Error", _T("failed UdpSession_.InitializeRecvFromForEventSelect"));
		//	End();
		//	return FALSE;
		//}

		//GameThreadDestroyEvent_	= CreateEvent(NULL, FALSE, FALSE, NULL);
		//GameThreadHandle_			= (HANDLE)::_beginthreadex(NULL, 0, ::ResetThreadCallback, this, 0, NULL);
		return TRUE;
	}

	BOOL CNetUdpIocp::End(VOID)
	{
		//if(!GameThreadHandle_)
		//	return FALSE;

		//SetEvent(GameThreadDestroyEvent_)

		//WaitForSingleObject(GameThreadHandle_, INFINITE)

		//CloseHandle(GameThreadDestroyEvent_)
		//CloseHandle(GameThreadHandle_)

		CIocp::End();
		UdpSession_.End();
		return TRUE;
	}

	BOOL CNetUdpIocp::SendToPacket(HisUtil::CMsg& msg, ADDR_IP remoteIP, ADDR_PORT remotePort)
	{
		return UdpSession_.SendToPacket(msg, remoteIP, remotePort);
	}

	VOID CNetUdpIocp::OnIoRecv(VOID *object, DWORD dataLength)
	{
		//AUTO_LOCK(csReceive_);

		CPacketSession* PacketSession = (CPacketSession*)object;
		if (NULL == PacketSession)// || FALSE == session->IsConnected())
			return;

		ADDR_IP remoteIP = 0;
		ADDR_PORT remotePort = 0;
		HisUtil::CMsg msgRecv;

		if (PacketSession->RecvFromPacketForIocp(dataLength))
		{
			//LOGEVENT("Session_Base_Info", _T("#	recv udp size(%d)"), dataLength);
			while (PacketSession->GetFromPacket(msgRecv, remoteIP, remotePort))
			{
				LOGEVENT("Session_Base_Info", _T("# Client udp data recv : size(%d)"), dataLength);
				//owner_->OnIoRecvUdpPacket(remoteIP, remotePort, msgRecv);
				(*m_OnIoRecvPacket)(CIocp::GetOwner(), remoteIP, remotePort, msgRecv);
			}
		}
	}

	VOID CNetUdpIocp::OnIoSend(VOID *object, DWORD dataLength)
	{
		CPacketSession *PacketSession = (CPacketSession*)object;
		PacketSession->SendUdpComplete();
		LOGEVENT("Session_Base_Info", _T("# Client udp data send : size(%d)"), dataLength);
	}

};//..namespace NetCore {