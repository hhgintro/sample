
using System;
using System.Collections.Generic;

namespace NetC2S
{

	//서버 접속이 완료됨
	//	remote : 서버에서 할당받은 자신의 host id
	public class stNetC2S_CORE_CONNECT_COMPLETED_NTF : IDisposable
	{
		public UInt64 remote;

		public void Dispose()
		{
		}

		public void Recv(FreeNet.CPacket msgRecv)
		{
			msgRecv.Decrypt();

			msgRecv.reset_pos(0);
			this.remote = msgRecv.pop((UInt64)0);
		}

		public void Send(FreeNet.CUserToken token)
		{
			FreeNet.CPacket msgSend = FreeNet.CPacket.create((ushort)NetC2S.PROTOCOL.NetC2S_CORE_CONNECT_COMPLETED_NTF, 1);
			msgSend.push(remote);

			msgSend.Encrypt();
			token.send(msgSend);
		}
	}//..CORE_CONNECT_COMPLETED_NTF;

	//서버 접속시 등록된 정보를 요청한다.
	//	ver : protocol 버전
	//	entry : client의 타입( user client, login, game, master, etc)
	//	serverTcpPort : 서버에 접속한 자신도 서버의 기능을 할때 port
	//[encrypt] CORE_SIGN_UP_REQ(PROTOCOL_T version, REMOTE_ENTRY_T entry, ADDR_PORT serverTcpPort, std::vector<NetCore::stRemoteEndpoint> peerinfo)
	public class stNetC2S_CORE_SIGN_UP_REQ : IDisposable
	{
		public UInt32 version;
		public byte entry;
		public UInt16 serverTcpPort;

		public void Dispose()
		{
		}

		public void Recv(FreeNet.CPacket msgRecv)
		{
			msgRecv.Decrypt();

			msgRecv.reset_pos(0);
			this.version = msgRecv.pop((UInt32)0);
			this.entry = msgRecv.pop((byte)0);
			this.serverTcpPort = msgRecv.pop((UInt16)0);
		}

		public void Send(FreeNet.CUserToken token)
		{
			FreeNet.CPacket msgSend = FreeNet.CPacket.create((ushort)NetC2S.PROTOCOL.NetC2S_CORE_SIGN_UP_REQ, 1);
			msgSend.push(version);
			msgSend.push(entry);
			msgSend.push(serverTcpPort);

			msgSend.Encrypt();
			token.send(msgSend);
		}
	}//..CORE_SIGN_UP_REQ;

	//서버 접속시 등록된 정보를 받는다.
	//	result : 결과
	//	servertime : 서버의 현재시간
	//	udpport : 서버의 udp port
	//[encrypt] CORE_SIGN_UP_ACK(RESULT_T result, TIME_T servertime, ADDR_PORT udpport, std::vector<NetCore::stRemoteEndpoint> peerinfo)
	public class stNetC2S_CORE_SIGN_UP_ACK : IDisposable
	{
		public UInt16 result;
		public UInt64 servertime;
		public UInt16 udpport;

		public void Dispose()
		{
		}

		public void Recv(FreeNet.CPacket msgRecv)
		{
			msgRecv.Decrypt();

			msgRecv.reset_pos(0);
			this.result = msgRecv.pop((UInt16)0);
			this.servertime = msgRecv.pop((UInt64)0);
			this.udpport = msgRecv.pop((UInt16)0);
		}

		public void Send(FreeNet.CUserToken token)
		{
			FreeNet.CPacket msgSend = FreeNet.CPacket.create((ushort)NetC2S.PROTOCOL.NetC2S_CORE_SIGN_UP_ACK, 1);
			msgSend.push(result);
			msgSend.push(servertime);
			msgSend.push(udpport);

			msgSend.Encrypt();
			token.send(msgSend);
		}
	}//..CORE_SIGN_UP_ACK;

