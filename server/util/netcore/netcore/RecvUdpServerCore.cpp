#include "stdafx.h"
#include "NetServer.h"

namespace NetCore {

	void CNetServer::OnNetC2S_CORE_UDP_HOLE_PUNCHING_SERVER_REQ(HisUtil::CMsg& msgRecv, ADDR_IP remoteIP, ADDR_PORT remotePort)
	{
		READ_PACKET_CLIENT(NetC2S_CORE_UDP_HOLE_PUNCHING_SERVER_REQ);
		//	remote : �������� �Ҵ���� �ڽ��� host id
		//	privateIP : client���� Ȯ���� �ڽ��� ip
		//	privatePort : client���� Ȯ���� �ڽ��� port

		CRemoteSession* session = (CRemoteSession*)FindRemote(st.remote);
		if (FALSE == CheckSessionStatus(session, eChk_Session))
			return;

		//public
		//printf("****_NetC2S_CORE_UDP_HOLE_PUNCHING_SERVER_REQ\n");
		session->SetRemotePublicIP(remoteIP);
		session->SetRemotePublicUdpPort(remotePort);
		//LOGEVENT("HG_CYAN", L"UDP : %d", remotePort);
		//private
		session->SetRemotePrivateIP(st.privateIP);
		session->SetRemotePrivateUdpPort(st.privatePort);
		LOGEVENT("HG_CYAN", L"private UDP : 0x%p/%d", st.privateIP, st.privatePort);

		session->SetHolePunchingStep(enPublicSuccess);

		//������ �������� �ʴ´�.
		//session->SetHolePunchingStep(enSuccess);
		CRemoteSessionManager::Instance().RegisterAddressIPToSession(remoteIP, remotePort, session);

		//ack
		stNetC2S_CORE_UDP_HOLE_PUNCHING_SERVER_ACK stAck;
		SEND_NetC2S_CORE_UDP_HOLE_PUNCHING_SERVER_ACK(session->GetHostID(), stAck);


		OnHolePunchingServer(session);
	}


	void CNetServer::OnCORE_UDP_RELAY_SERVER_TO_PEER_NTF(CRemoteSession* session, HisUtil::CMsg& msgRecv)
	{
		READ_PACKET_SERVER(CORE_UDP_RELAY_SERVER_TO_PEER_NTF);
		//	remoteTo : �������� �Ҵ���� Ÿ���� host id
		//	data : ���޹޾ƾ� �ϴ� ����Ÿ



		CRemoteSession* remote = (CRemoteSession*)FindRemote(st.remoteTo);
		if (NULL == remote || FALSE == remote->IsConnected())
		{
			LOGEVENT("Session_Base_Error", _T("Error ������ ����� ��ü�Դϴ�. : 0x%p"), st.remoteTo);
			return;
		}

		////HG_TODO : ���⿡ ���������� ����Ÿ�� �������� üũ�ϰ�
		////�޴� Ŭ���̾�Ʈ�� ����Ÿ�� �����Ѵ�.
		//st.data.ID(st.protocol)
		//CCrypt::Encrypt((UCHAR*)st.data.GetBuf() + MSG_HEADER_SIZE, (UCHAR*)st.data.GetBuf() + MSG_HEADER_SIZE, st.data.GetSize() - MSG_HEADER_SIZE)
		NetUdpIocp_.SendToPacket(st.msg, remote->GetRemotePublicIP(), remote->GetRemotePublicUdpPort());
		st.msg.Clear();

	}

#if __HEART_BEAT__
	void CNetServer::OnNetC2S_CORE_HEART_BEAT_ACK(CRemoteSession* session, HisUtil::CMsg& msgRecv)
	{
		READ_PACKET_SERVER(NetC2S_CORE_HEART_BEAT_ACK);
		if (FALSE == CheckSessionStatus(session, eChk_Session))
			return;

		//heart beat ����
		session->SetHeartBeat(st.servertime);
		LOGEVENT("Heart_Beart_Packet", _T("restore peer(0x%p) heart beat(%I64d ms)")
			, session->GetHostID(), session->GetHeartBeat());
	}
#endif //..__HEART_BEAT__

	void CNetServer::OnNetC2S_CORE_HOLE_PUNCHING_PEER_READY_REQ(CRemoteSession* session, HisUtil::CMsg& msgRecv)
	{
		READ_PACKET_SERVER(NetC2S_CORE_HOLE_PUNCHING_PEER_READY_REQ);
		if (FALSE == CheckSessionStatus(session, eChk_Session))
			return;

		//���� ���
		for (int i = 0; i < (int)st.remoteTos.size(); ++i)
		{
			CRemoteSession* remote = (CRemoteSession*)FindRemote(st.remoteTos[i].remote_);
			if (NULL == remote || FALSE == remote->IsConnected())
			{
				LOGEVENT("Session_Base_Error", _T("Error ������ ����� ��ü�Դϴ�. : 0x%p"), st.remoteTos[i].remote_);
				continue;
			}

			////��� ������...
			//CP2PGroup* group = P2PGroupPool_.Find(st.group);
			//if (NULL == group)
			//{
			//	LOGEVENT("Session_Base_Error", _T("failed hole-punching-peer not exist Group id (0x%p)"), st.group);
			//	return;
			//}

			//������ ����� �����ؼ� ������.
			stNetC2S_CORE_HOLE_PUNCHING_PEER_READY_NTF stNtf;
			stNtf.remoteFrom = session->GetHostID();
			SEND_NetC2S_CORE_HOLE_PUNCHING_PEER_READY_NTF(remote->GetHostID(), stNtf);
		}
	}

	////not using
	//void CNetServer::OnNetC2S_CORE_HOLE_PUNCHING_PEER_RESULT_NTF(CRemoteSession* session, HisUtil::CMsg& msgRecv)
	//{
	//	READ_PACKET_SERVER(NetC2S_CORE_HOLE_PUNCHING_PEER_RESULT_NTF);
	//	if (FALSE == CheckSessionStatus(session, eChk_Session))
	//		return;

	//	//HG_TODO : session �� remoteTo�� Ȧ��Ī�� �����ߴٴ� ���� ��� �����Ѵ�.???
	//	if (RESULT_OK != st.result)
	//	{
	//		LOGEVENT("Session_Base_Error", _T("failed(%d) of hole punching between peer(0x%p) with peer(0x%p)")
	//			, st.result, st.remoteFrom, st.remoteTo);
	//		return;
	//	}

	//	LOGEVENT("Session_Base_Packet", _T("success of hole punching between peer(0x%p) with peer(0x%p)")
	//		, st.remoteFrom, st.remoteTo);
	//}

};//..namespace NetCore {