#include "stdafx.h"
#include "NetServer.h"

namespace NetCore {

	void CNetServer::OnNetC2S_CORE_SIGN_UP_REQ(CRemoteSession* session, HisUtil::CMsg& msgRecv)
	{
		READ_PACKET_SERVER(NetC2S_CORE_SIGN_UP_REQ);
		if (FALSE == CheckSessionStatus(session, eChk_Session))
			return;

		stNetC2S_CORE_SIGN_UP_ACK stAck;
		if (NetC2S_PT_VERSION != st.version)
		{
			stAck.result = ERR_CORE_PROTOCOL_VERSION_DISCORDANCE;
			SEND_NetC2S_CORE_SIGN_UP_ACK(session->GetHostID(), stAck);
			LOGEVENT("Session_Base_Error", _T("========== core Different Protocal Version(%d/%d)"), NetC2S_PT_VERSION, st.version);

			//OnIoDisconnected(session);
			ProcessDisconnect(session);
			return;
		}

		session->SetSessionReady(TRUE);

		session->SetRemoteEntry(st.entry);
		session->SetRemotePublicTcpPort(st.serverTcpPort);

		stAck.servertime = ::GetTickCount64();
		stAck.udpport = GetUdpPort();
		SEND_NetC2S_CORE_SIGN_UP_ACK(session->GetHostID(), stAck);
	}

};//..namespace NetCore {