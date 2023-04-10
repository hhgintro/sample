#pragma once


namespace NetCore {

	class CP2PGroup
	{
		typedef HisUtil::CMemoryPool<HOSTID, IRemote> GROUP_PEER_POOL;

	public:
		CP2PGroup(void);
		~CP2PGroup(void);
		void Clear();

		BOOL JoinGroup(HOSTID host, IRemote* remote);
		BOOL LeaveGroup(HOSTID host);

		P2PGROUPID GetGroupID() { return GroupID_; }
		void SetGroupID(P2PGROUPID id) { GroupID_ = id; }

		GROUP_PEER_POOL& GetGroupPeerPool() { return mapGroupPeer_; }


	private:
		P2PGROUPID GroupID_;
		GROUP_PEER_POOL	mapGroupPeer_;	//Group에 등록된 유저 목록
	};

};//..namespace NetCore {