#include "stdafx.h"
#include "SoundSecondary.h"


SoundSecondary::SoundSecondary()
	:/* m_pWavData(NULL),*/ m_timerID(0)
{
	init();
}

SoundSecondary::~SoundSecondary()
{
	close();
}

void SoundSecondary::init()
{
	m_bPlaying = false;
	
	if (0 != m_timerID) {
		timeKillEvent(m_timerID);
		m_timerID = 0;
	}
	//TRACE("******* m_bPlaying init(%d)\n", m_bPlaying);

	//WAVEFORMATEX waveFormat;
	m_wfx.wFormatTag		= WAVE_FORMAT_PCM;
	m_wfx.nSamplesPerSec	= DS_SAMPLE_PER_SEC;
	m_wfx.wBitsPerSample	= DS_BITS_PER_SEC;
	m_wfx.nChannels			= DS_CHANNELS;
	m_wfx.nBlockAlign		= (m_wfx.wBitsPerSample / 8) * m_wfx.nChannels;
	m_wfx.nAvgBytesPerSec	= m_wfx.nSamplesPerSec * m_wfx.nBlockAlign;
	m_wfx.cbSize			= 0;


	for (int i = 0; i < Num_of_buffers; i++)
	{
		m_hEvents[i] = CreateEvent(NULL, FALSE, FALSE, NULL);
		//printf("*****        %x:event(%x) *****\n", this, m_hEvents[i]);
	}
}

void SoundSecondary::clear()
{
	m_poolData.Clear();
}

void SoundSecondary::close()
{
	////Shutdown wave files
	//if (m_pWavData) {
	//	delete[] m_pWavData;
	//	m_pWavData = NULL;
	//}

	m_poolData.End();

	if(m_secondaryBuffer1)
		m_secondaryBuffer1.Detach();
}

bool SoundSecondary::CreateSoundBuffer(CComPtr<IDirectSound8> & directSound)
{
	if (NULL == directSound) {
		printf("**** if (NULL == directSound) {\n");
		return false;
	}

	// Set the buffer description of the secondary sound buffer that the wave file will be loaded onto.
	DSBUFFERDESC bufferDesc;
	bufferDesc.dwSize			= sizeof(DSBUFFERDESC);
	bufferDesc.dwFlags			= DSBCAPS_CTRLPAN | DSBCAPS_CTRLVOLUME | DSBCAPS_STATIC | DSBCAPS_GLOBALFOCUS | DSBCAPS_CTRLPOSITIONNOTIFY;
	bufferDesc.dwBufferBytes	= SOUND_BUFFER;
	bufferDesc.dwReserved		= 0;
	bufferDesc.lpwfxFormat		= &m_wfx;
	bufferDesc.guid3DAlgorithm	= GUID_NULL;


	CComPtr<IDirectSoundBuffer> tempBuffer;
	HRESULT hr = directSound->CreateSoundBuffer(&bufferDesc, &tempBuffer, NULL);
	if (FAILED(hr))
	{
		_tprintf(_T("**** tempBuffer CreateSoundBuffer Fail(%x).\n"), hr);
		return false;
	}

	m_secondaryBuffer1.Release();
	//GUID IID_IDSoundBuffer = { 0x6825a449, 0x7524, 0x4d82, 0x92, 0x0f, 0x50, 0xe3, 0x6a, 0xb3, 0xab, 0x1e };
	tempBuffer->QueryInterface(IID_IDirectSoundBuffer8, (LPVOID*)&m_secondaryBuffer1);
	//**에러인경우:error LNK2001: unresolved external symbol _IID_IDirectSoundBuffer8
	//추가구문:#pragma comment(lib, "dxguid.lib")
	tempBuffer.Release();

	// Make Notification Point.
	CComPtr<IDirectSoundNotify8> lpDsNotify;
	DSBPOSITIONNOTIFY PositionNotify[Num_of_buffers];

	GUID IID_IDSoundNotify = { 0xb0210783, 0x89cd, 0x11d0, 0xaf, 0x8, 0x0, 0xa0, 0xc9, 0x25, 0xcd, 0x16 };
	hr = m_secondaryBuffer1->QueryInterface(IID_IDSoundNotify, (LPVOID*)&lpDsNotify);
	if (FAILED(hr))
	{
		_tprintf(_T("**** m_secondaryBuffer1 QueryInterface Fail(%x).\n"), hr);
		return false;
	}

	for (int i = 0; i < Num_of_buffers; i++)
	{
		PositionNotify[i].dwOffset = (SOUND_BUFFER / Num_of_buffers) * (i + 1) - 1;
		PositionNotify[i].hEventNotify = m_hEvents[i];
	}
	
	hr = lpDsNotify->SetNotificationPositions(Num_of_buffers, PositionNotify);
	return true;
}

