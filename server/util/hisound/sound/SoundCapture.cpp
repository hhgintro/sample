#include "stdafx.h"
#include "SoundCapture.h"


SoundCapture::SoundCapture()
	: m_timerID(0)
{
	CoInitialize(NULL);
}

SoundCapture::~SoundCapture()
{
	close();
	CoUninitialize();
}

bool SoundCapture::init(HWND hwnd, GUID& guidDevice)//, _playType nType, int index)
{
	if (NULL != m_dsCapture)
		return true;

	// Initialize the direct sound interface pointer for the default sound device.
	HRESULT result = DirectSoundCaptureCreate8(&guidDevice, &m_dsCapture, NULL);
	if (FAILED(result))
	{
		_tprintf(_T("******** DirectSound DirectSoundCreate8 Fail(0x%08x/%d).\n"), result, GetLastError());
		return false;
	}

	// Set Wave Format
	WAVEFORMATEX wfx;		// Input Output Waveformat
	memset(&wfx, 0, sizeof(wfx));
	wfx.wFormatTag		= WAVE_FORMAT_PCM;
	wfx.nSamplesPerSec	= DS_SAMPLE_PER_SEC;
	wfx.wBitsPerSample	= DS_BITS_PER_SEC;
	wfx.nChannels		= DS_CHANNELS;
	wfx.nBlockAlign		= (wfx.wBitsPerSample / 8) * wfx.nChannels;
	wfx.nAvgBytesPerSec	= wfx.nSamplesPerSec * wfx.nBlockAlign;
	wfx.cbSize			= 0;

	// Set Sound Buffer Attributes
	DSCBUFFERDESC bufferDesc;
	memset(&bufferDesc, 0, sizeof(bufferDesc));
	bufferDesc.dwSize			= sizeof(DSCBUFFERDESC);
	bufferDesc.dwFlags			= 0;
	bufferDesc.dwBufferBytes	= SOUND_BUFFER * NUM_OF_BUFFER;
	bufferDesc.dwReserved		= 0;
	bufferDesc.lpwfxFormat		= &wfx;

	// Get control of the primary sound buffer on the default sound device.
	result = m_dsCapture->CreateCaptureBuffer(&bufferDesc, &m_captureBuffer, NULL);
	if (FAILED(result))
	{
		_tprintf(_T("******** DirectSound CreateCaptureBuffer Fail(0x%08x/%d).\n"), result, GetLastError());
		return false;
	}

	CComPtr<IDirectSoundNotify> lpDsNotify;
	result = m_captureBuffer->QueryInterface(IID_IDirectSoundNotify, (LPVOID*)&lpDsNotify);
	if (FAILED(result))
	{
		_tprintf(_T("******** DirectSound QueryInterface Fail(0x%08x/%d).\n"), result, GetLastError());
		return false;
	}


	DSBPOSITIONNOTIFY PositionNotify[NUM_OF_BUFFER+1];
	for (int i = 0; i < NUM_OF_BUFFER; ++i)
	{
		m_hEvents[i] = CreateEvent(NULL, FALSE, FALSE, NULL);
		PositionNotify[i].dwOffset = SOUND_BUFFER * (i + 1) - 1;
		PositionNotify[i].hEventNotify = m_hEvents[i];
	}
	//마지막 위치에서는 다시 버퍼의 처음으로 돌아가게 합니다.
	m_hEvents[NUM_OF_BUFFER] = CreateEvent(NULL, FALSE, FALSE, NULL);
	PositionNotify[NUM_OF_BUFFER].dwOffset = DSBPN_OFFSETSTOP;
	PositionNotify[NUM_OF_BUFFER].hEventNotify = m_hEvents[NUM_OF_BUFFER];

	result = lpDsNotify->SetNotificationPositions(NUM_OF_BUFFER+1, PositionNotify);
	if (FAILED(result))
	{
		_tprintf(_T("******** DirectSound SetNotificationPositions Fail(0x%08x/%d).\n"), result, GetLastError());
		return false;
	}

	// Release Notification Object
	lpDsNotify.Release();
	return true;
}

void SoundCapture::close()
{
	m_captureBuffer.Release();
	m_dsCapture.Release();
}

bool SoundCapture::play()
{
	if (0 != m_timerID)
		return true;

	TIMECAPS tc;
	timeGetDevCaps(&tc, sizeof(TIMECAPS));
	UINT resolution = min(max(tc.wPeriodMin, 0), tc.wPeriodMax);
	//***중요 ***/
	//timeSetEvent()의 첫번째,두번째인자 바꾸지 마라. 음 끊겨서 들린다.
	m_timerID = timeSetEvent(1, resolution, TimerProcess, (DWORD_PTR)this, TIME_PERIODIC | TIME_CALLBACK_FUNCTION);

	HRESULT result = m_captureBuffer->Start(DSCBSTART_LOOPING);
	if (FAILED(result)) {
		_tprintf(_T("******** DirectSound play Fail(0x%08x/%d).\n"), result, GetLastError());
		return false;
	}
	return true;
}

void SoundCapture::stop()
{
	timeKillEvent(m_timerID);
	m_timerID = 0;

	m_captureBuffer->Stop();
}

bool SoundCapture::lock(DWORD dwOffset)
{
	if (NULL == m_captureBuffer)
		return false;

	byte buff[SOUND_BUFFER];
	DWORD dwBufferBytes;

	try {
		void *write1 = 0, *write2 = 0;
		unsigned long length1 = 0, length2 = 0;
		HRESULT hr = m_captureBuffer->Lock(dwOffset, sizeof(buff), &write1, &length1, &write2, &length2, 0);
		if (FAILED(hr)) return false;

		memcpy_s(buff, sizeof(buff), write1, length1);
		dwBufferBytes = length1;

		hr = m_captureBuffer->Unlock(write1, length1, write2, length2);

		//pure virtual function
		ReadCaptureBuffer(buff, dwBufferBytes);
	}
	catch (std::exception& e) {
		printf("**** EXCEPTION:%s\n", e.what());
	}

	return true;
}

void CALLBACK SoundCapture::TimerProcess(UINT uTimerID, UINT uMsg, DWORD_PTR dwUser, DWORD_PTR dw1, DWORD_PTR dw2)
{
	SoundCapture* sound = (SoundCapture*)dwUser;
	if (NULL == sound)	return;
	
	sound->timer();
}

void SoundCapture::timer()
{
	//printf("********************************** (0x%04x)before WAIT EVENT\n", this);
	//timeout시간은 0으로설정. 시간을 설정하면 thread가 다른thread처리가 완료된 후에 순차적으로 진행된다.
	DWORD dwResult = WaitForMultipleObjects(NUM_OF_BUFFER+1, m_hEvents, FALSE, 0);
	DWORD nIndex = dwResult - WAIT_OBJECT_0;
	//printf("********************************** (0x%04x)after WAIT EVENT\n", this);

	if (NUM_OF_BUFFER <= nIndex)
	{
		//stop();
		return;
	}

	lock(SOUND_BUFFER * nIndex);
}