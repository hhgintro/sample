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
		LOGEVENT("HG_RED", _T("fail ���� ������ game ������ �����ϴ�.") );
		return;
	}

	if(FALSE == GetOwner()->GetGameClient().BeginClient(st.game[0].ip_, st.game[0].portTcp_, st.game[0].portUdp_, MAX_CLIENT_RECV_TCP_POOL_SIZE, MAX_CLIENT_RECV_UDP_POOL_COUNT, MAX_CLIENT_SEND_UDP_POOL_COUNT))
	//if(FALSE == GetOwner()->GetGameClient().BeginClient(HisUtil::IP_aTon("175.197.48.218"), st.game[0].portTcp_, st.game[0].portUdp_))
	{
		LOGEVENT("HG_RED", _T("fail Game ���� ���ӿ� �����Ͽ����ϴ�.") );
		return;
	}

	GetOwner()->GetGameClient().SetMasterKey(st.masterkey);
	LOGEVENT("HG_WHITE", _T("Game ������ ���� �õ��մϴ�.") );

	//GetTcpSession()->End();
	//LOGEVENT("HG_GRAY", _T("Balance ���� ������ �����մϴ�.") );
}