	//이 protocol은 UDP 패킷 최상에 위치해 주세요.(인식문제)
	//서버 중재를 통한 peer 간의 데이타 전송
	//	remoteTo : 서버에서 할당받은 타인의 host id
	//	context : reliable / unreliable
	//	msg : 전달받아야 하는 데이타를 담는 컨테이너
	//[encrypt] CORE_UDP_RELAY_SERVER_TO_PEER_NTF(HOSTID remoteTo, PACKET_CONTEXT context, CMsg msg)
	//서버가 각 Client에게 ping을 체크한다.
	//	servertime : 서버의 현재시간
	public class stNetC2S_CORE_HEART_BEAT_REQ : IDisposable
	{
		public UInt64 servertime;

		public void Dispose()
		{
		}

		public void Recv(FreeNet.CPacket msgRecv)
		{
			msgRecv.Decrypt();

			msgRecv.reset_pos(0);
			this.servertime = msgRecv.pop((UInt64)0);
		}

		public void Send(FreeNet.CUserToken token)
		{
			FreeNet.CPacket msgSend = FreeNet.CPacket.create((ushort)NetC2S.PROTOCOL.NetC2S_CORE_HEART_BEAT_REQ, 1);
			msgSend.push(servertime);

			msgSend.Encrypt();
			token.send(msgSend);
		}
	}//..CORE_HEART_BEAT_REQ;

	//서버로 부터 받은 패킷을 client는 그대로 돌려준다.
	//	servertime : 패킷을 보낼때의 서버의 시간
	public class stNetC2S_CORE_HEART_BEAT_ACK : IDisposable
	{
		public UInt64 servertime;

		public void Dispose()
		{
		}

		public void Recv(FreeNet.CPacket msgRecv)
		{
			msgRecv.Decrypt();

			msgRecv.reset_pos(0);
			this.servertime = msgRecv.pop((UInt64)0);
		}

		public void Send(FreeNet.CUserToken token)
		{
			FreeNet.CPacket msgSend = FreeNet.CPacket.create((ushort)NetC2S.PROTOCOL.NetC2S_CORE_HEART_BEAT_ACK, 1);
			msgSend.push(servertime);

			msgSend.Encrypt();
			token.send(msgSend);
		}
	}//..CORE_HEART_BEAT_ACK;

	//group members info
	//	group : join한 group의 id
	//	peerinfo : group 맴버의 정보(아래 참조)
	//		remote : group 맴버의 서버에서 할당받은 자신의 host id
	//		publicIP : group 맴버의 public ip
	//		publicPort : group 맴버의 public port
	//		privateIP : group 맴버의 private ip
	//		privatePort : group 맴버의 private port
	public class stNetC2S_CORE_JOIN_GROUP_NTF : IDisposable
	{
		public UInt64 group;
		public List<FreeNet.stRemoteEndpoint> peerinfo = new List<FreeNet.stRemoteEndpoint>();

		public void Dispose()
		{
			peerinfo.Clear();
		}

		public void Recv(FreeNet.CPacket msgRecv)
		{
			msgRecv.Decrypt();

			msgRecv.reset_pos(0);
			this.group = msgRecv.pop((UInt64)0);
			FreeNet.CPacket.pop<FreeNet.stRemoteEndpoint>(peerinfo, ref msgRecv);
		}

		public void Send(FreeNet.CUserToken token)
		{
			FreeNet.CPacket msgSend = FreeNet.CPacket.create((ushort)NetC2S.PROTOCOL.NetC2S_CORE_JOIN_GROUP_NTF, 1);
			msgSend.push(group);
			FreeNet.CPacket.push<FreeNet.stRemoteEndpoint>(peerinfo, ref msgSend);

			msgSend.Encrypt();
			token.send(msgSend);
		}
	}//..CORE_JOIN_GROUP_NTF;

	//group에 자신의 info를 전송
	//	group : join한 group의 id
	//	peerinfo : group 맴버의 정보(아래 참조)
	//		remote : group 맴버의 서버에서 할당받은 자신의 host id
	//		publicIP : group 맴버의 public ip
	//		publicPort : group 맴버의 public port
	//		privateIP : group 맴버의 private ip
	//		privatePort : group 맴버의 private port
	public class stNetC2S_CORE_ENTER_GROUP_NTF : IDisposable
	{
		public UInt64 group;
		public List<FreeNet.stRemoteEndpoint> peerinfo = new List<FreeNet.stRemoteEndpoint>();

