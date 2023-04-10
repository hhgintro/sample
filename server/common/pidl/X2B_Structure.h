#pragma once



//로그인 요청
//	account : 계정명
//	authkey : 인증키(password)
//	version : protocol version
struct stX2B_AC_LOGIN_REQ
{
	stX2B_AC_LOGIN_REQ()
		: version(0)
	{
	}

	std::string account;
	std::string authkey;
	PROTOCOL_T version;
};


//로그인 요청에 대한 응답
//	result : 응답 결과값
//	result_noti : 부가 정보
//	masterkey : master서버 접속 인증키 ( game서버를 통해 접속할 때 검토한다.)
//	game : 게임서버의 접속 정보
//		ip
//		portTcp
//		portUdp
struct stX2B_AC_LOGIN_ACK
{
	stX2B_AC_LOGIN_ACK()
		: result(0), result_noti(0)
	{
	}

	RESULT_T result;
	RESULT_T result_noti;
	std::string masterkey;
	std::vector<stRemoteServerInfo> game;
};


//이 패킷을 join group을 위한 패킷이 아니라.
//이 패킷을 보냄으로 해서 join이 되는 결과를 낳게 된다.
//가령, Group이 형성된 작은 채널에 접속한 경우에 CH_JOIN_GROUP_REQ 명칭을 CH_ENTER_CHANNEL_REQ 등과 같이 바꿔사용하기 바란다.
//join group 요청
//	remote : 서버에서 할당받은 자신의 host id
struct stX2B_CH_JOIN_GROUP_REQ
{
	stX2B_CH_JOIN_GROUP_REQ()
		: remote(0)
	{
	}

	HOSTID remote;
};


//이 패킷을 leave group을 위한 패킷이 아니라.
//이 패킷을 보냄으로 해서 leave가 되는 결과를 낳게 된다.
//가령, Group이 형성된 작은 채널에서 퇴장한 경우에 CH_LEAVE_GROUP_REQ 명칭을 CH_LEAVE_CHANNEL_REQ 등과 같이 바꿔사용하기 바란다.
//leave group 요청
//	group : join한 group의 id
//	remote : 서버에서 할당받은 자신의 host id
struct stX2B_CH_LEAVE_GROUP_REQ
{
	stX2B_CH_LEAVE_GROUP_REQ()
		: group(0), remote(0)
	{
	}

	P2PGROUPID group;
	HOSTID remote;
};


//peer 간의 데이타 전송
//	remoteFrom : 서버에서 할당받은 자신의 host id
//	remoteTo : 서버에서 할당받은 타인의 host id
struct stX2B_CH_UDP_HELLO_PEER_REQ
{
	stX2B_CH_UDP_HELLO_PEER_REQ()
		: remoteFrom(0), remoteTo(0)
	{
	}

	HOSTID remoteFrom;
	HOSTID remoteTo;
};


//peer 간의 데이타 전송
//	remoteFrom : 서버에서 할당받은 자신의 host id
//	remoteTo : 서버에서 할당받은 타인의 host id
struct stX2B_CH_UDP_FINE_THANKS_PEER_ACK
{
	stX2B_CH_UDP_FINE_THANKS_PEER_ACK()
		: remoteFrom(0), remoteTo(0)
	{
	}

	HOSTID remoteFrom;
	HOSTID remoteTo;
};
