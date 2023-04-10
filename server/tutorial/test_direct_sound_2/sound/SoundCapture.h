#pragma once

#include "SoundSecondary.h"


class SoundCapture// : public HisUtil::CSingleton<SoundCapture>
{
public:
	enum { NUM_OF_BUFFER = 2, };
public:
	SoundCapture();
	virtual ~SoundCapture();

	virtual bool init(HWND hwnd, GUID& guidDevice);// , _playType nType, int index);

	virtual bool play();
	virtual void stop();

public:
	virtual void ReadCaptureBuffer(byte* buff, DWORD dwBufferBytes) = 0;

private:

	virtual void close();

	bool lock(DWORD dwOffset);

	static void CALLBACK TimerProcess(UINT uTimerID, UINT uMsg, DWORD dwUser, DWORD dw1, DWORD dw2);
	void timer();

protected:

	CComPtr<IDirectSoundCapture8> m_dsCapture;
	CComPtr<IDirectSoundCaptureBuffer> m_captureBuffer;

	HANDLE m_hEvents[NUM_OF_BUFFER+1];
	MMRESULT m_timerID;

};

