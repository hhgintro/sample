#include "StdAfx.h"



void CBalanceClient::OnX2B_AC_LOGIN_ACK(CMsg& msgRecv)
{
	READ_PACKET(X2B_AC_LOGIN_ACK);

	if(st.result)
	{
		LOGEVENT("HG_RED", _T("fail OnX2B_AC_LOGIN_ACK(0x%04x)"), st.result);
		return;
	}
	if(st.result_noti)
	{
		LOGEVENT("HG_CYAN", _T("notify OnX2B_AC_LOGIN_ACK(0x%04x)"), st.result_noti);
		//return;
	}

	if(st.game.size() <= 0)
	{
		LOGEVENT("HG_RED", _T("fail 접속 가능한 game 서버가 없습니다.") );
		return;
	}

	if(FALSE == GetOwner()->GetGameClient().BeginClient(st.game[0].ip_, st.game[0].portTcp_, st.game[0].portUdp_, MAX_CLIENT_RECV_TCP_POOL_SIZE, MAX_CLIENT_RECV_UDP_POOL_COUNT, MAX_CLIENT_SEND_UDP_POOL_COUNT))
	//if(FALSE == GetOwner()->GetGameClient().BeginClient(HisUtil::IP_aTon("175.197.48.218"), st.game[0].portTcp_, st.game[0].portUdp_))
	{
		LOGEVENT("HG_RED", _T("fail Game 서버 접속에 실패하였습니다.") );
		return;
	}

	GetOwner()->GetGameClient().SetMasterKey(st.masterkey);
	LOGEVENT("HG_WHITE", _T("Game 서버에 접속 시도합니다.") );

	//GetTcpSession()->End();
	//LOGEVENT("HG_GRAY", _T("Balance 서버 접속을 종료합니다.") );
}
