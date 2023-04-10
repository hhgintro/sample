#pragma once



//======================================
//	common
//======================================
//서버 status 변경 요청
//	remoteFrom : control서버의 는 host id
//	remoteTo : shutdown 시킬 서버의 host id
//	status : server 상태 (S_STATUS 참조)
struct stC2_UDP_CHANGE_SERVER_STATUS_REQ
{
	stC2_UDP_CHANGE_SERVER_STATUS_REQ()
		: remoteFrom(0), remoteTo(0)
	{
	}

	HOSTID remoteFrom;
	HOSTID remoteTo;
	S_STATUS_T status;
};


//서버 status 변경 요청에 대한 응답
//	remoteFrom : control서버의 는 host id
//	remoteTo : shutdown 시킬 서버의 host id
//	status : server 상태 (S_STATUS 참조)
struct stC2_UDP_CHANGE_SERVER_STATUS_ACK
{
	stC2_UDP_CHANGE_SERVER_STATUS_ACK()
		: remoteTo(0)
	{
	}

	HOSTID remoteTo;
	S_STATUS_T status;
};


//======================================
//	login
//======================================
//======================================
//	balance
//======================================
//======================================
//	game
//======================================
//자신(game 서버)의 갱신 정보를 일정시간마다 control 서버에게 전송한다.
//	_stGameServerInfo : 서버 정보
struct stC2_UDP_GAME_SERVER_INFO_NTF
{
	stC2_UDP_GAME_SERVER_INFO_NTF()
	{
	}

	std::vector<_stGameServerInfo> gameinfo;
};
