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
	char* m_pWavData;	//wav������ �о���� ����Ÿ.(stream�� �����ϱ� ���� ������ �д�.)
	DWORD m_nDataLen;


	DIRECT_SOUND_ENUMERATE m_poolSpks;	//��ϰ����� device���(speaker)
	DIRECT_SOUND_ENUMERATE m_poolMics;	//��ϰ����� device���(mic)

	HisUtil::CMemoryPool<int/*nDevice*/, SoundPrimary> m_poolDevice;	//����ī����
};

