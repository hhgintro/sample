#pragma once

//#include <windows.h>
//#include <atlbase.h>
//#include <memory>
//#include <dsound.h>
////#include <afx.h>
//
//
//#pragma comment(lib, "dsound.lib")
////#pragma comment(lib, "dxguid.lib")
//#pragma comment(lib, "Winmm.lib")

#include "TypeDef.h"

//문제점 : 22050 이하에서 잡음이 포함되어 출력됩니다.(원인불명)
const DWORD SOUND_BUFFER = PACKET_SIZE;
//689//960//8000//11025//22050//44100//88200//176400//352800


const DWORD DS_SAMPLE_PER_SEC	= 8000;
const DWORD DS_BITS_PER_SEC		= 16;
const DWORD DS_CHANNELS			= 1;


class SoundSecondary
{
	struct stSoundBuffer {
		stSoundBuffer() { Clear(); }
		void Clear() { memset(buf, 0, sizeof(buf)); }

		char buf[SOUND_BUFFER];
	};

	struct ArrayDeleter
	{
		template <class T>
		void operator()(T* p)
		{
			delete[] p;
		}
	};

public:
	SoundSecondary();
	virtual ~SoundSecondary();

	void clear();

	//===============================================//
	//파일을 읽는경우: LoadWaveFile1() -> CreateSoundBuffer() -> AddStreamBuffer() -> play()
	//STREAMING 경우:					CreateSoundBuffer() -> AddStreamBuffer(data) -> play()
	bool LoadWaveFile1(LPTSTR szFileName);
	bool CreateSoundBuffer(CComPtr<IDirectSound8> &directSound);
	void AddStreamBuffer();
	void AddStreamBuffer(char* data, int size);

	bool play();
	void stop();
	void test();

	void setPan(long pan);
	void setVolumn(long vol);

protected:
	void init();
	void close();


	bool lock(DWORD nIndex, DWORD dwOffset, DWORD dwBufferBytes);


	static void CALLBACK TimerProcess(UINT uTimerID, UINT uMsg, DWORD dwUser, DWORD dw1, DWORD dw2);
	void timer();



public:
	enum { Num_of_buffers = 2 };


protected:

	CComPtr<IDirectSoundBuffer8> m_secondaryBuffer1;
	WAVEFORMATEX m_wfx;

	bool m_bPlaying;
	char* m_pWavData;	//wav파일을 읽어들인 데이타.(stream을 구현하기 위한 저장해 둔다.)
	DWORD m_nDataLen;
	HisUtil::CMemoryQueuePool<stSoundBuffer> m_poolData;

	HANDLE m_hEvents[Num_of_buffers];
	MMRESULT m_timerID;

};

