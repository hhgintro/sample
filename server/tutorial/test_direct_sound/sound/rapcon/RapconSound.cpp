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
	// ����Ŀ �¿� ���� ����(-10000 ~ 10000)
	if (nType == SOUND_RIGHT_CHANNEL)     setPan(nType, index, DSBPAN_RIGHT); // ����Ŀ
	else if (nType == SOUND_LEFT_CHANNEL) setPan(nType, index, DSBPAN_LEFT); // ����
	else if (nType == SOUND_DUAL_CHANNEL) setPan(nType, index, DSBPAN_CENTER); // ���� + ����Ŀ

	//TRACE("******* VOICE Play nType(%d), index(%d)\n", nType, index);
	return SoundStreaming::play(nType, index, data, size);
}
