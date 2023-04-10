#pragma once

#pragma warning (disable:4786)

#include <set>


//#include "misc/ConsoleUtils.h"
#include "Telegram.h"

class IGameObject;


////to make code easier to read
//const TIME_T SEND_MSG_IMMEDIATELY = 0;
//const int   NO_ADDITIONAL_INFO   = 0;


class MessageDispatcher : public CThread, public Proud::CSingleton<MessageDispatcher>
{
	//typedef std::multiset<Telegram, TIME_COMPARE<Telegram> >		TELEGRAM_QUEUE_SET;
	//typedef CMemoryQueuePool<Telegram>							TELEGRAM_QUEUE_POOL;
	typedef CMemoryMultiSetPool<Telegram, TIME_COMPARE<Telegram> >	TELEGRAM_QUEUE_POOL;

public:
	MessageDispatcher();
	~MessageDispatcher();

	void Init();
	//TIME_T FirstInfo(int pos);	//맨앞의 telegram 시간을 가져온다.(처음 0:queue, 1~: msg pool)
	void AllExcute(int pos);	//시간관계없이 바로 실행시킨다.
	void AllRelease(int pos);	//실행없이 그냥 날린다.	


	//send a message to another agent. Receiving agent is referenced by ID.
	//return되는 Telegram* 을 가지고 Skip 이 가능하도록 처리함.
	//Telegram* Dispatch_Message(TIME_T delay, IGameObject* sender, IGameObject* receiver, message_type msg, void* ExtraInfo1, void* ExtraInfo2);
	BOOL Dispatch_Message(TIME_T delay, IGameObject* sender, IGameObject* receiver, message_type msg, void* ExtraInfo1, void* ExtraInfo2);

	//send out any delayed messages. This method is called each time through   
	//the main game loop.
	void Update();

	////skip telegram(non delay)
	//void Dispatch_Skip_Messages(TELEGRAMINDEX telegramindex);

	////ignore telegram 
	//void Dispatch_Ignore_Message(TELEGRAMINDEX telegramindex);

	void OnWorkerThread(int index);

private:
	//copy ctor and assignment should be private
	MessageDispatcher(const MessageDispatcher&);
	MessageDispatcher& operator=(const MessageDispatcher&);

	//this method is utilized by DispatchMessage or DispatchDelayedMessages.
	//This method calls the message handling member function of the receiving
	//entity, pReceiver, with the newly created telegram
	void Discharge(IGameObject* pReceiver, const Telegram& msg);


	//void AddTelegram(TIME_T time, IGameObject* sender, IGameObject* receiver, message_type msg, void* ExtraInfo1, void* ExtraInfo2);
	//int DispatchDelayedMessages(TIME_T CurrentTime);
	int DispatchDelayedPoolMessages(TIME_T CurrentTime, TELEGRAM_QUEUE_POOL& telegrampool);

private:

	TIME_T updatetime_;	//Thread update 시간


	//시간이 고정값을 가지는 telegram인 경우에는
	//이곳에 넣어 처리하는게 유용하다.
	//Dispatch_Message() 함수의 bStaticTime 을 TRUE로 설정합니다.
	TELEGRAM_QUEUE_POOL telegrampool_[eMax_Message_Type];


	
	CModuleManager m_module;
};


//to make life easier...
#define Dispatch MessageDispatcher::Instance()
