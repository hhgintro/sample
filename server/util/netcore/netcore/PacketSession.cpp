#include "stdafx.h"
#include "PacketSession.h"

namespace NetCore {
	extern CNetServer* g_server;

	CPacketSession::CPacketSession(VOID)
	{
		mLastReadTcpPacketNumber = 0;

		TcpSendCompleteEvent_ = CreateEvent(0, FALSE, FALSE, 0);
		//if (TcpSendCompleteEvent_ == NULL)
		//	return FALSE;

		srand(GetTickCount());
	}

	CPacketSession::~CPacketSession(VOID)
	{
		if (TcpSendCompleteEvent_)
		{
			CloseHandle(TcpSendCompleteEvent_);
			TcpSendCompleteEvent_ = NULL;
		}
	}

	BOOL CPacketSession::Begin(int nRecvTcpPoolSize, int nRecvUdpPoolCnt)
	{
		//AUTO_LOCK(csSession_);//CThreadSync Sync

		//mRemainLength			= 0;
		mLastReadTcpPacketNumber = 0;

		//패킷번호를 다르게 하기 위해
		mCurrentPacketNumber = rand() % 1000;

		if (0 < nRecvTcpPoolSize)
		{
			queueRecvTcpPacket_.Begin(nRecvTcpPoolSize);
			LOGEVENT("PoolBuffer_Info", _T("#	recv tcp Queue size(%d)"), nRecvTcpPoolSize);
		}
		if (0 < nRecvUdpPoolCnt)
		{
			//queueRecvUdpPacket_.Begin(nRecvUdpPoolCnt);
			poolRecvReliableUdp_.Begin(nRecvUdpPoolCnt);
			LOGEVENT("PoolBuffer_Info", _T("#	recv udp Queue size(%d)"), nRecvUdpPoolCnt);
		}
		//queueSendPacket_.Begin(nPoolCnt);

		//queueSendTcpPacket_.Begin(MAX_CLIENT_RECV_UDP_QUEUE_COUNT);
		//LOGEVENT("Session_Base_Info", _T("#	send tcp Queue size(%d)"), MAX_CLIENT_RECV_UDP_QUEUE_COUNT);

		LastPacketInfoForUdp_.End();

		return CNetworkSession::Begin();
	}

	BOOL CPacketSession::End(VOID)
	{
		//AUTO_LOCK(csSession_);//CThreadSync Sync

		//mRemainLength			= 0;
		mLastReadTcpPacketNumber = 0;

		//if (!WriteQueue.Begin())
		//	return FALSE;
		queueRecvTcpPacket_.Reset();
		//queueRecvUdpPacket_.Reset();
		poolRecvReliableUdp_.Clear();
		//queueSendPacket_.Reset();
		//queueSendTcpPacket_.Reset();

		LastPacketInfoForUdp_.End();

		return CNetworkSession::End();
	}

	BOOL CPacketSession::GetPacket(HisUtil::CMsg& msgRecv)//, DWORD &protocol, BYTE *packet, DWORD &packetLength)
	{
		//AUTO_LOCK(csSession_);//CThreadSync Sync

		//패킷을 읽어온다.
		if (FALSE == queueRecvTcpPacket_.Pop((char*)msgRecv.GetBuf()))
			return FALSE;

		//패킷해더의 사이즈를 체크
		if (msgRecv.GetSize() < HisUtil::MSG_HEADER_SIZE || msgRecv.GetSize() > HisUtil::MSG_TOTAL_SIZE) // Invalid Packet
		{
			queueRecvTcpPacket_.Reset();
			LOGEVENT("Network_Base_Core_Error", _T("잘못된 패킷(tcp 헤더 사이즈)을 받아 처리되어 버퍼를 초기화 합니다."));
			return FALSE;
		}

		//===========================================================================
		//TCP 전용 : UDP와 다른 부분
		if (FALSE == CheckTcpPacketNum(msgRecv))
			return FALSE;
		//..TCP 전용 : UDP와 다른 부분
		//===========================================================================

		return TRUE;
	}

