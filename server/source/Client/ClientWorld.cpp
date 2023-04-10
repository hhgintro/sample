#include "StdAfx.h"
#include "ClientWorld.h"


extern BOOL g_bIsMove;

CClientWorld::CClientWorld()
{
	// Winsock�� ����ϱ� ���� DLL �ε�
	WSADATA WsaData;
	WSAStartup(MAKEWORD(2, 2), &WsaData);	// 2.2 ������ �ε��մϴ�.

	Clear();
}

CClientWorld::~CClientWorld()
{
//	m_dbAccount.Disconnect();

	DELETE_SAFE_ARRAY(hWorldThread_);

	// ����� DLL�� ��ε� ��ŵ�ϴ�.
	//int WSACancelBlockingCall( void );
	//WSACancelBlockingCall();
	WSACleanup();
}

void CClientWorld::Clear()
{
	hWorldThread_			= NULL;
	memset(CONFIG_FILE_NAME, 0, sizeof(CONFIG_FILE_NAME));

	MAX_USER				= 0;
	//mapUser_.clear();
}


// ���Ӽ��� ������
void CClientWorld::OnWorkerThread(int index)
{
	//random �ð� ����
	srand(GetTickCount());

	TIME_T movetime = 0;

	while(true)
	{
		Sleep(1);

		if(NetCore::S_STATUS::eS_Running == m_nStatus)
		{
			//balance_.Update();
			game_.Update();

			//if(TRUE == GetGameClient().GetIsEnterWorld())
			//{
			//	//AUTO_LOCK(csClient_);

			//	if(movetime < HisUtil::Timer64())
			//	{
			//		if(FALSE == g_bIsMove)
			//		{
			//			movetime = HisUtil::Timer64() + TIME_SEC(5);
			//			continue;
			//		}

			//		int distance = 20;
			//		int random_x = rand();
			//		int scale_x = random_x % distance + 1;
			//		//* 2 : ������ ����ϱ� ����
			//		float randompos_x = (float)(rand() % (scale_x * 2) - scale_x);

			//		int random_y = rand();
			//		int scale_y = random_y % distance + 1;
			//		//* 2 : ������ ����ϱ� ����
			//		float randompos_y = (float)(rand() % (scale_y * 2) - scale_y);

			//		float x = GetGameClient().GetPatrolPos().x_ + randompos_x;
			//		float y = GetGameClient().GetPatrolPos().y_ + randompos_y - 10;// -10 �м��� ������ ���� ���ȴ�.
			//		GetGameClient().WorldMove(x, y);
			//		movetime = HisUtil::Timer64() + ((scale_x + scale_y) * 1000 / 5);	// ������� ���ǵ� 5 �� ������ �ҿ�ð� ����
			//	}
			//}

		}//..if(eS_Start == m_nStatus)
	}//..while(true)
}

// ���� ���� ����
DWORD CClientWorld::OnStart()
{
	//balance_.SetOwner(this);
	game_.SetOwner(this);

	//CIniFile IniFile;
	//if(FALSE == IniFile.Open(_T("./config/GameClient.ini")) )
	//	return ERR_SERVER_LOADCONFIG_OPEN;

	//*******************//
	// Master Server Info
	//*******************//

	////Balance server ip
	//WCHAR wzIP[MAX_IP_LENGTH] = L"";
	//if(FALSE == IniFile.GetValue(_T("server"), _T("ip"), wzIP, MAX_IP_LENGTH))
	//	return ERR_SERVER_LOADCONFIG_BALANCE_IP;

	//char szIP[MAX_IP_LENGTH] = "";
	//HisUtil::CW2A(wzIP, szIP, MAX_IP_LENGTH);
	//ADDR_IP remoteIP = HisUtil::IP_aTon(szIP);
	ADDR_IP remoteIP = HisUtil::IP_aTon("127.0.0.1");

	////Balance server port
	//ADDR_PORT remotePort = 0;
	//if(FALSE == IniFile.GetValue(_T("Balance"), _T("Port"), remotePort))
	//	return ERR_SERVER_LOADCONFIG_BALANCE_IP;
	//remotePort = htons(remotePort);
	ADDR_PORT remotePort = htons(10001);




	DWORD dwResult = SERVER_OK;

	SetServerIP(remoteIP);
	SetServerTcpPort(remotePort);
	SetServerUdpPort(remotePort);


	//balance_.SetRemoteEntry(REMOTE_ENTRY::eClient);
	//if(FALSE == balance_.BeginClient(GetServerIP(), GetServerTcpPort(), GetServerUdpPort(), MAX_CLIENT_RECV_TCP_POOL_SIZE, MAX_CLIENT_RECV_UDP_POOL_COUNT, MAX_CLIENT_SEND_UDP_POOL_COUNT))
	//	return ERR_SERVER_CONNECT_BALANCE_SERVER;

	game_.SetRemoteEntry(REMOTE_ENTRY::eClient);
	if (FALSE == game_.BeginClient(GetServerIP(), GetServerTcpPort(), GetServerUdpPort(), 81960, 32, 32))
		return 0x9999;

	CThread::BeginThread(1);

	LOGEVENT("HG_WHITE", _T("Clinet Start"));
	SET_LOG_EVENT_TICK(TIME_SEC(10));//�α� ��� �ֱ�
	m_nStatus = NetCore::S_STATUS::eS_Running;
	return dwResult;
}

void CClientWorld::OnStop()
{
	CThread::EndThread();

	//GetGameClient().SetIsEnterWorld(FALSE);

	//balance_.End();//OnX2G_AC_CERTIFY_ACK���� ���������
	game_.End();
}
