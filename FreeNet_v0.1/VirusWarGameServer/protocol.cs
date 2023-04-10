using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace VirusWarGameServer
{
	public enum PROTOCOL : short
	{
		BEGIN = 0,

		ENTER_GAME_ROOM_REQ = 1,
		ENTER_GAME_ROOM_ACK = 2,

		END
	}
}
