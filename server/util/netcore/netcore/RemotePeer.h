#pragma once

namespace NetCore {

	//Client���� ����� ��������
	//�ڽŰ� ��� Ŭ���̾�Ʈ�� ������ ��´�.
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
		//Ÿ������ �����Դϴ�.(�ڽ��� ������ ���� �ʽ��ϴ�.)

		//������ ������ ����
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
		//..//Ÿ������ �����Դϴ�.(�ڽ��� ������ ���� �ʽ��ϴ�.)
		//========================================================


	private:
		//������ ���� ip
		ADDR_IP serverPublicIP_;			//(�ڽ��� ������ CNetServer::GetPrivateIP() ���� )
		ADDR_PORT serverPublicTcpPort_;		//(�ڽ��� ������ CNetServer::GetTcpPort() ���� )
		ADDR_PORT serverPublicUdpPort_;		//(�ڽ��� ������ CNetServer::GetUdpPort() ���� )
		//ADDR_IP serverPrivateIP_;
		//ADDR_PORT serverPrivateTcpPort_;
		//ADDR_PORT serverPrivateUdpPort_;

		//Ÿ������ �����Դϴ�.(�ڽ��� ������ ���� �ʽ��ϴ�.)
		S_STATUS_T status_;		//struct NetCore::S_STATUS	(�ڽ��� ������ CParam::server_status ���� )
		UINT16 users_;			//���� �����ڼ� (�ڽ��� ������ CAccountManager::pool() ���� )
	};

};//..namespace NetCore {