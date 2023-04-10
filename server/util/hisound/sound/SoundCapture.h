#pragma once

#include "SoundSecondary.h"

//개체를 상속받아서 사용하세요.(pure virtual function 있음)
class SoundCapture// : public HisUtil::CSingleton<SoundCapture>
{
public:
	enum { NUM_OF_BUFFER = 4, };//SOUND_BUFFER를 처리되는 동안 예비를 위해서 2개를 권장함.(3개이상이 가능한지는 테스트 못해봄)

public:
	SoundCapture();
	virtual ~SoundCapture();

	virtual bool init(HWND hwnd, GUID& guidDevice);// , _playType nType, int index);

	virtual bool play();	//record start.
	virtual void stop();	//record end.

public:
	//Mic로 부터 capture된 데이타를 받는다.
	//pure virtual function: 상속받은 개체에서 선언해 줘야합니다.
	//buff:데이타는 복사후 사용하세요(delete하지마세요)
	virtual void ReadCaptureBuffer(byte* buff, DWORD dwBufferBytes) = 0;

protected:
	virtual void close();

private:

	bool lock(DWORD dwOffset);

	//timer thread
	static void CALLBACK TimerProcess(UINT uTimerID, UINT uMsg, DWORD_PTR dwUser, DWORD_PTR dw1, DWORD_PTR dw2);
	void timer();

protected:

	CComPtr<IDirectSoundCapture8> m_dsCapture;
	CComPtr<IDirectSoundCaptureBuffer> m_captureBuffer;

	HANDLE m_hEvents[NUM_OF_BUFFER+1];	//+1: DSBPN_OFFSETSTOP을 처리를 위한것인데, (현재 capture는 잘되고 있어서)검증을 해보지는 못했다
	MMRESULT m_timerID;

};

