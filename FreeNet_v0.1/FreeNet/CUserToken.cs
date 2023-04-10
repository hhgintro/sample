using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Net.Sockets;

namespace FreeNet
{
	public class CUserToken
	{
		public Socket socket { get; set; }

		public SocketAsyncEventArgs receive_event_args { get; private set; }
		public SocketAsyncEventArgs send_event_args { get; private set; }

		// 바이트를 패킷 형식으로 해석해주는 해석기.
		CMessageResolver message_resolver;

		// session객체. 어플리케이션 딴에서 구현하여 사용.
		IPeer peer;

		// 전송할 패킷을 보관해놓는 큐. 1-Send로 처리하기 위한 큐이다.
		Queue<CPacket> sending_queue;
		// sending_queue lock처리에 사용되는 객체.
		private object cs_sending_queue;

		//HG[2021.02.16]콜백위치를 sign_up 이후에서 처리합니다.
		private CConnector connector;

		public CUserToken()
		{
			this.cs_sending_queue = new object();

			this.message_resolver = new CMessageResolver();
			this.peer = null;
			this.sending_queue = new Queue<CPacket>();

			//HG[2021.02.16]콜백위치를 sign_up 이후에서 처리합니다.
			this.connector = null;
		}
		//HG[2021.02.16]콜백위치를 sign_up 이후에서 처리합니다.
		public CUserToken(CConnector connector)
		{
			this.cs_sending_queue = new object();

			this.message_resolver = new CMessageResolver();
			this.peer = null;
			this.sending_queue = new Queue<CPacket>();

			//HG[2021.02.16]콜백위치를 sign_up 이후에서 처리합니다.
			this.connector = connector;
		}
		//..//HG[2021.02.16]콜백위치를 sign_up 이후에서 처리합니다.

		public void set_peer(IPeer peer)
		{
			this.peer = peer;
		}

		public void set_event_args(SocketAsyncEventArgs receive_event_args, SocketAsyncEventArgs send_event_args)
		{
			this.receive_event_args = receive_event_args;
			this.send_event_args = send_event_args;
		}

		/// <summary>
		///	이 매소드에서 직접 바이트 데이터를 해석해도 되지만 Message resolver클래스를 따로 둔 이유는
		///	추후에 확장성을 고려하여 다른 resolver를 구현할 때 CUserToken클래스의 코드 수정을 최소화 하기 위함이다.
		/// </summary>
		/// <param name="buffer"></param>
		/// <param name="offset"></param>
		/// <param name="transfered"></param>
		public void on_receive(byte[] buffer, int offset, int transfered)
		{
			this.message_resolver.on_receive(buffer, offset, transfered, on_message);
		}

        void on_message(Const<byte[]> buffer)
        {
            if (this.peer == null)
                return;

            CPacket msg = new CPacket(buffer.Value, this.peer);
            NetC2S.PROTOCOL protocol_id = (NetC2S.PROTOCOL)BitConverter.ToUInt16(msg.buffer, 6);
            switch (protocol_id)
            {
                case NetC2S.PROTOCOL.NetC2S_CORE_CONNECT_COMPLETED_NTF:
                    {
						//recv
						NetC2S.stNetC2S_CORE_CONNECT_COMPLETED_NTF st = new NetC2S.stNetC2S_CORE_CONNECT_COMPLETED_NTF();
                        st.Recv(msg);
						//Console.WriteLine("remote:0x{0:x}", st.remote);
						Console.WriteLine("recv NetC2S_CORE_CONNECT_COMPLETED_NTF");

						//send
						NetC2S.stNetC2S_CORE_SIGN_UP_REQ stReq = new NetC2S.stNetC2S_CORE_SIGN_UP_REQ();
                        stReq.version		= NetC2S.PT.PT_VERSION;		//protocol version
                        stReq.entry			= 0x01;						//client
                        stReq.serverTcpPort = 0;
                        stReq.Send(this);
						Console.WriteLine("send stNetC2S_CORE_SIGN_UP_REQ");
					}
					break;

                case NetC2S.PROTOCOL.NetC2S_CORE_SIGN_UP_ACK:
                    {
						//recv
						NetC2S.stNetC2S_CORE_SIGN_UP_ACK st = new NetC2S.stNetC2S_CORE_SIGN_UP_ACK();
                        st.Recv(msg);
						//Console.WriteLine("result:{0}, servertime:{1}, udpport:{2}"
						//    , st.result, st.servertime, st.udpport);
						Console.WriteLine("recv NetC2S_CORE_SIGN_UP_ACK: {0}", st.result);

						//HG[2021.02.16]콜백위치를 sign_up 이후에서 처리합니다.
						if (this.connector.signup_callback != null)
							this.connector.signup_callback(this);

					}
					break;

                case NetC2S.PROTOCOL.NetC2S_CORE_HEART_BEAT_REQ:
                    {
                        //recv
                        NetC2S.stNetC2S_CORE_HEART_BEAT_REQ st = new NetC2S.stNetC2S_CORE_HEART_BEAT_REQ();
                        st.Recv(msg);
                        //Console.WriteLine("servertime:{0}", st.servertime);

                        //send
                        NetC2S.stNetC2S_CORE_HEART_BEAT_ACK stAck = new NetC2S.stNetC2S_CORE_HEART_BEAT_ACK();
                        stAck.servertime = st.servertime;
                        stAck.Send(this);
                    }
                    break;

                default:
                    this.peer.on_message(buffer);
                    break;
            }


        }

		public void on_removed()
		{
			this.sending_queue.Clear();

			if (this.peer != null)
			{
				this.peer.on_removed();

                //Program.remove_gameserver(this);

            }
		}

