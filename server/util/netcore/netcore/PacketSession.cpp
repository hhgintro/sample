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

		//��Ŷ��ȣ�� �ٸ��� �ϱ� ����
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

		//��Ŷ�� �о�´�.
		if (FALSE == queueRecvTcpPacket_.Pop((char*)msgRecv.GetBuf()))
			return FALSE;

		//��Ŷ�ش��� ����� üũ
		if (msgRecv.GetSize() < HisUtil::MSG_HEADER_SIZE || msgRecv.GetSize() > HisUtil::MSG_TOTAL_SIZE) // Invalid Packet
		{
			queueRecvTcpPacket_.Reset();
			LOGEVENT("Network_Base_Core_Error", _T("�߸��� ��Ŷ(tcp ��� ������)�� �޾� ó���Ǿ� ���۸� �ʱ�ȭ �մϴ�."));
			return FALSE;
		}

		//===========================================================================
		//TCP ���� : UDP�� �ٸ� �κ�
		if (FALSE == CheckTcpPacketNum(msgRecv))
			return FALSE;
		//..TCP ���� : UDP�� �ٸ� �κ�
		//===========================================================================

		return TRUE;
	}

	BOOL CPacketSession::CheckTcpPacketNum(HisUtil::CMsg& msgRecv)
	{
		AUTO_LOCK(csLastPacketNumber_);//CThreadSync Sync

//#ifdef PACKET_INCLUDE_PROTCOL_NUM

		//�ʱⰪ�� 0
		//ó��(0)�� �ƴѰ�쿡 üũ�մϴ�.
		if (0 != mLastReadTcpPacketNumber)
		{
			//�̹� ���� ����Ÿ�z ����
			if (msgRecv.GetNum() <= mLastReadTcpPacketNumber) // ��Ŷ��ȣ�� �������̰ų� ���� ���(����) �ش� ��Ŷ�� �����Ѵ�.
			{
				LOGEVENT("Network_Packet_Number_Error", _T("recv TCP size(%d) packet id(0x%04x) packet num(%d / %d)"), msgRecv.GetSize(), msgRecv.ID(), msgRecv.GetNum(), mLastReadTcpPacketNumber);
				return FALSE;
			}

			//TCP�� ������ �����ϱ⶧���� ���� ������Ŷ(+1)�����Ǵ��� �ʿ����.
			//���� �������� ������ �� ����, packet num�� �����ؾ� �ϹǷ�.
			//������Ŷ(+1)�� �������� �����Ƿ�, ���⼭�� üũ���� �ʴ´�.
			////������Ŷ���� üũ�Ѵ�.
			//if (msgRecv.GetNum() != mLastReadTcpPacketNumber + 1)
			//{
			//	//������ �ʿ��� ��Ե� �����״�...
			//	//�����Ҷ����� ��ٷ� ���ϴ�.
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


		//UNRELIABLE ��Ŷ�� ������ ó���Ѵ�.
		if (TRUE == CNetworkSession::GetFromUnreliablePacket(msgRecv, remoteIP, remotePort))
			return TRUE;//����Ÿ�� �ִ�.

		//��Ŷ�� �о�´�.
		//if (FALSE == queueRecvUdpPacket_.Pop(msgRecv.GetBuf(), HisUtil::MSG_TOTAL_SIZE, remoteIP, remotePort))
		//	return FALSE;
		stUdpPacket* packet = poolRecvReliableUdp_.Pop();
		if (NULL == packet)
			return FALSE;

		//===========================================================================
		//UDP ���� : TCP�� �ٸ� �κ�
		if (FALSE == CheckUdpPacketNum(packet)) {
			poolRecvReliableUdp_.Erase(packet);	//�ݵ�� �޸� ��ȯ
			return FALSE;
		}
		//..//UDP ���� : TCP�� �ٸ� �κ�
		//===========================================================================


		//setting
		msgRecv		= packet->msg;
		remoteIP	= packet->ip;
		remotePort	= packet->port;
		poolRecvReliableUdp_.Erase(packet);	//�ݵ�� �޸� ��ȯ
		return TRUE;
	}

	BOOL CPacketSession::CheckUdpPacketNum(stUdpPacket* packet)
	{
		////Peer to Peer �޽����ε� ������ ���� Relay�� ���� ip/port �� paket num�� �޶�����.
		//�̷���쿡 ���� ����ó���� �ʿ��ϴ�.

		//������ �޾Ҵ� ��Ŷ����
		READ_PACKET_INFO* lastPacketInfo = GetPacketNumberFromAddressIP(packet->ip, packet->port);
		if (NULL != lastPacketInfo)
		{
			//�ʱⰪ�� 0
			//ó��(0)�� �ƴѰ�쿡 üũ�մϴ�.
			if (0 != lastPacketInfo->recvLastPacketNumber)
			{
				//�̹� ���� ����Ÿ�z ����
				if (packet->msg.GetNum() <= lastPacketInfo->recvLastPacketNumber)
				{
					LOGEVENT("Network_Packet_Number_Info", _T("error recv old UDP size(%d) packet id(0x%04x) packet num(%d / %d) (0x%08x, port:0x%04x)"), packet->msg.GetSize(), packet->msg.ID(), packet->msg.GetNum(), lastPacketInfo->recvLastPacketNumber, packet->ip, packet->port);
					goto RECV_RELIABLE_PACKET_RELEASE;
					return FALSE;
				}

				//HG[2021.02.22]�������ʿ��� ��Ŷ 100,101�� ������ �޴��ʿ��� 101,100������ �޾Ƽ� ACK�� ������
				//				�޴��ʿ����� 100�� ���� ó���� ���� ���ϴ� ���� Ȯ��
				//				������ �ʿ��� 100 �Ϸ��Ŀ� 101�� ������? �������� ���� ��Ŷ�� �ٽ� ������ �������� ��������
				//				�Ǵ��� �� ���� �Ʒ� ������ �ּ�ó���մϴ�.
				////������Ŷ���� üũ�Ѵ�.
				//if (packet->msg.GetNum() != lastPacketInfo->recvLastPacketNumber + 1)
				//{
				//	//������ �ʿ��� ��Ե� �����״�...
				//	//�����Ҷ����� ��ٷ� ���ϴ�.
				//	LOGEVENT("Network_Packet_Number_Error", _T("error not yet udp size(%d) packet id(0x%04x) packet num(%d / %d) (0x%08x, port:0x%04x)"), packet->msg.GetSize(), packet->msg.ID(), packet->msg.GetNum(), lastPacketInfo->recvLastPacketNumber, packet->ip, packet->port);
				//	return FALSE;

				//	//�޾ƾ� �ϴ� ���� ����Ÿ�� ���� ���Ѱ��(���� or ����)
				//	//�̹� ���ð��� ����Ͽ��ٸ�...�׳ɻ���Ѵ�.
				//	//

				//	//ó�� ������ updatetime�� 0 �̴�.
				//	//ó���� �� �ð��� �����ϰ� �ٽ� �־��ش�.
				//	if (0 == lastPacketInfo->updatetime)
				//	{
				//		lastPacketInfo->updatetime = GetTickCount64() + UDP_RE_SEND_DELAY_TICK;
				//		//�ٽ� �־��ش�.
				//		poolRecvReliableUdp_.Insert(packet->msg.GetNum(), packet);
				//		LOGEVENT("Network_Packet_Number_Error", _T("error not yet udp size(%d) packet id(0x%04x) packet num(%d / %d) (0x%08x, port:0x%04x)"), packet->msg.GetSize(), packet->msg.ID(), packet->msg.GetNum(), lastPacketInfo->recvLastPacketNumber, packet->ip, packet->port);
				//		return FALSE;

				//	}

				//	//���� ȣ���� �ð��� �ȵǾ���.(�ٽ� �־��ش�.)
				//	if (GetTickCount64() < lastPacketInfo->updatetime)
				//	{
				//		//�ٽ� �־��ش�.
				//		poolRecvReliableUdp_.Insert(packet->msg.GetNum(), packet);
				//		LOGEVENT("Network_Packet_Number_Error", _T("error not yet udp size(%d) packet id(0x%04x) packet num(%d / %d) (0x%08x, port:0x%04x)"), packet->msg.GetSize(), packet->msg.ID(), packet->msg.GetNum(), ReadPacketInfo->recvLastPacketNumber, packet->ip, packet->port);
				//		return FALSE;
				//	}
				//}

				//HG[2021.02.22]������ �ʿ��� ��Ŷ��ȣ������ �����°� �������� �ʰ� ó���ϵ��� ������
				//�޴� �ʿ��� �������� ��Ŷ�� ��ȿ�ϰ� ó���ϵ��� �մϴ�.
				if (packet->msg.GetNum() < (lastPacketInfo->recvLastPacketNumber - PACKET_NUM_VALID_RANGE)
					|| (lastPacketInfo->recvLastPacketNumber + PACKET_NUM_VALID_RANGE) < packet->msg.GetNum())
				{
					//������ �ʿ��� ��Ե� �����״�...
					//�����Ҷ����� ��ٷ� ���ϴ�.
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

		//�Ʒ����� ������ �߻��� �� ó���� �����ϱ⿡ ���������.
		return TRUE;


		//===================
		// ����ó��
		//===================
	RECV_RELIABLE_PACKET_RELEASE:
		poolRecvReliableUdp_.Erase(packet);
		return FALSE;
	}

	// RecvPacketForIocp�� FALSE�� �������� ���� while���� ������.
	BOOL CPacketSession::RecvPacketForIocp(int readLength)
	{
		//AUTO_LOCK(csSession_);//CThreadSync Sync

		if (!CNetworkSession::RecvForIocp(queueRecvTcpPacket_, readLength))
			return FALSE;

		return TRUE;
	}

	// RecvPacketForEventSelect�� FALSE�� �������� ���� while���� ������.
	BOOL CPacketSession::RecvPacketForEventSelect(DWORD& ReadBytes)
	{
		//AUTO_LOCK(csSession_);//CThreadSync Sync

		if (!CNetworkSession::RecvForEventSelect(queueRecvTcpPacket_, ReadBytes))
			return FALSE;

		return TRUE;
	}

	// RecvPacketForIocp�� FALSE�� �������� ���� while���� ������.
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

	// RecvPacketForEventSelect�� FALSE�� �������� ���� while���� ������.
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

		// ��Ŷ�� �ε����� �ٿ� ���� ������ �� �־�� �Ѵ�.
		msg.SetNum(::InterlockedIncrement(&mCurrentPacketNumber));
		//msg.SetNum(++mCurrentPacketNumber);
		LOGEVENT("Network_Packet_Number_Info", _T("send TCP packet id(0x%04x) packet num(%d)"), msg.ID(), mCurrentPacketNumber);

		if (HisUtil::MAX_PACKET_NUM < mCurrentPacketNumber)
			::InterlockedExchange(&mCurrentPacketNumber, 0);
			//mCurrentPacketNumber = 0;

		BOOL ret = CNetworkSession::Send(reinterpret_cast<BYTE*>(msg.GetBuf()), msg.GetSize());

		//���� send�� ������ ���. ���ۺҰ� �̹Ƿ� ������ �����մϴ�.
		if (FALSE == ret)
		{
			LOGEVENT("Network_Base_Core_Error", _T("���� send�� ������ ���. ���ۺҰ� �̹Ƿ� ������ �����մϴ�."));
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
			// ��Ŷ�� �ε����� �ٿ� ���� ������ �� �־�� �Ѵ�.
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
	//	// WriteQueue���� Pop�� �� �ָ� �ȴ�.
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
	//	// WriteQueue���� Pop�� �� �ָ� �ȴ�.
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
			info->sendPacketNumber = ::rand() % 1000;	//���� ��Ŷ�� �����ϰ� �����ϰ�
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