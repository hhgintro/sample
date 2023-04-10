using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Net;
using System.Net.Sockets;
using FreeNet;

namespace CSampleClient
{
    class CReview
    {
        public string m_review;
        public int m_index;
        public string m_review1;
        public string m_review2;
    }

//	using GameServer;

	class Program
	{
		static List<IPeer> game_servers = new List<IPeer>();

        static public String account = "test01";
        static public String password = "1111";
        static public String ipLobby = "172.30.1.200";      //내컴
        //static public String ipLobby = "172.30.1.201";      //테섭
        //static public String ipLobby = "15.164.242.219";
        static public String masterkey;
        static public UInt32 ipGame = 0;
        static public UInt16 portGame = 0;

        static public CConnector connectorLobby;
        static public CConnector connectorGame;

        static List<CReview> m_listReview = new List<CReview>();
        static void LoadValue()
        {
            int counter = 0;
            string line;

            // Read the file and display it line by line.  
            System.IO.StreamReader file =
                new System.IO.StreamReader(@"D:\work\HorseRacing\source\server\bin\racing\Data\value.txt", Encoding.Default);
            while ((line = file.ReadLine()) != null)
            {
                System.Console.WriteLine(line);
                if (0 < counter)
                {
                    CReview review = new CReview();
                    review.m_review = line.Substring(0, 4);
                    review.m_index = int.Parse(line.Substring(6, 1));
                    if (45 < line.Length)
                    {
                        review.m_review1 = line.Substring(12, 30).Trim();
                        review.m_review2 = line.Substring(45);
                        System.Console.WriteLine(review.m_review1);
                        System.Console.WriteLine(review.m_review2);

                        m_listReview.Add(review);
                    }
                    else
                    {
                        review.m_review1 = line.Substring(12);
                        //review2가 공백인경우는 이전정보를 가져옵니다.
                        review.m_review2 = m_listReview[m_listReview.Count-1].m_review2;

                        System.Console.WriteLine(review.m_review1);
                        System.Console.WriteLine("");

                        m_listReview.Add(review);
                    }

                    System.Console.WriteLine("line: " + line);
                    System.Console.WriteLine("result: " + review.m_review1 + " " + review.m_review2);
                    System.Console.WriteLine("");
                }
                counter++;
            }

            file.Close();
            System.Console.WriteLine("There were {0} lines.", counter);

            int nValueIndex = 10;
            System.Console.WriteLine("단문 단평(" + nValueIndex + "): " + m_listReview[nValueIndex].m_review1 + " " + m_listReview[nValueIndex].m_review2);
            nValueIndex = 51;
            System.Console.WriteLine("단문 단평(" + nValueIndex + "): " + m_listReview[nValueIndex].m_review1 + " " + m_listReview[nValueIndex].m_review2);

            // Suspend the screen.  
            System.Console.ReadLine();
        }

        static void test1()
        {
            // anddroid console dubuging 명령어
            //C:\Users\Administrator\AppData\Local\Android\Sdk\platform-tools>adb logcat -s Unity > abc.txt

            var buffer = new byte[10000];

            FreeNet.CMessageResolver resolver = new FreeNet.CMessageResolver();
            resolver.message_size = 2632;
            resolver.on_receive(buffer, 0, 1460, null);
            resolver.on_receive(buffer, 0, 1181, null);
        }

