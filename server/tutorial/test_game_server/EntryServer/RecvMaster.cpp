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

void CMasterClient::OnM2_AC_LOGIN_ACK(HisUtil::CMsg& msgRecv)
{
	READ_PACKET(M2_AC_LOGIN_ACK);
	//	remoteFrom : 홀펀칭을 시도하는 host(서버에서 할당받은 자신의 host id)
	//	remoteTo : 서버에서 할당받은 타인의 host id

	//CWorld::GetInstance()->GetGameServer().SendCertifyAck(st);

	//if (RESULT_OK == st.result)
	//{
	//	CAccountData* account = NULL;
	//	CAccountManager::Instance().NewJoin(st.remoteX, st.accountpk, st.account, &account);
	//	//char --> wchar
	//	HisUtil::String accountid(account->GetAccountID().c_str());
	//	LOGEVENT("HG_WHITE", _T("account(%s/%d)"), accountid.w_str(), account->GetAccountPK());
	//}

	//stX2G_AC_LOGIN_ACK stAck;
	//stAck.result = st.result;
	//stAck.accountpk = st.accountpk;
	//CWorld::Instance().GetServer().SEND_X2G_AC_LOGIN_ACK(st.remoteX, NetCore::RELIABLE, stAck);


}

void CMasterClient::OnM2_IN_EQUIP_LOAD_ACK(HisUtil::CMsg& msgRecv)
{
	READ_PACKET(M2_IN_EQUIP_LOAD_ACK);

	//CAccountData* account = CAccountManager::Instance().GetHostIDPool().Find(st.remoteX);
	//if (NULL == account)
	//	return;
	//
	////setting...
	//account->SetInven(st.inven);

	////notify
	//stX2G_IN_EQUIP_LOAD_ACK stAck;
	//stAck.inven = st.inven;
	////stAck.gender = st.gender;
	////stAck.myhair = st.myhair;
	////stAck.myhead = st.myhead;
	////stAck.mycloth = st.mycloth;
	////stAck.myskincolor = st.myskincolor;
	////stAck.myclothcolor = st.myclothcolor;
	////stAck.hashairtype = st.hashairtype;
	////stAck.hasheadtype = st.hasheadtype;
	////stAck.hasclothtype = st.hasclothtype;
	//CWorld::Instance().GetServer().SEND_X2G_IN_EQUIP_LOAD_ACK(st.remoteX, NetCore::RELIABLE, stAck);
}

void CMasterClient::OnM2_IN_EQUIP_UPDATE_ACK(HisUtil::CMsg& msgRecv)
{
	READ_PACKET(M2_IN_EQUIP_UPDATE_ACK);

	//if(RESULT_OK == st.remoteX)
	//{
	//	CAccountData* account = CAccountManager::Instance().GetHostIDPool().Find(st.remoteX);
	//	if (NULL == account)
	//		return;

	//	//setting...
	//	account->SetInven(st.inven);
	//}

	//stX2G_IN_EQUIP_UPDATE_ACK stAck;
	//stAck.result = st.result;
	//CWorld::Instance().GetServer().SEND_X2G_IN_EQUIP_UPDATE_ACK(st.remoteX, NetCore::RELIABLE, stAck);
}

