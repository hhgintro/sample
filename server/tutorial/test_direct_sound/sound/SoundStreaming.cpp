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
	bufferDesc.dwFlags			= DSBCAPS_PRIMARYBUFFER | DSBCAPS_CTRLVOLUME;
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
	m_poolSecondary.Clear();

	m_primaryBuffer.Release();
	m_directSound.Release();
}

bool SoundStreaming::LoadWaveFile(int index, DWORD buflen, LPTSTR szFileName)
{
	if (NULL == szFileName)
		return false;

	SoundSecondary* secondary = m_poolSecondary.Find(index);
	if (NULL == secondary) {
		secondary = m_poolSecondary.Create();
		secondary->clear(buflen);
		m_poolSecondary.Insert(index, secondary);
	}
	
	if (false == secondary->LoadWaveFile1(szFileName))
		return false;

	if (false == secondary->CreateSoundBuffer(m_directSound))
		return false;

	return true;
}

bool SoundStreaming::CreateSoundBuffer(int index, DWORD buflen)
{
	SoundSecondary* secondary = m_poolSecondary.Find(index);
	if (NULL == secondary) {
		secondary = m_poolSecondary.Create();
		secondary->clear(buflen);
		m_poolSecondary.Insert(index, secondary);
	}

	return secondary->CreateSoundBuffer(m_directSound);
}

bool SoundStreaming::play(int index)
{
	SoundSecondary* secondary = m_poolSecondary.Find(index);
	if (NULL == secondary)
		return false;

	secondary->AddStreamBuffer();
	return secondary->play();
}

bool SoundStreaming::play(int index, char* data, int size)
{
	SoundSecondary* secondary = m_poolSecondary.Find(index);
	if (NULL == secondary)
		return false;

	secondary->AddStreamBuffer(data, size);
	return secondary->play();
}

void SoundStreaming::stop(int index)
{
	SoundSecondary* secondary = m_poolSecondary.Find(index);
	if (NULL == secondary)
		return;
	secondary->stop();
}

void SoundStreaming::test(int index)
{
	SoundSecondary* secondary = m_poolSecondary.Find(index);
	if (NULL == secondary)
		return;
	secondary->test();
}

void SoundStreaming::setPan(int index, long pan)
{
	SoundSecondary* secondary = m_poolSecondary.Find(index);
	if (NULL == secondary)
		return;
	secondary->setPan(pan);
}

void SoundStreaming::setVolumn(int index, long vol)
{
	SoundSecondary* secondary = m_poolSecondary.Find(index);
	if (NULL == secondary)
		return;
	secondary->setPan(vol);
}
