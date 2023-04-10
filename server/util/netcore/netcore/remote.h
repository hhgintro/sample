#pragma once


namespace NetCore {

	enum Hole_Punching_Step
	{
		enNotYet
		//, enDoing
		, enPublicAttempt		//public 홀펀칭 시도
		, enPublicFailed		//public 홀펀칭 실패
		, enPublicSuccess		//public 홀펀칭 성공

		, enPrivateAttempt		//private 홀펀칭 시도
		, enPrivateFailed		//private 홀펀칭 실패
		, enPrivateSuccess		//private 홀펀칭 성공
		
		, enMax_Step
	};

	//서버의 상태를 표기한다.(server <--> broker)
	struct S_STATUS {
		enum {
			eS_Stop				//서버 정지
			, eS_Running		//서버 실행
			, eS_Block			//서버 실행중이지만 신규만 접속차단
			, eS_Close			//서버 실행중이지만 강제 접속종료
		};
	};

	struct C_STATUS { //비트연산 처리
		enum {
			eC_Closed = 0//
			, eC_AttemptConnect = 1//연결 시도를 했다.(
			, eC_Connected = 2//연결되었다.
			, eC_Etc = 4//이후 추가 예정
		};
	};

	enum CHK_SESSION_LEVEL	//비트연산 처리
	{
		eChk_None = 0,
		eChk_Session = 1,
		eChk_AccountInfo = 2,
		eChk_CharInfo = 4,
		eChk_Move_Protocol_Tick = 8,

	};

	//IP/port를 2개(public/private) 관리한다.
	enum ADDRESS_END_POINT
	{
		enPublicEndPoint
		, enPrivateEndPoint
		, enMaxEndPoint
	};

	typedef struct _IP_ENDPOINT
	{
		ADDR_IP ip;
		ADDR_PORT port;
	} IP_ENDPOINT;

	enum IO_TYPE
	{
		IO_ACCEPT
		, IO_READ
		//	IO_READ_UDP
		, IO_WRITE
	};


	typedef struct _OVERLAPPED_EX
	{
		OVERLAPPED	Overlapped;
		IO_TYPE		IoType;
		VOID		*Object;
	} OVERLAPPED_EX;

	//p2p 홀펀칭을 위한 udp 정보
	struct stRemote
	{
		HOSTID remote_;

	public:
		stRemote() : remote_(0) {}
		stRemote(HOSTID remote) : remote_(remote) {}
		stRemote& operator = (const stRemote& rhs)
		{
			if (this == &rhs)	return *this;
			remote_ = rhs.remote_;
			return *this;
		}

		//friend HisUtil::CMsg& operator << (HisUtil::CMsg& msg, stRemote& pos)
		//{
		//	pos.PackInfo(msg);
		//	return msg;
		//}

		//friend HisUtil::CMsg& operator >> (HisUtil::CMsg& msg, stRemote& pos)
		//{
		//	pos.UnpackInfo(msg);
		//	return msg;
		//}

		void PackInfo(HisUtil::CMsg& msg)
		{
			msg << remote_;
		}
		void UnpackInfo(HisUtil::CMsg& msg)
		{
			msg >> remote_;
		}
	};

	struct stRemoteEndpoint
	{
		HOSTID remote;			//group 맴버의 서버에서 할당받은 자신의 host id
		REMOTE_ENTRY_T entry;
		ADDR_IP publicIP;		//publicIP : group 맴버의 public ip
		ADDR_PORT portTcp;		//tcp port
		ADDR_PORT portUdp;		//udp port
		ADDR_IP privateIP;		//privateIP : group 맴버의 private ip
		ADDR_PORT privatePort;	//privatePort : group 맴버의 private port

	public:
		//stRemoteEndpoint() : remote(0), entry(0), publicIP(0), privateIP(0), publicPort(0), privatePort(0) {}
		stRemoteEndpoint() : remote(0), entry(0), publicIP(0), portTcp(0), portUdp(0), privateIP(0), privatePort(0) {}
		//stRemoteEndpoint(HOSTID remote, REMOTE_ENTRY_T entry, ADDR_IP ip, ADDR_PORT portTcp, ADDR_PORT portUdp, INT16 users)
		//	: remote(remote), entry(entry), publicIP(ip), portTcp_(portTcp), portUdp_(portUdp), currentusers_(users) {}
		stRemoteEndpoint& operator = (const stRemoteEndpoint& rhs)
		{
			if (this == &rhs)	return *this;

			remote		= rhs.remote;
			entry		= rhs.entry;
			publicIP	= rhs.publicIP;
			portTcp		= rhs.portTcp;
			portUdp		= rhs.portUdp;
			privateIP	= rhs.privateIP;
			privatePort = rhs.privatePort;
			return *this;
		}

		friend HisUtil::CMsg& operator << (HisUtil::CMsg& msg, stRemoteEndpoint& pos)
		{
			pos.PackInfo(msg);
			return msg;
		}

		friend HisUtil::CMsg& operator >> (HisUtil::CMsg& msg, stRemoteEndpoint& pos)
		{
			pos.UnpackInfo(msg);
			return msg;
		}

