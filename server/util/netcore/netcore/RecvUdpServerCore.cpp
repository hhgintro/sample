#include "stdafx.h"
#include "NetServer.h"

namespace NetCore {

	void CNetServer::OnNetC2S_CORE_UDP_HOLE_PUNCHING_SERVER_REQ(HisUtil::CMsg& msgRecv, ADDR_IP remoteIP, ADDR_PORT remotePort)
	{
		READ_PACKET_CLIENT(NetC2S_CORE_UDP_HOLE_PUNCHING_SERVER_REQ);
		//	remote : 서버에서 할당받은 자신의 host id
		//	privateIP : client에서 확인한 자신의 ip
		//	privatePort : client에서 확인한 자신의 port

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

		//서버는 설정하지 않는다.
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
		//	remoteTo : 서버에서 할당받은 타인의 host id
		//	data : 전달받아야 하는 데이타



		CRemoteSession* remote = (CRemoteSession*)FindRemote(st.remoteTo);
		if (NULL == remote || FALSE == remote->IsConnected())
		{
			LOGEVENT("Session_Base_Error", _T("Error 접속이 종료된 개체입니다. : 0x%p"), st.remoteTo);
			return;
		}

		////HG_TODO : 여기에 정상적으로 데이타가 들어오는지 체크하고
		////받는 클라이언트로 데이타를 전달한다.
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

		//heart beat 갱신
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

		//받을 대상
		for (int i = 0; i < (int)st.remoteTos.size(); ++i)
		{
			CRemoteSession* remote = (CRemoteSession*)FindRemote(st.remoteTos[i].remote_);
			if (NULL == remote || FALSE == remote->IsConnected())
			{
				LOGEVENT("Session_Base_Error", _T("Error 접속이 종료된 개체입니다. : 0x%p"), st.remoteTos[i].remote_);
				continue;
			}

			////모두 받으면...
			//CP2PGroup* group = P2PGroupPool_.Find(st.group);
			//if (NULL == group)
			//{
			//	LOGEVENT("Session_Base_Error", _T("failed hole-punching-peer not exist Group id (0x%p)"), st.group);
			//	return;
			//}

			//보내는 사람을 세팅해서 보낸다.
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

	//	//HG_TODO : session 가 remoteTo와 홀펀칭에 성공했다는 것을 어떻게 관리한다.???
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