	BOOL CPacketSession::CheckTcpPacketNum(HisUtil::CMsg& msgRecv)
	{
		AUTO_LOCK(csLastPacketNumber_);//CThreadSync Sync

//#ifdef PACKET_INCLUDE_PROTCOL_NUM

		//초기값은 0
		//처음(0)이 아닌경우에 체크합니다.
		if (0 != mLastReadTcpPacketNumber)
		{
			//이미 받은 데이타틑 무시
			if (msgRecv.GetNum() <= mLastReadTcpPacketNumber) // 패킷번호가 이전것이거나 같을 경우(복사) 해당 패킷은 무시한다.
			{
				LOGEVENT("Network_Packet_Number_Error", _T("recv TCP size(%d) packet id(0x%04x) packet num(%d / %d)"), msgRecv.GetSize(), msgRecv.ID(), msgRecv.GetNum(), mLastReadTcpPacketNumber);
				return FALSE;
			}

			//TCP는 순서를 보장하기때문에 구지 다음패킷(+1)인지판단할 필요없다.
			//또한 서버에서 보낸는 곳 별로, packet num을 관리해야 하므로.
			//다음패킷(+1)을 보장하지 않으므로, 여기서는 체크하지 않는다.
			////다음패킷인지 체크한다.
			//if (msgRecv.GetNum() != mLastReadTcpPacketNumber + 1)
			//{
			//	//보내는 쪽에서 어떻게든 보낼테니...
			//	//도착할때까지 기다려 봅니다.
			//	LOGEVENT("Network_Packet_Number_Error", _T("error not yet TCP size(%d) packet id(0x%04x) packet num(%d / %d)"), msgRecv.GetSize(), msgRecv.ID(), msgRecv.GetNum(), mLastReadTcpPacketNumber);
			//	return FALSE;
			//}
		}

		mLastReadTcpPacketNumber = msgRecv.GetNum();
		LOGEVENT("Network_Packet_Number_Info", _T("recv TCP packet id(0x%04x) packet num(%d)"), msgRecv.ID(), mLastReadTcpPacketNumber);

		if (HisUtil::MAX_PACKET_NUM < mLastReadTcpPacketNumber)
			mLastReadTcpPacketNumber = 0;

//#endif //PACKET_INCLUDE_PROTCOL_NUM
		return TRUE;
	}

	BOOL CPacketSession::GetFromPacket(HisUtil::CMsg& msgRecv, ADDR_IP& remoteIP, ADDR_PORT& remotePort)//, DWORD &protocol, BYTE *packet, DWORD &packetLength)
	{

		//AUTO_LOCK(csSession_);//CThreadSync Sync


		//UNRELIABLE 패킷이 있으면 처리한다.
		if (TRUE == CNetworkSession::GetFromUnreliablePacket(msgRecv, remoteIP, remotePort))
			return TRUE;//데이타가 있다.

		//패킷을 읽어온다.
		//if (FALSE == queueRecvUdpPacket_.Pop(msgRecv.GetBuf(), HisUtil::MSG_TOTAL_SIZE, remoteIP, remotePort))
		//	return FALSE;
		stUdpPacket* packet = poolRecvReliableUdp_.Pop();
		if (NULL == packet)
			return FALSE;

		//===========================================================================
		//UDP 전용 : TCP와 다른 부분
		if (FALSE == CheckUdpPacketNum(packet)) {
			poolRecvReliableUdp_.Erase(packet);	//반드시 메모리 반환
			return FALSE;
		}
		//..//UDP 전용 : TCP와 다른 부분
		//===========================================================================


		//setting
		msgRecv		= packet->msg;
		remoteIP	= packet->ip;
		remotePort	= packet->port;
		poolRecvReliableUdp_.Erase(packet);	//반드시 메모리 반환
		return TRUE;
	}

