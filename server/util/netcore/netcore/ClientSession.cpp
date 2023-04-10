#include "stdafx.h"
#include "ClientSession.h"

namespace NetCore {

	BOOL CClientSession::BeginTcp(ADDR_IP ip, ADDR_PORT port, int nRecvTcpPoolSize)
	{
		if (!ip || port <= 0)
			return FALSE;


		//if (!mSession.Begin(MSG_TOTAL_SIZE, MAX_CLIENT_RECV_TCP_QUEUE_COUNT))
		if (!mSession.Begin(nRecvTcpPoolSize, 0))
		{
			End();
			return FALSE;
		}

		if (!mSession.TcpBind())
		{
			End();
			return FALSE;
		}

		if (!CEventSelect::Begin(mSession.GetSocket()))
		{
			End();
			return FALSE;
		}

		if (!mSession.Connect(ip, port))
		{
			End();
			return FALSE;
		}

		return TRUE;
	}

	BOOL CClientSession::BeginUdp(ADDR_PORT remotePort, int nRecvUdpPoolCnt, int nSendUdpPoolCnt)
	{
#if defined(_EXTERNAL_RELEASE_)
		if (remotePort <= 0)
			return FALSE;
#endif

		//if (!mSession.Begin(MSG_TOTAL_SIZE, MAX_CLIENT_RECV_UDP_QUEUE_COUNT))
		if (!mSession.Begin(0, nRecvUdpPoolCnt))
		{
			End();
			return FALSE;
		}

		//if (!mSession.UdpBind(remotePort, MAX_SEND_QUEUE_COUNT))
		if (!mSession.UdpBind(remotePort, nSendUdpPoolCnt))
		{
			End();
			return FALSE;
		}

		if (!CEventSelect::Begin(mSession.GetSocket()))
		{
			End();
			return FALSE;
		}

		return TRUE;
	}

	BOOL CClientSession::End(VOID)
	{
		CEventSelect::End();
		LOGEVENT("Session_Base_Info", _T("CEventSelect.End();"));
		mSession.End();
		LOGEVENT("Session_Base_Info", _T("CPacketSession.End();"));
		return TRUE;
	}

	ADDR_IP CClientSession::GetPrivateIP()
	{
		return mSession.GetPrivateIP();
	}
	
	ADDR_PORT CClientSession::GetPrivatePort()
	{
		return mSession.GetPrivatePort();
	}

	BOOL CClientSession::ReadPacket(void* pData)
	{
		int length = 0;
		return TRUE;//poolPacket_.Pop(pData);
	}

	BOOL CClientSession::ReadFromPacket(void* pData, ADDR_IP& remoteIP, ADDR_PORT &remotePort)
	{
		int length = 0;
		return TRUE;//poolPacket_.Pop(pData);
	}

	BOOL CClientSession::SendPacket(HisUtil::CMsg& msg)//, DWORD protocol, const BYTE *packet, int packetLength)
	{
		if (!mSession.SendPacket(msg))//, protocol, packet, packetLength))
			return FALSE;

		//if (!mSession.WriteComplete())
		//	return FALSE;

		return TRUE;
	}

	BOOL CClientSession::SendToPacket(HisUtil::CMsg& msg, ADDR_IP remoteIP, ADDR_PORT remotePort)//, DWORD protocol, const BYTE *packet, DWORD packetLength)
	{
		if (!mSession.SendToPacket(msg, remoteIP, remotePort))//, protocol, packet, packetLength))
			return FALSE;

		//if (!mSession.WriteComplete())
		//	return FALSE;

		return TRUE;
	}

};//..namespace NetCore {