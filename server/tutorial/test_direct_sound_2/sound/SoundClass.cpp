#include "stdafx.h"
#include "SoundClass.h"


SoundClass::SoundClass()
{

}

SoundClass::SoundClass(HWND hwnd)
{
	init(hwnd);
}

SoundClass::~SoundClass()
{
}

bool SoundClass::init(HWND hwnd)
{
	// Added code...
	HRESULT hr = DirectSoundCreate8(NULL, &m_lpDSound, NULL);
	if (FAILED(hr))
	{
		_tprintf(_T("DirectSoundCreate8 Fail.\n"));
		return false;
	}
	else
	{
		hr = m_lpDSound->SetCooperativeLevel(hwnd, DSSCL_PRIORITY);

		for (int i = 0; i < Num_of_buffers; i++)
			m_hEvents[i] = CreateEvent(NULL, FALSE, NULL, NULL);
	}
	return true;
}

bool SoundClass::LoadWaveFile(LPTSTR szFileName)
{
	if (NULL == szFileName)
		return false;

	HMMIO hmmio = mmioOpen(szFileName, NULL, MMIO_ALLOCBUF | MMIO_READ);
	if (NULL == hmmio)
	{
		_tprintf(_T("mmioOpen Fail.\n"));
		return false;
	}

	MMCKINFO mmckParent;
	mmckParent.fccType = mmioFOURCC('W', 'A', 'V', 'E');
	MMRESULT mmResult = mmioDescend(hmmio, &mmckParent, NULL, MMIO_FINDRIFF);
	if (MMSYSERR_NOERROR != mmResult)
	{
		mmioClose(hmmio, 0);
		_tprintf(_T("mmioDescend 'WAVE' Fail.\n"));
	}

	MMCKINFO mmckChild;
	mmckChild.ckid = mmioFOURCC('f', 'm', 't', ' ');
	mmResult = mmioDescend(hmmio, &mmckChild, &mmckParent, MMIO_FINDCHUNK);
	if (MMSYSERR_NOERROR != mmResult)
	{
		mmioClose(hmmio, 0);
		_tprintf(_T("mmioDescend 'fmt' Fail.\n"));
		return false;
	}

	LONG nFormatLen = mmckChild.cksize;
	if (mmioRead(hmmio, (HPSTR)&m_wfx, nFormatLen) != nFormatLen)
	{
		mmioClose(hmmio, 0);
		_tprintf(_T("mmioRead length Fail.\n"));
		return false;
	}

	mmResult = mmioAscend(hmmio, &mmckChild, 0);
	if (MMSYSERR_NOERROR != mmResult)
	{
		mmioClose(hmmio, 0);
		_tprintf(_T("mmioAscend Fail.\n"));
		return false;
	}

	mmckChild.ckid = mmioFOURCC('d', 'a', 't', 'a');
	mmResult = mmioDescend(hmmio, &mmckChild, &mmckParent, MMIO_FINDCHUNK);
	if (MMSYSERR_NOERROR != mmResult)
	{
		mmioClose(hmmio, 0);
		_tprintf(_T("mmioDescend 'data' check Fail.\n"));
		return false;
	}

	m_nDataLen = mmckChild.cksize;
	char* pTemp = new char[m_nDataLen];
	if (NULL == pTemp)
	{
		mmioClose(hmmio, 0);
		return false;
	}

	if (m_nDataLen != mmioRead(hmmio, (HPSTR)pTemp, m_nDataLen))
	{
		delete[] pTemp;
		mmioClose(hmmio, 0);
		_tprintf(_T("mmioRead Fail.\n"));
		return false;
	}

	m_pData.reset(pTemp, ArrayDeleter());
	mmioClose(hmmio, 0);

	//return true;
	return createBuffer();
}

