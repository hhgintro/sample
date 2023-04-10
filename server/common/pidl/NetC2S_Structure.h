#pragma once



//���� ������ �Ϸ��
//	remote : �������� �Ҵ���� �ڽ��� host id
struct stNetC2S_CORE_CONNECT_COMPLETED_NTF
{
	stNetC2S_CORE_CONNECT_COMPLETED_NTF()
		: remote(0)
	{
	}

	HOSTID remote;
};


//���� ���ӽ� ��ϵ� ������ ��û�Ѵ�.
//	ver : protocol ����
//	entry : client�� Ÿ��( user client, login, game, master, etc)
struct stNetC2S_CORE_SIGN_UP_REQ
{
	stNetC2S_CORE_SIGN_UP_REQ()
		: version(0), entry(0)
	{
	}

	PROTOCOL_T version;
	REMOTE_ENTRY_T entry;
};


//���� ���ӽ� ��ϵ� ������ �޴´�.
//	result : ���
//	servertime : ������ ����ð�
//	udpport : ������ udp port
struct stNetC2S_CORE_SIGN_UP_ACK
{
	stNetC2S_CORE_SIGN_UP_ACK()
		: result(0), servertime(0), udpport(0)
	{
	}

	RESULT_T result;
	TIME_T servertime;
	ADDR_PORT udpport;
};


//�� protocol�� UDP ��Ŷ �ֻ� ��ġ�� �ּ���.(�νĹ���)
//���� ���縦 ���� peer ���� ����Ÿ ����
//	remoteTo : �������� �Ҵ���� Ÿ���� host id
//	context : reliable / unreliable
//	msg : ���޹޾ƾ� �ϴ� ����Ÿ�� ��� �����̳�
//[encrypt] CORE_UDP_RELAY_SERVER_TO_PEER_NTF(HOSTID remoteTo, PACKET_CONTEXT context, CMsg msg)
//������ �� Client���� ping�� üũ�Ѵ�.
//	servertime : ������ ����ð�
struct stNetC2S_CORE_HEART_BEAT_REQ
{
	stNetC2S_CORE_HEART_BEAT_REQ()
		: servertime(0)
	{
	}

	TIME_T servertime;
};


//������ ���� ���� ��Ŷ�� client�� �״�� �����ش�.
//	servertime : ��Ŷ�� �������� ������ �ð�
struct stNetC2S_CORE_HEART_BEAT_ACK
{
	stNetC2S_CORE_HEART_BEAT_ACK()
		: servertime(0)
	{
	}

	TIME_T servertime;
};


//group members info
//	group : join�� group�� id
//	peerinfo : group �ɹ��� ����(�Ʒ� ����)
//		remote : group �ɹ��� �������� �Ҵ���� �ڽ��� host id
//		publicIP : group �ɹ��� public ip
//		publicPort : group �ɹ��� public port
//		privateIP : group �ɹ��� private ip
//		privatePort : group �ɹ��� private port
struct stNetC2S_CORE_JOIN_GROUP_NTF
{
	stNetC2S_CORE_JOIN_GROUP_NTF()
		: group(0)
	{
	}

	P2PGROUPID group;
	std::vector<NetCore::stRemoteEndpoint> peerinfo;
};


//group�� �ڽ��� info�� ����
//	group : join�� group�� id
//	peerinfo : group �ɹ��� ����(�Ʒ� ����)
//		remote : group �ɹ��� �������� �Ҵ���� �ڽ��� host id
//		publicIP : group �ɹ��� public ip
//		publicPort : group �ɹ��� public port
//		privateIP : group �ɹ��� private ip
//		privatePort : group �ɹ��� private port
struct stNetC2S_CORE_ENTER_GROUP_NTF
{
	stNetC2S_CORE_ENTER_GROUP_NTF()
		: group(0)
	{
	}

	P2PGROUPID group;
	std::vector<NetCore::stRemoteEndpoint> peerinfo;
};


//leave group �ֺ��� �뺸
//	group : join�� group�� id
//	remote : �������� �Ҵ���� �ڽ��� host id
struct stNetC2S_CORE_LEAVE_GROUP_NTF
{
	stNetC2S_CORE_LEAVE_GROUP_NTF()
		: group(0), remote(0)
	{
	}

	P2PGROUPID group;
	HOSTID remote;
};


//���� hole punching
//	remote : �������� �Ҵ���� �ڽ��� host id
//	privateIP : client���� Ȯ���� �ڽ��� ip
//	privatePort : client���� Ȯ���� �ڽ��� port
struct stNetC2S_CORE_UDP_HOLE_PUNCHING_SERVER_REQ
{
	stNetC2S_CORE_UDP_HOLE_PUNCHING_SERVER_REQ()
		: remote(0), privateIP(0), privatePort(0)
	{
	}

	HOSTID remote;
	ADDR_IP privateIP;
	ADDR_PORT privatePort;
};


//[udp,encrypt] CORE_UDP_HOLE_PUNCHING_SERVER_REQ(HOSTID remote)
//���� hole punching ���
struct stNetC2S_CORE_UDP_HOLE_PUNCHING_SERVER_ACK
{
	stNetC2S_CORE_UDP_HOLE_PUNCHING_SERVER_ACK()
	{
	}

};


//��� peer ���� Ȧ��Ī���� �غ� �Ǿ��ٰ� ������Ʋ ���� �����Ѵ�.
//	remoteTos : ���(����) peer
struct stNetC2S_CORE_HOLE_PUNCHING_PEER_READY_REQ
{
	stNetC2S_CORE_HOLE_PUNCHING_PEER_READY_REQ()
	{
	}

	std::vector<NetCore::stRemote> remoteTos;
};


//��� peer �� ���� Ȧ��Ī���� �غ� �Ǿ��ٰ� ������Ʋ ���� ���޹޴´�.
//	remoteFrom : ���(����) peer
struct stNetC2S_CORE_HOLE_PUNCHING_PEER_READY_NTF
{
	stNetC2S_CORE_HOLE_PUNCHING_PEER_READY_NTF()
		: remoteFrom(0)
	{
	}

	HOSTID remoteFrom;
};


//peer ���� hole punching ����� ������ �˸���.
//	result : ���
//	remoteFrom : Ȧ��Ī�� �õ��ϴ� host(�������� �Ҵ���� �ڽ��� host id)
//	remoteTo : �������� �Ҵ���� Ÿ���� host id
struct stNetC2S_CORE_HOLE_PUNCHING_PEER_RESULT_NTF
{
	stNetC2S_CORE_HOLE_PUNCHING_PEER_RESULT_NTF()
		: result(0), remoteFrom(0), remoteTo(0)
	{
	}

	RESULT_T result;
	HOSTID remoteFrom;
	HOSTID remoteTo;
};
