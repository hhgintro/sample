#include "stdafx.h"
#include "UdpClientSession.h"


namespace NetCore {

	VOID CUdpClientSession::OnIoSend(VOID)
	{

	}

	VOID CUdpClientSession::OnIoRecv(VOID)
	{
		//AUTO_LOCK(cs_);

		HisUtil::CMsg msgRecv;
		ADDR_IP remoteIP = 0;
		ADDR_PORT remotePort = 0;
		DWORD dataLength = 0;
		if (mSession.RecvFromPacketForEventSelect(dataLength))
		{
			LOGEVENT("Session_Base_Info", _T(" # udp data recv : size(%d)"), dataLength);
			while (mSession.GetFromPacket(msgRecv, remoteIP, remotePort))//, Protocol, Packet, PacketLength))
			{
				LOGEVENT("Session_Base_Info", _T(" # udp data recv : entry(%d), size(%d)"), owner_->GetRemoteEntry(), dataLength);
				owner_->OnIoRecvPacket(remoteIP, remotePort, msgRecv);
			}
		}
	}

};//..namespace NetCore {