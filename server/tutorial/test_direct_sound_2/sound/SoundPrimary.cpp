#include "stdafx.h"
#include "SoundPrimary.h"


SoundPrimary::SoundPrimary()
{

}

SoundPrimary::~SoundPrimary()
{
	close();
}

bool SoundPrimary::init(HWND hwnd, GUID& guidDevice)//, _playType nType, int index)
{
	if (NULL != m_directSound)
		return true;

	// Initialize the direct sound interface pointer for the default sound device.
	HRESULT result = DirectSoundCreate8(&guidDevice, &m_directSound, NULL);
	if (FAILED(result))
	{
		_tprintf(_T("******** DirectSound DirectSoundCreate8 Fail(%x).\n"), result);
		return false;
	}

	// Set the cooperative level to priority so the format of the primary sound buffer can be modified.
	//hwnd는 ::AfxGetMainWnd()->m_hWnd 이어야 합니다.
	result = m_directSound->SetCooperativeLevel(hwnd, DSSCL_PRIORITY);
	if (FAILED(result))
	{
		_tprintf(_T("******** DirectSound SetCooperativeLevel Fail(%x).\n"), result);
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
		_tprintf(_T("******** DirectSound CreateSoundBuffer Fail(%x).\n"), result);
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
		_tprintf(_T("******** DirectSound SetFormat Fail(%x).\n"), result);
		return false;
	}

	return true;
}

void SoundPrimary::close()
{
	for (int i = 0; i < SOUND_DUAL_CHANNEL; ++i)
		m_poolSecondary[i].End();

	m_primaryBuffer.Release();
	m_directSound.Release();
}

//개체가 없으면 만들어 준다.
SoundSecondary* SoundPrimary::GetSoundSecondary(_playType type, int index)
{
	SoundSecondary* secondary = m_poolSecondary[type].Find(index);
	if (NULL == secondary) {
		secondary = m_poolSecondary[type].Create();
		secondary->clear();
		m_poolSecondary[type].Insert(index, secondary);

		//buffer도 만들어주고.
		if (false == secondary->CreateSoundBuffer(m_directSound))
		{
			//secondary 버퍼생성 실패시...pool 을 되돌려준다.
			m_poolSecondary[type].Erase(index);
			return false;
		}
	}
	return secondary;
}

//bool SoundPrimary::LoadWaveFile(_playType type, int index, LPTSTR szFileName)
//{
//	if (NULL == szFileName)
//		return false;
//
//	SoundSecondary* secondary = GetSoundSecondary(type, index);
//	if (NULL == secondary) return false;
//
//	if (false == secondary->LoadWaveFile1(szFileName))
//		return false;
//
//	if (false == secondary->CreateSoundBuffer(m_directSound))
//		return false;
//
//	return true;
//}

bool SoundPrimary::play(_playType type, int index, char* data, int size)
{
	SoundSecondary* secondary = GetSoundSecondary(type, index);
	if (NULL == secondary) return false;

	secondary->AddStreamBuffer(data, size);
	//TRACE("******* VOICE Play nType(%d), index(%d)\n", type, index);
	return secondary->play();
}

//bool SoundPrimary::play(_playType type, int index)
//{
//	SoundSecondary* secondary = GetSoundSecondary(type, index);
//	if (NULL == secondary) return false;
//
//	secondary->AddStreamBuffer();
//	//TRACE("******* VOICE Play nType(%d), index(%d)\n", type, index);
//	return secondary->play();
//}

void SoundPrimary::stop(_playType type, int index)
{
	SoundSecondary* secondary = GetSoundSecondary(type, index);
	if (NULL == secondary) return;

	secondary->stop();
}

void SoundPrimary::setPan(_playType type, int index, long pan)
{
	SoundSecondary* secondary = GetSoundSecondary(type, index);
	if (NULL == secondary) return;

	//TRACE("++++++++ type(%d),index(%d),pan(%d)\n", type, index, pan);
	secondary->setPan(pan);
}

void SoundPrimary::setVolumn(_playType type, int index, long vol)
{
	SoundSecondary* secondary = GetSoundSecondary(type, index);
	if (NULL == secondary) return;

	//TRACE("++++++++ type(%d),index(%d),vol(%d)\n", type, index, vol);
	secondary->setVolumn(vol);
}
