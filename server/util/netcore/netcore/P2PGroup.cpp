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
		////����Ʈ�� ������ ����Ʈ�� �ʱ�ȭ�Ѵ�.
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
	//	//group �ɹ��� �ƴϴ�.
	//	if (NULL == mapGroupPeer_.Find(remote->GetHostID()))
	//		return false;

	//	if(NULL == mapHolePunchingReady_.Find(remote->GetHostID()))
	//		mapHolePunchingReady_.Insert(remote->GetHostID(), remote);

	//	//peer�� ready�� ���� ���Ѵ�.
	//	if (mapHolePunchingReady_.GetUsedMemSize() < mapGroupPeer_.GetUsedMemSize())
	//		return false;//�̵�ϵ� remote�� �ֱ�
	//	return true;//��� ��ϿϷ�
	//}

};//..namespace NetCore {