		/// <summary>
		/// 패킷을 전송한다.
		/// 큐가 비어 있을 경우에는 큐에 추가한 뒤 바로 SendAsync매소드를 호출하고,
		/// 데이터가 들어있을 경우에는 새로 추가만 한다.
		/// 
		/// 큐잉된 패킷의 전송 시점 :
		///		현재 진행중인 SendAsync가 완료되었을 때 큐를 검사하여 나머지 패킷을 전송한다.
		/// </summary>
		/// <param name="msg"></param>
		public void send(CPacket msg)
		{
			lock (this.cs_sending_queue)
			{
				// 큐가 비어 있다면 큐에 추가하고 바로 비동기 전송 매소드를 호출한다.
				if (this.sending_queue.Count <= 0)
				{
					this.sending_queue.Enqueue(msg);
					start_send();
					return;
				}

				// 큐에 무언가가 들어 있다면 아직 이전 전송이 완료되지 않은 상태이므로 큐에 추가만 하고 리턴한다.
				// 현재 수행중인 SendAsync가 완료된 이후에 큐를 검사하여 데이터가 있으면 SendAsync를 호출하여 전송해줄 것이다.
				this.sending_queue.Enqueue(msg);
			}
		}

		/// <summary>
		/// 비동기 전송을 시작한다.
		/// </summary>
		void start_send()
		{
			lock (this.cs_sending_queue)
			{
				// 전송이 아직 완료된 상태가 아니므로 데이터만 가져오고 큐에서 제거하진 않는다.
				CPacket msg = this.sending_queue.Peek();

				// 헤더에 패킷 사이즈를 기록한다.
				msg.record_size();
                //패킷 번호
                msg.record_num();
                //encrypt
                //msg.record_encrypt();
                //패킷의 position을 재설정해 줘야...패킷 사이즈만큼 전송된다.
                msg.reset_pos(msg.pop_protocol_size());

                // 이번에 보낼 패킷 사이즈 만큼 버퍼 크기를 설정하고
                this.send_event_args.SetBuffer(this.send_event_args.Offset, msg.position);
				// 패킷 내용을 SocketAsyncEventArgs버퍼에 복사한다.
				Array.Copy(msg.buffer, 0, this.send_event_args.Buffer, this.send_event_args.Offset, msg.position);

				// 비동기 전송 시작.
				bool pending = this.socket.SendAsync(this.send_event_args);
				if (!pending)
				{
					process_send(this.send_event_args);
				}
			}
		}

		static int sent_count = 0;
		static object cs_count = new object();
		/// <summary>
		/// 비동기 전송 완료시 호출되는 콜백 매소드.
		/// </summary>
		/// <param name="e"></param>
		public void process_send(SocketAsyncEventArgs e)
		{
			if (e.BytesTransferred <= 0 || e.SocketError != SocketError.Success)
			{
				//Console.WriteLine(string.Format("Failed to send. error {0}, transferred {1}", e.SocketError, e.BytesTransferred));
				return;
			}

			lock (this.cs_sending_queue)
			{
				// count가 0이하일 경우는 없겠지만...
				if (this.sending_queue.Count <= 0)
				{
					throw new Exception("Sending queue count is less than zero!");
				}

				//todo:재전송 로직 다시 검토~~ 테스트 안해봤음.
				// 패킷 하나를 다 못보낸 경우는??
				int size = this.sending_queue.Peek().position;
				if (e.BytesTransferred != size)
				{
					string error = string.Format("Need to send more! transferred {0},  packet size {1}", e.BytesTransferred, size);
					Console.WriteLine(error);

					// 남은 데이터 만큼 버퍼를 재설정 해주고 다시 전송한다.
					e.SetBuffer(e.Offset, size - e.BytesTransferred);
					bool pending = this.socket.SendAsync(e);
					if (!pending)
					{
						process_send(this.send_event_args);
					}

					return;
				}


				//System.Threading.Interlocked.Increment(ref sent_count);
				lock (cs_count)
				{
					++sent_count;
					////if (sent_count % 20000 == 0)
					//{
					//	Console.WriteLine(string.Format("process send : {0}, transferred {1}, sent count {2}",
					//		e.SocketError, e.BytesTransferred, sent_count));
					//}
				}

				//Console.WriteLine(string.Format("process send : {0}, transferred {1}, sent count {2}",
				//	e.SocketError, e.BytesTransferred, sent_count));

				// 전송 완료된 패킷을 큐에서 제거한다.
				CPacket packet = this.sending_queue.Dequeue();
				CPacket.destroy(packet);

				// 아직 전송하지 않은 대기중인 패킷이 있다면 다시한번 전송을 요청한다.
				if (this.sending_queue.Count > 0)
				{
					start_send();
				}
			}
		}

		//void send_directly(CPacket msg)
		//{
		//	msg.record_size();
		//	this.send_event_args.SetBuffer(this.send_event_args.Offset, msg.position);
		//	Array.Copy(msg.buffer, 0, this.send_event_args.Buffer, this.send_event_args.Offset, msg.position);
		//	bool pending = this.socket.SendAsync(this.send_event_args);
		//	if (!pending)
		//	{
		//		process_send(this.send_event_args);
		//	}
		//}

		public void disconnect()
		{
			// close the socket associated with the client
			try
			{
				this.socket.Shutdown(SocketShutdown.Send);
			}
			// throws if client process has already closed
			catch (Exception) { }
			this.socket.Close();
		}

		public void start_keepalive()
		{
			System.Threading.Timer keepalive = new System.Threading.Timer((object e) =>
			{
				CPacket msg = CPacket.create(0, 1);
				msg.push(0);
				send(msg);
			}, null, 0, 3000);
		}
	}
}
