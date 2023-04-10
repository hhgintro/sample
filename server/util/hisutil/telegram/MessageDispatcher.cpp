#include "stdafx.h"
#include "MessageDispatcher.h"
#include "MessageTypes.h"



MessageDispatcher::MessageDispatcher()
	: updatetime_(0)
{
	//telegramindex_ = 0;
	//telegrampool_.Init(10000);
	for(int i=0; i<eMax_Message_Type; ++i)
		telegrampool_[i].Init(100);	//n개 메모리를 확보해 둔다.


	_stTime time(2099, 12, 23, 12, 00, 0);
	m_module.Init(time);

	//Init();
}

MessageDispatcher::~MessageDispatcher()
{
	CThread::EndThread();
}

void MessageDispatcher::Init()
{
	SYSTEM_INFO SystemInfo;
	GetSystemInfo(&SystemInfo);
	CThread::BeginThread(SystemInfo.dwNumberOfProcessors * 10);//1
}

//TIME_T MessageDispatcher::FirstInfo(int pos)
//{
//	if(eMax_Message_Type <= pos)
//		return 0;
//
//	Telegram* telegram = telegrampool_[pos].Front();
//	if(NULL == telegram)
//		return 0;
//
//	return telegram->DispatchTime;
//}

void MessageDispatcher::AllExcute(int pos)
{
	if(eMax_Message_Type <= pos)
		return;

	DispatchDelayedPoolMessages(0xffffffffffffffffui64, telegrampool_[pos]);
}

void MessageDispatcher::AllRelease(int pos)
{
	if(eMax_Message_Type <= pos)
		return;

	telegrampool_[pos].Release();
}

//----------------------------- Dispatch ---------------------------------
//  
//  see description in header
//------------------------------------------------------------------------
void MessageDispatcher::Discharge(IGameObject* pReceiver,
                                  const Telegram& telegram)
{
	if (!pReceiver->HandleMessage(telegram))
		LOGEVENT("HG_RED", _T("telegram could not be handled") );
}

//---------------------------- DispatchMessage ---------------------------
//
//  given a message, a receiver, a sender and any time delay , this function
//  routes the message to the correct agent (if no delay) or stores
//  in the message queue to be dispatched at the correct time
//------------------------------------------------------------------------
//Telegram* MessageDispatcher::Dispatch_Message(TIME_T delay,
BOOL MessageDispatcher::Dispatch_Message(TIME_T delay,
                                        IGameObject* sender,
                                        IGameObject* receiver,
                                        message_type msg,
                                        void* ExtraInfo1,
										void* ExtraInfo2)
{
	//get pointers to the sender and receiver
	//IGameObject* pSender   = CObjectManager::GetInstance()->FindGameObjectInfo(sender);
	//IGameObject* pReceiver = CObjectManager::GetInstance()->FindGameObjectInfo(receiver);

	//make sure the receiver is valid
	if(NULL == receiver)
	{
		LOGEVENT("HG_GRAY", _T("Warning! No Receiver with ID of %08x found"), receiver);
		return FALSE;
	}

	//등록할 수 없는 정보
	if(msg <= notmessage || eMax_Message_Type <= msg)
		return FALSE;

	//모듈 보호
	if(FALSE == m_module.CheckValid())
		return FALSE;


	Telegram* telegram = telegrampool_[msg].Create();
	telegram->Set(GetTickCount64() + delay, sender, receiver, msg, ExtraInfo1, ExtraInfo2);
	telegrampool_[msg].Insert(telegram);


	{/*@@Debug 목적*/
		int usedMem = telegrampool_[msg].GetUsedMemSize();
		int freeMem = telegrampool_[msg].GetFreeMemSize();
		int leakMem = telegrampool_[msg].GetLeakMemSize();

		if(MAX_DEBUG_POOL_SIZE < usedMem
			|| MAX_DEBUG_POOL_SIZE < freeMem
			|| MAX_DEBUG_LEAK_POOL_SIZE < leakMem)
		{
			if(TRUE == telegrampool_[msg].GetIsLogTime())
			LOGEVENT("HG_RED", _T("******** %s(%d):used(%d), free(%d), leak(%d), pool 개수가 정상인지 체크하세요 *******")
				, Proud::StringA2W(__FILE__), __LINE__, Proud::StringA2W(typeid(this).name()), usedMem, freeMem, leakMem);
		}
	}

	//LOGEVENT("HG_CYAN", _T("add telegram(%d)"), msg);
	//LOGEVENT("HG_GRAY"
	//	, _T("지연된 메시지 전달 from  %s 기록시간:%f for %s. Msg is %s")
	//	, GetNameOfEntity(pSender->ID()), Clock->GetCurrentTime(), GetNameOfEntity(pReceiver->ID()),  MsgToStr(msg));

	return TRUE;
}

