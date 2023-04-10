#include "StdAfx.h"
#include "world.h"


CWorld::CWorld()
{
	// Winsock�� ����ϱ� ���� DLL �ε�
	WSADATA WsaData;
	WSAStartup(MAKEWORD(2, 2), &WsaData);	// 2.2 ������ �ε��մϴ�.

	Clear();

	//SYSTEM_INFO SystemInfo;
	//GetSystemInfo(&SystemInfo);
	CThread::BeginThread(1);//SystemInfo.dwNumberOfProcessors);// * 2 + 1);
}

CWorld::~CWorld()
{
//	m_dbAccount.Disconnect();

	OnStop();



	// ����� DLL(ws2_32.dll)�� ��ε� ��ŵ�ϴ�.
	//int WSACancelBlockingCall( void )
	//WSACancelBlockingCall();
	WSACleanup();
}

void CWorld::Clear()
{
	//memset(CONFIG_FILE_NAME, 0, sizeof(CONFIG_FILE_NAME));

	//ip_						= 0;
	//port_					= 0;
	////oListenTcp_				= NULL;
	////oListenUdp_				= NULL;

	//ServerRecvUdpPoolCount_ = 0;
	//ServerSendUdpPoolCount_ = 0;

	//RemoteRecvTcpPoolSize_ = 0;
	//RemoteRecvUdpPoolCount_ = 0;

	//ClientRecvTcpPoolSize_ = 0;
	//ClientRecvUdpPoolCount_ = 0;
	//ClinetSendUdpPoolCount_ = 0;

	//MAX_USER				= 0;
	////mapUser_.clear();

	m_nStatus = NetCore::eS_Closed;
}

//thread�� �� �ʿ��Ѱ���???????????
// ���Ӽ��� ������
void CWorld::OnWorkerThread(int index)
{
	while(true)
	{
		//SetEvent(CThread::StartupEventHandle_);
		Sleep(1);

		if(NetCore::eS_Start != m_nStatus)
			continue;

		//{
			server_.Update();

			master_.Update();
		//}
	}
}

// ���� ���� ����
DWORD CWorld::OnStart()
{
	DWORD dwResult = SERVER_OK;
	
	dwResult = LoadConfigurations();
	if( dwResult )
		return dwResult;

	dwResult = InitializeNetwork();
	if( dwResult )
		return dwResult;

	LOGEVENT("HG_WHITE", _T("%s Start"), GetModule().GetAppName());
	SET_LOG_EVENT_TICK(TIME_SEC(10));//�α� ��� �ֱ�
	m_nStatus = NetCore::eS_Start;
	return dwResult;
}

void CWorld::OnStop()
{
	CThread::EndThread();

	// CServerIocp�� �����Ҷ�

	// mapUser_ ����
	//std::map<std::wstring, USER*>::iterator it
	//for (it = mapUser_.begin() it != mapUser_.end() ++it)
	//	delete (*it).second
	//mapUser_.clear()


	//// IOCP�� �����մϴ�.
	//CIocp::End()

	//// �����ߴ� Listen�� ��ü�� �����ϰ� ������ �ݴϴ�.
	//if (oListenTcp_)
	//{
	//	oListenTcp_->End()

	//	delete oListenTcp_
	//}

	//if(oListenUdp_)
	//{
	//	oListenUdp_->End()

	//	delete oListenUdp_
	//}
}

DWORD CWorld::LoadConfigurations()
{
	DWORD dwResult = SERVER_OK;
	
	dwResult = LoadServerInfo();
	if( dwResult )
		return dwResult;

	dwResult = ConnectDatabase();
	if( dwResult )
		return dwResult;

	return 0;
}

