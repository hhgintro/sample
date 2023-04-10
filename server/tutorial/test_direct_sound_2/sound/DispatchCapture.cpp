#include "stdafx.h"
#include "DispatchCapture.h"

#include "DispatchSound.h"

DispatchCapture::DispatchCapture()
{
}

DispatchCapture::~DispatchCapture()
{
}

void DispatchCapture::ReadCaptureBuffer(byte* buff, DWORD dwBufferBytes)
{
	DispatchSound::Instance().play(0, SoundPrimary::SOUND_RIGHT_CHANNEL, 11, (char*)buff, dwBufferBytes);

}

