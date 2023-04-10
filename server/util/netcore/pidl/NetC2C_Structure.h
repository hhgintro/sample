#pragma once



//NetCore.h�� �̵���
//peer hole punching
//	remoteFrom : Ȧ��Ī�� �õ��ϴ� host(�������� �Ҵ���� �ڽ��� host id)
//	remoteTo : �������� �Ҵ���� Ÿ���� host id
//	bpublic : enPrivateAttempt ??, enPublicAttempt ?? (public���� Ȧ��Ī �õ��ΰ�?)
struct stNetC2C_CORE_UDP_HOLE_PUNCHING_PEER_REQ
{
	stNetC2C_CORE_UDP_HOLE_PUNCHING_PEER_REQ()
		: remoteFrom(0), remoteTo(0), bpublic(0)
	{
	}

	HOSTID remoteFrom;
	HOSTID remoteTo;
	UINT8 bpublic;
};


//NetCore.h�� �̵���
//peer hole punching ���
//	remoteFrom : Ȧ��Ī�� �õ��ϴ� host(�������� �Ҵ���� �ڽ��� host id)
//	remoteTo : �������� �Ҵ���� Ÿ���� host id
//	bpublic : enPrivateAttempt ??, enPublicAttempt ?? (public���� Ȧ��Ī �õ��ΰ�?)
struct stNetC2C_CORE_UDP_HOLE_PUNCHING_PEER_ACK
{
	stNetC2C_CORE_UDP_HOLE_PUNCHING_PEER_ACK()
		: remoteFrom(0), remoteTo(0), bpublic(0)
	{
	}

	HOSTID remoteFrom;
	HOSTID remoteTo;
	UINT8 bpublic;
};
