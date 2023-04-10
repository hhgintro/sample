using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using FreeNet;

namespace CSampleClient
{
	using GameServer;

	class CRemoteServerPeer : IPeer
	{
		public CUserToken token { get; private set; }
        public int serverType; //0:lobby, 1:game

		public CRemoteServerPeer(CUserToken token)
		{
			this.token = token;
			this.token.set_peer(this);
		}

		void IPeer.on_message(Const<byte[]> buffer)
		{
			CPacket msg = new CPacket(buffer.Value, this);
            //PROTOCOL protocol_id = (PROTOCOL)msg.pop_protocol_id();

            PROTOCOL protocol_id = (PROTOCOL)BitConverter.ToUInt16(msg.buffer, 6);
            switch (protocol_id)
			{
				case PROTOCOL.CHAT_MSG_ACK:
					{
						string text = msg.pop_string();
						Console.WriteLine(string.Format("text 0x{0}", text));

                        ////send
                        //X2L.stX2L_AC_LOGIN_REQ stReq = new X2L.stX2L_AC_LOGIN_REQ();
                        //stReq.account = "abc계정";
                        //stReq.password = "p000p";
                        //stReq.version = 20171030;

                        //stReq.testList = new List<FreeNet.stTest>();
                        //stReq.testList.Add(new FreeNet.stTest(1, "테1"));
                        //stReq.testList.Add(new FreeNet.stTest(2, "테2"));
                        //stReq.testList.Add(new FreeNet.stTest(3, "테3"));
                        //stReq.Send(this.token);

                    }
                    break;

                case (PROTOCOL)X2L.PROTOCOL.X2L_AC_REGIST_ACK:
                    {
                        //recv
                        X2L.stX2L_AC_REGIST_ACK st = new X2L.stX2L_AC_REGIST_ACK();
                        st.Recv(msg);
                        if (0 != st.result)
                        {
                            Console.WriteLine("Error: REGIST {0}", st.result);
                            break;
                        }
                    } break;

                case (PROTOCOL)X2L.PROTOCOL.X2L_AC_LOGIN_ACK:
                    {
                        //recv
                        X2L.stX2L_AC_LOGIN_ACK st = new X2L.stX2L_AC_LOGIN_ACK();
                        st.Recv(msg);
                        if(0 != st.result) {
                            Console.WriteLine("Error: LOGIN {0}", st.result);
                            break;
                        }

                        if(0 < st.game.Count)
                        {
                            Program.masterkey = st.masterkey;

                            for (int i = 0; i < st.game.Count; ++i) {
                                //int ip = System.Net.IPAddress.NetworkToHostOrder((int)st.game[i].ip_);
                                int ip = (int)st.game[i].ip_;
                                short port = System.Net.IPAddress.NetworkToHostOrder((short)st.game[i].portTcp_);

                                //서버에서 받은 game서버 접속 정보
                                Program.ipGame = (UInt32)ip;
                                Program.portGame = (UInt16)port;
                                Console.WriteLine("game ip:{0},port{1}", Program.ipGame, Program.portGame);
                            }
                            Console.WriteLine("로그인 성공 !!!!");

                            Program.gameConnect();
                        }
                    } break;

                case (PROTOCOL)X2G.PROTOCOL.X2G_AC_CERTIFY_ACK:
                    {
                        //recv
                        X2G.stX2G_AC_CERTIFY_ACK st = new X2G.stX2G_AC_CERTIFY_ACK();
                        st.Recv(msg);
                        if (0 != st.result) {
                            Console.WriteLine("Error: CERTIFY {0}", st.result);
                            break;
                        }

                        Console.WriteLine("game 인증성공 credit:{0} win:{1} !!!!", st.info[0].m_credit, st.info[0].m_win);

                        Program.game_enter();
                    } break;

                case (PROTOCOL)X2G.PROTOCOL.X2G_AC_CERTIFY_NTF:
                    {
                        //recv
                        X2G.stX2G_AC_CERTIFY_NTF st = new X2G.stX2G_AC_CERTIFY_NTF();
                        st.Recv(msg);

                        Console.WriteLine("중복접속 확인됨 Error:{0}", st.result);
                    } break;

                case (PROTOCOL)X2G.PROTOCOL.X2G_RC_GAME_ENTER_ACK:
                    {
                        //recv
                        X2G.stX2G_RC_GAME_ENTER_ACK st = new X2G.stX2G_RC_GAME_ENTER_ACK();
                        st.Recv(msg);
                        if (0 != st.result)
                        {
                            Console.WriteLine("Error:ENTER {0}, 다음배팅시간:{1}(ms)", st.result, st.remaintime);
                            if (0 == st.remaintime) break;
                        }

                        foreach (CSampleClient.CRaceInfo4Client raceinfo in st.raceinfo)
                        {
                            Console.WriteLine("말마리수:{0} / 남은배팅시간:{1}(ms)", raceinfo.m_nHorseCount, st.remaintime);
                            Console.WriteLine("순위:{0},{1},{2},{3}, {4},{5},{6},{7}, ..."
                                , raceinfo.m_nRank[0], raceinfo.m_nRank[1], raceinfo.m_nRank[2], raceinfo.m_nRank[3]
                                , raceinfo.m_nRank[4], raceinfo.m_nRank[5], raceinfo.m_nRank[6], raceinfo.m_nRank[7]);
                        }

                        Console.WriteLine("game 입장성공 !!!!");
                    }
                    break;

                case (PROTOCOL)X2G.PROTOCOL.X2G_RC_BETING_START_NTF:
                    {
                        //recv
                        X2G.stX2G_RC_BETING_START_NTF st = new X2G.stX2G_RC_BETING_START_NTF();
                        st.Recv(msg);

                        foreach (CSampleClient.CRaceInfo4Client raceinfo in st.raceinfo)
                        {
                            Console.WriteLine("말마리수:{0}", raceinfo.m_nHorseCount);
                            Console.WriteLine("순위:{0},{1},{2},{3}, {4},{5},{6},{7}, ..."
                                , raceinfo.m_nRank[0], raceinfo.m_nRank[1], raceinfo.m_nRank[2], raceinfo.m_nRank[3]
                                , raceinfo.m_nRank[4], raceinfo.m_nRank[5], raceinfo.m_nRank[6], raceinfo.m_nRank[7]);
                        }
                    } break;

                case (PROTOCOL)X2G.PROTOCOL.X2G_RC_GAMESTEP_NTF:
                    {
                        //recv
                        X2G.stX2G_RC_GAMESTEP_NTF st = new X2G.stX2G_RC_GAMESTEP_NTF();
                        st.Recv(msg);

                        Console.WriteLine("GAME_STEP:{0}", st.gamestep);

                        if(3 == st.gamestep) //bet_finish
                            Program.bet_coin();
                    } break;

                case (PROTOCOL)X2G.PROTOCOL.X2G_RC_DIVIDEND_NTF:
                    {
                        //recv
                        X2G.stX2G_RC_DIVIDEND_NTF st = new X2G.stX2G_RC_DIVIDEND_NTF();
                        st.Recv(msg);

                        for (int i = 0; i < st.dividendinfo.Count; ++i)
                        {
                            Console.WriteLine("***************배당정보 전송 {0},{1},{2}"
                                , st.dividendinfo[i].fDanDividend[2], st.dividendinfo[i].fSsangDividend[5, 1], st.dividendinfo[i].fPer);
                        }
                    }
                    break;

                case (PROTOCOL)X2G.PROTOCOL.X2G_RC_BET_COIN_ACK:
                    {
                        //recv
                        X2G.stX2G_RC_BET_COIN_ACK st = new X2G.stX2G_RC_BET_COIN_ACK();
                        st.Recv(msg);
                        Console.WriteLine("BET_COIN Error:{0}", st.result);

                    }
                    break;

                case (PROTOCOL)X2G.PROTOCOL.X2G_RC_RECORD_ACK:
                    {
                        //recv
                        X2G.stX2G_RC_RECORD_ACK st = new X2G.stX2G_RC_RECORD_ACK();
                        st.Recv(msg);
                        Console.WriteLine("통계 Error:{0}", st.result);

                        if (0 < st.record.Count)
                            st.record[0].Log();
                    }
                    break;

                case (PROTOCOL)X2G.PROTOCOL.X2G_RC_QNA_LIST_ACK:
                    {
                        X2G.stX2G_RC_QNA_LIST_ACK st = new X2G.stX2G_RC_QNA_LIST_ACK();
                        st.Recv(msg);
                        Console.WriteLine("result:{0}, total:{1}, page:{2} ", st.result, st.total, st.page);

                        //public UInt32 memopk;      //num
                        //public UInt32 board;       //댓글 그룹 id
                        //                           //sbyte type;       //0:
                        //                           //sbyte status;     //0:신규, 1:읽음, 2:처리완료, 98:사용자삭제, 99:운영자삭제
                        //public string memo;        //작성된 메모내용
                        //string gm;                 //답변 운영자 계정
                        //string answer;             //답변 내용
                        //string time;               //작성일시
                        foreach (CSampleClient.CMemoQnASelect qna in st.qnas)
                        {
                            Console.WriteLine(qna.memopk + " / " +
                                              qna.board + " / " +
                                              qna.memo);
                        }
                    }
                    break;
                case (PROTOCOL)X2G.PROTOCOL.X2G_RC_QNA_INSERT_ACK:
                    {
                        X2G.stX2G_RC_QNA_INSERT_ACK st = new X2G.stX2G_RC_QNA_INSERT_ACK();
                        st.Recv(msg);
                        Console.WriteLine("QNA_INSERT Error:{0}", st.result);
                    }
                    break;
                case (PROTOCOL)X2G.PROTOCOL.X2G_RC_LOG_RACE_ACK:
                    {
                        //recv
                        X2G.stX2G_RC_LOG_RACE_ACK st = new X2G.stX2G_RC_LOG_RACE_ACK();
                        st.Recv(msg);
                        Console.WriteLine("result:{0}, total:{1}, page:{2} ", st.result, st.total, st.page);

                        foreach (CSampleClient.CLogRaceSelect log in st.races)
                        {
                            Console.WriteLine(log.racepk +
                                              log.race   + " / " +
                                              log.meter  + " / " +
                                              log.horse  + " / " +
                                              log.rank   + " / " +
                                              log.dan    + " / " +
                                              log.bok    + " / " +
                                              log.ssang  + " / " +
                                              log.time   + " / " +
                                              log.bets);
                        }
                    }
                    break;

                    

                default:
                    Console.WriteLine(string.Format("Unhandled protocol id {0:X}", protocol_id));
                    break;
            }
        }

		void IPeer.on_removed()
		{
			Console.WriteLine("Server removed.");

            Program.remove_servers(this);
        }

        void IPeer.send(CPacket msg)
		{
			this.token.send(msg);
		}

		void IPeer.disconnect()
		{
			this.token.socket.Disconnect(false);
		}

		void IPeer.process_user_operation(CPacket msg)
		{
		}
	}
}
