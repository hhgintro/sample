#pragma once

#include "SoundCapture.h"


class DispatchCapture : public SoundCapture// : public HisUtil::CSingleton<SoundCapture>
{
public:
	DispatchCapture();
	virtual ~DispatchCapture();

	virtual void ReadCaptureBuffer(byte* buff, DWORD dwBufferBytes);

};

