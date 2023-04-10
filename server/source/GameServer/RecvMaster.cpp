#include "StdAfx.h"


//
//void CMasterClient::OnX2L_CH_UDP_HELLO_PEER_REQ(CMsg& msgRecv)
//{
//	READ_PACKET(X2L_CH_UDP_HELLO_PEER_REQ);
//	//	remoteFrom : 홀펀칭을 시도하는 host(서버에서 할당받은 자신의 host id)
//	//	remoteTo : 서버에서 할당받은 타인의 host id
//
//	stX2L_CH_UDP_FINE_THANKS_PEER_ACK stAck;
//	stAck.remoteFrom = remoteClient_.GetHostID();
//	stAck.remoteTo = st.remoteFrom;
//	SEND_X2L_CH_UDP_FINE_THANKS_PEER_ACK(stAck.remoteTo, RELIABLE, stAck);
//
//	LOGEVENT("HG_CYAN", _T("received hello from peer(0x%08x) to peer(0x%08x)"), st.remoteFrom, st.remoteTo);
//}
//
//void CMasterClient::OnX2L_CH_UDP_FINE_THANKS_PEER_ACK(CMsg& msgRecv)
//{
//	READ_PACKET(X2L_CH_UDP_FINE_THANKS_PEER_ACK);
//	//	remoteFrom : 홀펀칭을 시도하는 host(서버에서 할당받은 자신의 host id)
//	//	remoteTo : 서버에서 할당받은 타인의 host id
//
//	//stX2L_CH_UDP_FINE_THANKS_PEER_ACK stAck;
//	//stAck.remoteFrom = st.remoteFrom;
//	//stAck.remoteTo = st.remoteTo;
//	//SEND_CORE_UDP_PACKET(CH_UDP_FINE_THANKS_PEER_ACK, stAck, this);
//
//	LOGEVENT("HG_CYAN", _T("received fine thanks from peer(0x%08x) to peer(0x%08x)"), st.remoteFrom, st.remoteTo);
//}

//void CMasterClient::OnM2_AC_CERTIFY_ACK(HisUtil::CMsg& msgRecv)
//{
//	READ_PACKET(M2_AC_CERTIFY_ACK);
//	//	remoteFrom : 홀펀칭을 시도하는 host(서버에서 할당받은 자신의 host id)
//	//	remoteTo : 서버에서 할당받은 타인의 host id
//
//	CWorld::GetInstance()->GetGameServer().SendCertifyAck(st);
//}
