#include "stdafx.h"
#include "SoundStreaming.h"


SoundStreaming::SoundStreaming()
{

}

SoundStreaming::SoundStreaming(HWND hwnd)
{
	init(hwnd);
}

SoundStreaming::~SoundStreaming()
{
	close();
}

bool SoundStreaming::init(HWND hwnd)
{
	// Initialize the direct sound interface pointer for the default sound device.
	HRESULT result = DirectSoundCreate8(NULL, &m_directSound, NULL);
	if (FAILED(result))
	{
		_tprintf(_T("DirectSound DirectSoundCreate8 Fail.\n"));
		return false;
	}

	// Set the cooperative level to priority so the format of the primary sound buffer can be modified.
	result = m_directSound->SetCooperativeLevel(hwnd, DSSCL_PRIORITY);
	if (FAILED(result))
	{
		_tprintf(_T("DirectSound SetCooperativeLevel Fail.\n"));
		return false;
	}


	// Setup the primary buffer description.
	DSBUFFERDESC bufferDesc;
	bufferDesc.dwSize			= sizeof(DSBUFFERDESC);
	bufferDesc.dwFlags			= DSBCAPS_PRIMARYBUFFER | DSBCAPS_CTRLVOLUME | DSBCAPS_CTRLPAN;
	bufferDesc.dwBufferBytes	= 0;
	bufferDesc.dwReserved		= 0;
	bufferDesc.lpwfxFormat		= NULL;
	bufferDesc.guid3DAlgorithm	= GUID_NULL;

	// Get control of the primary sound buffer on the default sound device.
	result = m_directSound->CreateSoundBuffer(&bufferDesc, &m_primaryBuffer, NULL);
	if (FAILED(result))
	{
		_tprintf(_T("DirectSound CreateSoundBuffer Fail.\n"));
		return false;
	}

	// Setup the format of the primary sound bufffer.
	// In this case it is a .WAV file recorded at 44,100 samples per second in 16-bit stereo (cd audio format).
	WAVEFORMATEX waveFormat;
	waveFormat.wFormatTag		= WAVE_FORMAT_PCM;
	waveFormat.nSamplesPerSec	= DS_SAMPLE_PER_SEC;
	waveFormat.wBitsPerSample	= DS_BITS_PER_SEC;
	waveFormat.nChannels		= DS_CHANNELS;
	waveFormat.nBlockAlign		= (waveFormat.wBitsPerSample / 8) * waveFormat.nChannels;
	waveFormat.nAvgBytesPerSec	= waveFormat.nSamplesPerSec * waveFormat.nBlockAlign;
	waveFormat.cbSize			= 0;

	// Set the primary buffer to be the wave format specified.
	result = m_primaryBuffer->SetFormat(&waveFormat);
	if (FAILED(result))
	{
		_tprintf(_T("DirectSound SetFormat Fail.\n"));
		return false;
	}

	return true;
}

void SoundStreaming::close()
{
	for(int i=0; i<RapconSound::SOUND_DUAL_CHANNEL; ++i)
		m_poolSecondary[i].Clear();

	m_primaryBuffer.Release();
	m_directSound.Release();
}

bool SoundStreaming::LoadWaveFile(int index, LPTSTR szFileName)
{
	//if (NULL == szFileName)
	//	return false;

	//SoundSecondary* secondary = m_poolSecondary.Find(index);
	//if (NULL == secondary) {
	//	secondary = m_poolSecondary.Create();
	//	secondary->clear();
	//	m_poolSecondary.Insert(index, secondary);
	//}
	//
	//if (false == secondary->LoadWaveFile1(szFileName))
	//	return false;

	//if (false == secondary->CreateSoundBuffer(m_directSound))
	//	return false;

	return true;
}

//개체가 없으면 만들어 준다.
SoundSecondary* SoundStreaming::GetSoundSecondary(_playType type, int index)
{
	SoundSecondary* secondary = m_poolSecondary[type].Find(index);
	if (NULL == secondary) {
		secondary = m_poolSecondary[type].Create();
		secondary->clear();
		m_poolSecondary[type].Insert(index, secondary);

		//buffer도 만들어주고.
		secondary->CreateSoundBuffer(m_directSound);
	}
	return secondary;
}
//bool SoundStreaming::CreateSoundBuffer(_playType type, int index)
//{
//	SoundSecondary* secondary = GetSoundSecondary(type, index);
//	if (NULL == secondary) return false;
//
//	return secondary->CreateSoundBuffer(m_directSound);
//}

bool SoundStreaming::play(int index)
{
	//SoundSecondary* secondary = m_poolSecondary.Find(index);
	//if (NULL == secondary)
	//	return false;

	//secondary->AddStreamBuffer();
	//return secondary->play();
	return true;
}

bool SoundStreaming::play(_playType type, int index, char* data, int size)
{
	SoundSecondary* secondary = GetSoundSecondary(type, index);
	if (NULL == secondary) return false;

	// 스피커 좌우 볼류 설정(-10000 ~ 10000)
	switch (type) {
		case SOUND_RIGHT_CHANNEL:	secondary->setPan(DSBPAN_RIGHT); // 스피커
			break;
		case SOUND_LEFT_CHANNEL:	secondary->setPan(DSBPAN_LEFT); // 헤드셋
			break;
		case SOUND_DUAL_CHANNEL:	secondary->setPan(DSBPAN_CENTER); // 헤드셋 + 스피커
			break;
	}

	secondary->AddStreamBuffer(data, size);
	//TRACE("******* VOICE Play nType(%d), index(%d)\n", type, index);
	return secondary->play();
}

void SoundStreaming::stop(_playType type, int index)
{
	SoundSecondary* secondary = GetSoundSecondary(type, index);
	if (NULL == secondary) return;

	secondary->stop();
}

void SoundStreaming::test(_playType type, int index)
{
	SoundSecondary* secondary = GetSoundSecondary(type, index);
	if (NULL == secondary) return;

	secondary->test();
}

void SoundStreaming::setPan(_playType type, int index, long pan)
{
	SoundSecondary* secondary = GetSoundSecondary(type, index);
	if (NULL == secondary) return;

	//TRACE("++++++++ type(%d),index(%d),pan(%d)\n", type, index, pan);
	secondary->setPan(pan);
}

void SoundStreaming::setVolumn(_playType type, int index, long vol)
{
	SoundSecondary* secondary = GetSoundSecondary(type, index);
	if (NULL == secondary) return;

	//TRACE("++++++++ type(%d),index(%d),vol(%d)\n", type, index, vol);
	secondary->setVolumn(vol);
}
