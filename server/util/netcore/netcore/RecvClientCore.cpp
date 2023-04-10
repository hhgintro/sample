#include "stdafx.h"


namespace NetCore {

	//extern CNetServer* g_server;

	void CNetClient::OnNetC2S_CORE_CONNECT_COMPLETED_NTF(HisUtil::CMsg& msgRecv)
	{
		READ_PACKET_CLIENT(NetC2S_CORE_CONNECT_COMPLETED_NTF);
		//	remote : 서버에서 할당받은 자신의 host id
		//	servertime : 서버의 현재시간

		//SetStatus(CLIENT_CONNECTED);

		{//서버 정보를 설정한다.
			//create
			//CRemotePeer* peer = GetPeerPool().Create()

			RemoteServer_.SetHostID(Host_Server);
			//RemoteServer_.SetRemotePublicIP(GetServerIP());
			//RemoteServer_.SetRemotePublicTcpPort(GetServerTcpPort());
			//RemoteServer_.SetRemotePublicUdpPort(GetServerUdpPort());
			////RemoteServer_.SetRemotePrivateIP(GetServerIP());
			////RemoteServer_.SetRemotePrivatePort(GetServerUdpPort());

			//insert
			//GetPeerPool().Insert(peer->GetHostID(), peer);
		}

		remoteClient_.SetHostID(st.remote);
		remoteClient_.SetRemoteEntry(GetRemoteEntry());
		LOGEVENT("Session_Base_Packet", _T("regist host id (0x%p)"), st.remote);

		//서버에 자신을 등록요청 한다.
		stNetC2S_CORE_SIGN_UP_REQ stReq;
		stReq.version		= NetC2S_PT_VERSION;
		stReq.entry			= GetRemoteEntry();
		//stReq.serverTcpPort = GetServerTcpPort();
		//SEND_NetC2S_CORE_SIGN_UP_REQ(GetTcpSession(), Host_Server, RELIABLE, stReq);
		SEND_NetC2S_CORE_SIGN_UP_REQ(Host_Server, stReq);
	}

	void CNetClient::OnNetC2S_CORE_SIGN_UP_ACK(HisUtil::CMsg& msgRecv)
	{
		READ_PACKET_CLIENT(NetC2S_CORE_SIGN_UP_ACK);
		//	remote : 서버에서 할당받은 자신의 host id
		//	servertime : 서버의 현재시간

		if (RESULT_OK != st.result)
		{
			LOGEVENT("Session_Base_Error", _T("Error sign up(0x%04x)"), st.result);
			return;
		}

		////HG[2017.11.01]udp 장애 확인됨 : udp를 사용하지 않습니다.
		//return;


		//이걸 해 줘야 udp 전송이 가능하다.
		RemoteServer_.SetHolePunchingStep(enPublicAttempt);
		LOGEVENT("Session_Base_Info", _T("(public attempt)hole punching from peer(0x%p) to server"), remoteClient_.GetHostID());
		//printf("****_NetC2S_CORE_SIGN_UP_ACK\n");
		RemoteServer_.SetRemotePublicUdpPort(st.udpport);


		stNetC2S_CORE_UDP_HOLE_PUNCHING_SERVER_REQ stReq;
		stReq.remote			= remoteClient_.GetHostID();
		stReq.privateIP			= ClientUdpSession_.GetPrivateIP();
		stReq.privatePort		= ClientUdpSession_.GetPrivatePort();
		//if (NULL != g_server) {
		//	stReq.serverTcpPort = g_server->GetTcpPort();
		//	stReq.serverUdpPort = g_server->GetUdpPort();
		//}
		////SEND_NetC2S_CORE_UDP_HOLE_PUNCHING_SERVER_REQ(GetUdpSession(), Host_Server, UNRELIABLE, stReq);
		SEND_NetC2S_CORE_UDP_HOLE_PUNCHING_SERVER_REQ(Host_Server, stReq);
	}

	//group에 입장해서
	//기존 member정보를 가져옵니다.
	void CNetClient::OnNetC2S_CORE_JOIN_GROUP_NTF(HisUtil::CMsg& msgRecv)
	{
		READ_PACKET_CLIENT(NetC2S_CORE_JOIN_GROUP_NTF);
		//	group : join한 group의 id
		//	msg : group 맴버의 정보(아래 참조)
		//		remote : group 맴버의 서버에서 할당받은 자신의 host id
		//		publicIP : group 맴버의 public ip
		//		publicPort : group 맴버의 public port
		//		privateIP : group 맴버의 private ip
		//		privatePort : group 맴버의 private port


		//stNetC2S_CORE_HOLE_PUNCHING_PEER_READY_REQ stReq;

		//인원수 만큼 loop
		//printf("****_NetC2S_CORE_JOIN_GROUP_NTF\n");
		std::vector<stRemoteEndpoint>::iterator iter = st.peerinfo.begin();
		for (; iter != st.peerinfo.end(); ++iter)
		{
			stRemoteEndpoint& peerinfo = *iter;

			//create
			CRemotePeer* peer = GetPeerPool().Create();
			peer->Clear();

			peer->SetHostID(peerinfo.remote);
			peer->SetRemoteEntry(peerinfo.entry);
			peer->SetRemotePublicIP(peerinfo.publicIP);
			peer->SetRemotePublicTcpPort(peerinfo.portTcp);
			peer->SetRemotePublicUdpPort(peerinfo.portUdp);
			peer->SetRemotePrivateIP(peerinfo.privateIP);
			peer->SetRemotePrivateUdpPort(peerinfo.privatePort);
			//peer->SetRemoteServerInfo(peerinfo.serverinfo);

			//insert
			GetPeerPool().Insert(peer->GetHostID(), peer);
			LOGEVENT("Session_Base_Packet", _T("join group host id (0x%p)"), peer->GetHostID());

			//NetC2S_CORE_HOLE_PUNCHING_PEER_READY_NTF에서 진행한다.
			//hole punching 시도
			//HolePunching(peerinfo.remote);
			GetHolpunchingPool().Insert(peer->GetHostID(), peer);

			////stRemote remote = peerinfo.remote;
			////stReq.remoteTos.push_back(remote);
			//stNetC2C_CORE_UDP_HOLE_PUNCHING_PEER_REQ stReq;
			//stReq.remoteFrom = remoteClient_.GetHostID();
			//stReq.remoteTo = peer->GetHostID();
			//SEND_NetC2C_CORE_UDP_HOLE_PUNCHING_PEER_REQ(peer->GetHostID(), RELIABLE, stReq);
		}
		//SEND_NetC2S_CORE_HOLE_PUNCHING_PEER_READY_REQ(Host_Server, RELIABLE, stReq);

	}