bool SoundClass::createBuffer()
{
	DSBUFFERDESC bufdesc;
	ZeroMemory(&bufdesc, sizeof(DSBUFFERDESC));
	bufdesc.dwSize = sizeof(DSBUFFERDESC);

	bufdesc.dwFlags = DSBCAPS_CTRLPAN | DSBCAPS_CTRLVOLUME | DSBCAPS_STATIC | DSBCAPS_GLOBALFOCUS | DSBCAPS_CTRLPOSITIONNOTIFY;
	bufdesc.dwBufferBytes = m_wfx.nAvgBytesPerSec / 2 * Num_of_buffers;
	//bufdesc.dwBufferBytes = min(m_wfx.nSamplesPerSec * Num_of_buffers, m_nDataLen);
	bufdesc.lpwfxFormat = &m_wfx;

	CComPtr<IDirectSoundBuffer> pBuffer;
	HRESULT hr = m_lpDSound->CreateSoundBuffer(&bufdesc, &pBuffer, NULL);
	if (FAILED(hr))
	{
		_tprintf(_T("error:0x%x\n"), GetLastError());
		return false;
	}

	m_lpDSoundBuffer8.Release();
	GUID IID_IDSoundBuffer = { 0x6825a449, 0x7524, 0x4d82, 0x92, 0x0f, 0x50, 0xe3, 0x6a, 0xb3, 0xab, 0x1e };
	pBuffer->QueryInterface(IID_IDSoundBuffer, (LPVOID*)&m_lpDSoundBuffer8);

	//이부분은 Play()에서 처리하도록 이동합니다.
	//m_nDataPos = 0;//초기화를 안하면 재시작할때 이어서 재생되더라.
	//lock(0, 0, bufdesc.dwBufferBytes);
	m_dwBufferBytes = bufdesc.dwBufferBytes;

	GUID IID_IDSoundNotify = { 0xb0210783, 0x89cd, 0x11d0, 0xaf, 0x8, 0x0, 0xa0, 0xc9, 0x25, 0xcd, 0x16 };

	// Make Notification Point.
	CComPtr<IDirectSoundNotify8> lpDsNotify;
	DSBPOSITIONNOTIFY PositionNotify[Num_of_buffers];

	hr = m_lpDSoundBuffer8->QueryInterface(IID_IDSoundNotify, (LPVOID*)&lpDsNotify);
	if (FAILED(hr))
	{
		_tprintf(_T("error:0x%x\n"), GetLastError());
		return false;
	}

	for (int i = 0; i < Num_of_buffers; i++)
	{
		PositionNotify[i].dwOffset = m_wfx.nAvgBytesPerSec / 2 * (i + 1) - 1;
		PositionNotify[i].hEventNotify = m_hEvents[i];
	}
	hr = lpDsNotify->SetNotificationPositions(Num_of_buffers, PositionNotify);
	return true;
}

bool SoundClass::play()
{
	if (true == m_bPlaying)
	{
		//stop();
		return false;
	}

	if (nullptr == m_pData || 0 == m_nDataLen)
		return false;


	//이부분은 Play()에서 처리하도록 이동합니다.
	m_nDataPos = 0;//초기화를 안하면 재시작할때 이어서 재생되더라.
	lock(0, 0, m_dwBufferBytes);


	TIMECAPS tc;
	timeGetDevCaps(&tc, sizeof(TIMECAPS));
	UINT resolution = min(max(tc.wPeriodMin, 0), tc.wPeriodMax);

	//_tprintf(L"SET TIMER: %d\n", GetTickCount());
	m_timerID = timeSetEvent(1, resolution, TimerProcess, (DWORD)this, TIME_PERIODIC | TIME_CALLBACK_FUNCTION);

	//m_nDataPos = 0;//이거때문에 처음에 소리가 겹치는 현상있었다.

	m_bPlaying = true;
	m_lpDSoundBuffer8->SetCurrentPosition(0);
	m_lpDSoundBuffer8->Play(0, 0, DSBPLAY_LOOPING);// DSBPLAY_LOOPING);
	return true;
}

void SoundClass::stop()
{
	timeKillEvent(m_timerID);
	m_lpDSoundBuffer8->Stop();
	m_bPlaying = false;
}

void SoundClass::setVolumn(long vol)
{
	HRESULT ret = m_lpDSoundBuffer8->SetVolume(vol);
}

bool SoundClass::lock(DWORD nIndex, DWORD dwOffset, DWORD dwBufferBytes)
{
	void *write1 = 0, *write2 = 0;
	unsigned long length1 = 0, length2 = 0;
	HRESULT hr = m_lpDSoundBuffer8->Lock(dwOffset, dwBufferBytes, &write1, &length1, &write2, &length2, 0);
	if (FAILED(hr))
		return false;

	if (0 < length1)
	{
		int nSize = (length1 > m_nDataLen - m_nDataPos) ? m_nDataLen - m_nDataPos : length1;
		_tprintf(_T("index(%d), pos(%d), length(%d), size(%d)\n"), nIndex, m_nDataPos, length1, nSize);
		memset(write1, 0x00, length1);
		memcpy_s(write1, nSize, m_pData.get() + m_nDataPos, nSize);
		m_nDataPos += nSize;
		if (m_nDataLen <= m_nDataPos)
			m_nDataPos = 0;
	}

	hr = m_lpDSoundBuffer8->Unlock(write1, length1, write2, length2);
	return true;
}


void CALLBACK SoundClass::TimerProcess(UINT uTimerID, UINT uMsg, DWORD dwUser, DWORD dw1, DWORD dw2)
{
	SoundClass* pDDS = (SoundClass*)dwUser;

	DWORD dwResult = WaitForMultipleObjects(Num_of_buffers, pDDS->m_hEvents, FALSE, 0);
	if (Num_of_buffers <= (dwResult - WAIT_OBJECT_0))
		return;

	//_tprintf(_T("[LOG] Wait : %d(%d)\n"), dwResult, GetTickCount());
	DWORD nIndex = dwResult - WAIT_OBJECT_0;
	pDDS->lock(nIndex, (pDDS->m_wfx.nAvgBytesPerSec / 2) * nIndex, pDDS->m_wfx.nAvgBytesPerSec / 2);
}