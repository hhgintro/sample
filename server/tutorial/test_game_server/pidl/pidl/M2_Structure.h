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


//�α��� ��û
//	account : ������
//	password : ����Ű(password)
//	remoteX : ���� ������ host id
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


//�α��� ��û�� ���� ����
//	result : ���� �����
//	remoteX : ���� ������ host id
//	accountpk : ���� ���� �ε��� PK
//	account : ������
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


//���� ���� ��û
//	remoteX : ���� ������ host id
//	accountpk : ���� �ĺ���(pk)
struct stM2_IN_EQUIP_LOAD_REQ
{
	stM2_IN_EQUIP_LOAD_REQ()
		: remoteX(0), accountpk(0)
	{
	}

	HOSTID remoteX;
	ACCOUNTPK accountpk;
};


//���� ���� ��û�� ���� ����
//	remoteX : ���� ������ host id
//	inven : ������ �κ�����
struct stM2_IN_EQUIP_LOAD_ACK
{
	stM2_IN_EQUIP_LOAD_ACK()
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


//���� ���� ���� ��û�� ���� ����
//	remoteX : ���� ������ host id
//	result : ���� �����
//	inven : ������ �κ�����
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
