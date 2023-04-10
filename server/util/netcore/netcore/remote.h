#pragma once


namespace NetCore {

	enum Hole_Punching_Step
	{
		enNotYet
		//, enDoing
		, enPublicAttempt		//public Ȧ��Ī �õ�
		, enPublicFailed		//public Ȧ��Ī ����
		, enPublicSuccess		//public Ȧ��Ī ����

		, enPrivateAttempt		//private Ȧ��Ī �õ�
		, enPrivateFailed		//private Ȧ��Ī ����
		, enPrivateSuccess		//private Ȧ��Ī ����
		
		, enMax_Step
	};

	//������ ���¸� ǥ���Ѵ�.(server <--> broker)
	struct S_STATUS {
		enum {
			eS_Stop				//���� ����
			, eS_Running		//���� ����
			, eS_Block			//���� ������������ �űԸ� ��������
			, eS_Close			//���� ������������ ���� ��������
		};
	};

	struct C_STATUS { //��Ʈ���� ó��
		enum {
			eC_Closed = 0//
			, eC_AttemptConnect = 1//���� �õ��� �ߴ�.(
			, eC_Connected = 2//����Ǿ���.
			, eC_Etc = 4//���� �߰� ����
		};
	};

	enum CHK_SESSION_LEVEL	//��Ʈ���� ó��
	{
		eChk_None = 0,
		eChk_Session = 1,
		eChk_AccountInfo = 2,
		eChk_CharInfo = 4,
		eChk_Move_Protocol_Tick = 8,

	};

	//IP/port�� 2��(public/private) �����Ѵ�.
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

	//p2p Ȧ��Ī�� ���� udp ����
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
		HOSTID remote;			//group �ɹ��� �������� �Ҵ���� �ڽ��� host id
		REMOTE_ENTRY_T entry;
		ADDR_IP publicIP;		//publicIP : group �ɹ��� public ip
		ADDR_PORT portTcp;		//tcp port
		ADDR_PORT portUdp;		//udp port
		ADDR_IP privateIP;		//privateIP : group �ɹ��� private ip
		ADDR_PORT privatePort;	//privatePort : group �ɹ��� private port

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
		HOSTID remote_;					//������ ������ �ڽ��� hostid
		REMOTE_ENTRY_T entry_;			//������ ������ �ڽ��� type

		//**** �Ʒ�����(remotePublic... remotePrivate...�� Ŭ���̾�Ʈ�μ��� ��Ȱ�� �մϴ�.
		//IP_ENDPOINT IPAddress_[enMaxEndPoint];
		ADDR_IP remotePublicIP_;		//client��� ������ ����IP		/ ������� ������ client ip
		ADDR_PORT remotePublicTcpPort_;	//client��� ������ ���� port		/ ������� ������ client�� �����μ� port�� ������.
		ADDR_PORT remotePublicUdpPort_;	//�������� Ȯ�ε� client udp port
		ADDR_IP remotePrivateIP_;		//client �ڽ��� private ip 
		ADDR_PORT remotePrivateUdpPort_;//client �ڽ��� private port	

	//public:
		int nHolePunchingAttempt_;				//Ȧ��Ī �õ� ȸ��(�����ϸ� 0���� �ʱ�ȭ, �� ����ȸ���� �ǹ���)
		Hole_Punching_Step stepHolePunching_;	//Ȧ��Ī step
	};

};//..namespace NetCore {