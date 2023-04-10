#pragma once

namespace NetCore {

	class CSessionData;

	// CPacketSession을 상속받은 CRemoteSession
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
		
		//debug 모드에서 허용시간을 늘려 접속종료를 막을 수 있다.(최소 30초 이상 권장)
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
		TIME_T				TotolHeartBeat_;		//지금까지의 Heart Beat의 총합
		TIME_T				AverageHeartBeat_;		//지금까지의 Heart Beat의 평균
		TIME_T				LastHeartBeatTime_;		//마지막 Heart Beat 받은 시간
		TIME_T				HeartBeatTime_;			//Heart Beat 체크 주기
		TIME_T				HEART_BEAT_PERMIT_TICK;	//heart beat를 허용 체크 시간
#endif //..__HEART_BEAT__

		//CCharInfo* choice_charinfo_;		//world에 진입한 케릭터
		CSessionData* session_;			//부가정보(유저의 계정또는 Master에접속한 게임서버들...)

		//BOOL bIsDuplicatedConnect_;//계정 중복 접속됨

		BOOL bReady_;	//연결후 sign-up

	};

};//..namespace NetCore {