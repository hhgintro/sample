#pragma once


class CClientWorld : public HisUtil::CThread//, public Singleton<CClientWorld>
{
public:
	CClientWorld();
	~CClientWorld();

	DWORD OnStart();
	void OnStop();

private:
	void Clear();

	VOID OnWorkerThread(int index);

public:
	ADDR_IP GetServerIP() { return serverIP_; }
	void SetServerIP(ADDR_IP ip) { serverIP_ = ip; }

	ADDR_PORT GetServerTcpPort() { return serverTcpPort_; }
	void SetServerTcpPort(ADDR_PORT port) { serverTcpPort_ = port; }

	ADDR_PORT GetServerUdpPort() { return serverUdpPort_; }
	void SetServerUdpPort(ADDR_PORT port) { serverUdpPort_ = port; }

	//CBalanceClient& GetBalanceClient()	{ return balance_; }
	CGameClient& GetGameClient()		{ return game_; }


private:
	//World Server
	//BYTE				byServerClose_;					// 서버가 닫혀 있는가?
	TCHAR				CONFIG_FILE_NAME[MAX_PATH];

	//thread
	DWORD				dwThreadCount_;					//쓰레드 개수
	HANDLE*				hWorldThread_;						// 월드 쓰레드 핸들

	ADDR_IP serverIP_;
	ADDR_PORT serverTcpPort_;
	ADDR_PORT serverUdpPort_;

	//// 서버의 Listen을 담당할 개체
	//CBalanceClient balance_;
	CGameClient game_;
	////CTcpClientSession TcpSession_;
	////CUdpClientSession UdpSession_;


	int	MAX_USER;
	//// USER를 관리하는 map
	//std::map<std::wstring, USER*> mapUser_;

	int					m_nStatus;

	HisUtil::CCritSecBase csClient_;
};

