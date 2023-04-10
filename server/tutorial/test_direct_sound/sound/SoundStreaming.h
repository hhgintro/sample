#pragma once

#include "SoundSecondary.h"


class SoundStreaming : public HisUtil::CSingleton<SoundStreaming>
{

public:
	SoundStreaming();
	SoundStreaming(HWND hwnd);
	~SoundStreaming();

	//함수 호출순서
	//1. init				: 프로그램 맨 앞에서 호출
	//2. CreateSoundBuffer	: 사용할 개체 or index를 부여가능한 곳에서 호출
	//3. play				: 재생할때.
	//4. Destory			: 프로그램을 종료할 때(main() 끝부분)

	bool init(HWND hwnd);
	bool LoadWaveFile(int index, DWORD buflen, LPTSTR szFileName);
	bool CreateSoundBuffer(int index, DWORD buflen);

	bool play(int index);
	bool play(int index, char* data, int size);
	void stop(int index);
	void test(int index);

	void setPan(int index, long pan);
	void setVolumn(int index, long vol);

protected:
	void close();

	bool lock(DWORD nIndex, DWORD dwOffset, DWORD dwBufferBytes);


	static void CALLBACK TimerProcess(UINT uTimerID, UINT uMsg, DWORD dwUser, DWORD dw1, DWORD dw2);
	void timer();



protected:

	HisUtil::CMemoryPool<int, SoundSecondary> m_poolSecondary;

	CComPtr<IDirectSound8> m_directSound;
	CComPtr<IDirectSoundBuffer> m_primaryBuffer;

};