		public void Dispose()
		{
			peerinfo.Clear();
		}

		public void Recv(FreeNet.CPacket msgRecv)
		{
			msgRecv.Decrypt();

			msgRecv.reset_pos(0);
			this.group = msgRecv.pop((UInt64)0);
			FreeNet.CPacket.pop<FreeNet.stRemoteEndpoint>(peerinfo, ref msgRecv);
		}

		public void Send(FreeNet.CUserToken token)
		{
			FreeNet.CPacket msgSend = FreeNet.CPacket.create((ushort)NetC2S.PROTOCOL.NetC2S_CORE_ENTER_GROUP_NTF, 1);
			msgSend.push(group);
			FreeNet.CPacket.push<FreeNet.stRemoteEndpoint>(peerinfo, ref msgSend);

			msgSend.Encrypt();
			token.send(msgSend);
		}
	}//..CORE_ENTER_GROUP_NTF;

	//leave group 주변에 통보
	//	group : join한 group의 id
	//	remote : 서버에서 할당받은 자신의 host id
	public class stNetC2S_CORE_LEAVE_GROUP_NTF : IDisposable
	{
		public UInt64 group;
		public UInt64 remote;

		public void Dispose()
		{
		}

		public void Recv(FreeNet.CPacket msgRecv)
		{
			msgRecv.Decrypt();

			msgRecv.reset_pos(0);
			this.group = msgRecv.pop((UInt64)0);
			this.remote = msgRecv.pop((UInt64)0);
		}

		public void Send(FreeNet.CUserToken token)
		{
			FreeNet.CPacket msgSend = FreeNet.CPacket.create((ushort)NetC2S.PROTOCOL.NetC2S_CORE_LEAVE_GROUP_NTF, 1);
			msgSend.push(group);
			msgSend.push(remote);

			msgSend.Encrypt();
			token.send(msgSend);
		}
	}//..CORE_LEAVE_GROUP_NTF;

	//서버 hole punching
	//	remote : 서버에서 할당받은 자신의 host id
	//	privateIP : client에서 확인한 자신의 ip
	//	privatePort : client에서 확인한 자신의 port
	//	serverTcpPort : client가 서버의 역할을 할 경우 tcp port(not using)
	//	serverUdpPort : client가 서버의 역할을 할 경우 udp port(not using)
	//[udp,encrypt] CORE_UDP_HOLE_PUNCHING_SERVER_REQ(HOSTID remote, ADDR_IP privateIP, ADDR_PORT privatePort, ADDR_PORT serverTcpPort, ADDR_PORT serverUdpPort)
	public class stNetC2S_CORE_UDP_HOLE_PUNCHING_SERVER_REQ : IDisposable
	{
		public UInt64 remote;
		public UInt32 privateIP;
		public UInt16 privatePort;

		public void Dispose()
		{
		}

		public void Recv(FreeNet.CPacket msgRecv)
		{
			msgRecv.Decrypt();

			msgRecv.reset_pos(0);
			this.remote = msgRecv.pop((UInt64)0);
			this.privateIP = msgRecv.pop((UInt32)0);
			this.privatePort = msgRecv.pop((UInt16)0);
		}

		public void Send(FreeNet.CUserToken token)
		{
			FreeNet.CPacket msgSend = FreeNet.CPacket.create((ushort)NetC2S.PROTOCOL.NetC2S_CORE_UDP_HOLE_PUNCHING_SERVER_REQ, 1);
			msgSend.push(remote);
			msgSend.push(privateIP);
			msgSend.push(privatePort);

			msgSend.Encrypt();
			token.send(msgSend);
		}
	}//..CORE_UDP_HOLE_PUNCHING_SERVER_REQ;

	//서버 hole punching 결과
	public class stNetC2S_CORE_UDP_HOLE_PUNCHING_SERVER_ACK : IDisposable
	{

		public void Dispose()
		{
		}

		public void Recv(FreeNet.CPacket msgRecv)
		{
			msgRecv.Decrypt();

			msgRecv.reset_pos(0);
		}

