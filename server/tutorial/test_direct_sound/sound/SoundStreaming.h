#pragma once

#include "SoundSecondary.h"


class SoundStreaming : public HisUtil::CSingleton<SoundStreaming>
{

public:
	SoundStreaming();
	SoundStreaming(HWND hwnd);
	~SoundStreaming();

	//�Լ� ȣ�����
	//1. init				: ���α׷� �� �տ��� ȣ��
	//2. CreateSoundBuffer	: ����� ��ü or index�� �ο������� ������ ȣ��
	//3. play				: ����Ҷ�.
	//4. Destory			: ���α׷��� ������ ��(main() ���κ�)

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

