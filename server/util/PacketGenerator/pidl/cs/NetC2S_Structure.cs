
using System;
using System.Collections.Generic;

namespace NetC2S
{

	//���� ������ �Ϸ��
	//	remote : �������� �Ҵ���� �ڽ��� host id
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

	//���� ���ӽ� ��ϵ� ������ ��û�Ѵ�.
	//	ver : protocol ����
	//	entry : client�� Ÿ��( user client, login, game, master, etc)
	//	serverTcpPort : ������ ������ �ڽŵ� ������ ����� �Ҷ� port
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

	//���� ���ӽ� ��ϵ� ������ �޴´�.
	//	result : ���
	//	servertime : ������ ����ð�
	//	udpport : ������ udp port
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

	//�� protocol�� UDP ��Ŷ �ֻ� ��ġ�� �ּ���.(�νĹ���)
	//���� ���縦 ���� peer ���� ����Ÿ ����
	//	remoteTo : �������� �Ҵ���� Ÿ���� host id
	//	context : reliable / unreliable
	//	msg : ���޹޾ƾ� �ϴ� ����Ÿ�� ��� �����̳�
	//[encrypt] CORE_UDP_RELAY_SERVER_TO_PEER_NTF(HOSTID remoteTo, PACKET_CONTEXT context, CMsg msg)
	//������ �� Client���� ping�� üũ�Ѵ�.
	//	servertime : ������ ����ð�
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

	//������ ���� ���� ��Ŷ�� client�� �״�� �����ش�.
	//	servertime : ��Ŷ�� �������� ������ �ð�
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
	//	group : join�� group�� id
	//	peerinfo : group �ɹ��� ����(�Ʒ� ����)
	//		remote : group �ɹ��� �������� �Ҵ���� �ڽ��� host id
	//		publicIP : group �ɹ��� public ip
	//		publicPort : group �ɹ��� public port
	//		privateIP : group �ɹ��� private ip
	//		privatePort : group �ɹ��� private port
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

	//group�� �ڽ��� info�� ����
	//	group : join�� group�� id
	//	peerinfo : group �ɹ��� ����(�Ʒ� ����)
	//		remote : group �ɹ��� �������� �Ҵ���� �ڽ��� host id
	//		publicIP : group �ɹ��� public ip
	//		publicPort : group �ɹ��� public port
	//		privateIP : group �ɹ��� private ip
	//		privatePort : group �ɹ��� private port
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

	//leave group �ֺ��� �뺸
	//	group : join�� group�� id
	//	remote : �������� �Ҵ���� �ڽ��� host id
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

	//���� hole punching
	//	remote : �������� �Ҵ���� �ڽ��� host id
	//	privateIP : client���� Ȯ���� �ڽ��� ip
	//	privatePort : client���� Ȯ���� �ڽ��� port
	//	serverTcpPort : client�� ������ ������ �� ��� tcp port(not using)
	//	serverUdpPort : client�� ������ ������ �� ��� udp port(not using)
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

	//���� hole punching ���
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

	//��� peer ���� Ȧ��Ī���� �غ� �Ǿ��ٰ� ������Ʋ ���� �����Ѵ�.
	//	remoteTos : ���(����) peer
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

	//��� peer �� ���� Ȧ��Ī���� �غ� �Ǿ��ٰ� ������Ʋ ���� ���޹޴´�.
	//	remoteFrom : ���(����) peer
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

	//peer ���� hole punching ����� ������ �˸���.
	//	result : ���
	//	remoteFrom : Ȧ��Ī�� �õ��ϴ� host(�������� �Ҵ���� �ڽ��� host id)
	//	remoteTo : �������� �Ҵ���� Ÿ���� host id
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