//void SoundSecondary::AddStreamBuffer()
//{
//	if (nullptr == m_pWavData || 0 == m_nDataLen)
//		return;
//
//	int poolCnt = m_nDataLen / SOUND_BUFFER + 1;
//	for (int i = 0; i < poolCnt; ++i)
//	{
//		stSoundBuffer* sound = m_poolData.Create();
//		sound->Clear();
//		//읽어올 사이즈를 계산(SOUND_BUFFER보다 작은경우)
//		int nSize = (m_nDataLen > (SOUND_BUFFER*(i + 1))) ? SOUND_BUFFER : m_nDataLen - (SOUND_BUFFER*i);
//		memcpy_s(sound->buf, SOUND_BUFFER, m_pWavData + (SOUND_BUFFER*i), nSize);
//		m_poolData.Push(sound);
//		//TRACE("POOL cnt(add):%d\n", m_poolData.GetUsedMemSize());
//	}
//}

void SoundSecondary::AddStreamBuffer(char* data, int size)
{
	stSoundBuffer* sound = m_poolData.Create();
	if (NULL == sound)  return;

	sound->Clear();
	memcpy_s(sound->buf, SOUND_BUFFER, data, size);
	m_poolData.Push(sound);
	//TRACE("POOL cnt(add):%d\n", m_poolData.GetUsedMemSize());
}

bool SoundSecondary::play()
{
	//HG_TEST:
	//if (100 < m_poolData.GetUsedMemSize())
	//{
	//	int a = 0;
	//	a = 0;
	//}
	if (true == m_bPlaying)
		return true;
	//{
	//	stop();
	//	return false;
	//}


	if (0 == m_poolData.GetUsedMemSize())
	{
		_tprintf(_T("**** wav 데이타가 없습니다.\n"));
		return false;
	}

	//HG[2019.05.10]VOICE pool이 처리중에 뒤 데이타가 없으면 끊겨서 들리는 현상발생
	if (false == m_bPlaying)
	{
		//첫음이 시작할때는 pool을 n개 가지고 있을때 부터 시작합니다.
		if (m_poolData.GetUsedMemSize() < 2)
		{
			//printf("******* more need POOL\n");
			return false;
		}
	}

	m_bPlaying = true;
	//printf("**** m_bPlaying play(%d)\n", m_bPlaying);


	lock(0, SOUND_BUFFER);
	m_poolData.Pop();
	//TRACE("POOL cnt(sub):%d\n", m_poolData.GetUsedMemSize());

	TIMECAPS tc;
	timeGetDevCaps(&tc, sizeof(TIMECAPS));
	UINT resolution = min(max(tc.wPeriodMin, 0), tc.wPeriodMax);

	//_tprintf(L"SET TIMER: %d\n", GetTickCount());
	//if (m_timerID) timeKillEvent(m_timerID);

	//***중요 ***/
	//timeSetEvent()의 첫번째,두번째인자 바꾸지 마라. 음 끊겨서 들린다.
	//음이 끊겨 들린다면 다른곳에서 찾아라.( m_poolData 내 음이 없어도 끊긴다. pool count가 일정한지 체크하라)
	m_timerID = timeSetEvent(1, resolution, TimerProcess, (DWORD)this, TIME_PERIODIC | TIME_CALLBACK_FUNCTION);
	//printf("********************************** (0x%04x)timeSetEvent(%d)\n", this, m_timerID);

	if (m_secondaryBuffer1) {
		m_secondaryBuffer1->SetCurrentPosition(0);
		m_secondaryBuffer1->Play(0, 0, DSBPLAY_LOOPING);// DSBPLAY_LOOPING);
	}
	return true;
}

