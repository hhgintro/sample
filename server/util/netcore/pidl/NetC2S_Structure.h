#pragma once



//서버 접속이 완료됨
//	remote : 서버에서 할당받은 자신의 host id
//	winUsers : 사용자 환전가능금액
//	checking : enum CHECK_SERVER ( not using )
//	serviceinfo : 등록된 서비스 정보
struct stNetC2S_CORE_CONNECT_COMPLETED_NTF
{
	stNetC2S_CORE_CONNECT_COMPLETED_NTF()
		: remote(0)
	{
	}

	HOSTID remote;
};


//서버 접속시 등록된 정보를 요청한다.
//	ver : protocol 버전
//	entry : client의 타입( user client, login, game, master, etc)
//	serverTcpPort : 서버에 접속한 자신도 서버의 기능을 할때 port
//[encrypt] CORE_SIGN_UP_REQ(PROTOCOL_T version, REMOTE_ENTRY_T entry, ADDR_PORT serverTcpPort, std::vector<NetCore::stRemoteEndpoint> peerinfo)
struct stNetC2S_CORE_SIGN_UP_REQ
{
	stNetC2S_CORE_SIGN_UP_REQ()
		: version(0), entry(0), serverTcpPort(0)
	{
	}

	PROTOCOL_T version;
	REMOTE_ENTRY_T entry;
	ADDR_PORT serverTcpPort;
};


//서버 접속시 등록된 정보를 받는다.
//	result : 결과
//	servertime : 서버의 현재시간
//	udpport : 서버의 udp port
//[encrypt] CORE_SIGN_UP_ACK(RESULT_T result, TIME_T servertime, ADDR_PORT udpport, std::vector<NetCore::stRemoteEndpoint> peerinfo)
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


//이 protocol은 UDP 패킷 최상에 위치해 주세요.(인식문제)
//서버 중재를 통한 peer 간의 데이타 전송
//	remoteTo : 서버에서 할당받은 타인의 host id
//	context : reliable / unreliable
//	msg : 전달받아야 하는 데이타를 담는 컨테이너
//[encrypt] CORE_UDP_RELAY_SERVER_TO_PEER_NTF(HOSTID remoteTo, PACKET_CONTEXT context, CMsg msg)
//서버가 각 Client에게 ping을 체크한다.
//	servertime : 서버의 현재시간
struct stNetC2S_CORE_HEART_BEAT_REQ
{
	stNetC2S_CORE_HEART_BEAT_REQ()
		: servertime(0)
	{
	}

	TIME_T servertime;
};


//서버로 부터 받은 패킷을 client는 그대로 돌려준다.
//	servertime : 패킷을 보낼때의 서버의 시간
struct stNetC2S_CORE_HEART_BEAT_ACK
{
	stNetC2S_CORE_HEART_BEAT_ACK()
		: servertime(0)
	{
	}

	TIME_T servertime;
};


//group members info
//	group : join한 group의 id
//	peerinfo : group 맴버의 정보(아래 참조)
//		remote : group 맴버의 서버에서 할당받은 자신의 host id
//		publicIP : group 맴버의 public ip
//		publicPort : group 맴버의 public port
//		privateIP : group 맴버의 private ip
//		privatePort : group 맴버의 private port
struct stNetC2S_CORE_JOIN_GROUP_NTF
{
	stNetC2S_CORE_JOIN_GROUP_NTF()
		: group(0)
	{
	}

	P2PGROUPID group;
	std::vector<NetCore::stRemoteEndpoint> peerinfo;
};


//group에 자신의 info를 전송
//	group : join한 group의 id
//	peerinfo : group 맴버의 정보(아래 참조)
//		remote : group 맴버의 서버에서 할당받은 자신의 host id
//		publicIP : group 맴버의 public ip
//		publicPort : group 맴버의 public port
//		privateIP : group 맴버의 private ip
//		privatePort : group 맴버의 private port
struct stNetC2S_CORE_ENTER_GROUP_NTF
{
	stNetC2S_CORE_ENTER_GROUP_NTF()
		: group(0)
	{
	}

	P2PGROUPID group;
	std::vector<NetCore::stRemoteEndpoint> peerinfo;
};


//leave group 주변에 통보
//	group : join한 group의 id
//	remote : 서버에서 할당받은 자신의 host id
struct stNetC2S_CORE_LEAVE_GROUP_NTF
{
	stNetC2S_CORE_LEAVE_GROUP_NTF()
		: group(0), remote(0)
	{
	}

	P2PGROUPID group;
	HOSTID remote;
};


//서버 hole punching
//	remote : 서버에서 할당받은 자신의 host id
//	privateIP : client에서 확인한 자신의 ip
//	privatePort : client에서 확인한 자신의 port
//	serverTcpPort : client가 서버의 역할을 할 경우 tcp port(not using)
//	serverUdpPort : client가 서버의 역할을 할 경우 udp port(not using)
//[udp,encrypt] CORE_UDP_HOLE_PUNCHING_SERVER_REQ(HOSTID remote, ADDR_IP privateIP, ADDR_PORT privatePort, ADDR_PORT serverTcpPort, ADDR_PORT serverUdpPort)
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


//서버 hole punching 결과
struct stNetC2S_CORE_UDP_HOLE_PUNCHING_SERVER_ACK
{
	stNetC2S_CORE_UDP_HOLE_PUNCHING_SERVER_ACK()
	{
	}

};


//상대 peer 에게 홀펀칭받은 준비가 되었다고 서버로틀 통해 전달한다.
//	remoteTos : 상대(받을) peer
struct stNetC2S_CORE_HOLE_PUNCHING_PEER_READY_REQ
{
	stNetC2S_CORE_HOLE_PUNCHING_PEER_READY_REQ()
	{
	}

	std::vector<NetCore::stRemote> remoteTos;
};


//상대 peer 로 부터 홀펀칭받은 준비가 되었다고 서버로틀 통해 전달받는다.
//	remoteFrom : 상대(보낸) peer
struct stNetC2S_CORE_HOLE_PUNCHING_PEER_READY_NTF
{
	stNetC2S_CORE_HOLE_PUNCHING_PEER_READY_NTF()
		: remoteFrom(0)
	{
	}

	HOSTID remoteFrom;
};


//peer 간의 hole punching 결과를 서버에 알린다.
//	result : 결과
//	remoteFrom : 홀펀칭을 시도하는 host(서버에서 할당받은 자신의 host id)
//	remoteTo : 서버에서 할당받은 타인의 host id
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
