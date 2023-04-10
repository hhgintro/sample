#pragma once



//���� ��� ��û
struct stC2M_MT_SERVER_LIST_REQ
{
	stC2M_MT_SERVER_LIST_REQ()
	{
	}

};


//���� ��� ��û�� ���� ����
//	stRemoteEndpoint : ���� ����
struct stC2M_MT_SERVER_LIST_ACK
{
	stC2M_MT_SERVER_LIST_ACK()
	{
	}

	std::vector<stRemoteEndpoint> serverinfo;
};


//���� �߰� ��û
struct stC2M_MT_ADD_SERVER_REQ
{
	stC2M_MT_ADD_SERVER_REQ()
	{
	}

};


//���� �߰� ��û�� ���� ����
//	stRemoteEndpoint : ���� ����
struct stC2M_MT_ADD_SERVER_ACK
{
	stC2M_MT_ADD_SERVER_ACK()
	{
	}

	std::vector<stRemoteEndpoint> serverinfo;
};


//���� ���� ��û
struct stC2M_MT_DELETE_SERVER_REQ
{
	stC2M_MT_DELETE_SERVER_REQ()
	{
	}

};


//���� ���� ��û�� ���� ����
//	remote : ������ HostID
struct stC2M_MT_DELETE_SERVER_ACK
{
	stC2M_MT_DELETE_SERVER_ACK()
		: remote(0)
	{
	}

	HOSTID remote;
};


//���� ���� ��û�� ���� ����
//	remote : ������ HostID
struct stC2M_MT_GAME_SERVER_INFO_NTF
{
	stC2M_MT_GAME_SERVER_INFO_NTF()
	{
	}

	std::vector<_stGameServerInfo> gameinfo;
};


//���� status ���� ��û
//	remote : shutdown��ų HostID
//	status : server ���� (S_STATUS ����)
struct stC2M_MT_CHANGE_SERVER_STATUS_REQ
{
	stC2M_MT_CHANGE_SERVER_STATUS_REQ()
		: remote(0)
	{
	}

	HOSTID remote;
	S_STATUS_T status;
};


//���� status ���� ��û�� ���� ����
//	remote : shutdown��ų HostID
//	status : server ���� (S_STATUS ����)
struct stC2M_MT_CHANGE_SERVER_STATUS_ACK
{
	stC2M_MT_CHANGE_SERVER_STATUS_ACK()
		: remote(0)
	{
	}

	HOSTID remote;
	S_STATUS_T status;
};


//���� Launch ��û
//	_stLaunchServerInfo : launch ��ų server����
struct stC2M_MT_SERVER_LAUNCH_REQ
{
	stC2M_MT_SERVER_LAUNCH_REQ()
	{
	}

	std::vector<_stLaunchServerInfo> serverinfo;
};


//���� Launch ��û�� ���� ����
//[encrypt] MT_SERVER_LAUNCH_ACK()
//���� Shutdown ��û
//	_stLaunchServerInfo : shutdown ��ų server����
struct stC2M_MT_SERVER_SHUTDOWN_REQ
{
	stC2M_MT_SERVER_SHUTDOWN_REQ()
	{
	}

	std::vector<_stLaunchServerInfo> serverinfo;
};


//���� Shutdown ��û�� ���� ����
//[encrypt] MT_SERVER_SHUTDOWN_ACK()
//���� ��� �ʱ�ȭ
struct stC2M_MT_CLEAR_SERVER_LIST_NTF
{
	stC2M_MT_CLEAR_SERVER_LIST_NTF()
	{
	}

};
