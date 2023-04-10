using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace VirusWarGameServer
{
	using FreeNet;
	using System.Threading;

	class CGameServer
	{
		object operation_lock;
		Queue<CPacket> user_operations;

		// 로직은 하나의 스레드로만 처리한다.
		Thread logic_thread;
		AutoResetEvent loop_event;

		public CGameServer()
		{
			this.operation_lock = new object();
			this.loop_event = new AutoResetEvent(false);
			this.user_operations = new Queue<CPacket>();

			this.logic_thread = new Thread(gameloop);
			this.logic_thread.Start();
		}

		/// <summary>
		/// 게임 로직을 수행하는 루프.
		/// 유저 패킷 처리를 담당한다.
		/// </summary>
		void gameloop()
		{
			while (true)
			{
				CPacket packet = null;
				lock (this.operation_lock)
				{
					if (this.user_operations.Count > 0)
					{
						packet = this.user_operations.Dequeue();
					}
				}

				if (packet != null)
				{
					// 패킷 처리.
					process_receive(packet);
				}

				// 더이상 처리할 패킷이 없으면 스레드 대기.
				if (this.user_operations.Count <= 0)
				{
					this.loop_event.WaitOne();
				}
			}
		}

		public void enqueue_packet(CPacket packet, CGameUser user)
		{
			lock (this.operation_lock)
			{
				this.user_operations.Enqueue(packet);
				this.loop_event.Set();
			}
		}

		void process_receive(CPacket msg)
		{
			//todo:
			// user msg filter 체크.

			msg.owner.process_user_operation(msg);
		}
	}
}