		void PackInfo(HisUtil::CMsg& msg)
		{
			msg << remote
				<< entry
				<< publicIP
				<< portTcp
				<< portUdp
				<< privateIP
				<< privatePort
				;
		}
		void UnpackInfo(HisUtil::CMsg& msg)
		{
			msg >> remote
				>> entry
				>> publicIP
				>> portTcp
				>> portUdp
				>> privateIP
				>> privatePort
				;
		}
	};


	class IRemote
	{
	public:
		IRemote() : remote_(0), entry_(0), remotePublicIP_(0), remotePublicTcpPort_(0), remotePublicUdpPort_(0)
			, remotePrivateIP_(0), remotePrivateUdpPort_(0), nHolePunchingAttempt_(0), stepHolePunching_(enNotYet) {};
		virtual ~IRemote() {}

		virtual void Clear()
		{
			remote_					= 0;
			entry_					= 0;
			remotePublicIP_			= 0;
			remotePublicTcpPort_	= 0;
			remotePublicUdpPort_	= 0;
			remotePrivateIP_		= 0;
			remotePrivateUdpPort_	= 0;
			nHolePunchingAttempt_	= 0;
			stepHolePunching_		= enNotYet;
		}

		void SetHostID(HOSTID hostID) { remote_ = hostID; }
		HOSTID GetHostID() { return remote_; }

		void SetRemoteEntry(REMOTE_ENTRY_T entry) { entry_ = entry; }
		REMOTE_ENTRY_T GetRemoteEntry() { return entry_; }

		////public ip
		//void SetRemotePublicIP(ADDR_IP ip) { IPAddress_[enPublicEndPoint].ip = ip; }
		//ADDR_IP GetRemotePublicIP() { return IPAddress_[enPublicEndPoint].ip; }
		////public port
		//void SetRemotePublicPort(ADDR_PORT port) { IPAddress_[enPublicEndPoint].port = port; }
		//ADDR_PORT GetRemotePublicPort() { return IPAddress_[enPublicEndPoint].port; }
		//////private ip
		////void SetRemotePrivateIP(ADDR_IP ip) { IPAddress_[enPrivateEndPoint].ip = ip; }
		////ADDR_IP GetRemotePrivateIP() { return IPAddress_[enPrivateEndPoint].ip; }
		//////private port
		////void SetRemotePrivatePort(ADDR_PORT port) { IPAddress_[enPrivateEndPoint].port = port; }
		////ADDR_PORT GetRemotePrivatePort() { return IPAddress_[enPrivateEndPoint].port; }
		ADDR_IP GetRemotePublicIP() { return remotePublicIP_; }
		void SetRemotePublicIP(ADDR_IP ip) {
			remotePublicIP_ = ip;
			//printf("public ip:0x%x\n", ip);
		}

		ADDR_PORT GetRemotePublicTcpPort() { return remotePublicTcpPort_; }
		void SetRemotePublicTcpPort(ADDR_PORT port) {
			remotePublicTcpPort_ = port;
			//printf("public tcp port:0x%x\n", port);
		}

		ADDR_PORT GetRemotePublicUdpPort() { return remotePublicUdpPort_; }
		void SetRemotePublicUdpPort(ADDR_PORT port) {
			remotePublicUdpPort_ = port;
			//printf("public udp port:0x%x\n", port);
		}

		ADDR_IP GetRemotePrivateIP() { return remotePrivateIP_; }
		void SetRemotePrivateIP(ADDR_IP ip) {
			remotePrivateIP_ = ip;
			//printf("private ip:0x%x\n", ip);
		}

		ADDR_PORT GetRemotePrivateUdpPort() { return remotePrivateUdpPort_; }
		void SetRemotePrivateUdpPort(ADDR_PORT port) {
			remotePrivateUdpPort_ = port;
			//printf("private udp port:0x%x\n", port);
		}

		int IncHolePunchingAttempt() { return ++nHolePunchingAttempt_; }
		void SetHolePunchingAttempt(int attempt) { nHolePunchingAttempt_ = attempt; }

		void SetHolePunchingStep(Hole_Punching_Step step) { stepHolePunching_ = step; }
		Hole_Punching_Step GetHolePunchingStep() { return stepHolePunching_; }

	private:
		HOSTID remote_;					//서버에 접속한 자신의 hostid
		REMOTE_ENTRY_T entry_;			//서버에 접속한 자신의 type

		//**** 아래인자(remotePublic... remotePrivate...는 클라이언트로서의 역활만 합니다.
		//IP_ENDPOINT IPAddress_[enMaxEndPoint];
		ADDR_IP remotePublicIP_;		//client경우 접속할 서버IP		/ 서버경우 접속한 client ip
		ADDR_PORT remotePublicTcpPort_;	//client경우 접속할 서버 port		/ 서버경우 접속한 client도 서버로서 port를 열었다.
		ADDR_PORT remotePublicUdpPort_;	//서버에서 확인된 client udp port
		ADDR_IP remotePrivateIP_;		//client 자신의 private ip 
		ADDR_PORT remotePrivateUdpPort_;//client 자신의 private port	

	//public:
		int nHolePunchingAttempt_;				//홀펀칭 시도 회수(성공하면 0으로 초기화, 즉 실패회수를 의미함)
		Hole_Punching_Step stepHolePunching_;	//홀펀칭 step
	};

};//..namespace NetCore {