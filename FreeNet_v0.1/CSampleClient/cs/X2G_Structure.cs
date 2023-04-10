
using System;
using System.Collections.Generic;

namespace X2G
{

	//GAME 서버 접속 승인 요청
	//	account : 계정명
	//	masterkey : master서버 접속 인증키 ( balance서버를 통해 받았다.)
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

	//GAME 서버 접속 승인 요청에 대한 응답
	//	result : 응답 결과값
	//	servertime : 서버의 현재시간
	//	info : 사용자 기본정보 ( 안보내는 경우도 있기때문에 vector 사용 )
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

	//GAME 서버 접속 승인 통보(중복접속 확인메시지)
	//	result : 응답 결과값
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

	//개인정보 변경요청
	//	nickname : 별명
	//	old_pass : old 패스워드
	//	new_pass : new 패스워드
	//	phone : 전화변호
	//	bank : 계좌번호
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

	//개인정보 변경요청에 대한 응답
	//	result : 응답 결과값
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

	//경마 입장 요청
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

	//경마 입장 요청에 대한 응답
	//	result : 응답 결과값
	//	remaintime : 남은시간(단위:ms, 배팅중이면 배팅종료까지 남은시간, 경기중이면 다음배팅시작까지 남은시간)
	//	raceinfo : 게임정보(말정보및 경기정보 포함 - 안보내는 경우도 있기때문에 vector 사용)
	//	dividendinfo : 배당정보
	//	users : 동시접속자수
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

	//경마 입장 요청
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

	//경마 입장 요청에 대한 응답
	//	result : 응답 결과값
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

	//배팅 시작 통보(경마입장 대기중 배팅이 시작되면 자동통보)
	//	raceinfo : race 정보
	//	dividendinfo : 배당정보
	//	users : 동시접속자수
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

	//GAME step 통보
	//	gamestep : 1-배팅시작, 2-경마진행, 3-보상(struct GAME_STEP 참조)
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

	//배당 통보
	//	dividendinfo : 배당정보
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

	//배팅 요청( 배팅이 마감되면 배팅 결과를 서버로 전송한다. )
	//	vecSingle : type 0:단식, 1:연식, 2:복식, 3:복연식 ( struct BET_TYPE )
	//	vecDouble : 쌍식
	//	vecTriple : 삼복식
	// addBet : 사용자 추가 배팅 총합
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

	//배팅 요청에 대한 응답
	//	result : 응답 결과값
	//	winTotal : 총 수익금
	//	money : 현재 소지금액 ( 안보내는 경우도 있기때문에 vector 사용 )
	//	vecSingle : win 배팅정보(단식, 연식)
	//	vecDouble : win 배팅정보(복식, 쌍식)
	//	vecTriple : win 배팅정보(삼복식)
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

	//상품권 배출 요청
	// gift : 배출할 상품 금액
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

	//상품권 배출 요청에 대한 응답
	//	result : 응답 결과값
	//	money : 현재 소지금액 ( 안보내는 경우도 있기때문에 vector 사용 )
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

	//통계 요청
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

	//통계 요청에 대한 응답
	//	result : 응답 결과값
	//	record : 통계정보 ( 안보내는 경우도 있기때문에 vector 사용 )
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

	//사용자 돈 변경통보
	//	credit : 현재 소지 credit( + bonus 포함 )
	//	win : 현재 소지 win
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

	//사용자 경마 배팅 로그요청
	//	racepk : 경주번호
	//	page : page(0~ : 첫page)
	//	pagenum : page당 개수
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

	//사용자 경마 배팅 로그요청에 대한 응답
	//	result : 응답 결과값
	//	moneys : 배팅후 소지금
	//	totalwin : total win
	//	bets : 배팅 목록
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

	//경마 배당정보 통보( RC_LOG_ACCOUNT_BET_REQ 받았을때 보내준다 )
	//	dividends : 배당정보
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

	//경마 로그 목록요청
	//	page : page(0~ : 첫page)
	//	pagenum : page당 개수
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

	//경마 로그 목록요청에 대한 응답
	//	result : 응답 결과값
	//	total : 총 항목개수
	//	page : page(0~ : 첫page)
	//	races : 경마 로그 목록
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

	//사용자 입출금 내역요청
	//	page : page(0~ : 첫page)
	//	pagenum : page당 개수
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

	//사용자 입출금 내역요청에 대한 응답
	//	result : 응답 결과값
	//	total : 총 항목개수
	//	page : page(0~ : 첫page)
	//	deposits : 입출금 요청 목록
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

	//입출금 요청
	//	type : 0입금, 1:출금
	//	add_credit : 입출금 요청금액
	//	bank : 계좌
	//	bank_account : 계좌 사용자명
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

	//입출금 요청에 대한 응답
	//	result : 응답 결과값
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

	//QnA(쪽지) 목록요청
	//	page : page(0~ : 첫page)
	//	pagenum : page당 개수
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

	//QnA(쪽지) 목록요청에 대한 응답
	//	result : 응답 결과값
	//	total : 총 항목개수
	//	page : page(0~ : 첫page)
	//	qnas : 입출금 요청 목록
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

	//QnA(쪽지) 등록요청
	//	qna : 쪽지내용
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

	//QnA(쪽지) 등록요청요청에 대한 응답
	//	result : 응답 결과값
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

	//QnA(쪽지) 댓글 등록요청
	//	board : 댓글 그룹 id
	//	qna : 쪽지내용
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

	//QnA(쪽지) 댓글 등록요청에 대한 응답
	//	result : 응답 결과값
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

	//QnA(쪽지) 삭제요청
	//	memopk : 메모 번호
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

	//QnA(쪽지) 삭제요청에 대한 응답
	//	result : 응답 결과값
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

	//입출금및 QnA 변경통보( 이후 RC_MEMO_CHECK_REQ 요청진행)
	//	result : 응답 결과값(의미없는 변수)
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

	//QnA(쪽지) 최대개수요청
	//	depositpk : 마지막으로 체크한 입출금 pk
	//	qnapk : 마지막으로 체크한 QnA pk
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

	//QnA(쪽지) 최대개수요청에 대한 응답
	//	result : 응답 결과값
	//	depositpk : 마지막으로 추가된 입출금 pk
	//	deposit : 마지막으로 체크한 입출금 이후, 모든 입출금 수
	//	qnapk : 마지막으로 추가된 QnA pk
	//	qna : 마지막으로 체크한 QnA 이후, 모든 QnA 수
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

	//주(week) 정산 배당금 요청
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

	//주(week) 정산 배당금 요청에 대한 응답
	//	result : 응답 결과값
	//	money : 현재 소지금액 ( 안보내는 경우도 있기때문에 vector 사용 )
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

	//입/출금 client 전체에 통보(GM --> account)
	//	type : 0:입금, 1:출금
	//	target : 대상자
	//	add_credit : 입/출금 금액
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

	//최고 당첨자 client 전체에 통보(trace --> game)
	//	account : 당첨자
	//	win : 당첨금
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

	//공지 목록요청
	//	page : page(0~ : 첫page)
	//	pagenum : page당 개수
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

	//공지 목록요청에 대한 응답
	//	result : 응답 결과값
	//	total : 총 항목개수
	//	page : page(0~ : 첫page)
	//	notices : 공지 목록
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

	//공지 추가 통보
	//	notices : 공지
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
