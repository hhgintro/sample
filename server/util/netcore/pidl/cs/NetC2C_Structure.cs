

namespace NetC2C
{

	//NetCore.h�� �̵���
	//peer hole punching
	//	remoteFrom : Ȧ��Ī�� �õ��ϴ� host(�������� �Ҵ���� �ڽ��� host id)
	//	remoteTo : �������� �Ҵ���� Ÿ���� host id
	//	bpublic : enPrivateAttempt ??, enPublicAttempt ?? (public���� Ȧ��Ī �õ��ΰ�?)
	public class stNetC2C_CORE_UDP_HOLE_PUNCHING_PEER_REQ
	{
		public HOSTID remoteFrom;
		public HOSTID remoteTo;
		public UINT8 bpublic;

		public void Recv(FreeNet.CPacket msgRecv)
		{
			UInt16 size = BitConverter.ToUInt16(msgRecv.buffer, FreeNet.Defines.MSG_HEADER_PROTOCOL_SIZE_POS);
			byte[] deBuffer = new byte[size];
			FreeNet.Crypto.Decrypt(msgRecv.buffer, (uint)FreeNet.Defines.MSG_HEADER_SIZE, ref deBuffer, 0, size);
			Array.Copy(deBuffer, 0, msgRecv.buffer, FreeNet.Defines.MSG_HEADER_SIZE, size);

			msgRecv.reset_pos();
			this.remoteFrom = msgRecv.pop((HOSTID)0);
			this.remoteTo = msgRecv.pop((HOSTID)0);
			this.bpublic = msgRecv.pop((UINT8)0);
		}

		public void Send(FreeNet.CUserToken token)
		{
			FreeNet.CPacket msgSend = FreeNet.CPacket.create((ushort)NetC2C.PROTOCOL.NetC2C_CORE_UDP_HOLE_PUNCHING_PEER_REQ, 1);
			msgSend.push(remoteFrom);
			msgSend.push(remoteTo);
			msgSend.push(bpublic);
			token.send(msgSend);
		}
	}//..CORE_UDP_HOLE_PUNCHING_PEER_REQ;

	//NetCore.h�� �̵���
	//peer hole punching ���
	//	remoteFrom : Ȧ��Ī�� �õ��ϴ� host(�������� �Ҵ���� �ڽ��� host id)
	//	remoteTo : �������� �Ҵ���� Ÿ���� host id
	//	bpublic : enPrivateAttempt ??, enPublicAttempt ?? (public���� Ȧ��Ī �õ��ΰ�?)
	public class stNetC2C_CORE_UDP_HOLE_PUNCHING_PEER_ACK
	{
		public HOSTID remoteFrom;
		public HOSTID remoteTo;
		public UINT8 bpublic;

		public void Recv(FreeNet.CPacket msgRecv)
		{
			UInt16 size = BitConverter.ToUInt16(msgRecv.buffer, FreeNet.Defines.MSG_HEADER_PROTOCOL_SIZE_POS);
			byte[] deBuffer = new byte[size];
			FreeNet.Crypto.Decrypt(msgRecv.buffer, (uint)FreeNet.Defines.MSG_HEADER_SIZE, ref deBuffer, 0, size);
			Array.Copy(deBuffer, 0, msgRecv.buffer, FreeNet.Defines.MSG_HEADER_SIZE, size);

			msgRecv.reset_pos();
			this.remoteFrom = msgRecv.pop((HOSTID)0);
			this.remoteTo = msgRecv.pop((HOSTID)0);
			this.bpublic = msgRecv.pop((UINT8)0);
		}

		public void Send(FreeNet.CUserToken token)
		{
			FreeNet.CPacket msgSend = FreeNet.CPacket.create((ushort)NetC2C.PROTOCOL.NetC2C_CORE_UDP_HOLE_PUNCHING_PEER_ACK, 1);
			msgSend.push(remoteFrom);
			msgSend.push(remoteTo);
			msgSend.push(bpublic);
			token.send(msgSend);
		}
	}//..CORE_UDP_HOLE_PUNCHING_PEER_ACK;

} //..namespace NetC2C
