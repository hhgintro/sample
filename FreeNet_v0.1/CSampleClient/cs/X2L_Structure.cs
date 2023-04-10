
using System;
using System.Collections.Generic;

namespace X2L
{

	//계정생성 요청
	//	account : 계정명
	//	password : 패스워드
	//	phone : 전화번호
	//	bank : 계좌
	//	recommender : 추천 계정
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

	//계정생성 요청에 대한 응답
	//	result : 응답 결과값
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

	//로그인 요청
	//	account : 계정명
	//	password : 패스워드
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

	//로그인 요청에 대한 응답
	//	result : 응답 결과값
	//	duplicated : 0:정상, 1:중복접속
	//	masterkey : master서버 접속 인증키 ( game서버에 접속할 때 필요)
	//	game : Game서버의 접속 정보 리스트 ( 안보내는 경우도 있기때문에 vector 사용 )
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

	//계정 중복 체크요청
	//	account : 계정명
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

	//계정 중복 체크요청에 대한 응답
	//	result : 응답 결과값
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

	//추천인 체크요청
	//	account : 계정명
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

	//추천인 체크요청에 대한 응답
	//	result : 응답 결과값
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
