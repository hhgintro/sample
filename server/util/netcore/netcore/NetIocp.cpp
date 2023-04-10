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
		// ���� �����Լ����� �Ѿ�� pObject�� ������ ����� ��ü�� �Ѿ���� �˴ϴ�.
		// �̰��� ���⼭ Ŭ���̾�Ʈ�� ������ CRemoteSession���� ����ȯ�� �� �־� �ް� �˴ϴ�.
		// ����ȯ�� reinterpret_cast�� ����մϴ�.
		CRemoteSession* session = reinterpret_cast<CRemoteSession*>(object);
		if (!session)
			return;


		// IOCP �ʱ� �ޱ⸦ ������ �ݴϴ�.
		if (!session->InitializeRecvForIocp())
		{
			// ���� �������� ��� ��ü�� ������� �ݴϴ�.
			OnIoDisconnected(session);
			return;
		}

		CRemoteSessionManager::Instance().Connect(session);
		LOGEVENT("Network_Base_Core_Info", _T("# New client connected : HOSTID(0x%p)"), session);


		//CNetServer�� ��ӹ��� class���� �����Ǿ�� �մϴ�.
		//owner_->OnIoConnected(session);
		if (NULL != m_OnIoConnected) (*m_OnIoConnected)(CIocp::GetOwner(), session);
	}

	VOID CNetIocp::OnIoDisconnected(VOID *object)
	{
		// ���� �����Լ����� �Ѿ�� pObject�� OnIoConnected�� ���������� ������ ����� ��ü�� �Ѿ���� �˴ϴ�.
		// �̰��� ���⼭ Ŭ���̾�Ʈ�� ������ CRemoteSession���� ����ȯ�� �� �־� �ް� �˴ϴ�.
		// ����ȯ�� reinterpret_cast�� ����մϴ�.
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


		//disconnect���� ȣ���ؾ� �Ѵ�.
		//CNetServer�� ��ӹ��� class���� �����Ǿ�� �մϴ�.
		session->SetConnected(FALSE);//�ٷ� �Ʒ� OnIoDisconnected() �ռ� ó���Ǿ�� ��������� ��ü���� packet �Ⱥ�����.
		//owner_->OnIoDisconnected(session);
		if(NULL != m_OnIoDisconnected) (*m_OnIoDisconnected)(CIocp::GetOwner(), session);

		CRemoteSessionManager::Instance().Disconnect(session);
	}

	VOID CNetIocp::OnIoRecv(VOID *object, DWORD dataLength)
	{
		//AUTO_LOCK(csReceive_);

		// ���� �����Լ����� �Ѿ�� pObject�� OnIoConnected�� ���������� ������ ����� ��ü�� �Ѿ���� �˴ϴ�.
		// �̰��� ���⼭ Ŭ���̾�Ʈ�� ������ CRemoteSession���� ����ȯ�� �� �־� �ް� �˴ϴ�.
		// ����ȯ�� reinterpret_cast�� ����մϴ�.
		CRemoteSession* session = reinterpret_cast<CRemoteSession*>(object);
		if (NULL == session || FALSE == session->IsConnected())
			return;

		LOGEVENT("Network_Base_Core_Info", _T("# Client data recv : HOSTID(0x%p),size(%d)"), session, dataLength);

		HisUtil::CMsg msgRecv;

		// CNetworkSession���� CPacketSession���� �����͸� �����ɴϴ�.
		if (session->RecvPacketForIocp(dataLength))
		{
			// CPacketSession���� ��Ŷ�� �̾� ���ϴ�.
			while (session->GetPacket(msgRecv))//, dwProtocol, Packet, dwPacketLength))
			{
				//owner_->OnIoRecvTcpPacket(session, msgRecv);
				(*m_OnIoRecvPacket)(CIocp::GetOwner(), session, msgRecv);
			}
		}

		// TODO : ���� �����
		// End�� �� ���Ŀ�
		// session->End()
	}

	VOID CNetIocp::OnIoSend(VOID *object, DWORD dataLength)
	{
		// ���� �����Լ����� �Ѿ�� pObject�� OnIoConnected�� ���������� ������ ����� ��ü�� �Ѿ���� �˴ϴ�.
		// �̰��� ���⼭ Ŭ���̾�Ʈ�� ������ CRemoteSession���� ����ȯ�� �� �־� �ް� �˴ϴ�.
		// ����ȯ�� reinterpret_cast�� ����մϴ�.
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