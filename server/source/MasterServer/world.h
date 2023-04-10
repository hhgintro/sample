#pragma once


class CWorld : public HisUtil::CThread, public HisUtil::CSingleton<CWorld>
{
public:
	CWorld();
	~CWorld();


	DWORD OnStart();
		DWORD LoadConfigurations();
			DWORD LoadServerInfo();
			DWORD ConnectDatabase();
		DWORD InitializeNetwork();
			DWORD InitializeNetworkServer();
			DWORD InitializeNetworkConnect();
	void OnStop();

private:
	void Clear();


public:
	VOID OnWorkerThread(int index);

	//tstring& GetApplicationName() { return appname_; }
	CServer& GetServer()		{ return server_; }

	HisUtil::CModule& GetModule() { return module_; }

private:
	////World Server
	////tstring				appname_;					//서비스에 등록된 이름
	////BYTE				byServerClose_;			// 서버가 닫혀 있는가?
	//TCHAR				CONFIG_FILE_NAME[MAX_PATH];

	//ADDR_IP				ip_;
	//ADDR_PORT			port_;

	// 서버의 Listen을 담당할 개체
	CServer server_;

	HisUtil::CModule module_;

	////CNetworkSession* oListenTcp_;
	////CNetworkSession* oListenUdp_;

	//int ServerRecvUdpPoolCount_;
	//int ServerSendUdpPoolCount_;

	//int RemoteRecvTcpPoolSize_;
	//int RemoteRecvUdpPoolCount_;

	//int ClientRecvTcpPoolSize_;
	//int ClientRecvUdpPoolCount_;
	//int ClinetSendUdpPoolCount_;

	//int	MAX_USER;
	////// USER를 관리하는 map
	////std::map<std::wstring, USER*> mapUser_;
	S_STATUS_T m_nStatus;
};

