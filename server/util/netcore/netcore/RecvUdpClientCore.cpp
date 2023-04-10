#include "stdafx.h"
#include "NetClient.h"


namespace NetCore {

	void CNetClient::OnNetC2C_CORE_UDP_HOLE_PUNCHING_PEER_REQ(HisUtil::CMsg& msgRecv, ADDR_IP remoteIP, ADDR_PORT remotePort)
	{
		READ_PACKET_CLIENT(NetC2C_CORE_UDP_HOLE_PUNCHING_PEER_REQ);
		//	remoteFrom : Ȧ��Ī�� �õ��ϴ� host(�������� �Ҵ���� �ڽ��� host id)
		//	remoteTo : �������� �Ҵ���� Ÿ���� host id

		CRemotePeer* peer = GetPeerPool().Find(st.remoteFrom);
		if (NULL == peer)// || false == peer->IsConnected())
			return;

		//�̰� �� ��� udp ������ �����ϴ�.
		//if (enSuccess != peer->GetHolePunchingStep())
		//	//peer->SetHolePunchingStep(enAttempt);//�޾����� �������� �����Ѵ�.
		//	peer->SetHolePunchingStep(enSuccess);//�޾����� �������� �����Ѵ�.
		switch (st.bpublic)
		{
		case enPrivateAttempt:
		case enPrivateSuccess:
			peer->SetHolePunchingStep(enPrivateSuccess);//�޾����� �������� �����Ѵ�.
			LOGEVENT("Session_Base_Info", _T("(private success)hole punching from peer(0x%p) to peer(0x%p)"), st.remoteFrom, st.remoteTo);
			break;
		
		default:
			peer->SetHolePunchingStep(enPublicSuccess);//�޾����� �������� �����Ѵ�.
			LOGEVENT("Session_Base_Info", _T("(public success)hole punching from peer(0x%p) to peer(0x%p)"), st.remoteFrom, st.remoteTo);
			break;
		}

		stNetC2C_CORE_UDP_HOLE_PUNCHING_PEER_ACK stAck;
		stAck.remoteFrom = st.remoteFrom;
		stAck.remoteTo = st.remoteTo;
		stAck.bpublic = peer->GetHolePunchingStep();
		SEND_NetC2C_CORE_UDP_HOLE_PUNCHING_PEER_ACK(st.remoteFrom, stAck);

		//HG_TEST : ACK���� ó���׽�Ʈ(REQ������ ó������ ����)
		//OnJoinGroup(st.remoteFrom);
		LOGEVENT("Session_Base_Packet", _T("received hole punching attempt from peer(0x%p) to peer(0x%p)"), st.remoteFrom, st.remoteTo);

		OnJoinGroup(st.remoteFrom);
		OnHolepunchingComplete();
	}

	void CNetClient::OnNetC2C_CORE_UDP_HOLE_PUNCHING_PEER_ACK(HisUtil::CMsg& msgRecv, ADDR_IP remoteIP, ADDR_PORT remotePort)
	{
		READ_PACKET_CLIENT(NetC2C_CORE_UDP_HOLE_PUNCHING_PEER_ACK);
		//	remoteFrom : Ȧ��Ī�� �õ��ϴ� host(�������� �Ҵ���� �ڽ��� host id)
		//	remoteTo : �������� �Ҵ���� Ÿ���� host id

		if (st.remoteFrom != remoteClient_.GetHostID())
		{
			LOGEVENT("Session_Base_Error", _T("critical error  remoteFrom(0x%p)  hostid(0x%p)"), st.remoteFrom, remoteClient_.GetHostID());
			return;
		}

		//Peer ���� Ȧ��Ī ����� �����Ѵ�.
		CRemotePeer* peer = GetPeerPool().Find(st.remoteTo);
		if (NULL == peer)// || false == peer->IsConnected())
			return;

		////�̹� ������ ���
		//if (enSuccess == peer->GetHolePunchingStep())
		//	return;

		//�̹� ������ ���
		switch (peer->GetHolePunchingStep())
		{
		case enPrivateSuccess:
		case enPublicSuccess:
			return;
		}

		//setting...
		switch (st.bpublic)
		{
		case enPrivateAttempt:
		case enPrivateSuccess:
			peer->SetHolePunchingStep(enPrivateSuccess);//�޾����� �������� �����Ѵ�.
			LOGEVENT("Session_Base_Info", _T("(private success)hole punching from peer(0x%p) to peer(0x%p)"), st.remoteFrom, st.remoteTo);
			break;

		default:
			peer->SetHolePunchingStep(enPublicSuccess);//�޾����� �������� �����Ѵ�.
			LOGEVENT("Session_Base_Info", _T("(private success)hole punching from peer(0x%p) to peer(0x%p)"), st.remoteFrom, st.remoteTo);
			break;
		}
		peer->SetHolePunchingAttempt(0);
		LOGEVENT("Session_Base_Packet", _T("success hole punching from peer(0x%p) to peer(0x%p)"), st.remoteFrom, st.remoteTo);

		OnJoinGroup(st.remoteTo);
		OnHolepunchingComplete();

		////Peer ���� Ȧ��Ī ����� ������ �뺸�Ѵ�.
		//stNetC2S_CORE_HOLE_PUNCHING_PEER_RESULT_NTF stNtf;
		//stNtf.remoteFrom = remoteClient_.GetHostID();
		//stNtf.remoteTo = st.remoteTo;
		//SEND_NetC2S_CORE_HOLE_PUNCHING_PEER_RESULT_NTF(Host_Server, RELIABLE, stNtf);
	}

	void CNetClient::OnNetC2S_CORE_HEART_BEAT_REQ(HisUtil::CMsg& msgRecv)
	{
		READ_PACKET_CLIENT(NetC2S_CORE_HEART_BEAT_REQ);

		stNetC2S_CORE_HEART_BEAT_ACK stAck;
		stAck.servertime = st.servertime;
		SEND_NetC2S_CORE_HEART_BEAT_ACK(Host_Server, stAck);
	}

	void CNetClient::OnNetC2S_CORE_UDP_HOLE_PUNCHING_SERVER_ACK(HisUtil::CMsg& msgRecv)
	{
		READ_PACKET_CLIENT(NetC2S_CORE_UDP_HOLE_PUNCHING_SERVER_ACK);
		//	result : ���

		//if(st.result)
		//{
		//	LOGEVENT("Session_Base_Error", _T("faile OnNetC2S_CORE_UDP_HOLE_PUNCHING_SERVER_ACK(0x%04x)"), st.result)
		//	return
		//}

		//hole punching �õ� ���� ������ �����Ѵ�.
		//if (enPublicAttempt != RemoteServer_.GetHolePunchingStep())
		//	return;
		switch (RemoteServer_.GetHolePunchingStep())
		{
		case enPublicAttempt:
		case enPrivateAttempt:
			break;
		default:
			return;
		}


		//server���� Ȧ��Ī ����� �����Ѵ�.
		RemoteServer_.SetHolePunchingStep(enPublicSuccess);
		RemoteServer_.SetHolePunchingAttempt(0);
		//SetStatus(CLIENT_HOLE_PUNCHING_SUCCESS);
		LOGEVENT("Session_Base_Packet", _T("success hole punching with server"));
		//HG_TODO : �������� Ȧ��Ī ����� �����Ѵ�.

		OnIoServerHolePunchingCompleted();
	}

};//..namespace NetCore {