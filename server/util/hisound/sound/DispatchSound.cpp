#include "stdafx.h"
#include "DispatchSound.h"

//---------------------------------------------------------------------------------------------------
//	CALLBACK function
//---------------------------------------------------------------------------------------------------
BOOL CALLBACK DSoundEnumProc(LPGUID lpGUID, LPCTSTR lpszDesc, LPCTSTR lpszDrvName, LPVOID lpContext)
{
	DispatchSound* owner = (DispatchSound*)lpContext;
	owner->LoadDevices(owner->GetSpkPool(), lpGUID, lpszDesc, lpszDrvName);
	return TRUE;
}

BOOL CALLBACK DSoundEnumCaptureProc(LPGUID lpGUID, LPCTSTR lpszDesc, LPCTSTR lpszDrvName, LPVOID lpContext)
{
	DispatchSound* owner = (DispatchSound*)lpContext;
	owner->LoadDevices(owner->GetMicPool(), lpGUID, lpszDesc, lpszDrvName);
	return TRUE;
}
//---------------------------------------------------------------------------------------------------


DispatchSound::DispatchSound()
	: m_pWavData(NULL), m_nDataLen(0)
{
	DirectSoundEnumerate(DSoundEnumProc, (LPVOID)this);
	DirectSoundCaptureEnumerate(DSoundEnumCaptureProc, (LPVOID)this);
}

DispatchSound::~DispatchSound()
{
	close();
}

void DispatchSound::close()
{
	if (m_pWavData) {
		delete[] m_pWavData;
		m_pWavData = NULL;
	}

	m_poolDevice.End();

	m_poolSpks.End();
	m_poolMics.End();
}


// hwnd는 ::AfxGetMainWnd()->m_hWnd 이어야 합니다.
// szDevice: device 정보(검색이 되지 않을 때는 기본speaker로 설정된다)
// nDevice : szDevice로 검색한 사운드카드를 매칭할 번호.
void DispatchSound::init(HWND hwnd, TCHAR* szDevice, int nDevice)//, _playType nType, int index)
{
	SoundPrimary* primary = m_poolDevice.Find(nDevice);
	if (NULL != primary) {
		_tprintf(_T("이미 생성되어 있군.\n"));
		return;
	}

	//if (NULL != streaming)
	//	return;
	m_hWnd = hwnd;

	primary = m_poolDevice.Create();
	GUID guidDevice = GetSpkGUID(szDevice);
	if(true == primary->init(hwnd, guidDevice))
		_tcprintf(_T("matching success: %d --> %s\n"), nDevice, szDevice);
	else
		_tcprintf(_T("matching failed: %d --> %s\n"), nDevice, szDevice);
	m_poolDevice.Insert(nDevice, primary);
}

bool DispatchSound::play(int nDevice, SoundPrimary::_playType nType, int index, char* data, int size)
{
	SoundPrimary* primary = m_poolDevice.Find(nDevice);
	if (NULL == primary) {
		_tprintf(_T("Device(%d) 생성되지 않았다\n"), nDevice);
		return false;
	}

	// 스피커 좌우 볼류 설정(-10000 ~ 10000)
	if (nType == SoundPrimary::SOUND_RIGHT_CHANNEL)     primary->setPan(nType, index, DSBPAN_RIGHT); // 스피커
	else if (nType == SoundPrimary::SOUND_LEFT_CHANNEL) primary->setPan(nType, index, DSBPAN_LEFT); // 헤드셋
	else if (nType == SoundPrimary::SOUND_DUAL_CHANNEL) primary->setPan(nType, index, DSBPAN_CENTER); // 헤드셋 + 스피커

	////TRACE("******* (%d)VOICE Play nDevice(%d), nType(%d), index(%d)\n", this, nDevice, nType, index);
	//return SoundPrimary::play(nDevice, nType, index, data, size);
	return primary->play(nType, index, data, size);
}

void DispatchSound::play(int nDevice, SoundPrimary::_playType nType, int index)
{
	if (nullptr == m_pWavData || 0 == m_nDataLen)
		return;

	SoundPrimary* primary = m_poolDevice.Find(nDevice);
	if (NULL == primary) {
		_tprintf(_T("생성되지 않았다.\n"));
		return;
	}

	// 스피커 좌우 볼류 설정(-10000 ~ 10000)
	if (nType == SoundPrimary::SOUND_RIGHT_CHANNEL)     primary->setPan(nType, index, DSBPAN_RIGHT); // 스피커
	else if (nType == SoundPrimary::SOUND_LEFT_CHANNEL) primary->setPan(nType, index, DSBPAN_LEFT); // 헤드셋
	else if (nType == SoundPrimary::SOUND_DUAL_CHANNEL) primary->setPan(nType, index, DSBPAN_CENTER); // 헤드셋 + 스피커

	int poolCnt = m_nDataLen / SOUND_BUFFER + 1;
	for (int i = 0; i < poolCnt; ++i)
	{
		char buf[SOUND_BUFFER];
		memset(buf, 0, sizeof(buf));

		//읽어올 사이즈를 계산(SOUND_BUFFER보다 작은경우)
		int nSize = (m_nDataLen > (SOUND_BUFFER*(i + 1))) ? SOUND_BUFFER : m_nDataLen - (SOUND_BUFFER*i);
		memcpy_s(buf, SOUND_BUFFER, m_pWavData + (SOUND_BUFFER*i), nSize);

		primary->play(nType, index, buf, nSize);
	}
}

void DispatchSound::stop(int nDevice, SoundPrimary::_playType nType, int index)
{
	SoundPrimary* primary = m_poolDevice.Find(nDevice);
	if (NULL == primary) {
		_tprintf(_T("생성되지 않았다.\n"));
		return;
	}

	primary->stop(nType, index);
}

bool DispatchSound::LoadWaveFile(LPTSTR szFileName)
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

	//기존꺼 삭제
	if (m_pWavData) delete[] m_pWavData;

	m_nDataLen = mmckChild.cksize;
	m_pWavData = new char[m_nDataLen];
	if (NULL == m_pWavData)
	{
		mmioClose(hmmio, 0);
		return false;
	}

	if (m_nDataLen != mmioRead(hmmio, (HPSTR)m_pWavData, m_nDataLen))
	{
		mmioClose(hmmio, 0);
		_tprintf(_T("mmioRead Fail.\n"));
		return false;
	}

	mmioClose(hmmio, 0);
	return true;
}

void DispatchSound::LoadDevices(DIRECT_SOUND_ENUMERATE& pool, LPGUID lpGUID, LPCTSTR lpszDesc, LPCTSTR lpszDrvName)
{
	DispatchSound::stGUID* guid = pool.Find(lpszDesc);
	if (NULL != guid) return;

	guid = pool.Create();
	guid->clear();
	if (NULL != lpGUID)
		guid->guid = (GUID)(*lpGUID);
	_tcscpy_s(guid->desc, lpszDesc);
	//_tcscpy_s(guid->device, lpszDrvName);
	pool.Insert(lpszDesc, guid);
}

GUID DispatchSound::GetSpkGUID(LPCTSTR szDevice)
{
	stGUID* guid = m_poolSpks.Find(szDevice);
	if (NULL == guid) {
		return GUID();
	}
	return guid->guid;
}
