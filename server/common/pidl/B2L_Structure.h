#pragma once



//로그인 요청
//	account : 계정명
//	authkey : 인증키(password)
//	remoteBalance : Balance서버의 host id - 응답을 받을때 바로 처리하기 위해
//	remoteX : 접속 유저의 host id
struct stB2L_AC_LOGIN_REQ
{
	stB2L_AC_LOGIN_REQ()
		: remoteBalance(0), remoteX(0)
	{
	}

	std::string account;
	std::string authkey;
	HOSTID remoteBalance;
	HOSTID remoteX;
};


//로그인 요청에 대한 응답
//	result : 응답 결과값
//	result_noti : 부가 정보
//	remoteX : 접속 유저의 host id
//	accountpk : 계정 고유 인덱스 PK
//	account : 계정명
//	masterkey : master서버 접속 인증키 ( game서버를 통해 접속할 때 검토한다.)
//	gameserverno : 접속할 gameserver no( 0 이면 제한없이 접속가능 )
struct stB2L_AC_LOGIN_ACK
{
	stB2L_AC_LOGIN_ACK()
		: result(0), result_noti(0), remoteX(0), accountpk(0), gameserverno(0)
	{
	}

	RESULT_T result;
	RESULT_T result_noti;
	HOSTID remoteX;
	ACCOUNTPK accountpk;
	std::string account;
	std::string masterkey;
	INT16 gameserverno;
};
