
using System;
using System.Collections.Generic;

namespace X2G
{

	//GAME ���� ���� ���� ��û
	//	account : ������
	//	masterkey : master���� ���� ����Ű ( balance������ ���� �޾Ҵ�.)
	//	version : protocol version
	public class stX2G_AC_CERTIFY_REQ : IDisposable
	{
		public string account;
		public string masterkey;
		public UInt32 version;

		public void Dispose()
		{
		}

		public void Recv(FreeNet.CPacket msgRecv)
		{
			msgRecv.Decrypt();

			msgRecv.reset_pos(0);
			this.account = msgRecv.pop_string();
			this.masterkey = msgRecv.pop_string();
			this.version = msgRecv.pop((UInt32)0);
		}

		public void Send(FreeNet.CUserToken token)
		{
			FreeNet.CPacket msgSend = FreeNet.CPacket.create((ushort)X2G.PROTOCOL.X2G_AC_CERTIFY_REQ, 1);
			msgSend.push(account);
			msgSend.push(masterkey);
			msgSend.push(version);

			msgSend.Encrypt();
			token.send(msgSend);
		}
	}//..AC_CERTIFY_REQ;

	//GAME ���� ���� ���� ��û�� ���� ����
	//	result : ���� �����
	//	servertime : ������ ����ð�
	//	info : ����� �⺻���� ( �Ⱥ����� ��쵵 �ֱ⶧���� vector ��� )
	public class stX2G_AC_CERTIFY_ACK : IDisposable
	{
		public UInt16 result;
		public UInt64 servertime;
		public List<CSampleClient.CCertifyInfo> info = new List<CSampleClient.CCertifyInfo>();

		public void Dispose()
		{
			info.Clear();
		}

		public void Recv(FreeNet.CPacket msgRecv)
		{
			msgRecv.Decrypt();

			msgRecv.reset_pos(0);
			this.result = msgRecv.pop((UInt16)0);
			this.servertime = msgRecv.pop((UInt64)0);
			FreeNet.CPacket.pop<CSampleClient.CCertifyInfo>(info, ref msgRecv);
		}

		public void Send(FreeNet.CUserToken token)
		{
			FreeNet.CPacket msgSend = FreeNet.CPacket.create((ushort)X2G.PROTOCOL.X2G_AC_CERTIFY_ACK, 1);
			msgSend.push(result);
			msgSend.push(servertime);
			FreeNet.CPacket.push<CSampleClient.CCertifyInfo>(info, ref msgSend);

			msgSend.Encrypt();
			token.send(msgSend);
		}
	}//..AC_CERTIFY_ACK;

	//GAME ���� ���� ���� �뺸(�ߺ����� Ȯ�θ޽���)
	//	result : ���� �����
	public class stX2G_AC_CERTIFY_NTF : IDisposable
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
			FreeNet.CPacket msgSend = FreeNet.CPacket.create((ushort)X2G.PROTOCOL.X2G_AC_CERTIFY_NTF, 1);
			msgSend.push(result);