	BOOL CPacketSession::CheckUdpPacketNum(stUdpPacket* packet)
	{
		////Peer to Peer 메시지인데 서버를 통해 Relay될 경우는 ip/port 와 paket num이 달라진다.
		//이런경우에 대한 예외처리가 필요하다.

		//이전에 받았던 패킷정보
		READ_PACKET_INFO* lastPacketInfo = GetPacketNumberFromAddressIP(packet->ip, packet->port);
		if (NULL != lastPacketInfo)
		{
			//초기값은 0
			//처음(0)이 아닌경우에 체크합니다.
			if (0 != lastPacketInfo->recvLastPacketNumber)
			{
				//이미 받은 데이타틑 무시
				if (packet->msg.GetNum() <= lastPacketInfo->recvLastPacketNumber)
				{
					LOGEVENT("Network_Packet_Number_Info", _T("error recv old UDP size(%d) packet id(0x%04x) packet num(%d / %d) (0x%08x, port:0x%04x)"), packet->msg.GetSize(), packet->msg.ID(), packet->msg.GetNum(), lastPacketInfo->recvLastPacketNumber, packet->ip, packet->port);
					goto RECV_RELIABLE_PACKET_RELEASE;
					return FALSE;
				}

				//HG[2021.02.22]보내는쪽에서 패킷 100,101을 보낼때 받는쪽에서 101,100순서로 받아서 ACK를 날리면
				//				받는쪽에서는 100에 대한 처리가 되지 못하는 버그 확인
				//				보내는 쪽에서 100 완료후에 101을 보낼지? 수신하지 못한 패킷을 다시 보내는 로직으로 구성할지
				//				판단할 때 까지 아래 로직을 주석처리합니다.
				////다음패킷인지 체크한다.
				//if (packet->msg.GetNum() != lastPacketInfo->recvLastPacketNumber + 1)
				//{
				//	//보내는 쪽에서 어떻게든 보낼테니...
				//	//도착할때까지 기다려 봅니다.
				//	LOGEVENT("Network_Packet_Number_Error", _T("error not yet udp size(%d) packet id(0x%04x) packet num(%d / %d) (0x%08x, port:0x%04x)"), packet->msg.GetSize(), packet->msg.ID(), packet->msg.GetNum(), lastPacketInfo->recvLastPacketNumber, packet->ip, packet->port);
				//	return FALSE;

				//	//받아야 하는 다음 데이타를 받지 못한경우(유실 or 지연)
				//	//이미 대기시간을 경과하였다면...그냥사용한다.
				//	//

				//	//처음 들어오면 updatetime은 0 이다.
				//	//처리를 할 시간을 설정하고 다시 넣어준다.
				//	if (0 == lastPacketInfo->updatetime)
				//	{
				//		lastPacketInfo->updatetime = GetTickCount64() + UDP_RE_SEND_DELAY_TICK;
				//		//다시 넣어준다.
				//		poolRecvReliableUdp_.Insert(packet->msg.GetNum(), packet);
				//		LOGEVENT("Network_Packet_Number_Error", _T("error not yet udp size(%d) packet id(0x%04x) packet num(%d / %d) (0x%08x, port:0x%04x)"), packet->msg.GetSize(), packet->msg.ID(), packet->msg.GetNum(), lastPacketInfo->recvLastPacketNumber, packet->ip, packet->port);
				//		return FALSE;

				//	}

				//	//아직 호출할 시간이 안되었다.(다시 넣어준다.)
				//	if (GetTickCount64() < lastPacketInfo->updatetime)
				//	{
				//		//다시 넣어준다.
				//		poolRecvReliableUdp_.Insert(packet->msg.GetNum(), packet);
				//		LOGEVENT("Network_Packet_Number_Error", _T("error not yet udp size(%d) packet id(0x%04x) packet num(%d / %d) (0x%08x, port:0x%04x)"), packet->msg.GetSize(), packet->msg.ID(), packet->msg.GetNum(), ReadPacketInfo->recvLastPacketNumber, packet->ip, packet->port);
				//		return FALSE;
				//	}
				//}

				//HG[2021.02.22]보내는 쪽에서 패킷번호순으로 보내는걸 보장하지 않고 처리하도록 함으로
				//받는 쪽에서 일정범위 패킷을 유효하게 처리하도록 합니다.
				if (packet->msg.GetNum() < (lastPacketInfo->recvLastPacketNumber - PACKET_NUM_VALID_RANGE)
					|| (lastPacketInfo->recvLastPacketNumber + PACKET_NUM_VALID_RANGE) < packet->msg.GetNum())
				{
					//보내는 쪽에서 어떻게든 보낼테니...
					//도착할때까지 기다려 봅니다.
					LOGEVENT("Network_Packet_Number_Error", _T("error not yet udp size(%d) packet id(0x%04x) packet num(%d / %d) (0x%08x, port:0x%04x)"), packet->msg.GetSize(), packet->msg.ID(), packet->msg.GetNum(), lastPacketInfo->recvLastPacketNumber, packet->ip, packet->port);
					return FALSE;
				}
			}//..if (0 != lastPacketInfo->RecvLastPacketNumber)

			lastPacketInfo->updatetime = GetTickCount64() + UDP_RE_SEND_DELAY_TICK;
			lastPacketInfo->recvLastPacketNumber = packet->msg.GetNum();
			if (HisUtil::MAX_PACKET_NUM < lastPacketInfo->recvLastPacketNumber)
				lastPacketInfo->recvLastPacketNumber = 0;
			LOGEVENT("Network_Packet_Number_Info", _T("recv UDP size(%d) packet id(0x%04x) packet num(%d) (0x%08x, port:0x%04x)"), packet->msg.GetSize(), packet->msg.ID(), packet->msg.GetNum(), packet->ip, packet->port);
			//LOGEVENT("HG_RED", _T("recv UDP size(%d) packet id(0x%04x) packet num(%d) (0x%08x, port:0x%04x)"), packet->msg.GetSize(), packet->msg.ID(), packet->msg.GetNum(), packet->ip, packet->port);
		}

		//아래쪽은 오류가 발생할 떄 처리를 진행하기에 여기까지만.
		return TRUE;


		//===================
		// 오류처리
		//===================
	RECV_RELIABLE_PACKET_RELEASE:
		poolRecvReliableUdp_.Erase(packet);
		return FALSE;
	}

