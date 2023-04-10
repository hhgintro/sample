#pragma once



//NetCore.h로 이동함
//peer hole punching
//	remoteFrom : 홀펀칭을 시도하는 host(서버에서 할당받은 자신의 host id)
//	remoteTo : 서버에서 할당받은 타인의 host id
//	bpublic : enPrivateAttempt ??, enPublicAttempt ?? (public으로 홀펀칭 시도인가?)
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


//NetCore.h로 이동함
//peer hole punching 결과
//	remoteFrom : 홀펀칭을 시도하는 host(서버에서 할당받은 자신의 host id)
//	remoteTo : 서버에서 할당받은 타인의 host id
//	bpublic : enPrivateAttempt ??, enPublicAttempt ?? (public으로 홀펀칭 시도인가?)
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
