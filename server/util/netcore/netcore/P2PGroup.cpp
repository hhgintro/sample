#include "stdafx.h"
#include "P2PGroup.h"

namespace NetCore {

	CP2PGroup::CP2PGroup(void)
		: GroupID_(0)
	{
	}

	CP2PGroup::~CP2PGroup(void)
	{
		Clear();
	}

	void CP2PGroup::Clear()
	{
		GetGroupPeerPool().End();
	}

	BOOL CP2PGroup::JoinGroup(HOSTID host, IRemote* remote)
	{
		////리스트에 없으면 리스트를 초기화한다.
		//if (NULL != mapGroupPeer_.Find(host))
		//	mapHolePunchingReady_.Clear();

		return GetGroupPeerPool().Insert(host, remote);
	}

	BOOL CP2PGroup::LeaveGroup(HOSTID host)
	{
		GetGroupPeerPool().Erase(host);
		return true;
	}

	//bool CP2PGroup::IsHolePunchingReady(IRemote* remote)
	//{
	//	//group 맴버가 아니다.
	//	if (NULL == mapGroupPeer_.Find(remote->GetHostID()))
	//		return false;

	//	if(NULL == mapHolePunchingReady_.Find(remote->GetHostID()))
	//		mapHolePunchingReady_.Insert(remote->GetHostID(), remote);

	//	//peer와 ready의 수를 비교한다.
	//	if (mapHolePunchingReady_.GetUsedMemSize() < mapGroupPeer_.GetUsedMemSize())
	//		return false;//미등록된 remote가 있군
	//	return true;//모두 등록완료
	//}

};//..namespace NetCore {