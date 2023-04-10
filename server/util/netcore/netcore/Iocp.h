#pragma once

namespace NetCore {

	class CNetServer;

	class CIocp : public HisUtil::CThread
	{
	public:
		CIocp(VOID);
		virtual ~CIocp(VOID);

	protected:
		virtual VOID		OnIoRecv(VOID *object, DWORD dataLength) = 0;
		virtual VOID		OnIoSend(VOID *object, DWORD dataLength) = 0;
		virtual VOID		OnIoConnected(VOID *object) = 0;
		virtual VOID		OnIoDisconnected(VOID *object) = 0;

	public:
		BOOL				Begin(VOID);
		BOOL				End(VOID);

		BOOL				RegisterSocketToIocp(SOCKET socket, ULONG_PTR completionKey);
		virtual void		OnWorkerThread(int index);

		void				SetOwner(void* owner) { owner_ = owner; }
		void*				GetOwner() { return owner_; }

		//void SetEventSink(INetServerEvent* eventsink)	{ ServerEvent_ = eventsink }

	protected:

		//	INetServerEvent*	ServerEvent_;
		//HisUtil::CCritSecBase		csReceive_;	//OnIoRecv() 함수에서 사용중(tcp, udp)

	private:
		HANDLE				IocpHandle_;
		void*				owner_;
	};

};//..namespace NetCore {