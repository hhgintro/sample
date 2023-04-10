#include "stdafx.h"
#include "NetIocp.h"


namespace NetCore {

	CNetIocp::CNetIocp(VOID)
		: m_OnIoConnected(NULL), m_OnIoDisconnected(NULL), m_OnIoRecvPacket(NULL)
	{
	}

	CNetIocp::~CNetIocp(VOID)
	{
		End();
	}

	BOOL CNetIocp::Begin(ADDR_PORT port, void* owner, void* Callback_OnIoConnected, void* Callback_OnIoDisconnected, void* callback_OnIoRecvPacket)
	{
		CIocp::SetOwner(owner);
		m_OnIoConnected = (func_OnIoConnected)Callback_OnIoConnected;
		m_OnIoDisconnected = (func_OnIoDisconnected)Callback_OnIoDisconnected;
		m_OnIoRecvPacket = (func_OnIoRecvTcpPacket)callback_OnIoRecvPacket;

		if (!CIocp::Begin())
		{
			LOGEVENT("Network_Base_Core_Error", _T("fail CIocp::Begin()"));
			End();
			return FALSE;
		}

		if (!mListenSession.Begin())
		{
			LOGEVENT("Network_Base_Core_Error", _T("fail ListenSession.Begin()"));
			End();
			return FALSE;
		}

		if (!mListenSession.TcpBind())
		{
			LOGEVENT("Network_Base_Core_Error", _T("fail ListenSession.TcpBind()"));
			End();
			return FALSE;
		}

		if (!mListenSession.Listen(port))
		{
			LOGEVENT("Network_Base_Core_Error", _T("fail ListenSession.Listen()"));
			End();
			return FALSE;
		}

		if (!CIocp::RegisterSocketToIocp(mListenSession.GetSocket(), (ULONG_PTR)&mListenSession))
		{
			LOGEVENT("Network_Base_Core_Error", _T("fail CIocp::RegisterSocketToIocp()"));
			End();
			return FALSE;
		}

		return TRUE;
	}

	BOOL CNetIocp::End(VOID)
	{
		CIocp::End();
		return TRUE;
	}

	VOID CNetIocp::OnIoConnected(VOID *object)
	{
		// 여기 가상함수에서 넘어온 pObject는 접속을 담당한 개체가 넘어오게 됩니다.
		// 이것을 여기서 클라이언트를 관리할 CRemoteSession으로 형변환을 해 주어 받게 됩니다.
		// 형변환은 reinterpret_cast를 사용합니다.
		CRemoteSession* session = reinterpret_cast<CRemoteSession*>(object);
		if (!session)
			return;


		// IOCP 초기 받기를 실행해 줍니다.
		if (!session->InitializeRecvForIocp())
		{
			// 만일 실패했을 경우 개체를 재시작해 줍니다.
			OnIoDisconnected(session);
			return;
		}

		CRemoteSessionManager::Instance().Connect(session);
		LOGEVENT("Network_Base_Core_Info", _T("# New client connected : HOSTID(0x%p)"), session);


		//CNetServer를 상속받은 class에서 구현되어야 합니다.
		//owner_->OnIoConnected(session);
		if (NULL != m_OnIoConnected) (*m_OnIoConnected)(CIocp::GetOwner(), session);
	}

	VOID CNetIocp::OnIoDisconnected(VOID *object)
	{
		// 여기 가상함수에서 넘어온 pObject는 OnIoConnected와 마찬가지로 접속을 담당한 개체가 넘어오게 됩니다.
		// 이것을 여기서 클라이언트를 관리할 CRemoteSession으로 형변환을 해 주어 받게 됩니다.
		// 형변환은 reinterpret_cast를 사용합니다.
		CRemoteSession* session = reinterpret_cast<CRemoteSession*>(object);
		//if (!session || FALSE == session->IsConnected())
		//	return;
		if (!session)
		{
			LOGEVENT("Network_Base_Core_Error", L"session is NULL");
			return;
		}
		if (FALSE == session->IsConnected())
		{
			LOGEVENT("Network_Base_Core_Info", L"session(0x%p) is not connected", session->GetHostID());
			return;
		}


		//disconnect전에 호출해야 한다.
		//CNetServer를 상속받은 class에서 구현되어야 합니다.
		session->SetConnected(FALSE);//바로 아래 OnIoDisconnected() 앞서 처리되어야 접속종료된 개체에게 packet 안보낸다.
		//owner_->OnIoDisconnected(session);
		if(NULL != m_OnIoDisconnected) (*m_OnIoDisconnected)(CIocp::GetOwner(), session);

		CRemoteSessionManager::Instance().Disconnect(session);
	}

	VOID CNetIocp::OnIoRecv(VOID *object, DWORD dataLength)
	{
		//AUTO_LOCK(csReceive_);

		// 여기 가상함수에서 넘어온 pObject는 OnIoConnected와 마찬가지로 접속을 담당한 개체가 넘어오게 됩니다.
		// 이것을 여기서 클라이언트를 관리할 CRemoteSession으로 형변환을 해 주어 받게 됩니다.
		// 형변환은 reinterpret_cast를 사용합니다.
		CRemoteSession* session = reinterpret_cast<CRemoteSession*>(object);
		if (NULL == session || FALSE == session->IsConnected())
			return;

		LOGEVENT("Network_Base_Core_Info", _T("# Client data recv : HOSTID(0x%p),size(%d)"), session, dataLength);

		HisUtil::CMsg msgRecv;

		// CNetworkSession에서 CPacketSession으로 데이터를 가져옵니다.
		if (session->RecvPacketForIocp(dataLength))
		{
			// CPacketSession에서 패킷을 뽑아 냅니다.
			while (session->GetPacket(msgRecv))//, dwProtocol, Packet, dwPacketLength))
			{
				//owner_->OnIoRecvTcpPacket(session, msgRecv);
				(*m_OnIoRecvPacket)(CIocp::GetOwner(), session, msgRecv);
			}
		}

		// TODO : 강제 종료부
		// End는 꼭 이후에
		// session->End()
	}

	VOID CNetIocp::OnIoSend(VOID *object, DWORD dataLength)
	{
		// 여기 가상함수에서 넘어온 pObject는 OnIoConnected와 마찬가지로 접속을 담당한 개체가 넘어오게 됩니다.
		// 이것을 여기서 클라이언트를 관리할 CRemoteSession으로 형변환을 해 주어 받게 됩니다.
		// 형변환은 reinterpret_cast를 사용합니다.
		CRemoteSession *session = reinterpret_cast<CRemoteSession*>(object);
		if (!session || FALSE == session->IsConnected())
			return;

		session->SendTcpComplete();
		LOGEVENT("Network_Base_Core_Info", _T("# Client data send : HOSTID(0x%p),size(%d)"), session, dataLength);
	}

	ADDR_IP CNetIocp::GetPrivateIP()
	{
		return mListenSession.GetPrivateIP();
	}
	ADDR_PORT CNetIocp::GetPrivatePort()
	{
		return mListenSession.GetPrivatePort();
	}

};//..namespace NetCore {