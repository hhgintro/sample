#pragma once



//======================================
//	common
//======================================
//�� ��Ŷ�� join group�� ���� ��Ŷ�� �ƴ϶�.
//�� ��Ŷ�� �������� �ؼ� join�� �Ǵ� ����� ���� �ȴ�.
//����, Group�� ������ ���� ä�ο� ������ ��쿡 CH_JOIN_GROUP_REQ ��Ī�� CH_ENTER_CHANNEL_REQ ��� ���� �ٲ����ϱ� �ٶ���.
//������ ������ ������ master�� ����Ѵ�.
//	serverinfo : Master�� ������ remote�� ���� ����
//		ip : ������ listen ip
//		portTcp : ������ listen tcp port
//		portUdp : ������ listen udp port
struct stM2_JOIN_GROUP_REQ
{
	stM2_JOIN_GROUP_REQ()
		: remote(0)
	{
	}

	HOSTID remote;
	std::vector<stRemoteServerInfo> serverinfo;
};


//�� ��Ŷ�� leave group�� ���� ��Ŷ�� �ƴ϶�.
//�� ��Ŷ�� �������� �ؼ� leave�� �Ǵ� ����� ���� �ȴ�.
//����, Group�� ������ ���� ä�ο��� ������ ��쿡 CH_LEAVE_GROUP_REQ ��Ī�� CH_LEAVE_CHANNEL_REQ ��� ���� �ٲ����ϱ� �ٶ���.
//leave group ��û
//	group : join�� group�� id
//	remote : �������� �Ҵ���� �ڽ��� host id
//[encrypt] CH_LEAVE_GROUP_REQ(P2PGROUPID group, HOSTID remote)
//peer ���� ����Ÿ ����
//	remoteFrom : �������� �Ҵ���� �ڽ��� host id
//	remoteTo : �������� �Ҵ���� Ÿ���� host id
struct stM2_CH_UDP_HELLO_PEER_REQ
{
	stM2_CH_UDP_HELLO_PEER_REQ()
		: remoteFrom(0), remoteTo(0)
	{
	}

	HOSTID remoteFrom;
	HOSTID remoteTo;
};


//peer ���� ����Ÿ ����
//	remoteFrom : �������� �Ҵ���� �ڽ��� host id
//	remoteTo : �������� �Ҵ���� Ÿ���� host id
struct stM2_CH_UDP_FINE_THANKS_PEER_ACK
{
	stM2_CH_UDP_FINE_THANKS_PEER_ACK()
		: remoteFrom(0), remoteTo(0)
	{
	}

	HOSTID remoteFrom;
	HOSTID remoteTo;
};


//�ڽ�(����)�� ���� ������ �����ð����� �ֺ� �������� �����Ѵ�.
//	_stGameServerInfo : ���� ����
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
//�α��� ��û
//	accountpk : ���� ���� �ε��� PK
//	account : ������
//	gameserverno : ������ gameserver no( 0 �̸� ���Ѿ��� ���Ӱ��� )
//	remoteBalance : Balance������ host id - ������ ������ �ٷ� ó���ϱ� ����
//	remoteX : ���� ������ host id
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


//�α��� ��û�� ���� ����
//	result : ���� �����
//	result_noti : �ΰ� ����
//	remoteBalance : ������ ������ Balance������ host id - ������ ������ �ٷ� ó���ϱ� ����
//	remoteX : ���� ������ host id
//	accountpk : ���� ���� �ε��� PK
//	account : ������
//	masterkey : master���� ���� ����Ű ( game������ ���� ������ �� �����Ѵ�.)
//	gameserverno : ������ gameserver no( 0 �̸� ���Ѿ��� ���Ӱ��� )
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
//�α׾ƿ� ��û
//	accountpk : ���� ���� �ε��� PK
//	entry : client�� Ÿ��( user client, login, game, master, etc)
//	remoteServer : ������ �����ϰ� �ִ� balance���� �Ǵ� game������ host id
//	remoteX : ���� ������ host id
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


//game ������ status ������ balance�� �뺸
//	remote : ����� ������ host id
//	status : server ���� (S_STATUS ����)
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
//GAME ���� ���� ���� ��û
//	account : ������
//	masterkey : master���� ���� ����Ű ( balance������ ���� �޾Ҵ�.)
//	remoteGame : ������ ������ Game������ host id - ������ ������ �ٷ� ó���ϱ� ����
//	remoteX : Game������ ���� ������ host id
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


//GAME ���� ���� ���� ��û�� ���� ����
//	result : ���� �����
//	remoteX : Game������ ���� ������ host id
//	accountpk : ���� ���� �ε��� PK
//	account : ������
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
