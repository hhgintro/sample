#pragma once



//서버 목록 요청
struct stC2M_MT_SERVER_LIST_REQ
{
	stC2M_MT_SERVER_LIST_REQ()
	{
	}

};


//서버 목록 요청에 대한 응답
//	stRemoteEndpoint : 서버 정보
struct stC2M_MT_SERVER_LIST_ACK
{
	stC2M_MT_SERVER_LIST_ACK()
	{
	}

	std::vector<stRemoteEndpoint> serverinfo;
};


//서버 추가 요청
struct stC2M_MT_ADD_SERVER_REQ
{
	stC2M_MT_ADD_SERVER_REQ()
	{
	}

};


//서버 추가 요청에 대한 응답
//	stRemoteEndpoint : 서버 정보
struct stC2M_MT_ADD_SERVER_ACK
{
	stC2M_MT_ADD_SERVER_ACK()
	{
	}

	std::vector<stRemoteEndpoint> serverinfo;
};


//서버 삭제 요청
struct stC2M_MT_DELETE_SERVER_REQ
{
	stC2M_MT_DELETE_SERVER_REQ()
	{
	}

};


//서버 삭제 요청에 대한 응답
//	remote : 삭제할 HostID
struct stC2M_MT_DELETE_SERVER_ACK
{
	stC2M_MT_DELETE_SERVER_ACK()
		: remote(0)
	{
	}

	HOSTID remote;
};


//서버 삭제 요청에 대한 응답
//	remote : 삭제할 HostID
struct stC2M_MT_GAME_SERVER_INFO_NTF
{
	stC2M_MT_GAME_SERVER_INFO_NTF()
	{
	}

	std::vector<_stGameServerInfo> gameinfo;
};


//서버 status 변경 요청
//	remote : shutdown시킬 HostID
//	status : server 상태 (S_STATUS 참조)
struct stC2M_MT_CHANGE_SERVER_STATUS_REQ
{
	stC2M_MT_CHANGE_SERVER_STATUS_REQ()
		: remote(0)
	{
	}

	HOSTID remote;
	S_STATUS_T status;
};


//서버 status 변경 요청에 대한 응답
//	remote : shutdown시킬 HostID
//	status : server 상태 (S_STATUS 참조)
struct stC2M_MT_CHANGE_SERVER_STATUS_ACK
{
	stC2M_MT_CHANGE_SERVER_STATUS_ACK()
		: remote(0)
	{
	}

	HOSTID remote;
	S_STATUS_T status;
};


//서버 Launch 요청
//	_stLaunchServerInfo : launch 시킬 server정보
struct stC2M_MT_SERVER_LAUNCH_REQ
{
	stC2M_MT_SERVER_LAUNCH_REQ()
	{
	}

	std::vector<_stLaunchServerInfo> serverinfo;
};


//서버 Launch 요청에 대한 응답
//[encrypt] MT_SERVER_LAUNCH_ACK()
//서버 Shutdown 요청
//	_stLaunchServerInfo : shutdown 시킬 server정보
struct stC2M_MT_SERVER_SHUTDOWN_REQ
{
	stC2M_MT_SERVER_SHUTDOWN_REQ()
	{
	}

	std::vector<_stLaunchServerInfo> serverinfo;
};


//서버 Shutdown 요청에 대한 응답
//[encrypt] MT_SERVER_SHUTDOWN_ACK()
//서버 목록 초기화
struct stC2M_MT_CLEAR_SERVER_LIST_NTF
{
	stC2M_MT_CLEAR_SERVER_LIST_NTF()
	{
	}

};
