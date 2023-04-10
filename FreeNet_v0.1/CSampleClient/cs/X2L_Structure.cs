
using System;
using System.Collections.Generic;

namespace X2L
{

	//�������� ��û
	//	account : ������
	//	password : �н�����
	//	phone : ��ȭ��ȣ
	//	bank : ����
	//	recommender : ��õ ����
	public class stX2L_AC_REGIST_REQ : IDisposable
	{
		public string account;
		public string password;
		public string phone;
		public string bank;
		public string recommender;

		public void Dispose()
		{
		}

		public void Recv(FreeNet.CPacket msgRecv)
		{
			msgRecv.Decrypt();

			msgRecv.reset_pos(0);
			this.account = msgRecv.pop_string();
			this.password = msgRecv.pop_string();
			this.phone = msgRecv.pop_string();
			this.bank = msgRecv.pop_string();
			this.recommender = msgRecv.pop_string();
		}

		public void Send(FreeNet.CUserToken token)
		{
			FreeNet.CPacket msgSend = FreeNet.CPacket.create((ushort)X2L.PROTOCOL.X2L_AC_REGIST_REQ, 1);
			msgSend.push(account);
			msgSend.push(password);
			msgSend.push(phone);
			msgSend.push(bank);
			msgSend.push(recommender);

			msgSend.Encrypt();
			token.send(msgSend);
		}
	}//..AC_REGIST_REQ;

	//�������� ��û�� ���� ����
	//	result : ���� �����
	public class stX2L_AC_REGIST_ACK : IDisposable
	{
		public UInt16 result;

		public void Dispose()
		{
		}

		public void Recv(FreeNet.CPacket msgRecv)
		{
			msgRecv.Decrypt();

			msgRecv.reset_pos(0);
			this.result = msgRecv.pop((UInt16)0);
		}

		public void Send(FreeNet.CUserToken token)
		{
			FreeNet.CPacket msgSend = FreeNet.CPacket.create((ushort)X2L.PROTOCOL.X2L_AC_REGIST_ACK, 1);
			msgSend.push(result);

			msgSend.Encrypt();
			token.send(msgSend);
		}
	}//..AC_REGIST_ACK;

	//�α��� ��û
	//	account : ������
	//	password : �н�����
	//	version : protocol version
	public class stX2L_AC_LOGIN_REQ : IDisposable
	{
		public string account;
		public string password;
		public UInt32 version;

		public void Dispose()
		{
		}

		public void Recv(FreeNet.CPacket msgRecv)
		{
			msgRecv.Decrypt();

			msgRecv.reset_pos(0);
			this.account = msgRecv.pop_string();
			this.password = msgRecv.pop_string();
			this.version = msgRecv.pop((UInt32)0);
		}

		public void Send(FreeNet.CUserToken token)
		{
			FreeNet.CPacket msgSend = FreeNet.CPacket.create((ushort)X2L.PROTOCOL.X2L_AC_LOGIN_REQ, 1);
			msgSend.push(account);
			msgSend.push(password);
			msgSend.push(version);

			msgSend.Encrypt();
			token.send(msgSend);
		}
	}//..AC_LOGIN_REQ;

	//�α��� ��û�� ���� ����
	//	result : ���� �����
	//	duplicated : 0:����, 1:�ߺ�����
	//	masterkey : master���� ���� ����Ű ( game������ ������ �� �ʿ�)
	//	game : Game������ ���� ���� ����Ʈ ( �Ⱥ����� ��쵵 �ֱ⶧���� vector ��� )
	//		ip
	//		portUdp
	public class stX2L_AC_LOGIN_ACK : IDisposable
	{
		public UInt16 result;
		public UInt16 duplicated;
		public string masterkey;
		public List<CSampleClient.CRemoteServerInfo> game = new List<CSampleClient.CRemoteServerInfo>();

		public void Dispose()
		{
			game.Clear();
		}