//void MessageDispatcher::AddTelegram(TIME_T time, IGameObject* sender, IGameObject* receiver, message_type msg, void* ExtraInfo1, void* ExtraInfo2)
//{
//	Proud::CriticalSectionLock(m_cs, true);
//
//	//and put it in the queue
//	PriorityQ.insert(Telegram(time, sender, receiver, msg, ExtraInfo1, ExtraInfo2));   
//}

//int MessageDispatcher::DispatchDelayedMessages(TIME_T CurrentTime)
//{
//	int sizeQueue = 0;
//	{
//		Proud::CriticalSectionLock(m_cs, true);
//		//AUTO_LOCK(csPatch_);
//
//		//int count = PriorityQ.size();
//		TELEGRAM_QUEUE_SET::iterator iter;
//		for(iter = PriorityQ.begin(); iter != PriorityQ.end(); )
//		{
//			//read the telegram from the front of the queue
//			//TELEGRAM_QUEUE_SET::iterator iter = PriorityQ.begin();
//			const Telegram telegram = *iter;
//			//if(NULL == telegram)
//			//	continue;
//
//			//ignore이면...무시
//			//if(NULL == ignorepool_.Find(telegramindex))
//			{
//				//시간순으로 정렬되기 때문에
//				//telegram의 실행 시간이 되지 않았다면, 뒤쪽 telegram은 체크할 필요도 없다.
//				if(CurrentTime < telegram.DispatchTime)
//					break;
//
//				//send the telegram to the recipient
//				Discharge(telegram.Receiver, telegram);
//			}
//
//			//remove it from the queue
//			iter = PriorityQ.erase(iter);
//			//telegrampool_.Erase(telegram.m_index);
//			//ignorepool_.Erase(telegram.m_index);
//		}
//
//		sizeQueue = (int)PriorityQ.size();
//	}
//
//	return sizeQueue;
//}

int MessageDispatcher::DispatchDelayedPoolMessages(TIME_T CurrentTime, TELEGRAM_QUEUE_POOL& telegrampool)
{
	if(telegrampool.GetUsedMemSize() <= 0)
		return 0;

	while(1)
	{
		Sleep(1);

		Telegram* telegram = telegrampool.GetFirstData();
		if(NULL == telegram)
			break;

		//시간순으로 정렬되기 때문에
		//telegram의 실행 시간이 되지 않았다면, 뒤쪽 telegram은 체크할 필요도 없다.
		if(CurrentTime < telegram->DispatchTime)
		{
			telegrampool.Insert(telegram);
			break;
		}

		//send the telegram to the recipient
		Discharge(telegram->Receiver, *telegram);
		//LOGEVENT("HG_CYAN", _T("delete telegram(%d)"), telegram->Msg);
		telegrampool.Erase(telegram);
	}

	return telegrampool.GetUsedMemSize();
}

