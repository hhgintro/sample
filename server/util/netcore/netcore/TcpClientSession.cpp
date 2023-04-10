#include "stdafx.h"
#include "TcpClientSession.h"


namespace NetCore {

	VOID CTcpClientSession::OnIoConnected(VOID)
	{
		//connect�� �������� ó���� �κ��� �ֱ⿡
		//������ ���� connect complete�� �޾� ����ó���� �����Ѵ�.
		owner_->OnIoConnected();
	}

	VOID CTcpClientSession::OnIoDisconnected(VOID)
	{
		//CEventSelect::End()
	//	CClientSession::OnIoDisconnected()
		//owner_->SetStatus(CLIENT_DISCONNECTED);
		owner_->OnIoDisconnected();
	}

	VOID CTcpClientSession::OnIoSend(VOID)
	{

	}

	VOID CTcpClientSession::OnIoRecv(VOID)
	{
		//AUTO_LOCK(cs_);

		ADDR_IP remoteIP = 0;
		ADDR_PORT remotePort = 0;
		HisUtil::CMsg msgRecv;
		DWORD ReadBytes = 0;

		if (mSession.RecvPacketForEventSelect(ReadBytes))
		{
			while (mSession.GetPacket(msgRecv))
			{
				LOGEVENT("Session_Base_Info", _T(" # tcp data recv : entry(%d), size(%d)"), owner_->GetRemoteEntry(), ReadBytes);
				owner_->OnIoRecvPacket(remoteIP, remotePort, msgRecv);
			}
		}
	}

};//..namespace NetCore {