using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using FreeNet;

namespace VirusWarGameServer
{
	/// <summary>
	/// 하나의 session객체를 나타낸다.
	/// </summary>
	class CGameUser : IPeer
	{
		CUserToken token;

		public CGameUser(CUserToken token)
		{
			this.token = token;
			this.token.set_peer(this);
		}

		void IPeer.on_message(Const<byte[]> buffer)
		{
			// ex)
			byte[] clone = new byte[Defines.MSG_TOTAL_SIZE];
			Array.Copy(buffer.Value, clone, buffer.Value.Length);
			CPacket msg = new CPacket(clone, this);
			Program.game_main.enqueue_packet(msg, this);
		}

		void IPeer.on_removed()
		{
			Console.WriteLine("The client disconnected.");

			Program.remove_user(this);
		}

		public void send(CPacket msg)
		{
			this.token.send(msg);
		}

		void IPeer.disconnect()
		{
			this.token.socket.Disconnect(false);
		}

		void IPeer.process_user_operation(CPacket msg)
		{
			PROTOCOL protocol = (PROTOCOL)msg.pop_protocol_id();
			Console.WriteLine("protocol id " + protocol);
			switch (protocol)
			{
				case PROTOCOL.ENTER_GAME_ROOM_REQ:
					{
						Int32 age = msg.pop((Int32)0);
						string text = msg.pop_string();
						Console.WriteLine(string.Format("age {0}, text {1}", age, text));

						CPacket response = CPacket.create((UInt16)PROTOCOL.ENTER_GAME_ROOM_ACK, 1);
						response.push(77);
						response.push("Reseponse : Thank you.");
						send(response);

						//rooms.Add(new CGameRoom());
					}
					break;
			}
		}
	}
}
