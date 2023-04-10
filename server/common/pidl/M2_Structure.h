#pragma once



//======================================
//	common
//======================================
//이 패킷을 join group을 위한 패킷이 아니라.
//이 패킷을 보냄으로 해서 join이 되는 결과를 낳게 된다.
//가령, Group이 형성된 작은 채널에 접속한 경우에 CH_JOIN_GROUP_REQ 명칭을 CH_ENTER_CHANNEL_REQ 등과 같이 바꿔사용하기 바란다.
//구동된 서버의 정보를 master에 등록한다.
//	serverinfo : Master에 접속한 remote의 서버 정보
//		ip : 서버의 listen ip
//		portTcp : 서버의 listen tcp port
//		portUdp : 서버의 listen udp port
struct stM2_JOIN_GROUP_REQ
{
	stM2_JOIN_GROUP_REQ()
		: remote(0)
	{
	}

	HOSTID remote;
	std::vector<stRemoteServerInfo> serverinfo;
};


//이 패킷을 leave group을 위한 패킷이 아니라.
//이 패킷을 보냄으로 해서 leave가 되는 결과를 낳게 된다.
//가령, Group이 형성된 작은 채널에서 퇴장한 경우에 CH_LEAVE_GROUP_REQ 명칭을 CH_LEAVE_CHANNEL_REQ 등과 같이 바꿔사용하기 바란다.
//leave group 요청
//	group : join한 group의 id
//	remote : 서버에서 할당받은 자신의 host id
//[encrypt] CH_LEAVE_GROUP_REQ(P2PGROUPID group, HOSTID remote)
//peer 간의 데이타 전송
//	remoteFrom : 서버에서 할당받은 자신의 host id
//	remoteTo : 서버에서 할당받은 타인의 host id
struct stM2_CH_UDP_HELLO_PEER_REQ
{
	stM2_CH_UDP_HELLO_PEER_REQ()
		: remoteFrom(0), remoteTo(0)
	{
	}

	HOSTID remoteFrom;
	HOSTID remoteTo;
};


//peer 간의 데이타 전송
//	remoteFrom : 서버에서 할당받은 자신의 host id
//	remoteTo : 서버에서 할당받은 타인의 host id
struct stM2_CH_UDP_FINE_THANKS_PEER_ACK
{
	stM2_CH_UDP_FINE_THANKS_PEER_ACK()
		: remoteFrom(0), remoteTo(0)
	{
	}

	HOSTID remoteFrom;
	HOSTID remoteTo;
};


//자신(서버)의 갱신 정보를 일정시간마다 주변 서버에게 전송한다.
//	_stGameServerInfo : 서버 정보
struct stM2_CH_UDP_CURRENT_USER_NTF
{
	stM2_CH_UDP_CURRENT_USER_NTF()
	{
	}

	std::vector<_stGameServerInfo> serverinfo;
};


//======================================
//	login
//======================================
//로그인 요청
//	accountpk : 계정 고유 인덱스 PK
//	account : 계정명
//	gameserverno : 접속할 gameserver no( 0 이면 제한없이 접속가능 )
//	remoteBalance : Balance서버의 host id - 응답을 받을때 바로 처리하기 위해
//	remoteX : 접속 유저의 host id
struct stM2_AC_LOGIN_REQ
{
	stM2_AC_LOGIN_REQ()
		: accountpk(0), gameserverno(0), remoteBalance(0), remoteX(0)
	{
	}

	ACCOUNTPK accountpk;
	std::string account;
	INT16 gameserverno;
	HOSTID remoteBalance;
	HOSTID remoteX;
};


//로그인 요청에 대한 응답
//	result : 응답 결과값
//	result_noti : 부가 정보
//	remoteBalance : 유저가 접속한 Balance서버의 host id - 응답을 받을때 바로 처리하기 위해
//	remoteX : 접속 유저의 host id
//	accountpk : 계정 고유 인덱스 PK
//	account : 계정명
//	masterkey : master서버 접속 인증키 ( game서버를 통해 접속할 때 검토한다.)
//	gameserverno : 접속할 gameserver no( 0 이면 제한없이 접속가능 )
struct stM2_AC_LOGIN_ACK
{
	stM2_AC_LOGIN_ACK()
		: result(0), result_noti(0), remoteBalance(0), remoteX(0), accountpk(0), gameserverno(0)
	{
	}

	RESULT_T result;
	RESULT_T result_noti;
	HOSTID remoteBalance;
	HOSTID remoteX;
	ACCOUNTPK accountpk;
	std::string account;
	std::string masterkey;
	INT16 gameserverno;
};


//======================================
//	balance
//======================================
//로그아웃 요청
//	accountpk : 계정 고유 인덱스 PK
//	entry : client의 타입( user client, login, game, master, etc)
//	remoteServer : 유저가 접속하고 있는 balance서버 또는 game서버의 host id
//	remoteX : 접속 유저의 host id
struct stM2_AC_LOGOUT_REQ
{
	stM2_AC_LOGOUT_REQ()
		: accountpk(0), entry(0), remoteServer(0), remoteX(0)
	{
	}

	ACCOUNTPK accountpk;
	REMOTE_ENTRY_T entry;
	HOSTID remoteServer;
	HOSTID remoteX;
};


//game 서버의 status 변경을 balance에 통보
//	remote : 변경된 서버의 host id
//	status : server 상태 (S_STATUS 참조)
struct stM2_UDP_CHANGE_SERVER_STATUS_NTF
{
	stM2_UDP_CHANGE_SERVER_STATUS_NTF()
		: remote(0)
	{
	}

	HOSTID remote;
	S_STATUS_T status;
};


//======================================
//	game
//======================================
//GAME 서버 접속 승인 요청
//	account : 계정명
//	masterkey : master서버 접속 인증키 ( balance서버를 통해 받았다.)
//	remoteGame : 유저가 접속한 Game서버의 host id - 응답을 받을때 바로 처리하기 위해
//	remoteX : Game서버에 접속 유저의 host id
struct stM2_AC_CERTIFY_REQ
{
	stM2_AC_CERTIFY_REQ()
		: remoteGame(0), remoteX(0)
	{
	}

	std::string account;
	std::string masterkey;
	HOSTID remoteGame;
	HOSTID remoteX;
};


//GAME 서버 접속 승인 요청에 대한 응답
//	result : 응답 결과값
//	remoteX : Game서버에 접속 유저의 host id
//	accountpk : 계정 고유 인덱스 PK
//	account : 계정명
struct stM2_AC_CERTIFY_ACK
{
	stM2_AC_CERTIFY_ACK()
		: result(0), remoteX(0), accountpk(0)
	{
	}

	RESULT_T result;
	HOSTID remoteX;
	ACCOUNTPK accountpk;
	std::string account;
};