			msgSend.Encrypt();
			token.send(msgSend);
		}
	}//..AC_CERTIFY_NTF;

	//�������� �����û
	//	nickname : ����
	//	old_pass : old �н�����
	//	new_pass : new �н�����
	//	phone : ��ȭ��ȣ
	//	bank : ���¹�ȣ
	public class stX2G_AC_ACOUNT_CHANGE_REQ : IDisposable
	{
		public string nickname;
		public string old_pass;
		public string new_pass;
		public string phone;
		public string bank;

		public void Dispose()
		{
		}

		public void Recv(FreeNet.CPacket msgRecv)
		{
			msgRecv.Decrypt();

			msgRecv.reset_pos(0);
			this.nickname = msgRecv.pop_string();
			this.old_pass = msgRecv.pop_string();
			this.new_pass = msgRecv.pop_string();
			this.phone = msgRecv.pop_string();
			this.bank = msgRecv.pop_string();
		}

		public void Send(FreeNet.CUserToken token)
		{
			FreeNet.CPacket msgSend = FreeNet.CPacket.create((ushort)X2G.PROTOCOL.X2G_AC_ACOUNT_CHANGE_REQ, 1);
			msgSend.push(nickname);
			msgSend.push(old_pass);
			msgSend.push(new_pass);
			msgSend.push(phone);
			msgSend.push(bank);

			msgSend.Encrypt();
			token.send(msgSend);
		}
	}//..AC_ACOUNT_CHANGE_REQ;

	//�������� �����û�� ���� ����
	//	result : ���� �����
	public class stX2G_AC_ACOUNT_CHANGE_ACK : IDisposable
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
			FreeNet.CPacket msgSend = FreeNet.CPacket.create((ushort)X2G.PROTOCOL.X2G_AC_ACOUNT_CHANGE_ACK, 1);
			msgSend.push(result);

			msgSend.Encrypt();
			token.send(msgSend);
		}
	}//..AC_ACOUNT_CHANGE_ACK;

	//�渶 ���� ��û
	public class stX2G_RC_GAME_ENTER_REQ : IDisposable
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
			FreeNet.CPacket msgSend = FreeNet.CPacket.create((ushort)X2G.PROTOCOL.X2G_RC_GAME_ENTER_REQ, 1);

			msgSend.Encrypt();
			token.send(msgSend);
		}
	}//..RC_GAME_ENTER_REQ;

	//�渶 ���� ��û�� ���� ����
	//	result : ���� �����
	//	remaintime : �����ð�(����:ms, �������̸� ����������� �����ð�, ������̸� �������ý��۱��� �����ð�)
	//	raceinfo : ��������(�������� ������� ���� - �Ⱥ����� ��쵵 �ֱ⶧���� vector ���)
	//	dividendinfo : �������
	//	users : ���������ڼ�
	public class stX2G_RC_GAME_ENTER_ACK : IDisposable
	{
		public UInt16 result;
		public UInt32 remaintime;
		public List<CSampleClient.CRaceInfo4Client> raceinfo = new List<CSampleClient.CRaceInfo4Client>();
		public List<CSampleClient.CDividend> dividendinfo = new List<CSampleClient.CDividend>();
		public UInt16 users;

		public void Dispose()
		{
			raceinfo.Clear();
			dividendinfo.Clear();
		}

		public void Recv(FreeNet.CPacket msgRecv)
		{
			msgRecv.Decrypt();

			msgRecv.reset_pos(0);
			this.result = msgRecv.pop((UInt16)0);
			this.remaintime = msgRecv.pop((UInt32)0);
			FreeNet.CPacket.pop<CSampleClient.CRaceInfo4Client>(raceinfo, ref msgRecv);
			FreeNet.CPacket.pop<CSampleClient.CDividend>(dividendinfo, ref msgRecv);
			this.users = msgRecv.pop((UInt16)0);
		}

		public void Send(FreeNet.CUserToken token)
		{
			FreeNet.CPacket msgSend = FreeNet.CPacket.create((ushort)X2G.PROTOCOL.X2G_RC_GAME_ENTER_ACK, 1);
			msgSend.push(result);
			msgSend.push(remaintime);
			FreeNet.CPacket.push<CSampleClient.CRaceInfo4Client>(raceinfo, ref msgSend);
			FreeNet.CPacket.push<CSampleClient.CDividend>(dividendinfo, ref msgSend);
			msgSend.push(users);

			msgSend.Encrypt();
			token.send(msgSend);
		}
	}//..RC_GAME_ENTER_ACK;

	//�渶 ���� ��û
	public class stX2G_RC_GAME_LEAVE_REQ : IDisposable
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
			FreeNet.CPacket msgSend = FreeNet.CPacket.create((ushort)X2G.PROTOCOL.X2G_RC_GAME_LEAVE_REQ, 1);

			msgSend.Encrypt();
			token.send(msgSend);
		}
	}//..RC_GAME_LEAVE_REQ;

	//�渶 ���� ��û�� ���� ����
	//	result : ���� �����
	public class stX2G_RC_GAME_LEAVE_ACK : IDisposable
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
			FreeNet.CPacket msgSend = FreeNet.CPacket.create((ushort)X2G.PROTOCOL.X2G_RC_GAME_LEAVE_ACK, 1);
			msgSend.push(result);

			msgSend.Encrypt();
			token.send(msgSend);
		}
	}//..RC_GAME_LEAVE_ACK;

	//���� ���� �뺸(�渶���� ����� ������ ���۵Ǹ� �ڵ��뺸)
	//	raceinfo : race ����
	//	dividendinfo : �������
	//	users : ���������ڼ�
	public class stX2G_RC_BETING_START_NTF : IDisposable
	{
		public List<CSampleClient.CRaceInfo4Client> raceinfo = new List<CSampleClient.CRaceInfo4Client>();
		public List<CSampleClient.CDividend> dividendinfo = new List<CSampleClient.CDividend>();
		public UInt16 users;

		public void Dispose()
		{
			raceinfo.Clear();
			dividendinfo.Clear();
		}

		public void Recv(FreeNet.CPacket msgRecv)
		{
			msgRecv.Decrypt();

			msgRecv.reset_pos(0);
			FreeNet.CPacket.pop<CSampleClient.CRaceInfo4Client>(raceinfo, ref msgRecv);
			FreeNet.CPacket.pop<CSampleClient.CDividend>(dividendinfo, ref msgRecv);
			this.users = msgRecv.pop((UInt16)0);
		}

		public void Send(FreeNet.CUserToken token)
		{
			FreeNet.CPacket msgSend = FreeNet.CPacket.create((ushort)X2G.PROTOCOL.X2G_RC_BETING_START_NTF, 1);
			FreeNet.CPacket.push<CSampleClient.CRaceInfo4Client>(raceinfo, ref msgSend);
			FreeNet.CPacket.push<CSampleClient.CDividend>(dividendinfo, ref msgSend);
			msgSend.push(users);

			msgSend.Encrypt();
			token.send(msgSend);
		}
	}//..RC_BETING_START_NTF;

	//GAME step �뺸
	//	gamestep : 1-���ý���, 2-�渶����, 3-����(struct GAME_STEP ����)
	public class stX2G_RC_GAMESTEP_NTF : IDisposable
	{
		public byte gamestep;

		public void Dispose()
		{
		}

		public void Recv(FreeNet.CPacket msgRecv)
		{
			msgRecv.Decrypt();

			msgRecv.reset_pos(0);
			this.gamestep = msgRecv.pop((byte)0);
		}

		public void Send(FreeNet.CUserToken token)
		{
			FreeNet.CPacket msgSend = FreeNet.CPacket.create((ushort)X2G.PROTOCOL.X2G_RC_GAMESTEP_NTF, 1);
			msgSend.push(gamestep);

			msgSend.Encrypt();
			token.send(msgSend);
		}
	}//..RC_GAMESTEP_NTF;

	//��� �뺸
	//	dividendinfo : �������
	public class stX2G_RC_DIVIDEND_NTF : IDisposable
	{
		public List<CSampleClient.CDividend> dividendinfo = new List<CSampleClient.CDividend>();

		public void Dispose()
		{
			dividendinfo.Clear();
		}

		public void Recv(FreeNet.CPacket msgRecv)
		{
			msgRecv.Decrypt();

			msgRecv.reset_pos(0);
			FreeNet.CPacket.pop<CSampleClient.CDividend>(dividendinfo, ref msgRecv);
		}

		public void Send(FreeNet.CUserToken token)
		{
			FreeNet.CPacket msgSend = FreeNet.CPacket.create((ushort)X2G.PROTOCOL.X2G_RC_DIVIDEND_NTF, 1);
			FreeNet.CPacket.push<CSampleClient.CDividend>(dividendinfo, ref msgSend);

			msgSend.Encrypt();
			token.send(msgSend);
		}
	}//..RC_DIVIDEND_NTF;

	//���� ��û( ������ �����Ǹ� ���� ����� ������ �����Ѵ�. )
	//	vecSingle : type 0:�ܽ�, 1:����, 2:����, 3:������ ( struct BET_TYPE )
	//	vecDouble : �ֽ�
	//	vecTriple : �ﺹ��
	// addBet : ����� �߰� ���� ����
	public class stX2G_RC_BET_COIN_REQ : IDisposable
	{
		public List<CSampleClient.CBetSingle> vecSingle = new List<CSampleClient.CBetSingle>();
		public List<CSampleClient.CBetDouble> vecDouble = new List<CSampleClient.CBetDouble>();
		public List<CSampleClient.CBetTriple> vecTriple = new List<CSampleClient.CBetTriple>();
		public Int32 addBet;

		public void Dispose()
		{
			vecSingle.Clear();
			vecDouble.Clear();
			vecTriple.Clear();
		}

		public void Recv(FreeNet.CPacket msgRecv)
		{
			msgRecv.Decrypt();

			msgRecv.reset_pos(0);
			FreeNet.CPacket.pop<CSampleClient.CBetSingle>(vecSingle, ref msgRecv);
			FreeNet.CPacket.pop<CSampleClient.CBetDouble>(vecDouble, ref msgRecv);
			FreeNet.CPacket.pop<CSampleClient.CBetTriple>(vecTriple, ref msgRecv);
			this.addBet = msgRecv.pop((Int32)0);
		}

		public void Send(FreeNet.CUserToken token)
		{
			FreeNet.CPacket msgSend = FreeNet.CPacket.create((ushort)X2G.PROTOCOL.X2G_RC_BET_COIN_REQ, 1);
			FreeNet.CPacket.push<CSampleClient.CBetSingle>(vecSingle, ref msgSend);
			FreeNet.CPacket.push<CSampleClient.CBetDouble>(vecDouble, ref msgSend);
			FreeNet.CPacket.push<CSampleClient.CBetTriple>(vecTriple, ref msgSend);
			msgSend.push(addBet);

			msgSend.Encrypt();
			token.send(msgSend);
		}
	}//..RC_BET_COIN_REQ;

	//���� ��û�� ���� ����
	//	result : ���� �����
	//	winTotal : �� ���ͱ�
	//	money : ���� �����ݾ� ( �Ⱥ����� ��쵵 �ֱ⶧���� vector ��� )
	//	vecSingle : win ��������(�ܽ�, ����)
	//	vecDouble : win ��������(����, �ֽ�)
	//	vecTriple : win ��������(�ﺹ��)
	public class stX2G_RC_BET_COIN_ACK : IDisposable
	{
		public UInt16 result;
		public Int32 winTotal;
		public List<CSampleClient.CAccountMoney> money = new List<CSampleClient.CAccountMoney>();
		public List<CSampleClient.CBetResultSingle> vecSingle = new List<CSampleClient.CBetResultSingle>();
		public List<CSampleClient.CBetResultDouble> vecDouble = new List<CSampleClient.CBetResultDouble>();
		public List<CSampleClient.CBetResultTriple> vecTriple = new List<CSampleClient.CBetResultTriple>();

		public void Dispose()
		{
			money.Clear();
			vecSingle.Clear();
			vecDouble.Clear();
			vecTriple.Clear();
		}

		public void Recv(FreeNet.CPacket msgRecv)
		{
			msgRecv.Decrypt();

			msgRecv.reset_pos(0);
			this.result = msgRecv.pop((UInt16)0);
			this.winTotal = msgRecv.pop((Int32)0);
			FreeNet.CPacket.pop<CSampleClient.CAccountMoney>(money, ref msgRecv);
			FreeNet.CPacket.pop<CSampleClient.CBetResultSingle>(vecSingle, ref msgRecv);
			FreeNet.CPacket.pop<CSampleClient.CBetResultDouble>(vecDouble, ref msgRecv);
			FreeNet.CPacket.pop<CSampleClient.CBetResultTriple>(vecTriple, ref msgRecv);
		}

		public void Send(FreeNet.CUserToken token)
		{
			FreeNet.CPacket msgSend = FreeNet.CPacket.create((ushort)X2G.PROTOCOL.X2G_RC_BET_COIN_ACK, 1);
			msgSend.push(result);
			msgSend.push(winTotal);
			FreeNet.CPacket.push<CSampleClient.CAccountMoney>(money, ref msgSend);
			FreeNet.CPacket.push<CSampleClient.CBetResultSingle>(vecSingle, ref msgSend);
			FreeNet.CPacket.push<CSampleClient.CBetResultDouble>(vecDouble, ref msgSend);
			FreeNet.CPacket.push<CSampleClient.CBetResultTriple>(vecTriple, ref msgSend);

			msgSend.Encrypt();
			token.send(msgSend);
		}
	}//..RC_BET_COIN_ACK;

	//��ǰ�� ���� ��û
	// gift : ������ ��ǰ �ݾ�
	public class stX2G_RC_GIFT_EJECT_REQ : IDisposable
	{
		public Int32 gift;

		public void Dispose()
		{
		}

		public void Recv(FreeNet.CPacket msgRecv)
		{
			msgRecv.Decrypt();

			msgRecv.reset_pos(0);
			this.gift = msgRecv.pop((Int32)0);
		}

		public void Send(FreeNet.CUserToken token)
		{
			FreeNet.CPacket msgSend = FreeNet.CPacket.create((ushort)X2G.PROTOCOL.X2G_RC_GIFT_EJECT_REQ, 1);
			msgSend.push(gift);

			msgSend.Encrypt();
			token.send(msgSend);
		}
	}//..RC_GIFT_EJECT_REQ;

	//��ǰ�� ���� ��û�� ���� ����
	//	result : ���� �����
	//	money : ���� �����ݾ� ( �Ⱥ����� ��쵵 �ֱ⶧���� vector ��� )
	public class stX2G_RC_GIFT_EJECT_ACK : IDisposable
	{
		public UInt16 result;
		public List<CSampleClient.CAccountMoney> money = new List<CSampleClient.CAccountMoney>();

		public void Dispose()
		{
			money.Clear();
		}

		public void Recv(FreeNet.CPacket msgRecv)
		{
			msgRecv.Decrypt();

			msgRecv.reset_pos(0);
			this.result = msgRecv.pop((UInt16)0);
			FreeNet.CPacket.pop<CSampleClient.CAccountMoney>(money, ref msgRecv);
		}

		public void Send(FreeNet.CUserToken token)
		{
			FreeNet.CPacket msgSend = FreeNet.CPacket.create((ushort)X2G.PROTOCOL.X2G_RC_GIFT_EJECT_ACK, 1);
			msgSend.push(result);
			FreeNet.CPacket.push<CSampleClient.CAccountMoney>(money, ref msgSend);

			msgSend.Encrypt();
			token.send(msgSend);
		}
	}//..RC_GIFT_EJECT_ACK;

	//��� ��û
	public class stX2G_RC_RECORD_REQ : IDisposable
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
			FreeNet.CPacket msgSend = FreeNet.CPacket.create((ushort)X2G.PROTOCOL.X2G_RC_RECORD_REQ, 1);

			msgSend.Encrypt();
			token.send(msgSend);
		}
	}//..RC_RECORD_REQ;

	//��� ��û�� ���� ����
	//	result : ���� �����
	//	record : ������� ( �Ⱥ����� ��쵵 �ֱ⶧���� vector ��� )
	public class stX2G_RC_RECORD_ACK : IDisposable
	{
		public UInt16 result;
		public List<CSampleClient.CRecordInfo> record = new List<CSampleClient.CRecordInfo>();

		public void Dispose()
		{
			record.Clear();
		}

		public void Recv(FreeNet.CPacket msgRecv)
		{
			msgRecv.Decrypt();

			msgRecv.reset_pos(0);
			this.result = msgRecv.pop((UInt16)0);
			FreeNet.CPacket.pop<CSampleClient.CRecordInfo>(record, ref msgRecv);
		}

		public void Send(FreeNet.CUserToken token)
		{
			FreeNet.CPacket msgSend = FreeNet.CPacket.create((ushort)X2G.PROTOCOL.X2G_RC_RECORD_ACK, 1);
			msgSend.push(result);
			FreeNet.CPacket.push<CSampleClient.CRecordInfo>(record, ref msgSend);

			msgSend.Encrypt();
			token.send(msgSend);
		}
	}//..RC_RECORD_ACK;

	//����� �� �����뺸
	//	credit : ���� ���� credit( + bonus ���� )
	//	win : ���� ���� win
	public class stX2G_RC_MONEY_NTF : IDisposable
	{
		public List<CSampleClient.CAccountMoney> money = new List<CSampleClient.CAccountMoney>();

		public void Dispose()
		{
			money.Clear();
		}

		public void Recv(FreeNet.CPacket msgRecv)
		{
			msgRecv.Decrypt();

			msgRecv.reset_pos(0);
			FreeNet.CPacket.pop<CSampleClient.CAccountMoney>(money, ref msgRecv);
		}

		public void Send(FreeNet.CUserToken token)
		{
			FreeNet.CPacket msgSend = FreeNet.CPacket.create((ushort)X2G.PROTOCOL.X2G_RC_MONEY_NTF, 1);
			FreeNet.CPacket.push<CSampleClient.CAccountMoney>(money, ref msgSend);

			msgSend.Encrypt();
			token.send(msgSend);
		}
	}//..RC_MONEY_NTF;

	//����� �渶 ���� �α׿�û
	//	racepk : ���ֹ�ȣ
	//	page : page(0~ : ùpage)
	//	pagenum : page�� ����
	public class stX2G_RC_LOG_ACCOUNT_BET_REQ : IDisposable
	{
		public UInt32 racepk;

		public void Dispose()
		{
		}

		public void Recv(FreeNet.CPacket msgRecv)
		{
			msgRecv.Decrypt();

			msgRecv.reset_pos(0);
			this.racepk = msgRecv.pop((UInt32)0);
		}

		public void Send(FreeNet.CUserToken token)
		{
			FreeNet.CPacket msgSend = FreeNet.CPacket.create((ushort)X2G.PROTOCOL.X2G_RC_LOG_ACCOUNT_BET_REQ, 1);
			msgSend.push(racepk);

			msgSend.Encrypt();
			token.send(msgSend);
		}
	}//..RC_LOG_ACCOUNT_BET_REQ;

	//����� �渶 ���� �α׿�û�� ���� ����
	//	result : ���� �����
	//	moneys : ������ ������
	//	totalwin : total win
	//	bets : ���� ���
	public class stX2G_RC_LOG_ACCOUNT_BET_ACK : IDisposable
	{
		public UInt16 result;
		public List<CSampleClient.CAccountMoney> moneys = new List<CSampleClient.CAccountMoney>();
		public Int32 totalwin;
		public List<CSampleClient.CLogAccountBetSelect> bets = new List<CSampleClient.CLogAccountBetSelect>();

		public void Dispose()
		{
			moneys.Clear();
			bets.Clear();
		}

		public void Recv(FreeNet.CPacket msgRecv)
		{
			msgRecv.Decrypt();

			msgRecv.reset_pos(0);
			this.result = msgRecv.pop((UInt16)0);
			FreeNet.CPacket.pop<CSampleClient.CAccountMoney>(moneys, ref msgRecv);
			this.totalwin = msgRecv.pop((Int32)0);
			FreeNet.CPacket.pop<CSampleClient.CLogAccountBetSelect>(bets, ref msgRecv);
		}

		public void Send(FreeNet.CUserToken token)
		{
			FreeNet.CPacket msgSend = FreeNet.CPacket.create((ushort)X2G.PROTOCOL.X2G_RC_LOG_ACCOUNT_BET_ACK, 1);
			msgSend.push(result);
			FreeNet.CPacket.push<CSampleClient.CAccountMoney>(moneys, ref msgSend);
			msgSend.push(totalwin);
			FreeNet.CPacket.push<CSampleClient.CLogAccountBetSelect>(bets, ref msgSend);

			msgSend.Encrypt();
			token.send(msgSend);
		}
	}//..RC_LOG_ACCOUNT_BET_ACK;

	//�渶 ������� �뺸( RC_LOG_ACCOUNT_BET_REQ �޾����� �����ش� )
	//	dividends : �������
	public class stX2G_RC_LOG_DIVIDEND_NTF : IDisposable
	{
		public List<CSampleClient.CDividend> dividends = new List<CSampleClient.CDividend>();

		public void Dispose()
		{
			dividends.Clear();
		}

		public void Recv(FreeNet.CPacket msgRecv)
		{
			msgRecv.Decrypt();

			msgRecv.reset_pos(0);
			FreeNet.CPacket.pop<CSampleClient.CDividend>(dividends, ref msgRecv);
		}

		public void Send(FreeNet.CUserToken token)
		{
			FreeNet.CPacket msgSend = FreeNet.CPacket.create((ushort)X2G.PROTOCOL.X2G_RC_LOG_DIVIDEND_NTF, 1);
			FreeNet.CPacket.push<CSampleClient.CDividend>(dividends, ref msgSend);

			msgSend.Encrypt();
			token.send(msgSend);
		}
	}//..RC_LOG_DIVIDEND_NTF;

	//�渶 �α� ��Ͽ�û
	//	page : page(0~ : ùpage)
	//	pagenum : page�� ����
	public class stX2G_RC_LOG_RACE_REQ : IDisposable
	{
		public UInt16 page;
		public byte pagenum;

		public void Dispose()
		{
		}

		public void Recv(FreeNet.CPacket msgRecv)
		{
			msgRecv.Decrypt();

			msgRecv.reset_pos(0);
			this.page = msgRecv.pop((UInt16)0);
			this.pagenum = msgRecv.pop((byte)0);
		}

		public void Send(FreeNet.CUserToken token)
		{
			FreeNet.CPacket msgSend = FreeNet.CPacket.create((ushort)X2G.PROTOCOL.X2G_RC_LOG_RACE_REQ, 1);
			msgSend.push(page);
			msgSend.push(pagenum);

			msgSend.Encrypt();
			token.send(msgSend);
		}
	}//..RC_LOG_RACE_REQ;

	//�渶 �α� ��Ͽ�û�� ���� ����
	//	result : ���� �����
	//	total : �� �׸񰳼�
	//	page : page(0~ : ùpage)
	//	races : �渶 �α� ���
	public class stX2G_RC_LOG_RACE_ACK : IDisposable
	{
		public UInt16 result;
		public UInt16 total;
		public UInt16 page;
		public List<CSampleClient.CLogRaceSelect> races = new List<CSampleClient.CLogRaceSelect>();

		public void Dispose()
		{
			races.Clear();
		}

		public void Recv(FreeNet.CPacket msgRecv)
		{
			msgRecv.Decrypt();

			msgRecv.reset_pos(0);
			this.result = msgRecv.pop((UInt16)0);
			this.total = msgRecv.pop((UInt16)0);
			this.page = msgRecv.pop((UInt16)0);
			FreeNet.CPacket.pop<CSampleClient.CLogRaceSelect>(races, ref msgRecv);
		}

		public void Send(FreeNet.CUserToken token)
		{
			FreeNet.CPacket msgSend = FreeNet.CPacket.create((ushort)X2G.PROTOCOL.X2G_RC_LOG_RACE_ACK, 1);
			msgSend.push(result);
			msgSend.push(total);
			msgSend.push(page);
			FreeNet.CPacket.push<CSampleClient.CLogRaceSelect>(races, ref msgSend);

			msgSend.Encrypt();
			token.send(msgSend);
		}
	}//..RC_LOG_RACE_ACK;

	//����� ����� ������û
	//	page : page(0~ : ùpage)
	//	pagenum : page�� ����
	public class stX2G_RC_MONEY_DEPOSIT_LIST_REQ : IDisposable
	{
		public UInt16 page;
		public byte pagenum;

		public void Dispose()
		{
		}

		public void Recv(FreeNet.CPacket msgRecv)
		{
			msgRecv.Decrypt();

			msgRecv.reset_pos(0);
			this.page = msgRecv.pop((UInt16)0);
			this.pagenum = msgRecv.pop((byte)0);
		}

		public void Send(FreeNet.CUserToken token)
		{
			FreeNet.CPacket msgSend = FreeNet.CPacket.create((ushort)X2G.PROTOCOL.X2G_RC_MONEY_DEPOSIT_LIST_REQ, 1);
			msgSend.push(page);
			msgSend.push(pagenum);

			msgSend.Encrypt();
			token.send(msgSend);
		}
	}//..RC_MONEY_DEPOSIT_LIST_REQ;

	//����� ����� ������û�� ���� ����
	//	result : ���� �����
	//	total : �� �׸񰳼�
	//	page : page(0~ : ùpage)
	//	deposits : ����� ��û ���
	public class stX2G_RC_MONEY_DEPOSIT_LIST_ACK : IDisposable
	{
		public UInt16 result;
		public UInt16 total;
		public UInt16 page;
		public List<CSampleClient.CMemoDepositSelect> deposits = new List<CSampleClient.CMemoDepositSelect>();

		public void Dispose()
		{
			deposits.Clear();
		}

		public void Recv(FreeNet.CPacket msgRecv)
		{
			msgRecv.Decrypt();

			msgRecv.reset_pos(0);
			this.result = msgRecv.pop((UInt16)0);
			this.total = msgRecv.pop((UInt16)0);
			this.page = msgRecv.pop((UInt16)0);
			FreeNet.CPacket.pop<CSampleClient.CMemoDepositSelect>(deposits, ref msgRecv);
		}

		public void Send(FreeNet.CUserToken token)
		{
			FreeNet.CPacket msgSend = FreeNet.CPacket.create((ushort)X2G.PROTOCOL.X2G_RC_MONEY_DEPOSIT_LIST_ACK, 1);
			msgSend.push(result);
			msgSend.push(total);
			msgSend.push(page);
			FreeNet.CPacket.push<CSampleClient.CMemoDepositSelect>(deposits, ref msgSend);

			msgSend.Encrypt();
			token.send(msgSend);
		}
	}//..RC_MONEY_DEPOSIT_LIST_ACK;

	//����� ��û
	//	type : 0�Ա�, 1:���
	//	add_credit : ����� ��û�ݾ�
	//	bank : ����
	//	bank_account : ���� ����ڸ�
	public class stX2G_RC_MONEY_DEPOSIT_INSERT_REQ : IDisposable
	{
		public byte type;
		public Int32 add_credit;
		public string bank;
		public string bank_account;

		public void Dispose()
		{
		}

		public void Recv(FreeNet.CPacket msgRecv)
		{
			msgRecv.Decrypt();

			msgRecv.reset_pos(0);
			this.type = msgRecv.pop((byte)0);
			this.add_credit = msgRecv.pop((Int32)0);
			this.bank = msgRecv.pop_string();
			this.bank_account = msgRecv.pop_string();
		}

		public void Send(FreeNet.CUserToken token)
		{
			FreeNet.CPacket msgSend = FreeNet.CPacket.create((ushort)X2G.PROTOCOL.X2G_RC_MONEY_DEPOSIT_INSERT_REQ, 1);
			msgSend.push(type);
			msgSend.push(add_credit);
			msgSend.push(bank);
			msgSend.push(bank_account);

			msgSend.Encrypt();
			token.send(msgSend);
		}
	}//..RC_MONEY_DEPOSIT_INSERT_REQ;

	//����� ��û�� ���� ����
	//	result : ���� �����
	public class stX2G_RC_MONEY_DEPOSIT_INSERT_ACK : IDisposable
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
			FreeNet.CPacket msgSend = FreeNet.CPacket.create((ushort)X2G.PROTOCOL.X2G_RC_MONEY_DEPOSIT_INSERT_ACK, 1);
			msgSend.push(result);

			msgSend.Encrypt();
			token.send(msgSend);
		}
	}//..RC_MONEY_DEPOSIT_INSERT_ACK;

	//QnA(����) ��Ͽ�û
	//	page : page(0~ : ùpage)
	//	pagenum : page�� ����
	public class stX2G_RC_QNA_LIST_REQ : IDisposable
	{
		public UInt16 page;
		public byte pagenum;

		public void Dispose()
		{
		}

		public void Recv(FreeNet.CPacket msgRecv)
		{
			msgRecv.Decrypt();

			msgRecv.reset_pos(0);
			this.page = msgRecv.pop((UInt16)0);
			this.pagenum = msgRecv.pop((byte)0);
		}

		public void Send(FreeNet.CUserToken token)
		{
			FreeNet.CPacket msgSend = FreeNet.CPacket.create((ushort)X2G.PROTOCOL.X2G_RC_QNA_LIST_REQ, 1);
			msgSend.push(page);
			msgSend.push(pagenum);

			msgSend.Encrypt();
			token.send(msgSend);
		}
	}//..RC_QNA_LIST_REQ;

	//QnA(����) ��Ͽ�û�� ���� ����
	//	result : ���� �����
	//	total : �� �׸񰳼�
	//	page : page(0~ : ùpage)
	//	qnas : ����� ��û ���
	public class stX2G_RC_QNA_LIST_ACK : IDisposable
	{
		public UInt16 result;
		public UInt16 total;
		public UInt16 page;
		public List<CSampleClient.CMemoQnASelect> qnas = new List<CSampleClient.CMemoQnASelect>();

		public void Dispose()
		{
			qnas.Clear();
		}

		public void Recv(FreeNet.CPacket msgRecv)
		{
			msgRecv.Decrypt();

			msgRecv.reset_pos(0);
			this.result = msgRecv.pop((UInt16)0);
			this.total = msgRecv.pop((UInt16)0);
			this.page = msgRecv.pop((UInt16)0);
			FreeNet.CPacket.pop<CSampleClient.CMemoQnASelect>(qnas, ref msgRecv);
		}

		public void Send(FreeNet.CUserToken token)
		{
			FreeNet.CPacket msgSend = FreeNet.CPacket.create((ushort)X2G.PROTOCOL.X2G_RC_QNA_LIST_ACK, 1);
			msgSend.push(result);
			msgSend.push(total);
			msgSend.push(page);
			FreeNet.CPacket.push<CSampleClient.CMemoQnASelect>(qnas, ref msgSend);

			msgSend.Encrypt();
			token.send(msgSend);
		}
	}//..RC_QNA_LIST_ACK;

	//QnA(����) ��Ͽ�û
	//	qna : ��������
	public class stX2G_RC_QNA_INSERT_REQ : IDisposable
	{
		public string qna;

		public void Dispose()
		{
		}

		public void Recv(FreeNet.CPacket msgRecv)
		{
			msgRecv.Decrypt();

			msgRecv.reset_pos(0);
			this.qna = msgRecv.pop_string();
		}

		public void Send(FreeNet.CUserToken token)
		{
			FreeNet.CPacket msgSend = FreeNet.CPacket.create((ushort)X2G.PROTOCOL.X2G_RC_QNA_INSERT_REQ, 1);
			msgSend.push(qna);

			msgSend.Encrypt();
			token.send(msgSend);
		}
	}//..RC_QNA_INSERT_REQ;

	//QnA(����) ��Ͽ�û��û�� ���� ����
	//	result : ���� �����
	public class stX2G_RC_QNA_INSERT_ACK : IDisposable
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
			FreeNet.CPacket msgSend = FreeNet.CPacket.create((ushort)X2G.PROTOCOL.X2G_RC_QNA_INSERT_ACK, 1);
			msgSend.push(result);

			msgSend.Encrypt();
			token.send(msgSend);
		}
	}//..RC_QNA_INSERT_ACK;

	//QnA(����) ��� ��Ͽ�û
	//	board : ��� �׷� id
	//	qna : ��������
	public class stX2G_RC_QNA_COMMENT_REQ : IDisposable
	{
		public UInt32 board;
		public string qna;

		public void Dispose()
		{
		}

		public void Recv(FreeNet.CPacket msgRecv)
		{
			msgRecv.Decrypt();

			msgRecv.reset_pos(0);
			this.board = msgRecv.pop((UInt32)0);
			this.qna = msgRecv.pop_string();
		}

		public void Send(FreeNet.CUserToken token)
		{
			FreeNet.CPacket msgSend = FreeNet.CPacket.create((ushort)X2G.PROTOCOL.X2G_RC_QNA_COMMENT_REQ, 1);
			msgSend.push(board);
			msgSend.push(qna);

			msgSend.Encrypt();
			token.send(msgSend);
		}
	}//..RC_QNA_COMMENT_REQ;

	//QnA(����) ��� ��Ͽ�û�� ���� ����
	//	result : ���� �����
	public class stX2G_RC_QNA_COMMENT_ACK : IDisposable
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
			FreeNet.CPacket msgSend = FreeNet.CPacket.create((ushort)X2G.PROTOCOL.X2G_RC_QNA_COMMENT_ACK, 1);
			msgSend.push(result);

			msgSend.Encrypt();
			token.send(msgSend);
		}
	}//..RC_QNA_COMMENT_ACK;

	//QnA(����) ������û
	//	memopk : �޸� ��ȣ
	public class stX2G_RC_QNA_DELETE_REQ : IDisposable
	{
		public UInt32 memopk;

		public void Dispose()
		{
		}

		public void Recv(FreeNet.CPacket msgRecv)
		{
			msgRecv.Decrypt();

			msgRecv.reset_pos(0);
			this.memopk = msgRecv.pop((UInt32)0);
		}

		public void Send(FreeNet.CUserToken token)
		{
			FreeNet.CPacket msgSend = FreeNet.CPacket.create((ushort)X2G.PROTOCOL.X2G_RC_QNA_DELETE_REQ, 1);
			msgSend.push(memopk);

			msgSend.Encrypt();
			token.send(msgSend);
		}
	}//..RC_QNA_DELETE_REQ;

	//QnA(����) ������û�� ���� ����
	//	result : ���� �����
	public class stX2G_RC_QNA_DELETE_ACK : IDisposable
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
			FreeNet.CPacket msgSend = FreeNet.CPacket.create((ushort)X2G.PROTOCOL.X2G_RC_QNA_DELETE_ACK, 1);
			msgSend.push(result);

			msgSend.Encrypt();
			token.send(msgSend);
		}
	}//..RC_QNA_DELETE_ACK;

	//����ݹ� QnA �����뺸( ���� RC_MEMO_CHECK_REQ ��û����)
	//	result : ���� �����(�ǹ̾��� ����)
	public class stX2G_RC_MEMO_INSERT_NTF : IDisposable
	{
		public byte result;

		public void Dispose()
		{
		}

		public void Recv(FreeNet.CPacket msgRecv)
		{
			msgRecv.Decrypt();

			msgRecv.reset_pos(0);
			this.result = msgRecv.pop((byte)0);
		}

		public void Send(FreeNet.CUserToken token)
		{
			FreeNet.CPacket msgSend = FreeNet.CPacket.create((ushort)X2G.PROTOCOL.X2G_RC_MEMO_INSERT_NTF, 1);
			msgSend.push(result);

			msgSend.Encrypt();
			token.send(msgSend);
		}
	}//..RC_MEMO_INSERT_NTF;

	//QnA(����) �ִ밳����û
	//	depositpk : ���������� üũ�� ����� pk
	//	qnapk : ���������� üũ�� QnA pk
	public class stX2G_RC_MEMO_CHECK_REQ : IDisposable
	{
		public UInt32 depositpk;
		public UInt32 qnapk;

		public void Dispose()
		{
		}

		public void Recv(FreeNet.CPacket msgRecv)
		{
			msgRecv.Decrypt();

			msgRecv.reset_pos(0);
			this.depositpk = msgRecv.pop((UInt32)0);
			this.qnapk = msgRecv.pop((UInt32)0);
		}

		public void Send(FreeNet.CUserToken token)
		{
			FreeNet.CPacket msgSend = FreeNet.CPacket.create((ushort)X2G.PROTOCOL.X2G_RC_MEMO_CHECK_REQ, 1);
			msgSend.push(depositpk);
			msgSend.push(qnapk);

			msgSend.Encrypt();
			token.send(msgSend);
		}
	}//..RC_MEMO_CHECK_REQ;

	//QnA(����) �ִ밳����û�� ���� ����
	//	result : ���� �����
	//	depositpk : ���������� �߰��� ����� pk
	//	deposit : ���������� üũ�� ����� ����, ��� ����� ��
	//	qnapk : ���������� �߰��� QnA pk
	//	qna : ���������� üũ�� QnA ����, ��� QnA ��
	public class stX2G_RC_MEMO_CHECK_ACK : IDisposable
	{
		public UInt16 result;
		public UInt32 depositpk;
		public UInt16 deposit;
		public UInt32 qnapk;
		public UInt16 qna;

		public void Dispose()
		{
		}

		public void Recv(FreeNet.CPacket msgRecv)
		{
			msgRecv.Decrypt();

			msgRecv.reset_pos(0);
			this.result = msgRecv.pop((UInt16)0);
			this.depositpk = msgRecv.pop((UInt32)0);
			this.deposit = msgRecv.pop((UInt16)0);
			this.qnapk = msgRecv.pop((UInt32)0);
			this.qna = msgRecv.pop((UInt16)0);
		}

		public void Send(FreeNet.CUserToken token)
		{
			FreeNet.CPacket msgSend = FreeNet.CPacket.create((ushort)X2G.PROTOCOL.X2G_RC_MEMO_CHECK_ACK, 1);
			msgSend.push(result);
			msgSend.push(depositpk);
			msgSend.push(deposit);
			msgSend.push(qnapk);
			msgSend.push(qna);

			msgSend.Encrypt();
			token.send(msgSend);
		}
	}//..RC_MEMO_CHECK_ACK;

	//��(week) ���� ���� ��û
	//	qnapk : QnA pk
	public class stX2G_RC_CALCULATE_MONEY_REQ : IDisposable
	{
		public UInt32 qnapk;

		public void Dispose()
		{
		}

		public void Recv(FreeNet.CPacket msgRecv)
		{
			msgRecv.Decrypt();

			msgRecv.reset_pos(0);
			this.qnapk = msgRecv.pop((UInt32)0);
		}

		public void Send(FreeNet.CUserToken token)
		{
			FreeNet.CPacket msgSend = FreeNet.CPacket.create((ushort)X2G.PROTOCOL.X2G_RC_CALCULATE_MONEY_REQ, 1);
			msgSend.push(qnapk);

			msgSend.Encrypt();
			token.send(msgSend);
		}
	}//..RC_CALCULATE_MONEY_REQ;

	//��(week) ���� ���� ��û�� ���� ����
	//	result : ���� �����
	//	money : ���� �����ݾ� ( �Ⱥ����� ��쵵 �ֱ⶧���� vector ��� )
	public class stX2G_RC_CALCULATE_MONEY_ACK : IDisposable
	{
		public UInt16 result;
		public List<CSampleClient.CAccountMoney> money = new List<CSampleClient.CAccountMoney>();

		public void Dispose()
		{
			money.Clear();
		}

		public void Recv(FreeNet.CPacket msgRecv)
		{
			msgRecv.Decrypt();

			msgRecv.reset_pos(0);
			this.result = msgRecv.pop((UInt16)0);
			FreeNet.CPacket.pop<CSampleClient.CAccountMoney>(money, ref msgRecv);
		}

		public void Send(FreeNet.CUserToken token)
		{
			FreeNet.CPacket msgSend = FreeNet.CPacket.create((ushort)X2G.PROTOCOL.X2G_RC_CALCULATE_MONEY_ACK, 1);
			msgSend.push(result);
			FreeNet.CPacket.push<CSampleClient.CAccountMoney>(money, ref msgSend);

			msgSend.Encrypt();
			token.send(msgSend);
		}
	}//..RC_CALCULATE_MONEY_ACK;

	//��/��� client ��ü�� �뺸(GM --> account)
	//	type : 0:�Ա�, 1:���
	//	target : �����
	//	add_credit : ��/��� �ݾ�
	public class stX2G_RC_DEPOSIT_ALL_NTF : IDisposable
	{
		public byte type;
		public string target;
		public Int32 add_credit;

		public void Dispose()
		{
		}

		public void Recv(FreeNet.CPacket msgRecv)
		{
			msgRecv.Decrypt();

			msgRecv.reset_pos(0);
			this.type = msgRecv.pop((byte)0);
			this.target = msgRecv.pop_string();
			this.add_credit = msgRecv.pop((Int32)0);
		}

		public void Send(FreeNet.CUserToken token)
		{
			FreeNet.CPacket msgSend = FreeNet.CPacket.create((ushort)X2G.PROTOCOL.X2G_RC_DEPOSIT_ALL_NTF, 1);
			msgSend.push(type);
			msgSend.push(target);
			msgSend.push(add_credit);

			msgSend.Encrypt();
			token.send(msgSend);
		}
	}//..RC_DEPOSIT_ALL_NTF;

	//�ְ� ��÷�� client ��ü�� �뺸(trace --> game)
	//	account : ��÷��
	//	win : ��÷��
	public class stX2G_RC_HIGHEST_WIN_ALL_NTF : IDisposable
	{
		public string account;
		public Int32 win;

		public void Dispose()
		{
		}

		public void Recv(FreeNet.CPacket msgRecv)
		{
			msgRecv.Decrypt();

			msgRecv.reset_pos(0);
			this.account = msgRecv.pop_string();
			this.win = msgRecv.pop((Int32)0);
		}

		public void Send(FreeNet.CUserToken token)
		{
			FreeNet.CPacket msgSend = FreeNet.CPacket.create((ushort)X2G.PROTOCOL.X2G_RC_HIGHEST_WIN_ALL_NTF, 1);
			msgSend.push(account);
			msgSend.push(win);

			msgSend.Encrypt();
			token.send(msgSend);
		}
	}//..RC_HIGHEST_WIN_ALL_NTF;

	//���� ��Ͽ�û
	//	page : page(0~ : ùpage)
	//	pagenum : page�� ����
	public class stX2G_RC_NOTICE_LIST_REQ : IDisposable
	{
		public UInt16 page;
		public byte pagenum;

		public void Dispose()
		{
		}

		public void Recv(FreeNet.CPacket msgRecv)
		{
			msgRecv.Decrypt();

			msgRecv.reset_pos(0);
			this.page = msgRecv.pop((UInt16)0);
			this.pagenum = msgRecv.pop((byte)0);
		}

		public void Send(FreeNet.CUserToken token)
		{
			FreeNet.CPacket msgSend = FreeNet.CPacket.create((ushort)X2G.PROTOCOL.X2G_RC_NOTICE_LIST_REQ, 1);
			msgSend.push(page);
			msgSend.push(pagenum);

			msgSend.Encrypt();
			token.send(msgSend);
		}
	}//..RC_NOTICE_LIST_REQ;

	//���� ��Ͽ�û�� ���� ����
	//	result : ���� �����
	//	total : �� �׸񰳼�
	//	page : page(0~ : ùpage)
	//	notices : ���� ���
	public class stX2G_RC_NOTICE_LIST_ACK : IDisposable
	{
		public UInt16 result;
		public UInt16 total;
		public UInt16 page;
		public List<CSampleClient.CNoticeSelect> notices = new List<CSampleClient.CNoticeSelect>();

		public void Dispose()
		{
			notices.Clear();
		}

		public void Recv(FreeNet.CPacket msgRecv)
		{
			msgRecv.Decrypt();

			msgRecv.reset_pos(0);
			this.result = msgRecv.pop((UInt16)0);
			this.total = msgRecv.pop((UInt16)0);
			this.page = msgRecv.pop((UInt16)0);
			FreeNet.CPacket.pop<CSampleClient.CNoticeSelect>(notices, ref msgRecv);
		}

		public void Send(FreeNet.CUserToken token)
		{
			FreeNet.CPacket msgSend = FreeNet.CPacket.create((ushort)X2G.PROTOCOL.X2G_RC_NOTICE_LIST_ACK, 1);
			msgSend.push(result);
			msgSend.push(total);
			msgSend.push(page);
			FreeNet.CPacket.push<CSampleClient.CNoticeSelect>(notices, ref msgSend);

			msgSend.Encrypt();
			token.send(msgSend);
		}
	}//..RC_NOTICE_LIST_ACK;

	//���� �߰� �뺸
	//	notices : ����
	public class stX2G_RC_NOTICE_INSERT_NTF : IDisposable
	{
		public List<CSampleClient.CNoticeSelect> notices = new List<CSampleClient.CNoticeSelect>();

		public void Dispose()
		{
			notices.Clear();
		}

		public void Recv(FreeNet.CPacket msgRecv)
		{
			msgRecv.Decrypt();

			msgRecv.reset_pos(0);
			FreeNet.CPacket.pop<CSampleClient.CNoticeSelect>(notices, ref msgRecv);
		}

		public void Send(FreeNet.CUserToken token)
		{
			FreeNet.CPacket msgSend = FreeNet.CPacket.create((ushort)X2G.PROTOCOL.X2G_RC_NOTICE_INSERT_NTF, 1);
			FreeNet.CPacket.push<CSampleClient.CNoticeSelect>(notices, ref msgSend);

			msgSend.Encrypt();
			token.send(msgSend);
		}
	}//..RC_NOTICE_INSERT_NTF;

} //..namespace X2G
