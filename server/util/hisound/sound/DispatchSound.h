#pragma once
#include "SoundPrimary.h"


class DispatchSound : public HisUtil::CSingleton<DispatchSound>
{
public:
	struct stGUID {
		GUID guid;
		TCHAR desc[MAX_PATH];
		//TCHAR device[MAX_PATH];

		void clear() {
			memset(&guid, 0, sizeof(guid));
			memset(desc, 0, sizeof(desc));
			//memset(device, 0, sizeof(device));
		}
	};
	typedef HisUtil::CMemoryPool<std::wstring, stGUID> DIRECT_SOUND_ENUMERATE;


public:
	DispatchSound();
	~DispatchSound();
	void close();

	void init(HWND hwnd, TCHAR* szDevice, int nDevice);// , _playType nType, int index);
	bool play(int nDevice, SoundPrimary::_playType nType, int index,char* data, int size);
	void play(int nDevice, SoundPrimary::_playType nType, int index);
	void stop(int nDevice, SoundPrimary::_playType nType, int index);

	bool LoadWaveFile(LPTSTR szFileName);


	void LoadDevices(DIRECT_SOUND_ENUMERATE& pool, LPGUID lpGUID, LPCTSTR lpszDesc, LPCTSTR lpszDrvName);
	GUID GetSpkGUID(LPCTSTR szDevice);

	DIRECT_SOUND_ENUMERATE& GetSpkPool() { return m_poolSpks; }
	DIRECT_SOUND_ENUMERATE& GetMicPool() { return m_poolMics; }
private:
	HWND m_hWnd;

	//wave file
	WAVEFORMATEX m_wfx;
	char* m_pWavData;	//wav파일을 읽어들인 데이타.(stream을 구현하기 위한 저장해 둔다.)
	DWORD m_nDataLen;


	DIRECT_SOUND_ENUMERATE m_poolSpks;	//등록가능한 device목록(speaker)
	DIRECT_SOUND_ENUMERATE m_poolMics;	//등록가능한 device목록(mic)

	HisUtil::CMemoryPool<int/*nDevice*/, SoundPrimary> m_poolDevice;	//사운드카드목록
};