void SoundSecondary::stop()
{
	timeKillEvent(m_timerID);
	//printf("***** time event stop(%d) *****\n", m_timerID);
	m_timerID = 0;

	if (m_secondaryBuffer1)
		m_secondaryBuffer1->Stop();
	m_bPlaying = false;
	//printf("**** m_bPlaying stop(%d)\n", m_bPlaying);

	m_poolData.Clear();
}


void SoundSecondary::setPan(long pan)
{
	if (NULL == m_secondaryBuffer1)
		return;
	m_secondaryBuffer1->SetPan(pan);
}

void SoundSecondary::setVolumn(long vol)
{
	if (NULL == m_secondaryBuffer1)
		return;
	m_secondaryBuffer1->SetVolume(vol);
}

bool SoundSecondary::lock(DWORD dwOffset, DWORD dwBufferBytes)
{
	if (NULL == m_secondaryBuffer1)
		return false;

	try {
		void *write1 = 0, *write2 = 0;
		unsigned long length1 = 0, length2 = 0;
		HRESULT hr = m_secondaryBuffer1->Lock(dwOffset, dwBufferBytes, &write1, &length1, &write2, &length2, 0);
		if (FAILED(hr)) return false;

		memset(write1, 0x00, length1);	//잡음제거용.
		stSoundBuffer* sound = m_poolData.Front();
		if (NULL != sound) {
			//_tprintf(_T("index(%d), write1(%d), length1(%d), dwOffset(%d)\n"), nIndex, (int)write1, length1, dwOffset);
			//TRACE(_T("index(%d), write1(%d), length1(%d), dwOffset(%d)\n"), nIndex, (int)write1, length1, dwOffset);
			memcpy_s(write1, length1, sound->buf + dwOffset, length1);
		}

		hr = m_secondaryBuffer1->Unlock(write1, length1, write2, length2);
	} catch(std::exception& e) {
		printf("**** EXCEPTION:%s\n", e.what());
	}

	return true;
}

void CALLBACK SoundSecondary::TimerProcess(UINT uTimerID, UINT uMsg, DWORD dwUser, DWORD dw1, DWORD dw2)
{
	SoundSecondary* sound = (SoundSecondary*)dwUser;
	if (NULL != sound)	sound->timer();
}

void SoundSecondary::timer()
{
	//printf("********************************** (0x%04x)before WAIT EVENT\n", this);
	//timeout시간은 0으로설정. 시간을 설정하면 thread가 다른thread처리가 완료된 후에 순차적으로 진행된다.
	DWORD dwResult = WaitForMultipleObjects(Num_of_buffers, m_hEvents, FALSE, 0);
	DWORD nIndex = dwResult - WAIT_OBJECT_0;
	//printf("********************************** (0x%04x)after WAIT EVENT\n", this);


	//_tprintf(_T("nIndex(%d)\n"), nIndex);
	//TRACE(_T("------------nIndex(%d)\n"), nIndex);
	if (Num_of_buffers <= nIndex)
	{
		//printf("_________ WaitForMultipleObjects WAIT_TIMEOUT _______\n");
		return;
	}

	//pool이 비었으면 thread를 종료합니다.
	if (0 == m_poolData.GetUsedMemSize())
	{
		stop();
		return;
	}

	//_tprintf(_T("nIndex(%d)\n"), nIndex);
	//TRACE(_T("------------nIndex(%d)\n"), nIndex);

	//pool의 front() 버퍼를 Num_of_buffers 로 나눠서 순차적으로 적용합니다.
	DWORD dwBufferBytes = SOUND_BUFFER / Num_of_buffers;
	lock(dwBufferBytes * nIndex, dwBufferBytes);

	//pool의 front() 버퍼의 끝부분까지 모두 적용하면 pool에서 제거합니다.
	if (nIndex >= Num_of_buffers - 1)
	{
		m_poolData.Pop();
		//TRACE("POOL cnt(sub):%d\n", m_poolData.GetUsedMemSize());
	}
}
