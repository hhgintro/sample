#include "stdafx.h"
#include "NetClient.h"


namespace NetCore {

	void CNetClient::OnNetC2C_CORE_UDP_HOLE_PUNCHING_PEER_REQ(HisUtil::CMsg& msgRecv, ADDR_IP remoteIP, ADDR_PORT remotePort)
	{
		READ_PACKET_CLIENT(NetC2C_CORE_UDP_HOLE_PUNCHING_PEER_REQ);
		//	remoteFrom : 홀펀칭을 시도하는 host(서버에서 할당받은 자신의 host id)
		//	remoteTo : 서버에서 할당받은 타인의 host id

		CRemotePeer* peer = GetPeerPool().Find(st.remoteFrom);
		if (NULL == peer)// || false == peer->IsConnected())
			return;

		//이걸 해 줘야 udp 전송이 가능하다.
		//if (enSuccess != peer->GetHolePunchingStep())
		//	//peer->SetHolePunchingStep(enAttempt);//받았으니 성공으로 설정한다.
		//	peer->SetHolePunchingStep(enSuccess);//받았으니 성공으로 설정한다.
		switch (st.bpublic)
		{
		case enPrivateAttempt:
		case enPrivateSuccess:
			peer->SetHolePunchingStep(enPrivateSuccess);//받았으니 성공으로 설정한다.
			LOGEVENT("Session_Base_Info", _T("(private success)hole punching from peer(0x%p) to peer(0x%p)"), st.remoteFrom, st.remoteTo);
			break;
		
		default:
			peer->SetHolePunchingStep(enPublicSuccess);//받았으니 성공으로 설정한다.
			LOGEVENT("Session_Base_Info", _T("(public success)hole punching from peer(0x%p) to peer(0x%p)"), st.remoteFrom, st.remoteTo);
			break;
		}

		stNetC2C_CORE_UDP_HOLE_PUNCHING_PEER_ACK stAck;
		stAck.remoteFrom = st.remoteFrom;
		stAck.remoteTo = st.remoteTo;
		stAck.bpublic = peer->GetHolePunchingStep();
		SEND_NetC2C_CORE_UDP_HOLE_PUNCHING_PEER_ACK(st.remoteFrom, stAck);

		//HG_TEST : ACK에서 처리테스트(REQ에서는 처리하지 않음)
		//OnJoinGroup(st.remoteFrom);
		LOGEVENT("Session_Base_Packet", _T("received hole punching attempt from peer(0x%p) to peer(0x%p)"), st.remoteFrom, st.remoteTo);

		OnJoinGroup(st.remoteFrom);
		OnHolepunchingComplete();
	}

	void CNetClient::OnNetC2C_CORE_UDP_HOLE_PUNCHING_PEER_ACK(HisUtil::CMsg& msgRecv, ADDR_IP remoteIP, ADDR_PORT remotePort)
	{
		READ_PACKET_CLIENT(NetC2C_CORE_UDP_HOLE_PUNCHING_PEER_ACK);
		//	remoteFrom : 홀펀칭을 시도하는 host(서버에서 할당받은 자신의 host id)
		//	remoteTo : 서버에서 할당받은 타인의 host id

		if (st.remoteFrom != remoteClient_.GetHostID())
		{
			LOGEVENT("Session_Base_Error", _T("critical error  remoteFrom(0x%p)  hostid(0x%p)"), st.remoteFrom, remoteClient_.GetHostID());
			return;
		}

		//Peer 간의 홀펀칭 결과를 저장한다.
		CRemotePeer* peer = GetPeerPool().Find(st.remoteTo);
		if (NULL == peer)// || false == peer->IsConnected())
			return;

		////이미 성공한 경우
		//if (enSuccess == peer->GetHolePunchingStep())
		//	return;

		//이미 성공한 경우
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
			peer->SetHolePunchingStep(enPrivateSuccess);//받았으니 성공으로 설정한다.
			LOGEVENT("Session_Base_Info", _T("(private success)hole punching from peer(0x%p) to peer(0x%p)"), st.remoteFrom, st.remoteTo);
			break;

		default:
			peer->SetHolePunchingStep(enPublicSuccess);//받았으니 성공으로 설정한다.
			LOGEVENT("Session_Base_Info", _T("(private success)hole punching from peer(0x%p) to peer(0x%p)"), st.remoteFrom, st.remoteTo);
			break;
		}
		peer->SetHolePunchingAttempt(0);
		LOGEVENT("Session_Base_Packet", _T("success hole punching from peer(0x%p) to peer(0x%p)"), st.remoteFrom, st.remoteTo);

		OnJoinGroup(st.remoteTo);
		OnHolepunchingComplete();

		////Peer 간의 홀펀칭 결과를 서버에 통보한다.
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
		//	result : 결과

		//if(st.result)
		//{
		//	LOGEVENT("Session_Base_Error", _T("faile OnNetC2S_CORE_UDP_HOLE_PUNCHING_SERVER_ACK(0x%04x)"), st.result)
		//	return
		//}

		//hole punching 시도 없이 받으면 무시한다.
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


		//server와의 홀펀칭 결과를 저장한다.
		RemoteServer_.SetHolePunchingStep(enPublicSuccess);
		RemoteServer_.SetHolePunchingAttempt(0);
		//SetStatus(CLIENT_HOLE_PUNCHING_SUCCESS);
		LOGEVENT("Session_Base_Packet", _T("success hole punching with server"));
		//HG_TODO : 서버와의 홀펀칭 결과를 저장한다.

		OnIoServerHolePunchingCompleted();
	}

};//..namespace NetCore {