        static void Main(string[] args)
		{
            //LoadValue();

            //test1();


            CPacketBufferManager.initialize(2000);
			// CNetworkService객체는 메시지의 비동기 송,수신 처리를 수행한다.
			// 메시지 송,수신은 서버, 클라이언트 모두 동일한 로직으로 처리될 수 있으므로
			// CNetworkService객체를 생성하여 Connector객체에 넘겨준다.
			CNetworkService serviceLobby = new CNetworkService();

			// endpoint정보를 갖고있는 Connector생성. 만들어둔 NetworkService객체를 넣어준다.
			connectorLobby = new CConnector(serviceLobby);
			// 접속 성공시 호출될 콜백 매소드 지정.
			connectorLobby.connected_callback   += on_connected_lobbyserver;
			connectorLobby.signup_callback      += on_signup_lobbyserver;        //HG[2021.02.16]콜백위치를 sign_up 이후에서 처리합니다.

            //IPEndPoint endpointLobby = new IPEndPoint(IPAddress.Parse(ipLobby), 8601);
            //Console.WriteLine(endpointLobby.ToString());
            ////connector.connect(endpoint);
            //////System.Threading.Thread.Sleep(10);
            //connectorLobby.connect(endpointLobby);  //HG[2021.02.15]자동진행
            lobbyConnect();


            //game
            CNetworkService serviceGame = new CNetworkService();
            connectorGame = new CConnector(serviceGame);
            // 접속 성공시 호출될 콜백 매소드 지정.
            connectorGame.connected_callback    += on_connected_gameserver;
            connectorGame.signup_callback       += on_signup_gameserver;          //HG[2021.02.16]콜백위치를 sign_up 이후에서 처리합니다.
            //IPEndPoint endpointGame;


            while (true)
			{
                Console.WriteLine("======== commend =========");
                Console.WriteLine("\t lobby connect");
                Console.WriteLine("\t lobby disconnect");
                Console.WriteLine("\t login");
                Console.WriteLine("\t game connect");
                Console.WriteLine("\t game disconnect");
                Console.WriteLine("\t certify");
                Console.WriteLine("\t enter");
                Console.WriteLine("\t bet_coin");
                Console.WriteLine("\t q: exit");
                Console.WriteLine("==========================");
                Console.Write(">");
				string line = Console.ReadLine();
				if (line == "q")
					break;

                switch (line)
                {
                    case "lobby connect":
                        //접속중이면 접속종료처리후 새로 접속한다.
                        lobbyDisconnect();

                        //잠시 대기
                        System.Threading.Thread.Sleep(1000);


                        lobbyConnect();
                        break;

                    case "lobby disconnect":
                        lobbyDisconnect();
                        break;

                    case "login":
                        login();
                        break;

                    case "game connect":
                        gameConnect();
                        break;

                    case "game disconnect":
                        gameDisconnect();
                        break;

                    case "certify":
                        certify();
                        break;

                    case "enter":
                        game_enter();
                        break;

                    case "bet_coin":
                        bet_coin();
                        break;

                    case "rec"://통계요청
                        record_req();
                        break;

                    case "qalist":
                        Send_QnAListRequest(0, 10);
                        break;
                    case "qasend":
                        Send_QnARequest("test message");
                        break;
                    case "record":
                        Send_TodayIsMatchRecord(0, 10);
                        break;

                    default:
                        Console.WriteLine("default:{0}", line);
                        break;
                }


                if (game_servers.Count < 0)
                    continue;

                //CPacket msg = CPacket.create((ushort)PROTOCOL.CHAT_MSG_REQ, 1);
                //msg.push(line);
                //game_servers[0].send(msg);


            }

            //모든 연결 종료
            allDisconnect();

			////System.Threading.Thread.Sleep(1000 * 20);
			//Console.ReadKey();
		}

        //모든 연결 종료
        static public void allDisconnect()
        {
            foreach (CRemoteServerPeer peer in game_servers)
                peer.token.disconnect();
        }
            static public void lobbyDisconnect()
        {
            foreach (CRemoteServerPeer peer in game_servers)
            {
                //type 0:lobby, 1:game
                if (0 == peer.serverType)
                    peer.token.disconnect();
            }
        }

        static public void lobbyConnect()
        {
            IPEndPoint endpointLobby = new IPEndPoint(IPAddress.Parse(ipLobby), 8601);
            Console.WriteLine(endpointLobby.ToString());
            //connector.connect(endpoint);
            ////System.Threading.Thread.Sleep(10);
            connectorLobby.connect(endpointLobby);  //HG[2021.02.15]자동진행
        }

        static void login()
        {
            //send
            X2L.stX2L_AC_LOGIN_REQ stReq = new X2L.stX2L_AC_LOGIN_REQ();
            stReq.account = account;
            stReq.password = password;
            stReq.version = X2L.PT.PT_VERSION;
            //stReq.Send(((CRemoteServerPeer)game_servers[0]).token);
            ////game_servers[0].send(msg);
            foreach (CRemoteServerPeer peer in game_servers)
            {
                //type 0:lobby, 1:game
                if (0 == peer.serverType)
                {
                    stReq.Send(peer.token);
                    break;  //한곳에만 보낸다.
                }
            }
        }

        static public void gameConnect()
        {
            if (0 == ipGame || 0 == portGame)
                return;

            //접속중이면 접속종료처리후 새로 접속한다.
            gameDisconnect();

            //잠시 대기
            System.Threading.Thread.Sleep(1000);


            IPEndPoint endpointGame = new IPEndPoint(ipGame, portGame);
            //endpointGame = new IPEndPoint(IPAddress.Parse("172.30.1.201"), portGame);
            connectorGame.connect(endpointGame);
        }
        static public void gameDisconnect()
        {
            foreach (CRemoteServerPeer peer in game_servers)
            {
                //type 0:lobby, 1:game
                if (1 == peer.serverType)
                    peer.token.disconnect();
            }
        }

        static void certify()
        {
            //send
            X2G.stX2G_AC_CERTIFY_REQ stReq = new X2G.stX2G_AC_CERTIFY_REQ();
            stReq.account = account;
            stReq.masterkey = masterkey;
            stReq.version = X2G.PT.PT_VERSION;
            //stReq.Send(((CRemoteServerPeer)game_servers[0]).token);
            ////game_servers[0].send(msg);
            foreach (CRemoteServerPeer peer in game_servers)
            {
                //type 0:lobby, 1:game
                if (1 == peer.serverType)
                {
                    stReq.Send(peer.token);
                    break;  //한곳에만 보낸다.
                }
            }
        }