//지우지 마세요....참고 교육용(견본)
//void MessageDispatcher::DispatchDelayedMessages()
//{
//	Proud::CriticalSectionLock(m_cs, true);
//	//AUTO_LOCK(csPatch_);
//
//	//get current time
//	TIME_T CurrentTime = GetTickCount64();
//
//	////HG_TEST : 처리량 체크
//	//{
//	//	static TIME_T elipsetime = CurrentTime;
//	//	if(elipsetime + TIME_SEC(30) < CurrentTime)
//	//	{
//	//		elipsetime = CurrentTime;
//	//		LOGEVENT("HG_YELLOW", _T("MessageDispatcher 처리량 : %d"), PriorityQ.size());
//	//	}
//	//}
//
//
//	//static TIME_T time = GetTickCount64() + TIME_SEC(10);
//	//if(time < GetTickCount64())
//	//{
//	//	time = GetTickCount64() + TIME_SEC(10);
//	//	//_tprintf(_T("*************PriorityQ(%d), telegrampool_(%d)********\n"), PriorityQ.size(), telegrampool_.GetUsedMemSize());
//	//}
//
//
//	//now peek at the queue to see if any telegrams need dispatching.
//	//remove all telegrams from the front of the queue that have gone
//	//past their sell by date
//	//while(FALSE == PriorityQ.empty())
//	int count = PriorityQ.size();
//	TELEGRAM_QUEUE_SET::iterator iter;
//	for(iter = PriorityQ.begin(); iter != PriorityQ.end(); )
//	{
//		//read the telegram from the front of the queue
//		//TELEGRAM_QUEUE_SET::iterator iter = PriorityQ.begin();
//		const Telegram telegram = *iter;
//		//if(NULL == telegram)
//		//	continue;
//
//		//ignore이면...무시
//		//if(NULL == ignorepool_.Find(telegramindex))
//		{
//			//시간순으로 정렬되기 때문에
//			//telegram의 실행 시간이 되지 않았다면, 뒤쪽 telegram은 체크할 필요도 없다.
//			if(CurrentTime < telegram.DispatchTime)
//				break;
//
//			//send the telegram to the recipient
//			Discharge(telegram.Receiver, telegram);
//		}
//
//		//remove it from the queue
//		iter = PriorityQ.erase(iter);
//		//telegrampool_.Erase(telegram.m_index);
//		//ignorepool_.Erase(telegram.m_index);
//	}
//
//	////now peek at the queue to see if any telegrams need dispatching.
//	////remove all telegrams from the front of the queue that have gone
//	////past their sell by date
//	////while(FALSE == PriorityQ.empty())
//	//std::vector<Telegram*> vecAll;
//	//telegrampool_.GetAllList(vecAll);
//	//for(int i=0; i<(int)vecAll.size(); ++i)
//	//{
//	//	//read the telegram from the front of the queue
//	//	//TELEGRAM_QUEUE_SET::iterator iter = PriorityQ.begin();
//	//	const Telegram& telegram = *vecAll[i];
//
//	//	//ignore이면...무시
//	//	//if(NULL == ignorepool_.Find(telegramindex))
//	//	{
//	//		if(CurrentTime < telegram.DispatchTime)
//	//			continue;
//
//	//		//send the telegram to the recipient
//	//		Discharge(telegram.Receiver, telegram);
//	//	}
//
//	//	//remove it from the queue
//	//	//iter = PriorityQ.erase(iter);
//	//	telegrampool_.Erase(telegram.m_index);
//	//	//ignorepool_.Erase(telegram.m_index);
//	//}
//
//	static TIME_T timeCheck = 0;
//	if(timeCheck < GetTickCount64())
//	{
//		LOGEVENT("HG_YELLOW", _T("******* telegram count = %d *******"), PriorityQ.size());
//		timeCheck = GetTickCount64() + TIME_MIN(1);
//	}
//}


//---------------------- Update -------------------------
//
//  This function dispatches any telegrams with a timestamp that has
//  expired. Any dispatched telegrams are removed from the queue
//------------------------------------------------------------------------
void MessageDispatcher::Update()
{
	TIME_T CurrentTime = GetTickCount64();
	//if(CurrentTime < updatetime_)
	//	return;
	//updatetime_ = CurrentTime + TIME_MSEC(100);

	// 0 : notmessage 이므로 무시합니다.
	int count = 0;
	
	//{
	//	count += DispatchDelayedMessages(CurrentTime);
	//	buff.Format(_T("Q(%d)"), count);
	//}

	//notmessage : 1부터 시작한다.
	for(int i=0; i<eMax_Message_Type; ++i)
		DispatchDelayedPoolMessages(CurrentTime, telegrampool_[i]);


	//log
	static TIME_T timeCheck = GetTickCount64() + TIME_MIN(1);
	if(timeCheck < GetTickCount64())
	{
		timeCheck = GetTickCount64() + TIME_MIN(1);

		Proud::String buff;
		for(int i=0; i<eMax_Message_Type; ++i)
		{
			int cnt = telegrampool_[i].GetUsedMemSize();
			if(0 < cnt)
			{
				count += cnt;
				Proud::String temp;
				temp.Format(_T(" t%02d(%d)"), i, cnt);
				buff.Append(temp.GetString());
			}
		}
		LOGEVENT("HG_YELLOW", _T("******* telegram count = %d(%s) *******"), count, buff.GetString());
	}
}

//
//void MessageDispatcher::Dispatch_Skip_Messages(TELEGRAMINDEX telegramindex)
//{
//	//Proud::CriticalSectionLock(m_cs, true);
//	//AUTO_LOCK(csPatch_);
//
//	Telegram* telegram = telegrampool_.Find(telegramindex);
//	if(NULL == telegram)
//		return;
//
//	//ignore이면...무시
//	//if(NULL == ignorepool_.Find(telegramindex))
//	{
//		//send the telegram to the recipient
//		Discharge(telegram->Receiver, *telegram);
//	}
//
//	telegrampool_.Erase(telegramindex);
//	//ignorepool_.Erase(telegramindex);
//}
//
//void MessageDispatcher::Dispatch_Ignore_Message(TELEGRAMINDEX telegramindex)
//{
//	Telegram* telegram = telegrampool_.Find(telegramindex);
//	if(NULL == telegram)
//		return;
//
//	//ignorepool_.Insert(telegram->m_index, telegram);
//}
//

void MessageDispatcher::OnWorkerThread(int index)
{
	while(TRUE == IsRunning())
	{
		Sleep(1);

		Update();
	}
}