		public void Send(FreeNet.CUserToken token)
		{
			FreeNet.CPacket msgSend = FreeNet.CPacket.create((ushort)NetC2S.PROTOCOL.NetC2S_CORE_UDP_HOLE_PUNCHING_SERVER_ACK, 1);

			msgSend.Encrypt();
			token.send(msgSend);
		}
	}//..CORE_UDP_HOLE_PUNCHING_SERVER_ACK;

	//상대 peer 에게 홀펀칭받은 준비가 되었다고 서버로틀 통해 전달한다.
	//	remoteTos : 상대(받을) peer
	public class stNetC2S_CORE_HOLE_PUNCHING_PEER_READY_REQ : IDisposable
	{
		public List<FreeNet.stRemote> remoteTos = new List<FreeNet.stRemote>();

		public void Dispose()
		{
			remoteTos.Clear();
		}

		public void Recv(FreeNet.CPacket msgRecv)
		{
			msgRecv.Decrypt();

			msgRecv.reset_pos(0);
			FreeNet.CPacket.pop<FreeNet.stRemote>(remoteTos, ref msgRecv);
		}

		public void Send(FreeNet.CUserToken token)
		{
			FreeNet.CPacket msgSend = FreeNet.CPacket.create((ushort)NetC2S.PROTOCOL.NetC2S_CORE_HOLE_PUNCHING_PEER_READY_REQ, 1);
			FreeNet.CPacket.push<FreeNet.stRemote>(remoteTos, ref msgSend);

			msgSend.Encrypt();
			token.send(msgSend);
		}
	}//..CORE_HOLE_PUNCHING_PEER_READY_REQ;

	//상대 peer 로 부터 홀펀칭받은 준비가 되었다고 서버로틀 통해 전달받는다.
	//	remoteFrom : 상대(보낸) peer
	public class stNetC2S_CORE_HOLE_PUNCHING_PEER_READY_NTF : IDisposable
	{
		public UInt64 remoteFrom;

		public void Dispose()
		{
		}

		public void Recv(FreeNet.CPacket msgRecv)
		{
			msgRecv.Decrypt();

			msgRecv.reset_pos(0);
			this.remoteFrom = msgRecv.pop((UInt64)0);
		}

		public void Send(FreeNet.CUserToken token)
		{
			FreeNet.CPacket msgSend = FreeNet.CPacket.create((ushort)NetC2S.PROTOCOL.NetC2S_CORE_HOLE_PUNCHING_PEER_READY_NTF, 1);
			msgSend.push(remoteFrom);

			msgSend.Encrypt();
			token.send(msgSend);
		}
	}//..CORE_HOLE_PUNCHING_PEER_READY_NTF;

	//peer 간의 hole punching 결과를 서버에 알린다.
	//	result : 결과
	//	remoteFrom : 홀펀칭을 시도하는 host(서버에서 할당받은 자신의 host id)
	//	remoteTo : 서버에서 할당받은 타인의 host id
	public class stNetC2S_CORE_HOLE_PUNCHING_PEER_RESULT_NTF : IDisposable
	{
		public UInt16 result;
		public UInt64 remoteFrom;
		public UInt64 remoteTo;

		public void Dispose()
		{
		}

		public void Recv(FreeNet.CPacket msgRecv)
		{
			msgRecv.Decrypt();

			msgRecv.reset_pos(0);
			this.result = msgRecv.pop((UInt16)0);
			this.remoteFrom = msgRecv.pop((UInt64)0);
			this.remoteTo = msgRecv.pop((UInt64)0);
		}

		public void Send(FreeNet.CUserToken token)
		{
			FreeNet.CPacket msgSend = FreeNet.CPacket.create((ushort)NetC2S.PROTOCOL.NetC2S_CORE_HOLE_PUNCHING_PEER_RESULT_NTF, 1);
			msgSend.push(result);
			msgSend.push(remoteFrom);
			msgSend.push(remoteTo);

			msgSend.Encrypt();
			token.send(msgSend);
		}
	}//..CORE_HOLE_PUNCHING_PEER_RESULT_NTF;

} //..namespace NetC2S
