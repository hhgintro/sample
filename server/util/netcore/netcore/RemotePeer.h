#pragma once

namespace NetCore {

	//Client에서 사용을 목적으로
	//자신과 상대 클라이언트의 정보를 담는다.
	class CRemotePeer : public IRemote
	{
	public:
		CRemotePeer(void)
			//: serverPublicIP_(0), serverPublicTcpPort_(0), serverPublicUdpPort_(0)
			////, serverPrivateIP_(0), serverPrivateTcpPort_(0), serverPrivateUdpPort_(0)
			//, status_(0), users_(0)
		{}
		virtual ~CRemotePeer(void) {}

		virtual void Clear() {
			IRemote::Clear();
			//memset(&serverInfo_, 0, sizeof(serverInfo_));

			serverPublicIP_			= 0;
			serverPublicTcpPort_	= 0;
			serverPublicUdpPort_	= 0;
			status_					= 0;
			users_					= 0;
		}

		//========================================================
		//타서버의 정보입니다.(자신의 정보는 담지 않습니다.)

		//접속할 서버의 정보
		ADDR_IP GetServerPublicIP()						{ return serverPublicIP_; }
		void SetServerPublicIP(ADDR_IP ip)				{ serverPublicIP_  = ip; }

		ADDR_PORT GetServerPublicTcpPort()				{ return serverPublicTcpPort_; }
		void SetServerPublicTcpPort(ADDR_PORT port)		{ serverPublicTcpPort_ = port; }

		ADDR_PORT GetServerPublicUdpPort()				{ return serverPublicUdpPort_; }
		void SetServerPublicUdpPort(ADDR_PORT port)		{ serverPublicUdpPort_ = port; }

		//ADDR_IP GetServerPrivateIP()					{ return serverPrivateIP_; }
		//void SetServerPrivateIP(ADDR_IP ip)			{ serverPrivateIP_ = ip; }

		//ADDR_PORT GetServerPrivateTcpPort()			{ return serverPrivateTcpPort_; }
		//void SetServerPrivateTcpPort(ADDR_PORT port)	{ serverPrivateTcpPort_ = port; }

		//ADDR_PORT GetServerPrivateUdpPort()			{ return serverPrivateUdpPort_; }
		//void SetServerPrivateUdpPort(ADDR_PORT port)	{ serverPrivateUdpPort_ = port; }


		S_STATUS_T GetServerStatus()					{ return status_; }
		void SetServerStatus(S_STATUS_T status)			{ status_ = status; }

		UINT16 GetCurrentUsers()						{ return users_; }
		void SetCurrentUsers(UINT16 users)				{ users_ = users; }
		//..//타서버의 정보입니다.(자신의 정보는 담지 않습니다.)
		//========================================================


	private:
		//접속할 서버 ip
		ADDR_IP serverPublicIP_;			//(자신의 정보는 CNetServer::GetPrivateIP() 참조 )
		ADDR_PORT serverPublicTcpPort_;		//(자신의 정보는 CNetServer::GetTcpPort() 참조 )
		ADDR_PORT serverPublicUdpPort_;		//(자신의 정보는 CNetServer::GetUdpPort() 참조 )
		//ADDR_IP serverPrivateIP_;
		//ADDR_PORT serverPrivateTcpPort_;
		//ADDR_PORT serverPrivateUdpPort_;

		//타서버의 정보입니다.(자신의 정보는 담지 않습니다.)
		S_STATUS_T status_;		//struct NetCore::S_STATUS	(자신의 정보는 CParam::server_status 참조 )
		UINT16 users_;			//동시 접속자수 (자신의 정보는 CAccountManager::pool() 참조 )
	};

};//..namespace NetCore {