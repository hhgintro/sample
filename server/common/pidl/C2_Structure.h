#pragma once



//======================================
//	common
//======================================
//���� status ���� ��û
//	remoteFrom : control������ �� host id
//	remoteTo : shutdown ��ų ������ host id
//	status : server ���� (S_STATUS ����)
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


//���� status ���� ��û�� ���� ����
//	remoteFrom : control������ �� host id
//	remoteTo : shutdown ��ų ������ host id
//	status : server ���� (S_STATUS ����)
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
//�ڽ�(game ����)�� ���� ������ �����ð����� control �������� �����Ѵ�.
//	_stGameServerInfo : ���� ����
struct stC2_UDP_GAME_SERVER_INFO_NTF
{
	stC2_UDP_GAME_SERVER_INFO_NTF()
	{
	}

	std::vector<_stGameServerInfo> gameinfo;
};
