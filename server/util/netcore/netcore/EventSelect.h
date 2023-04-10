#pragma once

namespace NetCore {

	class CNetClient;

	class CEventSelect : public HisUtil::CThread
	{
	public:
		CEventSelect(VOID);
		virtual ~CEventSelect(VOID);

	private:
		HANDLE mSelectEventHandle;
		SOCKET socket_;

	protected:
		virtual VOID	OnIoConnected(VOID) = 0;
		virtual VOID	OnIoDisconnected(VOID) = 0;
		virtual VOID	OnIoRecv(VOID) = 0;
		virtual VOID	OnIoSend(VOID) = 0;

	public:
		BOOL Begin(SOCKET socket);
		BOOL End(VOID);

		VOID OnWorkerThread(int index);


		void				SetOwner(CNetClient* client) { owner_ = client; }
		CNetClient*			GetOwner() { return owner_; }

		//	void SetEventSink(INetClientEvent* eventsink)	{ ClientEvent_ = eventsink; }

	protected:
		CNetClient*			owner_;
		//	INetClientEvent*	ClientEvent_;

	};

};//..namespace NetCore {