DWORD CWorld::LoadServerInfo()
{
	DWORD dwResult = SERVER_OK;

	TCHAR configfile[MAX_PATH] = _T("");
	_stprintf_s(configfile, _T("%s/config/%s.ini"), GetModule().GetPathName(), GetModule().GetAppName());
	dwResult = CParam::Instance().Open(configfile);
	if (SERVER_OK != dwResult)
		return dwResult;

	//HisUtil::CIniLoader loder;
	//if (FALSE == loder.Open(_T("./config/MasterServer.ini")))
	//	return ERR_SERVER_LOADCONFIG_OPEN;

	//////*******************//
	//////		common
	//////*******************//

	////���񽺿� ��ϵ� �̸�
	//TCHAR wzAppName[MAX_PATH + 1]	= _T("");
	//if (FALSE == loder.GetValue(_T("Common"), _T("AppName"), wzAppName, MAX_PATH))
	//{
	//	LOGEVENT("HG_RED", _T("Failed g_szAppName :%s"), wzAppName);
	//	return ERR_SERVER_LOADCONFIG_APPLICATION_NAME;
	//}
	//g_szAppName = wzAppName;
	//LOGEVENT("HG_YELLOW", _T("Loading g_szAppName : %s"), g_szAppName.c_str());


	//////Machine Name
	////TCHAR wzMachineName[MAX_PATH + 1] = _T("");
	////char ac[80];
	////::gethostname(ac,sizeof(ac));
	////HisUtil::CA2W(ac, wzMachineName, MAX_PATH);

	////serverinfo_.machinename_ = wzMachineName;
	////serverinfo_.appname_ = wzAppName;


	////Listen socket port
	//if (FALSE == loder.GetValue(_T("Common"), _T("Port"), port_))
	//	return ERR_SERVER_LOADCONFIG_WORLD_PORT;
	//port_ = htons(port_);

	//// ���밡�� ������
	//if (FALSE == loder.GetValue(_T("Common"), _T("MaxUser"), MAX_USER))
	//	return ERR_SERVER_LOADCONFIG_LIMIT_USER;


	//////*******************//
	//////	Packet Pool Size
	//////*******************//
	//if (FALSE == loder.GetValue(_T("PacketPool"), _T("ServerRecvUdpPoolCount"), ServerRecvUdpPoolCount_))
	//	return ERR_SERVER_LOADCONFIG_RECV_UDP_POOL_COUNT;
	//if (FALSE == loder.GetValue(_T("PacketPool"), _T("ServerSendUdpPoolCount"), ServerSendUdpPoolCount_))
	//	return ERR_SERVER_LOADCONFIG_SEND_UDP_POOL_COUNT;

	//if (FALSE == loder.GetValue(_T("PacketPool"), _T("RemoteRecvTcpPoolSize"), RemoteRecvTcpPoolSize_))
	//	return ERR_SERVER_LOADCONFIG_REMOTE_RECV_TCP_POOL_SIZE;
	//if (FALSE == loder.GetValue(_T("PacketPool"), _T("RemoteRecvUdpPoolCount"), RemoteRecvUdpPoolCount_))
	//	return ERR_SERVER_LOADCONFIG_REMOTE_RECV_UDP_POOL_COUNT;

	////if(FALSE == loder.GetValue(_T("PacketPool"), _T("ClientRecvTcpPoolSize"), ClientRecvTcpPoolSize_))
	////	return ERR_SERVER_LOADCONFIG_CLIENT_RECV_TCP_POOL_SIZE;
	////if(FALSE == loder.GetValue(_T("PacketPool"), _T("ClientRecvUdpPoolCount"), ClientRecvUdpPoolCount_))
	////	return ERR_SERVER_LOADCONFIG_CLIENT_RECV_UDP_POOL_COUNT;
	////if(FALSE == loder.GetValue(_T("PacketPool"), _T("ClinetSendUdpPoolCount"), ClinetSendUdpPoolCount_))
	////	return ERR_SERVER_LOADCONFIG_CLIENT_SEND_UDP_POOL_COUNT;

	return dwResult;
}

DWORD CWorld::ConnectDatabase()
{
	DWORD dwResult = SERVER_OK;

	//if(!m_dbAccount.Connect(m_stAccountDB.m_szDNS, m_stAccountDB.m_szUser, m_stAccountDB.m_szPassword))
	//	return ERR_SERVER_LOADCONFIG_ACCOUNTDB_CONNECT


	//CSPAccount	spAccount
	//memcpy(spAccount.m_szAccount, "his",sizeof(spAccount.m_szAccount))
	//memcpy(spAccount.m_szPassword, "his_pass",sizeof(spAccount.m_szPassword))
	//spAccount.m_dwResult	= 0

	//if( spAccount.Open(&m_dbAccount) )
	//{
	//	if(spAccount.m_dwResult==0)
	//		LOGEVENT("HG_GRAY", "���� ����")
	//}

	//CTBLAccountLogin tblAccount
	//tblAccount.m_szAccount = 
	//if(!tblAccount.Open(&m_dbAccount))
	//	return -1

	//while(tblAccount.Fetch())
	//{
	//	LOGEVENT("HG_GRAY", "dwID(%d),Account(%s),pass(%s)", tblAccount.m_dwID, tblAccount.m_szAccount, tblAccount.m_szPassword)
	//}

	return dwResult;
}

DWORD CWorld::InitializeNetwork()
{
	DWORD dwResult = SERVER_OK;

	dwResult = InitializeNetworkServer();
	if (SERVER_OK != dwResult)
		return dwResult;

	dwResult = InitializeNetworkConnect();
	if (SERVER_OK != dwResult)
		return dwResult;

	return dwResult;
}

DWORD CWorld::InitializeNetworkServer()
{
	DWORD dwResult = SERVER_OK;
	//server_.GetGameUdpIocp().SetEventSink(this)
	//server_.GetGameIocp().SetEventSink(this)

	//dwResult = server_.Start(MAX_USER, port_, port_, ServerRecvUdpPoolCount_, ServerSendUdpPoolCount_, RemoteRecvTcpPoolSize_, RemoteRecvUdpPoolCount_);
	dwResult = server_.Start(CParam::Instance().max_user
		, CParam::Instance().port_tcp
		, CParam::Instance().port_udp
		, CParam::Instance().ServerRecvUdpPoolCount
		, CParam::Instance().ServerSendUdpPoolCount
		, CParam::Instance().RemoteRecvTcpPoolSize
		, CParam::Instance().RemoteRecvUdpPoolCount
	);

	return dwResult;
}

DWORD CWorld::InitializeNetworkConnect()
{
	//DWORD dwResult = SERVER_OK;

	master_.SetRemoteEntry(REMOTE_ENTRY::eGameServer);
	master_.BeginClient(CParam::Instance().ip_master
		, CParam::Instance().port_master
		, CParam::Instance().port_master
		, CParam::Instance().ClientRecvTcpPoolSize
		, CParam::Instance().ClientRecvUdpPoolCount
		, CParam::Instance().ClientSendUdpPoolCount
	);

	//return dwResult;
	return SERVER_OK;
}
