#pragma once



struct stM2_BD_VOICE_CHAT_REQ
{
	stM2_BD_VOICE_CHAT_REQ()
	{
	}

	std::wstring chat;
};


struct stM2_BD_VOICE_CHAT_ACK
{
	stM2_BD_VOICE_CHAT_ACK()
	{
	}

	std::wstring chat;
};


//로그인 요청
//	account : 계정명
//	password : 인증키(password)
//	remoteX : 접속 유저의 host id
struct stM2_AC_LOGIN_REQ
{
	stM2_AC_LOGIN_REQ()
		: remoteX(0)
	{
	}

	std::wstring account;
	std::wstring password;
	HOSTID remoteX;
};


//로그인 요청에 대한 응답
//	result : 응답 결과값
//	remoteX : 접속 유저의 host id
//	accountpk : 계정 고유 인덱스 PK
//	account : 계정명
struct stM2_AC_LOGIN_ACK
{
	stM2_AC_LOGIN_ACK()
		: result(0), remoteX(0), accountpk(0)
	{
	}

	RESULT_T result;
	HOSTID remoteX;
	ACCOUNTPK accountpk;
	std::wstring account;
};


//장착 정보 요청
//	remoteX : 접속 유저의 host id
//	accountpk : 계정 식별자(pk)
struct stM2_IN_EQUIP_LOAD_REQ
{
	stM2_IN_EQUIP_LOAD_REQ()
		: remoteX(0), accountpk(0)
	{
	}

	HOSTID remoteX;
	ACCOUNTPK accountpk;
};


//장착 정보 요청에 대한 응답
//	remoteX : 접속 유저의 host id
//	inven : 장착및 인벤정보
struct stM2_IN_EQUIP_LOAD_ACK
{
	stM2_IN_EQUIP_LOAD_ACK()
		: remoteX(0)
	{
	}

	HOSTID remoteX;
	stInven inven;
};


//장착 정보 변경 요청
//	remoteX : 접속 유저의 host id
//	accountpk : 계정 식별자(pk)
//	inven : 장착및 인벤정보
struct stM2_IN_EQUIP_UPDATE_REQ
{
	stM2_IN_EQUIP_UPDATE_REQ()
		: remoteX(0), accountpk(0)
	{
	}

	HOSTID remoteX;
	ACCOUNTPK accountpk;
	stInven inven;
};


//장착 정보 변경 요청에 대한 응답
//	remoteX : 접속 유저의 host id
//	result : 응답 결과값
//	inven : 장착및 인벤정보
struct stM2_IN_EQUIP_UPDATE_ACK
{
	stM2_IN_EQUIP_UPDATE_ACK()
		: remoteX(0), result(0)
	{
	}

	HOSTID remoteX;
	RESULT_T result;
	stInven inven;
};
