#pragma once

#include <windows.h>
#include <atlbase.h>
#include <memory>
#include <dsound.h>
//#include <afx.h>

#pragma comment(lib, "dsound.lib")
//#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "Winmm.lib")

class SoundClass
{
	struct ArrayDeleter
	{
		template <class T>
		void operator()(T* p)
		{
			delete[] p;
		}
	};

public:
	SoundClass();
	SoundClass(HWND hwnd);
	~SoundClass();


	bool init(HWND hwnd);
	bool LoadWaveFile(LPTSTR szFileName);

	bool play();
	void stop();

	void setVolumn(long vol);

protected:
	bool createBuffer();
	bool lock(DWORD nIndex, DWORD dwOffset, DWORD dwBufferBytes);

	static void CALLBACK TimerProcess(UINT uTimerID, UINT uMsg, DWORD dwUser, DWORD dw1, DWORD dw2);



public:
	enum { Num_of_buffers = 2 };


protected:

	bool m_bPlaying;
	std::shared_ptr<char> m_pData;
	DWORD m_nDataLen;
	DWORD m_nDataPos;
	DWORD m_dwBufferBytes;

	CComPtr<IDirectSound8> m_lpDSound;
	CComPtr<IDirectSoundBuffer8> m_lpDSoundBuffer8;
	
	HANDLE m_hEvents[Num_of_buffers];
	MMRESULT m_timerID;
	WAVEFORMATEX m_wfx;

};

