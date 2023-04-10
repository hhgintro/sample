#pragma once



//�α��� ��û
//	account : ������
//	password : ����Ű(password)
//	remoteX : ���� ������ host id
struct stG2DB_AC_LOGIN_REQ
{
	stG2DB_AC_LOGIN_REQ()
		: remoteX(0)
	{
	}

	std::wstring account;
	std::wstring password;
	HOSTID remoteX;
};


//�α��� ��û�� ���� ����
//	result : ���� �����
//	remoteX : ���� ������ host id
//	accountpk : ���� ���� �ε��� PK
//	account : ������
struct stG2DB_AC_LOGIN_ACK
{
	stG2DB_AC_LOGIN_ACK()
		: result(0), remoteX(0), accountpk(0)
	{
	}

	RESULT_T result;
	HOSTID remoteX;
	ACCOUNTPK accountpk;
	std::wstring account;
};


//���� ���� ��û
//	remoteX : ���� ������ host id
//	accountpk : ���� �ĺ���(pk)
struct stG2DB_IN_EQUIP_LOAD_REQ
{
	stG2DB_IN_EQUIP_LOAD_REQ()
		: remoteX(0), accountpk(0)
	{
	}

	HOSTID remoteX;
	ACCOUNTPK accountpk;
};


//���� ���� ��û�� ���� ����
//	remoteX : ���� ������ host id
//	inven : ������ �κ�����
struct stG2DB_IN_EQUIP_LOAD_ACK
{
	stG2DB_IN_EQUIP_LOAD_ACK()
		: remoteX(0)
	{
	}

	HOSTID remoteX;
	stInven inven;
};


//���� ���� ���� ��û
//	remoteX : ���� ������ host id
//	accountpk : ���� �ĺ���(pk)
//	inven : ������ �κ�����
struct stG2DB_IN_EQUIP_UPDATE_REQ
{
	stG2DB_IN_EQUIP_UPDATE_REQ()
		: remoteX(0), accountpk(0)
	{
	}

	HOSTID remoteX;
	ACCOUNTPK accountpk;
	stInven inven;
};


//���� ���� ���� ��û�� ���� ����
//	remoteX : ���� ������ host id
//	result : ���� �����
//	inven : ������ �κ�����
struct stG2DB_IN_EQUIP_UPDATE_ACK
{
	stG2DB_IN_EQUIP_UPDATE_ACK()
		: remoteX(0), result(0)
	{
	}

	HOSTID remoteX;
	RESULT_T result;
	stInven inven;
};