		public void Recv(FreeNet.CPacket msgRecv)
		{
			msgRecv.Decrypt();

			msgRecv.reset_pos(0);
			this.result = msgRecv.pop((UInt16)0);
			this.duplicated = msgRecv.pop((UInt16)0);
			this.masterkey = msgRecv.pop_string();
			FreeNet.CPacket.pop<CSampleClient.CRemoteServerInfo>(game, ref msgRecv);
		}

		public void Send(FreeNet.CUserToken token)
		{
			FreeNet.CPacket msgSend = FreeNet.CPacket.create((ushort)X2L.PROTOCOL.X2L_AC_LOGIN_ACK, 1);
			msgSend.push(result);
			msgSend.push(duplicated);
			msgSend.push(masterkey);
			FreeNet.CPacket.push<CSampleClient.CRemoteServerInfo>(game, ref msgSend);

			msgSend.Encrypt();
			token.send(msgSend);
		}
	}//..AC_LOGIN_ACK;

	//���� �ߺ� üũ��û
	//	account : ������
	public class stX2L_AC_DUPLICATE_CHECK_REQ : IDisposable
	{
		public string account;

		public void Dispose()
		{
		}

		public void Recv(FreeNet.CPacket msgRecv)
		{
			msgRecv.Decrypt();

			msgRecv.reset_pos(0);
			this.account = msgRecv.pop_string();
		}

		public void Send(FreeNet.CUserToken token)
		{
			FreeNet.CPacket msgSend = FreeNet.CPacket.create((ushort)X2L.PROTOCOL.X2L_AC_DUPLICATE_CHECK_REQ, 1);
			msgSend.push(account);

			msgSend.Encrypt();
			token.send(msgSend);
		}
	}//..AC_DUPLICATE_CHECK_REQ;

	//���� �ߺ� üũ��û�� ���� ����
	//	result : ���� �����
	public class stX2L_AC_DUPLICATE_CHECK_ACK : IDisposable
	{
		public UInt16 result;

		public void Dispose()
		{
		}

		public void Recv(FreeNet.CPacket msgRecv)
		{
			msgRecv.Decrypt();

			msgRecv.reset_pos(0);
			this.result = msgRecv.pop((UInt16)0);
		}

		public void Send(FreeNet.CUserToken token)
		{
			FreeNet.CPacket msgSend = FreeNet.CPacket.create((ushort)X2L.PROTOCOL.X2L_AC_DUPLICATE_CHECK_ACK, 1);
			msgSend.push(result);

			msgSend.Encrypt();
			token.send(msgSend);
		}
	}//..AC_DUPLICATE_CHECK_ACK;

	//��õ�� üũ��û
	//	account : ������
	public class stX2L_AC_RECOMMENDER_CHECK_REQ : IDisposable
	{
		public string account;

		public void Dispose()
		{
		}

		public void Recv(FreeNet.CPacket msgRecv)
		{
			msgRecv.Decrypt();

			msgRecv.reset_pos(0);
			this.account = msgRecv.pop_string();
		}

		public void Send(FreeNet.CUserToken token)
		{
			FreeNet.CPacket msgSend = FreeNet.CPacket.create((ushort)X2L.PROTOCOL.X2L_AC_RECOMMENDER_CHECK_REQ, 1);
			msgSend.push(account);

			msgSend.Encrypt();
			token.send(msgSend);
		}
	}//..AC_RECOMMENDER_CHECK_REQ;

	//��õ�� üũ��û�� ���� ����
	//	result : ���� �����
	public class stX2L_AC_RECOMMENDER_CHECK_ACK : IDisposable
	{
		public UInt16 result;

		public void Dispose()
		{
		}

		public void Recv(FreeNet.CPacket msgRecv)
		{
			msgRecv.Decrypt();

			msgRecv.reset_pos(0);
			this.result = msgRecv.pop((UInt16)0);
		}

		public void Send(FreeNet.CUserToken token)
		{
			FreeNet.CPacket msgSend = FreeNet.CPacket.create((ushort)X2L.PROTOCOL.X2L_AC_RECOMMENDER_CHECK_ACK, 1);
			msgSend.push(result);

			msgSend.Encrypt();
			token.send(msgSend);
		}
	}//..AC_RECOMMENDER_CHECK_ACK;

} //..namespace X2L
