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


//������ : 22050 ���Ͽ��� ������ ���ԵǾ� ��µ˴ϴ�.(���κҸ�)
const DWORD SOUND_BUFFER = 960;
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

	struct ArrayDeleter {
		template <class T> void operator()(T* p) { delete[] p; }
	};

public:
	SoundSecondary();
	virtual ~SoundSecondary();

	void clear();

	//===============================================//
	//������ �д°��: LoadWaveFile1() -> CreateSoundBuffer() -> AddStreamBuffer() -> play()
	//STREAMING ���:					CreateSoundBuffer() -> AddStreamBuffer(data) -> play()
	bool CreateSoundBuffer(CComPtr<IDirectSound8> &directSound);
	//void AddStreamBuffer();
	void AddStreamBuffer(char* data, int size);

	bool play();
	void stop();

	void setPan(long pan);
	void setVolumn(long vol);

protected:
	void init();
	void close();


	bool lock(DWORD dwOffset, DWORD dwBufferBytes);


	static void CALLBACK TimerProcess(UINT uTimerID, UINT uMsg, DWORD_PTR dwUser, DWORD_PTR dw1, DWORD_PTR dw2);
	void timer();


public:

	enum { Num_of_buffers = 8 };	//SOUND_BUFFER�� Num_of_buffers�������� ������ ���� play�� �����մϴ�.


protected:

	CComPtr<IDirectSoundBuffer8> m_secondaryBuffer1;
	WAVEFORMATEX m_wfx;

	bool m_bPlaying;
	//char* m_pWavData;	//wav������ �о���� ����Ÿ.(stream�� �����ϱ� ���� ������ �д�.)
	//DWORD m_nDataLen;
	HisUtil::CMemoryQueuePool<stSoundBuffer> m_poolData;

	HANDLE m_hEvents[Num_of_buffers];
	MMRESULT m_timerID;

};
