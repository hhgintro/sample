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
	//TIME_T FirstInfo(int pos);	//�Ǿ��� telegram �ð��� �����´�.(ó�� 0:queue, 1~: msg pool)
	void AllExcute(int pos);	//�ð�������� �ٷ� �����Ų��.
	void AllRelease(int pos);	//������� �׳� ������.	


	//send a message to another agent. Receiving agent is referenced by ID.
	//return�Ǵ� Telegram* �� ������ Skip �� �����ϵ��� ó����.
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

	TIME_T updatetime_;	//Thread update �ð�


	//�ð��� �������� ������ telegram�� ��쿡��
	//�̰��� �־� ó���ϴ°� �����ϴ�.
	//Dispatch_Message() �Լ��� bStaticTime �� TRUE�� �����մϴ�.
	TELEGRAM_QUEUE_POOL telegrampool_[eMax_Message_Type];


	
	CModuleManager m_module;
};


//to make life easier...
#define Dispatch MessageDispatcher::Instance()
