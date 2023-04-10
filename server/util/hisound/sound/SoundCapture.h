#pragma once

#include "SoundSecondary.h"

//��ü�� ��ӹ޾Ƽ� ����ϼ���.(pure virtual function ����)
class SoundCapture// : public HisUtil::CSingleton<SoundCapture>
{
public:
	enum { NUM_OF_BUFFER = 4, };//SOUND_BUFFER�� ó���Ǵ� ���� ���� ���ؼ� 2���� ������.(3���̻��� ���������� �׽�Ʈ ���غ�)

public:
	SoundCapture();
	virtual ~SoundCapture();

	virtual bool init(HWND hwnd, GUID& guidDevice);// , _playType nType, int index);

	virtual bool play();	//record start.
	virtual void stop();	//record end.

public:
	//Mic�� ���� capture�� ����Ÿ�� �޴´�.
	//pure virtual function: ��ӹ��� ��ü���� ������ ����մϴ�.
	//buff:����Ÿ�� ������ ����ϼ���(delete����������)
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

	HANDLE m_hEvents[NUM_OF_BUFFER+1];	//+1: DSBPN_OFFSETSTOP�� ó���� ���Ѱ��ε�, (���� capture�� �ߵǰ� �־)������ �غ����� ���ߴ�
	MMRESULT m_timerID;

};

