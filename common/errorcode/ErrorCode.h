#pragma once

//===============================================
//	�ſ� �߿�.
//	enum���� ���������� ����Ǿ�� �մϴ�.
//	�Ʒ���(Ŭ�󿡼� ��뿹��) string�� �������� �κ�ó��(GameResultCodeString)�� ���� �����ּž� �մϴ�.
//	GameResultCodeString ������ �ּ���.
//===============================================


//client�� �������� �����ڵ� ��ü
enum GameResultCode
{
	RESULT_OK
	//[kr]����,
	//[en]Success,
	//[jp]��������,


	//===========================//
	// ���⼭ ���ʹ� DB �α��Դϴ� //
	//===========================//

	, DB_EXCEPTION
	//[kr]DB Exception�߻�,
	//[en]DB Exception�߻�,
	//[jp]DB Exception�߻�,

	, DB_OPEN_FAIL
	//[kr]DB open ����
	//[en]DB Ȯ�ε��� ���� �����Դϴ�.
	//[jp]DB Ȯ�ε��� ���� �����Դϴ�.

	, DB_NOT_FOUND_ERROR
	//[kr]DB Ȯ�ε��� ���� �����Դϴ�.
	//[en]DB Ȯ�ε��� ���� �����Դϴ�.
	//[jp]DB Ȯ�ε��� ���� �����Դϴ�.


	, DB_NOT_FOUND_ACCOUNT = 10
	//[kr]���������� Ȯ���� �� �����ϴ�.
	//[en]���������� Ȯ���� �� �����ϴ�.
	//[jp]���������� Ȯ���� �� �����ϴ�.

	, DB_ALREADY_EXIST_ACCOUNT
	//[kr]���������� �̹� �����մϴ�.
	//[en]���������� �̹� �����մϴ�.
	//[jp]���������� �̹� �����մϴ�.

	, DB_NOT_FOUND_RECOMMEND_ACCOUNT
	//[kr]��õ���� Ȯ���� �� �����ϴ�.
	//[en]��õ���� Ȯ���� �� �����ϴ�.
	//[jp]��õ���� Ȯ���� �� �����ϴ�.


	//=============================//
	// ���⼭ ���ʹ� core �α��Դϴ� //
	//=============================//

	, ERR_CORE_PROTOCOL_VERSION_DISCORDANCE = 100
	//[kr]�������� ������ �ٸ���(core),
	//[en]differ protocol version,
	//[jp]differ protocol version,

	, ERR_HOLE_PUNCHING_EXCEED_THE_COUNT_LIMIT
	//[kr]Ȧ��Ī ȸ�� �ʰ�,
	//[en]hole punching exceed ther count limit,
	//[jp]hole punching exceed ther count limit,





	//=============================//
	// ���⼭ ���ʹ� game �α��Դϴ� //
	//=============================//

	, ERR_PROTOCOL_VERSION_DISCORDANCE = 200
	//[kr]�������� ������ �ٸ���,
	//[en]differ protocol version,
	//[jp]differ protocol version,

	, ERR_LOGIN_NOT_FOUND_ACCOUNT_SERVER
	//[kr]���������� Ȯ���� �� �����ϴ�.,
	//[en]proud1,
	//[jp]proud1,

	, ERR_LOGIN_NOT_FOUND_GAME_SERVER
	//[kr]���Ӽ����� Ȯ���� �� �����ϴ�.,
	//[en]proud1,
	//[jp]proud1,

	, ERR_LOGIN_DUPLICATION_NEW_CONNECTION
	//[kr]���� �������� ������ Ȯ�εǾ� �����մϴ�(��������).,
	//[en]proud1,
	//[jp]proud1,

	, ERR_LOGIN_DUPLICATION_CONNECTION
	//[kr]���� �������� ������ Ȯ�εǾ����ϴ�(Ȯ�ο�).,
	//[en]proud1,
	//[jp]proud1,

	, ERR_GAME_NOT_FOUND_ACCOUNT
	//[kr]Account������ ���������� Ȯ�ε��� �ʽ��ϴ�.,
	//[en]proud1,
	//[jp]proud1,

	, ERR_GAME_DIFF_CERTIFY
	//[kr]Account�������� ������ �����Ͽ����ϴ�.,
	//[en]proud2,
	//[jp]proud2,

	, ERR_GAME_NOT_REGIST_ACCOUNT
	//[kr]Game������ ��ϵ� ���������� �����ϴ�.,
	//[en]proud2,
	//[jp]proud2,

	, ERR_LOGIN_NOT_FOUND_TRACK_SERVER
	//[kr]�渶(track)������ Ȯ���� �� �����ϴ�.,
	//[en]proud1,
	//[jp]proud1,

	, ERR_NOT_FOUND_RACEINFO
	//[kr]�渶������ Ȯ���� �� �����ϴ�.
	//[en]Please wait until the next game
	//[jp]proud1,

	, ERR_WAIT_UNTIL_NEXT_GAME
	//[kr]���� ������ ��ٷ� �ּ���
	//[en]Please wait until the next game
	//[jp]proud1,

	, ERR_WAIT_UNTIL_BET_FINISH
	//[kr]������ �����ɶ� ���� ��ٷ� �ּ���.
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
