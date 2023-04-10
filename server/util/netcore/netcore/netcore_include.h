#pragma once


typedef UINT16			RESULT_T;
typedef UINT64			HOSTID;
typedef UINT32			PROTOCOL_T;
typedef UINT8			REMOTE_ENTRY_T;	//see "struct REMOTE_ENTRY"
typedef UINT64			P2PGROUPID;
typedef UINT32			ADDR_IP;
typedef UINT16			ADDR_PORT;
typedef UINT8			S_STATUS_T;
typedef UINT8			PACKET_CONTEXT;


namespace NetCore {
		
		const HOSTID Host_Server = 1;	//server의 HOSTID를 강제설정한다. 클라이언트에게 같은 값을 부여해서는 안된다.

};//..namespace NetCore {

#include <winsock2.h>	//	-- Lib : Winmm.lib
#include <mswsock.h>	//AcceptEx(),TransmitFile() -- Lib : Mswsock.lib
#include <process.h>    /* _beginthread, _endthread */
#include <ws2tcpip.h>	// inet_ntop

#include "netcore_define.h"
#include "remote.h"

#include "PacketBuffer.h"
#include "PoolBuffer.h"

#include "NetworkSession.h"
#include "PacketSession.h"
#include "netcore.h"

#include "../../netcore/pidl/NetC2S_Protocol.h"
#include "../../netcore/pidl/NetC2S_Structure.h"
#include "../../netcore/pidl/NetC2S_RecvPacket.h"
#include "../../netcore/pidl/NetC2S_SendPacket.h"

#include "../../netcore/pidl/NetC2C_Protocol.h"
#include "../../netcore/pidl/NetC2C_Structure.h"
#include "../../netcore/pidl/NetC2C_RecvPacket.h"
#include "../../netcore/pidl/NetC2C_SendPacket.h"

#include "Iocp.h"
#include "NetIocp.h"
#include "NetUdpIocp.h"
#include "P2PGroup.h"
#include "NetServerEvent.h"
#include "NetServer.h"

#include "RemoteSession.h"
#include "RemoteSessionManager.h"

#include "EventSelect.h"
#include "ClientSession.h"
#include "TcpClientSession.h"
#include "UdpClientSession.h"
#include "RemotePeer.h"

#include "netclientevent.h"
#include "netclient.h"







//#pragma comment(lib, "Ws2_32.lib")
////#pragma comment(lib, "Winmm.lib")
//#pragma comment(lib, "Mswsock.lib")