	// RecvPacketForIocp는 FALSE가 떨어질때 까지 while문을 돌린다.
	BOOL CPacketSession::RecvPacketForIocp(int readLength)
	{
		//AUTO_LOCK(csSession_);//CThreadSync Sync

		if (!CNetworkSession::RecvForIocp(queueRecvTcpPacket_, readLength))
			return FALSE;

		return TRUE;
	}

	// RecvPacketForEventSelect는 FALSE가 떨어질때 까지 while문을 돌린다.
	BOOL CPacketSession::RecvPacketForEventSelect(DWORD& ReadBytes)
	{
		//AUTO_LOCK(csSession_);//CThreadSync Sync

		if (!CNetworkSession::RecvForEventSelect(queueRecvTcpPacket_, ReadBytes))
			return FALSE;

		return TRUE;
	}

	// RecvPacketForIocp는 FALSE가 떨어질때 까지 while문을 돌린다.
	BOOL CPacketSession::RecvFromPacketForIocp(DWORD readLength)
	{
		//AUTO_LOCK(csSession_);//CThreadSync Sync

		//if (!CNetworkSession::RecvFromForIocp(queueRecvUdpPacket_, readLength))//, mPacketBuffer + mRemainLength, readLength))
		//	return FALSE;
		if (!CNetworkSession::RecvFromForIocp(readLength))//, mPacketBuffer + mRemainLength, readLength))
			return FALSE;

		//mRemainLength	+= readLength;

		//return getPacket(remoteIP, remotePort, protocol, packet, packetLength);
		return TRUE;
	}

	// RecvPacketForEventSelect는 FALSE가 떨어질때 까지 while문을 돌린다.
	BOOL CPacketSession::RecvFromPacketForEventSelect(DWORD& readLength)
	{
		//AUTO_LOCK(csSession_);//CThreadSync Sync

		//if (!CNetworkSession::RecvFromForEventSelect(queueRecvUdpPacket_, readLength))//, mPacketBuffer + mRemainLength, ReadLength))
		//	return FALSE;
		if (!CNetworkSession::RecvFromForEventSelect(readLength))//, mPacketBuffer + mRemainLength, ReadLength))
			return FALSE;

		//mRemainLength	+= readLength;

		//return getPacket(remoteIP, remotePort, protocol, packet, packetLength);
		return TRUE;
	}
	//send...
	BOOL CPacketSession::SendPacket(HisUtil::CMsg& msg)//, DWORD protocol, const BYTE *packet, int packetLength)
	{
		AUTO_LOCK(csCurrentPacketNumber_);//CThreadSync Sync

		// 패킷에 인덱스를 붙여 순서 보정을 해 주어야 한다.
		msg.SetNum(::InterlockedIncrement(&mCurrentPacketNumber));
		//msg.SetNum(++mCurrentPacketNumber);
		LOGEVENT("Network_Packet_Number_Info", _T("send TCP packet id(0x%04x) packet num(%d)"), msg.ID(), mCurrentPacketNumber);

		if (HisUtil::MAX_PACKET_NUM < mCurrentPacketNumber)
			::InterlockedExchange(&mCurrentPacketNumber, 0);
			//mCurrentPacketNumber = 0;

		BOOL ret = CNetworkSession::Send(reinterpret_cast<BYTE*>(msg.GetBuf()), msg.GetSize());

		//소켓 send가 실패한 경우. 전송불가 이므로 연결을 해지합니다.
		if (FALSE == ret)
		{
			LOGEVENT("Network_Base_Core_Error", _T("소켓 send가 실패한 경우. 전송불가 이므로 연결을 해지합니다."));
			if(NULL != g_server)
				g_server->ProcessDisconnect((CRemoteSession*)this);
		}
		
		return ret;
	}

