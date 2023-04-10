#include "stdafx.h"


namespace NetCore {

	//extern CNetServer* g_server;

	void CNetClient::OnNetC2S_CORE_CONNECT_COMPLETED_NTF(HisUtil::CMsg& msgRecv)
	{
		READ_PACKET_CLIENT(NetC2S_CORE_CONNECT_COMPLETED_NTF);
		//	remote : �������� �Ҵ���� �ڽ��� host id
		//	servertime : ������ ����ð�

		//SetStatus(CLIENT_CONNECTED);

		{//���� ������ �����Ѵ�.
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

		//������ �ڽ��� ��Ͽ�û �Ѵ�.
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
		//	remote : �������� �Ҵ���� �ڽ��� host id
		//	servertime : ������ ����ð�

		if (RESULT_OK != st.result)
		{
			LOGEVENT("Session_Base_Error", _T("Error sign up(0x%04x)"), st.result);
			return;
		}

		////HG[2017.11.01]udp ��� Ȯ�ε� : udp�� ������� �ʽ��ϴ�.
		//return;


		//�̰� �� ��� udp ������ �����ϴ�.
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

	//group�� �����ؼ�
	//���� member������ �����ɴϴ�.
	void CNetClient::OnNetC2S_CORE_JOIN_GROUP_NTF(HisUtil::CMsg& msgRecv)
	{
		READ_PACKET_CLIENT(NetC2S_CORE_JOIN_GROUP_NTF);
		//	group : join�� group�� id
		//	msg : group �ɹ��� ����(�Ʒ� ����)
		//		remote : group �ɹ��� �������� �Ҵ���� �ڽ��� host id
		//		publicIP : group �ɹ��� public ip
		//		publicPort : group �ɹ��� public port
		//		privateIP : group �ɹ��� private ip
		//		privatePort : group �ɹ��� private port


		//stNetC2S_CORE_HOLE_PUNCHING_PEER_READY_REQ stReq;

		//�ο��� ��ŭ loop
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

			//NetC2S_CORE_HOLE_PUNCHING_PEER_READY_NTF���� �����Ѵ�.
			//hole punching �õ�
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

	//��� ������ member�� ������ �����ɴϴ�.
	void CNetClient::OnNetC2S_CORE_ENTER_GROUP_NTF(HisUtil::CMsg& msgRecv)
	{
		READ_PACKET_CLIENT(NetC2S_CORE_ENTER_GROUP_NTF);
		//	group : join�� group�� id
		//	msg : group �ɹ��� ����(�Ʒ� ����)
		//		remote : group �ɹ��� �������� �Ҵ���� �ڽ��� host id
		//		publicIP : group �ɹ��� public ip
		//		publicPort : group �ɹ��� public port
		//		privateIP : group �ɹ��� private ip
		//		privatePort : group �ɹ��� private port

		//stNetC2S_CORE_HOLE_PUNCHING_PEER_READY_REQ stReq;

		//�ο��� ��ŭ loop
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


			//hole punching �õ�
			//HolePunching(peerinfo.remote);
			GetHolpunchingPool().Insert(peer->GetHostID(), peer);

			////NetC2S_CORE_HOLE_PUNCHING_PEER_READY_NTF���� �����Ѵ�.
			////��� ���� �ֵ��� Ȧ��Ī �Ⱥ�����. ���ʿ��� �������� ������...
			////�Ⱥ������ ���� �����..����
			////HolePunching(peerinfo.remote);
			//stRemote remote = peerinfo.remote;
			//stReq.remoteTos.push_back(remote);
		}
		//SEND_NetC2S_CORE_HOLE_PUNCHING_PEER_READY_REQ(Host_Server, RELIABLE, stReq);

	}

	void CNetClient::OnNetC2S_CORE_LEAVE_GROUP_NTF(HisUtil::CMsg& msgRecv)
	{
		READ_PACKET_CLIENT(NetC2S_CORE_LEAVE_GROUP_NTF);
		//	group : join�� group�� id
		//	remote : �������� �Ҵ���� �ڽ��� host id

		if (remoteClient_.GetHostID() == st.remote)
		{
			//�ڽ��� �׷��� ��������, ������ ������ �ش� �׷��� �����Ѵ�.
			//owner_->GetP2PGroup().Clear()
			GetPeerPool().End();
			LOGEVENT("Session_Base_Packet", _T("leave group oneself host id (0x%p)"), remoteClient_.GetHostID());
			return;
		}

		OnLeaveGroup(st.remote);

		//�ڽ��� ���� ���� CH_LEAVE_GROUP_ACK ���� ó���Ѵ�.
		//����� Ÿ���� ���� ��츸 ó���Ѵ�.
		//owner_->GetP2PGroup().LeaveGroup(st.remote)
		GetPeerPool().Erase(st.remote);
		GetHolpunchingPool().Erase(st.remote);	//hole-punching �������� ��쵵 �����.
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