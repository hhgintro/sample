#pragma once

//===============================================
//	매우 중요.
//	enum형은 순차적으로 적용되어야 합니다.
//	아래쪽(클라에서 사용예정) string을 가져오는 부분처리(GameResultCodeString)를 위해 지켜주셔야 합니다.
//	GameResultCodeString 참조해 주세요.
//===============================================


//client에 보내어질 오류코드 일체
enum GameResultCode
{
	RESULT_OK
	//[kr]성공,
	//[en]Success,
	//[jp]サクセス,


	//===========================//
	// 여기서 부터는 DB 로그입니다 //
	//===========================//

	, DB_EXCEPTION
	//[kr]DB Exception발생,
	//[en]DB Exception발생,
	//[jp]DB Exception발생,

	, DB_OPEN_FAIL
	//[kr]DB open 실패
	//[en]DB 확인되지 않은 오류입니다.
	//[jp]DB 확인되지 않은 오류입니다.

	, DB_NOT_FOUND_ERROR
	//[kr]DB 확인되지 않은 오류입니다.
	//[en]DB 확인되지 않은 오류입니다.
	//[jp]DB 확인되지 않은 오류입니다.


	, DB_NOT_FOUND_ACCOUNT = 10
	//[kr]계정정보를 확인할 수 없습니다.
	//[en]계정정보를 확인할 수 없습니다.
	//[jp]계정정보를 확인할 수 없습니다.

	, DB_ALREADY_EXIST_ACCOUNT
	//[kr]계정정보가 이미 존재합니다.
	//[en]계정정보가 이미 존재합니다.
	//[jp]계정정보가 이미 존재합니다.

	, DB_NOT_FOUND_RECOMMEND_ACCOUNT
	//[kr]추천인을 확인할 수 없습니다.
	//[en]추천인을 확인할 수 없습니다.
	//[jp]추천인을 확인할 수 없습니다.


	//=============================//
	// 여기서 부터는 core 로그입니다 //
	//=============================//

	, ERR_CORE_PROTOCOL_VERSION_DISCORDANCE = 100
	//[kr]프로토콜 버전이 다르다(core),
	//[en]differ protocol version,
	//[jp]differ protocol version,

	, ERR_HOLE_PUNCHING_EXCEED_THE_COUNT_LIMIT
	//[kr]홀펀칭 회수 초과,
	//[en]hole punching exceed ther count limit,
	//[jp]hole punching exceed ther count limit,





	//=============================//
	// 여기서 부터는 game 로그입니다 //
	//=============================//

	, ERR_PROTOCOL_VERSION_DISCORDANCE = 200
	//[kr]프로토콜 버전이 다르다,
	//[en]differ protocol version,
	//[jp]differ protocol version,

	, ERR_LOGIN_NOT_FOUND_ACCOUNT_SERVER
	//[kr]계정서버를 확인할 수 없습니다.,
	//[en]proud1,
	//[jp]proud1,

	, ERR_LOGIN_NOT_FOUND_GAME_SERVER
	//[kr]게임서버를 확인할 수 없습니다.,
	//[en]proud1,
	//[jp]proud1,

	, ERR_LOGIN_DUPLICATION_NEW_CONNECTION
	//[kr]동일 계정으로 접속이 확인되어 종료합니다(접속종료).,
	//[en]proud1,
	//[jp]proud1,

	, ERR_LOGIN_DUPLICATION_CONNECTION
	//[kr]동일 계정으로 접속이 확인되었습니다(확인용).,
	//[en]proud1,
	//[jp]proud1,

	, ERR_GAME_NOT_FOUND_ACCOUNT
	//[kr]Account서버에 계정정보가 확인되지 않습니다.,
	//[en]proud1,
	//[jp]proud1,

	, ERR_GAME_DIFF_CERTIFY
	//[kr]Account서버에서 인증이 실패하였습니다.,
	//[en]proud2,
	//[jp]proud2,

	, ERR_GAME_NOT_REGIST_ACCOUNT
	//[kr]Game서버에 등록된 계정정보가 없습니다.,
	//[en]proud2,
	//[jp]proud2,

	, ERR_LOGIN_NOT_FOUND_TRACK_SERVER
	//[kr]경마(track)서버를 확인할 수 없습니다.,
	//[en]proud1,
	//[jp]proud1,

	, ERR_NOT_FOUND_RACEINFO
	//[kr]경마정보를 확인할 수 없습니다.
	//[en]Please wait until the next game
	//[jp]proud1,

	, ERR_WAIT_UNTIL_NEXT_GAME
	//[kr]다음 경기까지 기다려 주세요
	//[en]Please wait until the next game
	//[jp]proud1,

	, ERR_WAIT_UNTIL_BET_FINISH
	//[kr]배팅이 마감될때 까지 기다려 주세요.
	//[en]Please wait until the next game
	//[jp]proud1,


	, ProudError_00003
	//[kr]proud3,
	//[en]proud3,
	//[jp]proud3,







	, MAX_GAME_RESULT
	//[kr]MAX_GAME_RESULT
	//[en]MAX_GAME_RESULT
	//[jp]MAX_GAME_RESULT
};
