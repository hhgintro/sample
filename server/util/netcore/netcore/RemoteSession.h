#pragma once

namespace NetCore {

	class CSessionData;

	// CPacketSession�� ��ӹ��� CRemoteSession
	class CRemoteSession : public CPacketSession, public IRemote, public NetC2S_SEND
	{
	public:
		CRemoteSession(VOID);
		virtual ~CRemoteSession(VOID);
		virtual void Clear();
		BOOL Begin(int nRecvTcpPoolSize, int nRecvUdpPoolCnt);
		BOOL End(SOCKET listenSocket, int nRecvTcpPoolSize, int nRecvUdpPoolCnt);


		IRemote* FindRemote(HOSTID remote);
		CPacketSession* FindPacketSession(IRemote* peer, bool bIsUdp);

		void Update(SOCKET listenSocket);

		void SendConnectComplete();

#if __HEART_BEAT__
		void SendHeartBeat();
		void SetHeartBeat(TIME_T beat);
		UINT64 GetHeartBeat();
		TIME_T GetLastHeartBeatTime() { return LastHeartBeatTime_; }
		void SetLastHeartBeatTime(TIME_T t) { LastHeartBeatTime_ = t; }
		
		//debug ��忡�� ���ð��� �÷� �������Ḧ ���� �� �ִ�.(�ּ� 30�� �̻� ����)
		void SetHeartBeatPermitTick(TIME_T time) { HEART_BEAT_PERMIT_TICK = time; }
#endif //..__HEART_BEAT__

		inline WORD			GetTcpPacketNumber() { if (mTcpPacketNumber > HisUtil::MAX_PACKET_NUM) return 0; return mTcpPacketNumber; }
		inline VOID			IncreaseTcpPacketNumber() { InterlockedIncrement((LONG*)&mTcpPacketNumber); }
		inline WORD			GetUdpPacketNumber() { if (mUdpPacketNumber > HisUtil::MAX_PACKET_NUM) return 0; return mUdpPacketNumber; }
		inline VOID			IncreaseUdpPacketNumber() { InterlockedIncrement((LONG*)&mUdpPacketNumber); }


		//CCharInfo* GetChoiceCharInfo() { return choice_charinfo_; }
		//void SetChoiceCharInfo(CCharInfo* info) { choice_charinfo_ = info; }

		CSessionData* GetSessionData() { return session_; }
		void SetSessionData(CSessionData* data) { session_ = data; }

		//BOOL GetDuplicatedConnect() { return bIsDuplicatedConnect_; }
		//void SetDuplicatedConnect(BOOL bDuplicated) { bIsDuplicatedConnect_ = bDuplicated; }

		BOOL GetSessionReady() { return bReady_; }
		void SetSessionReady(BOOL ready) {
			bReady_ = ready;
#if __HEART_BEAT__
			if (TRUE == ready) LastHeartBeatTime_ = ::GetTickCount64();
#endif //..__HEART_BEAT__
		}


	private:
		WORD mTcpPacketNumber;
		WORD mUdpPacketNumber;

#if __HEART_BEAT__
		//heart beat
		std::vector<TIME_T> vecHeartBeat_;
		TIME_T				TotolHeartBeat_;		//���ݱ����� Heart Beat�� ����
		TIME_T				AverageHeartBeat_;		//���ݱ����� Heart Beat�� ���
		TIME_T				LastHeartBeatTime_;		//������ Heart Beat ���� �ð�
		TIME_T				HeartBeatTime_;			//Heart Beat üũ �ֱ�
		TIME_T				HEART_BEAT_PERMIT_TICK;	//heart beat�� ��� üũ �ð�
#endif //..__HEART_BEAT__

		//CCharInfo* choice_charinfo_;		//world�� ������ �ɸ���
		CSessionData* session_;			//�ΰ�����(������ �����Ǵ� Master�������� ���Ӽ�����...)

		//BOOL bIsDuplicatedConnect_;//���� �ߺ� ���ӵ�

		BOOL bReady_;	//������ sign-up

	};

};//..namespace NetCore {