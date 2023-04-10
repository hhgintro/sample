#pragma once

#include "SoundSecondary.h"
#include "../../../util/hisutil/pool/MemoryPool.h"


class SoundPrimary// : public HisUtil::CSingleton<SoundPrimary>
{
public:
	enum _playType { SOUND_LEFT_CHANNEL, SOUND_RIGHT_CHANNEL, SOUND_DUAL_CHANNEL };	//left: HeadSet, right:Speaker

public:
	SoundPrimary();
	virtual ~SoundPrimary();

	//�Լ� ȣ�����
	//1. init				: ���α׷� �� �տ��� ȣ��
	//2. CreateSoundBuffer	: ����� ��ü or index�� �ο������� ������ ȣ��
	//3. play				: ����Ҷ�.
	//4. Destory			: ���α׷��� ������ ��(main() ���κ�)

	bool init(HWND hwnd, GUID& guidDevice);// , _playType nType, int index);
	//bool LoadWaveFile(_playType type, int index, LPTSTR szFileName);

	bool play(_playType type, int index, char* data, int size);
	//bool play(_playType type, int index);
	void stop(_playType type, int index);

	void setPan(_playType type, int index, long pan);
	void setVolumn(_playType type, int index, long vol);

protected:
	SoundSecondary* GetSoundSecondary(_playType type, int index);

	void close();

	bool lock(DWORD nIndex, DWORD dwOffset, DWORD dwBufferBytes);

	static void CALLBACK TimerProcess(UINT uTimerID, UINT uMsg, DWORD dwUser, DWORD dw1, DWORD dw2);
	void timer();

protected:

	HisUtil::CMemoryPool<int, SoundSecondary> m_poolSecondary[SoundPrimary::SOUND_DUAL_CHANNEL];

	CComPtr<IDirectSound8> m_directSound;
	CComPtr<IDirectSoundBuffer> m_primaryBuffer;

};

