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
	////tstring				appname_;					//���񽺿� ��ϵ� �̸�
	////BYTE				byServerClose_;			// ������ ���� �ִ°�?
	//TCHAR				CONFIG_FILE_NAME[MAX_PATH];

	//ADDR_IP				ip_;
	//ADDR_PORT			port_;

	// ������ Listen�� ����� ��ü
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
	////// USER�� �����ϴ� map
	////std::map<std::wstring, USER*> mapUser_;
	S_STATUS_T m_nStatus;
};