        public static void game_enter()
        {
            //send
            X2G.stX2G_RC_GAME_ENTER_REQ stReq = new X2G.stX2G_RC_GAME_ENTER_REQ();
            foreach (CRemoteServerPeer peer in game_servers)
            {
                //type 0:lobby, 1:game
                if (1 == peer.serverType)
                {
                    stReq.Send(peer.token);
                    break;  //한곳에만 보낸다.
                }
            }
        }

        public static void bet_coin()
        {
            //send
            X2G.stX2G_RC_BET_COIN_REQ stReq = new X2G.stX2G_RC_BET_COIN_REQ();
            stReq.addBet = 20;

            CBetSingle dan = new CBetSingle();
            dan.type = 0;
            dan.num = 9;
            dan.bet = 10;
            stReq.vecSingle.Add(dan);

            CBetSingle bok = new CBetSingle();
            bok.type = 1;
            bok.num = 8;
            bok.bet = 10;
            stReq.vecSingle.Add(bok);

            foreach (CRemoteServerPeer peer in game_servers)
            {
                //type 0:lobby, 1:game
                if (1 == peer.serverType)
                {
                    stReq.Send(peer.token);
                    break;  //한곳에만 보낸다.
                }
            }
        }

        public static void record_req()
        {
            //send
            X2G.stX2G_RC_RECORD_REQ stReq = new X2G.stX2G_RC_RECORD_REQ();

            foreach (CRemoteServerPeer peer in game_servers)
            {
                //type 0:lobby, 1:game
                if (1 == peer.serverType)
                {
                    stReq.Send(peer.token);
                    break;  //한곳에만 보낸다.
                }
            }
        }

        /// <summary>
        /// 접속 성공시 호출될 콜백 매소드.
        /// </summary>
        /// <param name="server_token"></param>
        static void on_connected_lobbyserver(CUserToken server_token)
		{
			lock (game_servers)
			{
                CRemoteServerPeer server = new CRemoteServerPeer(server_token);
                server.serverType = 0;//0:lobby, 1:game
                game_servers.Add(server);
				Console.WriteLine("Lobby Connected !!!");
            }
        }
        static void on_signup_lobbyserver(CUserToken server_token)
        {
            login();
        }

        static void on_connected_gameserver(CUserToken server_token)
        {
            lock (game_servers)
            {
                CRemoteServerPeer server = new CRemoteServerPeer(server_token);
                server.serverType = 1;//0:lobby, 1:game
                game_servers.Add(server);
                Console.WriteLine("Game Connected !!!");

                //연결후에는 지워줍니다.(또 연결시도 할 수도 있기때문에)
                Program.ipGame = 0;
                Program.portGame = 0;
            }
        }
        static void on_signup_gameserver(CUserToken server_token)
        {
            certify();
        }

        public static void remove_servers(IPeer server)
        {
            lock (game_servers)
            {
                game_servers.Remove(server);
				Console.WriteLine("{0} Dis-connected!(0:lobby, 1:game)", ((CRemoteServerPeer)server).serverType);
            }
        }
        public static void Send_QnAListRequest(int _page, int _pageNum)
        {
            foreach (CSampleClient.CRemoteServerPeer peer in game_servers)
            {
                //type 0:lobby, 1:game
                if (1 == peer.serverType)
                {
                    Console.WriteLine("Send_QnAListRequest() : " + _page + " / " + _pageNum);

                    X2G.stX2G_RC_QNA_LIST_REQ m_NoteList = new X2G.stX2G_RC_QNA_LIST_REQ();
                    m_NoteList.page = (ushort)_page;
                    m_NoteList.pagenum = (byte)_pageNum;

                    m_NoteList.Send(peer.token);
                }
            }
        }
        public static void Send_QnARequest(string _Note) // 쪽지
        {
            foreach (CSampleClient.CRemoteServerPeer peer in game_servers)
            {
                //type 0:lobby, 1:game
                if (1 == peer.serverType)
                {
                    Console.WriteLine("Send_QnARequest()");

                    X2G.stX2G_RC_QNA_INSERT_REQ m_Note = new X2G.stX2G_RC_QNA_INSERT_REQ();
                    m_Note.qna = _Note;

                    m_Note.Send(peer.token);
                }
            }
        }
        public static void Send_TodayIsMatchRecord(int _page, int _pageNum)
        {
            foreach (CSampleClient.CRemoteServerPeer peer in game_servers)
            {
                //type 0:lobby, 1:game
                if (1 == peer.serverType)
                {
                    Console.WriteLine("Send_TodayIsMatchRecord() : " + _page + " / " + _pageNum);

                    X2G.stX2G_RC_LOG_RACE_REQ m_InOut = new X2G.stX2G_RC_LOG_RACE_REQ();
                    m_InOut.page = (ushort)_page;
                    m_InOut.pagenum = (byte)_pageNum;

                    m_InOut.Send(peer.token);
                }
            }
        }
    }
}
