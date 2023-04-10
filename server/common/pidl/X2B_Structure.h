#pragma once



//�α��� ��û
//	account : ������
//	authkey : ����Ű(password)
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


//�α��� ��û�� ���� ����
//	result : ���� �����
//	result_noti : �ΰ� ����
//	masterkey : master���� ���� ����Ű ( game������ ���� ������ �� �����Ѵ�.)
//	game : ���Ӽ����� ���� ����
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


//�� ��Ŷ�� join group�� ���� ��Ŷ�� �ƴ϶�.
//�� ��Ŷ�� �������� �ؼ� join�� �Ǵ� ����� ���� �ȴ�.
//����, Group�� ������ ���� ä�ο� ������ ��쿡 CH_JOIN_GROUP_REQ ��Ī�� CH_ENTER_CHANNEL_REQ ��� ���� �ٲ����ϱ� �ٶ���.
//join group ��û
//	remote : �������� �Ҵ���� �ڽ��� host id
struct stX2B_CH_JOIN_GROUP_REQ
{
	stX2B_CH_JOIN_GROUP_REQ()
		: remote(0)
	{
	}

	HOSTID remote;
};


//�� ��Ŷ�� leave group�� ���� ��Ŷ�� �ƴ϶�.
//�� ��Ŷ�� �������� �ؼ� leave�� �Ǵ� ����� ���� �ȴ�.
//����, Group�� ������ ���� ä�ο��� ������ ��쿡 CH_LEAVE_GROUP_REQ ��Ī�� CH_LEAVE_CHANNEL_REQ ��� ���� �ٲ����ϱ� �ٶ���.
//leave group ��û
//	group : join�� group�� id
//	remote : �������� �Ҵ���� �ڽ��� host id
struct stX2B_CH_LEAVE_GROUP_REQ
{
	stX2B_CH_LEAVE_GROUP_REQ()
		: group(0), remote(0)
	{
	}

	P2PGROUPID group;
	HOSTID remote;
};


//peer ���� ����Ÿ ����
//	remoteFrom : �������� �Ҵ���� �ڽ��� host id
//	remoteTo : �������� �Ҵ���� Ÿ���� host id
struct stX2B_CH_UDP_HELLO_PEER_REQ
{
	stX2B_CH_UDP_HELLO_PEER_REQ()
		: remoteFrom(0), remoteTo(0)
	{
	}

	HOSTID remoteFrom;
	HOSTID remoteTo;
};


//peer ���� ����Ÿ ����
//	remoteFrom : �������� �Ҵ���� �ڽ��� host id
//	remoteTo : �������� �Ҵ���� Ÿ���� host id
struct stX2B_CH_UDP_FINE_THANKS_PEER_ACK
{
	stX2B_CH_UDP_FINE_THANKS_PEER_ACK()
		: remoteFrom(0), remoteTo(0)
	{
	}

	HOSTID remoteFrom;
	HOSTID remoteTo;
};
