#pragma once

#include "SoundSecondary.h"

class SoundPrimary// : public HisUtil::CSingleton<SoundPrimary>
{
public:
	enum _playType { SOUND_LEFT_CHANNEL, SOUND_RIGHT_CHANNEL, SOUND_DUAL_CHANNEL };	//left: HeadSet, right:Speaker

public:
	SoundPrimary();
	virtual ~SoundPrimary();

	//함수 호출순서
	//1. init				: 프로그램 맨 앞에서 호출
	//2. CreateSoundBuffer	: 사용할 개체 or index를 부여가능한 곳에서 호출
	//3. play				: 재생할때.
	//4. Destory			: 프로그램을 종료할 때(main() 끝부분)

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

protected:

	HisUtil::CMemoryPool<int, SoundSecondary> m_poolSecondary[SoundPrimary::SOUND_DUAL_CHANNEL];

	CComPtr<IDirectSound8> m_directSound;
	CComPtr<IDirectSoundBuffer> m_primaryBuffer;

};

