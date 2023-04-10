#pragma once

//#include <iostream>
//#include <math.h>

class IGameObject;

struct Telegram
{
	//TELEGRAMINDEX m_index;//식별번호

	//the entity that sent this telegram
	IGameObject* Sender;

	//the entity that is to receive this telegram
	IGameObject* Receiver;

	//the message itself. These are all enumerated in the file
	//"MessageTypes.h"
	message_type Msg;

	//messages can be dispatched immediately or delayed for a specified amount
	//of time. If a delay is necessary this field is stamped with the time 
	//the message should be dispatched.
	TIME_T DispatchTime;

	//any additional information that may accompany the message
	void* ExtraInfo1;
	void* ExtraInfo2;


	Telegram() : DispatchTime(-1), Sender(0), Receiver(0), Msg(notmessage) {}
	Telegram(TIME_T time, IGameObject* sender, IGameObject* receiver, message_type msg, void* info1 = NULL, void* info2 = NULL)
		: DispatchTime(time), Sender(sender), Receiver(receiver), Msg(msg), ExtraInfo1(info1), ExtraInfo2(info2)
	{
		//LOGEVENT("HG_BLUE", _T("time(%I64d), receiver(%x), msg(%d)"), time, receiver, msg);
	}

	void Set(TIME_T time, IGameObject* sender, IGameObject* receiver, message_type msg, void* info1 = NULL, void* info2 = NULL)
	{
		DispatchTime = time;
		Sender = sender;
		Receiver = receiver;
		Msg = msg;
		ExtraInfo1 = info1;
		ExtraInfo2 = info2;
		//LOGEVENT("HG_BLUE", _T("time(%I64d), receiver(%x), msg(%d)"), time, receiver, msg);
	}

	BOOL operator == (const Telegram& rhs)
	{
		if(DispatchTime != rhs.DispatchTime)
			return FALSE;
		if(Sender != rhs.Sender)
			return FALSE;
		if(Receiver != rhs.Receiver)
			return FALSE;
		if(Msg != rhs.Msg)
			return FALSE;
		return TRUE;
	}

};

template<class T>
struct TIME_COMPARE
{
	bool operator () (const T& t1, const T& t2) const
	{
		return (t1.DispatchTime < t2.DispatchTime);
	}
	bool operator () (const T* t1, const T* t2) const
	{
		return (t1->DispatchTime < t2->DispatchTime);
	}
};

//these telegrams will be stored in a priority queue. Therefore the >
//operator needs to be overloaded so that the PQ can sort the telegrams
//by time priority. Note how the times must be smaller than
//SmallestDelay apart before two Telegrams are considered unique.
const TIME_T SmallestDelay = 500;


inline bool operator==(const Telegram& t1, const Telegram& t2)
{
	return ( abs((double)(t1.DispatchTime-t2.DispatchTime) < SmallestDelay)
		&& (t1.Sender == t2.Sender)
		&& (t1.Receiver == t2.Receiver)
		&& (t1.Msg == t2.Msg));
}

inline bool operator<(const Telegram& t1, const Telegram& t2)
{
	if (t1 == t2)		return false;
	return  (t1.DispatchTime < t2.DispatchTime);
}

inline std::ostream& operator<<(std::ostream& os, const Telegram& t)
{
	//os << "time: " << t.DispatchTime << "  Sender: " << t.Sender
	//	<< "   Receiver: " << t.Receiver << "   Msg: " << t.Msg;

  return os;
}

//handy helper function for dereferencing the ExtraInfo field of the Telegram 
//to the required type.
template <class T>
inline T DereferenceToType(void* p)
{
	return *(T*)(p);
}
