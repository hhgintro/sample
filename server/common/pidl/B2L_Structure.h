#pragma once



//�α��� ��û
//	account : ������
//	authkey : ����Ű(password)
//	remoteBalance : Balance������ host id - ������ ������ �ٷ� ó���ϱ� ����
//	remoteX : ���� ������ host id
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


//�α��� ��û�� ���� ����
//	result : ���� �����
//	result_noti : �ΰ� ����
//	remoteX : ���� ������ host id
//	accountpk : ���� ���� �ε��� PK
//	account : ������
//	masterkey : master���� ���� ����Ű ( game������ ���� ������ �� �����Ѵ�.)
//	gameserverno : ������ gameserver no( 0 �̸� ���Ѿ��� ���Ӱ��� )
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
