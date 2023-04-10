#pragma once

#include "SoundStreaming.h"


class RapconSound : public SoundStreaming, public HisUtil::CSingleton<RapconSound>
{

public:
	RapconSound();
	~RapconSound();

	bool play(_playType nType, int index,char* data, int size);
};

