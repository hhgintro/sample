#pragma once

#include "SoundSecondary.h"


class SoundStreaming// : public HisUtil::CSingleton<SoundStreaming>
{
public:
	enum _playType { SOUND_LEFT_CHANNEL, SOUND_RIGHT_CHANNEL, SOUND_DUAL_CHANNEL };	//left: HeadSet, right:Speaker

public:
	SoundStreaming();
	SoundStreaming(HWND hwnd);
	virtual ~SoundStreaming();

	//�Լ� ȣ�����
	//1. init				: ���α׷� �� �տ��� ȣ��
	//2. CreateSoundBuffer	: ����� ��ü or index�� �ο������� ������ ȣ��
	//3. play				: ����Ҷ�.
	//4. Destory			: ���α׷��� ������ ��(main() ���κ�)

	bool init(HWND hwnd);
	bool LoadWaveFile(int index, LPTSTR szFileName);
	//bool CreateSoundBuffer(_playType type, int index);

	bool play(int index);
	bool play(_playType type, int index, char* data, int size);
	void stop(_playType type, int index);
	void test(_playType type, int index);

	void setPan(_playType type, int index, long pan);
	void setVolumn(_playType type, int index, long vol);

protected:
	SoundSecondary* GetSoundSecondary(_playType type, int index);

	void close();

	bool lock(DWORD nIndex, DWORD dwOffset, DWORD dwBufferBytes);

	static void CALLBACK TimerProcess(UINT uTimerID, UINT uMsg, DWORD dwUser, DWORD dw1, DWORD dw2);
	void timer();


protected:

	HisUtil::CMemoryPool<int, SoundSecondary> m_poolSecondary[SoundStreaming::SOUND_DUAL_CHANNEL];

	CComPtr<IDirectSound8> m_directSound;
	CComPtr<IDirectSoundBuffer> m_primaryBuffer;

};