	//방금 입장한 member의 정보를 가져옵니다.
	void CNetClient::OnNetC2S_CORE_ENTER_GROUP_NTF(HisUtil::CMsg& msgRecv)
	{
		READ_PACKET_CLIENT(NetC2S_CORE_ENTER_GROUP_NTF);
		//	group : join한 group의 id
		//	msg : group 맴버의 정보(아래 참조)
		//		remote : group 맴버의 서버에서 할당받은 자신의 host id
		//		publicIP : group 맴버의 public ip
		//		publicPort : group 맴버의 public port
		//		privateIP : group 맴버의 private ip
		//		privatePort : group 맴버의 private port

		//stNetC2S_CORE_HOLE_PUNCHING_PEER_READY_REQ stReq;

		//인원수 만큼 loop
		//printf("****_NetC2S_CORE_ENTER_GROUP_NTF\n");
		std::vector<stRemoteEndpoint>::iterator iter = st.peerinfo.begin();
		for (; iter != st.peerinfo.end(); ++iter)
		{
			stRemoteEndpoint& peerinfo = *iter;

			//create
			CRemotePeer* peer = GetPeerPool().Create();
			peer->Clear();

			peer->SetHostID(peerinfo.remote);
			peer->SetRemoteEntry(peerinfo.entry);
			peer->SetRemotePublicIP(peerinfo.publicIP);
			peer->SetRemotePublicTcpPort(peerinfo.portTcp);
			peer->SetRemotePublicUdpPort(peerinfo.portUdp);
			peer->SetRemotePrivateIP(peerinfo.privateIP);
			peer->SetRemotePrivateUdpPort(peerinfo.privatePort);
			//peer->SetRemoteServerInfo(peerinfo.serverinfo);

			//insert
			GetPeerPool().Insert(peer->GetHostID(), peer);
			LOGEVENT("Session_Base_Packet", _T("enter group host id (0x%p)"), peer->GetHostID());


			//hole punching 시도
			//HolePunching(peerinfo.remote);
			GetHolpunchingPool().Insert(peer->GetHostID(), peer);

			////NetC2S_CORE_HOLE_PUNCHING_PEER_READY_NTF에서 진행한다.
			////방금 들어온 애들은 홀펑칭 안보낸다. 그쪽에서 보내오기 때문에...
			////안보내기깐 문제 생기네..ㅋㅋ
			////HolePunching(peerinfo.remote);
			//stRemote remote = peerinfo.remote;
			//stReq.remoteTos.push_back(remote);
		}
		//SEND_NetC2S_CORE_HOLE_PUNCHING_PEER_READY_REQ(Host_Server, RELIABLE, stReq);

	}

	void CNetClient::OnNetC2S_CORE_LEAVE_GROUP_NTF(HisUtil::CMsg& msgRecv)
	{
		READ_PACKET_CLIENT(NetC2S_CORE_LEAVE_GROUP_NTF);
		//	group : join한 group의 id
		//	remote : 서버에서 할당받은 자신의 host id

		if (remoteClient_.GetHostID() == st.remote)
		{
			//자신이 그룹을 떠났으니, 서버를 제외한 해당 그룹을 삭제한다.
			//owner_->GetP2PGroup().Clear()
			GetPeerPool().End();
			LOGEVENT("Session_Base_Packet", _T("leave group oneself host id (0x%p)"), remoteClient_.GetHostID());
			return;
		}

		OnLeaveGroup(st.remote);

		//자신이 떠난 경우는 CH_LEAVE_GROUP_ACK 에서 처리한다.
		//여기는 타인이 빠진 경우만 처리한다.
		//owner_->GetP2PGroup().LeaveGroup(st.remote)
		GetPeerPool().Erase(st.remote);
		GetHolpunchingPool().Erase(st.remote);	//hole-punching 진행중인 경우도 멈춤다.
		LOGEVENT("Session_Base_Packet", _T("leave group host id (0x%p)"), st.remote);
	}


	void CNetClient::OnNetC2S_CORE_HOLE_PUNCHING_PEER_READY_NTF(HisUtil::CMsg& msgRecv)
	{
		READ_PACKET_CLIENT(NetC2S_CORE_HOLE_PUNCHING_PEER_READY_NTF);

		CRemotePeer* peer = GetPeerPool().Find(st.remoteFrom);
		if (NULL == peer)
		{
			LOGEVENT("Session_Base_Packet", _T("not found peer(0x%p)"), st.remoteFrom);
			return;
		}

		//HolePunching(peer);
		GetHolpunchingPool().Insert(peer->GetHostID(), peer);
	}

};//..namespace NetCore {