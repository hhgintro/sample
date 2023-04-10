#include "stdafx.h"
#include "RapconSound.h"


RapconSound::RapconSound()
{

}

RapconSound::~RapconSound()
{
	close();
}

bool RapconSound::play(_playType nType, int index, char* data, int size)
{
	// 스피커 좌우 볼류 설정(-10000 ~ 10000)
	if (nType == SOUND_RIGHT_CHANNEL)     setPan(nType, index, DSBPAN_RIGHT); // 스피커
	else if (nType == SOUND_LEFT_CHANNEL) setPan(nType, index, DSBPAN_LEFT); // 헤드셋
	else if (nType == SOUND_DUAL_CHANNEL) setPan(nType, index, DSBPAN_CENTER); // 헤드셋 + 스피커

	//TRACE("******* VOICE Play nType(%d), index(%d)\n", nType, index);
	return SoundStreaming::play(nType, index, data, size);
}