	BOOL CPacketSession::SendToPacket(HisUtil::CMsg& msg, ADDR_IP remoteIP, ADDR_PORT remotePort)
	{
		//AUTO_LOCK(csSession_);//CThreadSync Sync

		//UNRELIABLE
		HisUtil::PacketContext context = msg.GetContext();
		if (UNRELIABLE == context)
		{
			BOOL ret = CNetworkSession::SendTo(remoteIP, remotePort, reinterpret_cast<BYTE*>(msg.GetBuf()), msg.GetSize());
			LOGEVENT("Network_Packet_Number_Info", _T("send UDP unreliable packet ret(%d),id(0x%04x)"), GetLastError(), msg.ID());
			return ret;
		}

		//RELIABLE
		READ_PACKET_INFO* info = GetPacketNumberFromAddressIP(remoteIP, remotePort);
		if(NULL != info)
		{
			// 패킷에 인덱스를 붙여 순서 보정을 해 주어야 한다.
			//msg.SetNum(++mCurrentPacketNumber);
			//msg.SetNum(++info->sendPacketNumber);
			msg.SetNum(InterlockedIncrement(&info->sendPacketNumber));
			LOGEVENT("Network_Packet_Number_Info", _T("send UDP packet id(0x%04x) packet num(%d)"), msg.ID(), msg.GetNum());

			if (HisUtil::MAX_PACKET_NUM < info->sendPacketNumber) {
				//info->sendPacketNumber = 0;
				InterlockedExchange(&info->sendPacketNumber, 0);
			}

		}
		return CNetworkSession::SendToReliable(remoteIP, remotePort, reinterpret_cast<BYTE*>(msg.GetBuf()), msg.GetSize());
	}

	//BOOL CPacketSession::SendTcpComplete(VOID)
	//{
	//	//AUTO_LOCK(csSession_);//CThreadSync Sync
	//
	//	// WriteQueue에서 Pop을 해 주면 된다.
	//	SetEvent(TcpSendCompleteEvent_);
	//	return TRUE;//WriteQueue.Pop();
	//	//CMsg tempmsg;
	//	//return queueSendTcpPacket_.Pop(tempmsg.GetBuf(), MSG_TOTAL_SIZE);
	//}
	//
	//BOOL CPacketSession::SendUnreliableUdpComplete(VOID)
	//{
	//	//AUTO_LOCK(csSession_);//CThreadSync Sync
	//
	//	// WriteQueue에서 Pop을 해 주면 된다.
	//	//SetEvent(TcpSendCompleteEvent_);
	//	return TRUE;//WriteQueue.Pop();
	//}

	BOOL CPacketSession::ResetUdp(VOID)
	{
		//AUTO_LOCK(csSession_);//CThreadSync Sync

		//mLastReadPacketInfoVectorForUdp.clear();
		//LastPacketInfoForUdp_.Release();

		return TRUE;
	}

	READ_PACKET_INFO* CPacketSession::GetPacketNumberFromAddressIP(ADDR_IP remoteIP, ADDR_PORT remotePort)
	{
		INT64 key = MAKEINT64(remoteIP, remotePort);
		READ_PACKET_INFO* info = LastPacketInfoForUdp_.Find(key);
		if (NULL == info)
		{
			info = LastPacketInfoForUdp_.Create();
			if (NULL == info)	return NULL;

			info->ip = remoteIP;
			info->port = remotePort;
			info->sendPacketNumber = ::rand() % 1000;	//보낼 패킷은 랜덤하게 생성하고
			info->recvLastPacketNumber = 0;
			info->updatetime = GetTickCount64() + UDP_RE_SEND_DELAY_TICK;
			LastPacketInfoForUdp_.Insert(key, info);
		}
		return info;
	}
		
	void CPacketSession::ReleasePacketNumberFromAddressIP(ADDR_IP remoteIP, ADDR_PORT remotePort)
	{
		LastPacketInfoForUdp_.Erase(MAKEINT64(remoteIP, remotePort));
	}

};//..namespace NetCore {