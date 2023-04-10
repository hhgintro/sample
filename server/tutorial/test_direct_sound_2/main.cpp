// md5.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "sound/DispatchSound.h"
//#include "sound/SoundClass.h"
#include "sound/DispatchCapture.h"

#include <vector>
#include <string.h>


//===========================================================
#include <windows.h> 
#include <dsound.h>
#include <conio.h>
#include <iostream>
using namespace std;

#define			CEVENTS 3
#define			PEVENTS 2
#define			CHANNELS 1//2
#define			SAMPLESPERSEC 8000//44100
#define			BITSPERSAMPLE 16

#define			SOUND_BUFFER	960

typedef struct {
	DWORD dwDataBuffer[44100];
	bool       bFull;			// Buffer Full or Empty
}DataT;

HRESULT	hr;					// Error Variable

WAVEFORMATEX			wfx;		// Input Output Waveformat
LPDIRECTSOUNDFULLDUPLEX		pDSFD;		// Full Duplex Device Pointer
LPDIRECTSOUNDCAPTUREBUFFER8	pDSCB;		// Capture Buffer Pointer
LPDIRECTSOUNDBUFFER8		pDSB;		// Sound Buffer Pointer

HANDLE	hThread[2],				// Thread Handle
hCaptureEvent[CEVENTS] = { 0 },	// Capture Event Handle
hPlayEvent[PEVENTS] = { 0 };	// Play Event Handle

bool	bStart = false;				// Start/Stop Variable

DataT	sData1,					// Data Buffer First Part
sData2;					// Data Buffer Second Part

DWORD WINAPI WaitForCaptureNotifications(void);		// Wait for Capture Events Thread Proc
DWORD WINAPI WaitForPlayNotifications(void);		// Wait for Play Events	Thread Proc

DWORD WriteSoundBuffer(DWORD dwOffset, DataT* pData);	// Write Data Part from Data Buffer to Sound Buffer
DWORD ReadCaptureBuffer(DWORD dwOffset, DataT* pData);	// Write Data Part from Capture Buffer to Data Buffer


HRESULT CreateFullDuplexDevice(void);				// Create Full Duplex Device
HRESULT SetCaptureNotifications(void);				// Set the Capture Buffer Notifications
HRESULT SetPlayNotifications(void);				// Set the Play Buffer Notifications

HWND GetCMDHwnd(void);						// Get Window Handle

void captureMain()
{
	hr = CreateFullDuplexDevice();
	if (FAILED(hr)) {
		MessageBox(NULL, L"Could not create Full Duplex Device.", L"Error", NULL);
	}

	hr = SetCaptureNotifications();
	if (FAILED(hr)) {
		MessageBox(NULL, L"Could not create Capture Notification.", L"Error", NULL);
	}

	hr = SetPlayNotifications();
	if (FAILED(hr)) {
		MessageBox(NULL, L"Unable to create Play Notification.", L"Error", NULL);
	}

	hr = pDSCB->Start(DSCBSTART_LOOPING);
	if (FAILED(hr)) {
		MessageBox(NULL, L"Capture Buffer cannot be started.", L"Error", NULL);
	}
	else {
		// Set Start Variable and Create Wait for Capture Events Thread
		bStart = true;
		hThread[0] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)WaitForCaptureNotifications, NULL, 0, NULL);
	}

	hr = pDSB->Play(0, 0, DSBPLAY_LOOPING);
	if (FAILED(hr)) {
		MessageBox(NULL, L"Could not start Play Buffer.", L"Error", NULL);
	}

	printf("'q' press to finish recording.\n");
	while (_getch() != 113);
	hr = pDSCB->Stop();
	if (FAILED(hr)) {
		MessageBox(NULL, L"Capture Buffer cannot be stopped.", L"Error", NULL);
	}

	printf("'q' press to finish playback.\n");
	while (_getch() != 113);
	hr = pDSB->Stop();
	if (FAILED(hr)) {
		MessageBox(NULL, L"Unable to stop Play Buffer.", L"Error", NULL);
	}

	// Close Handles
	for (int i = 0; i < 2; i++) {
		CloseHandle(hThread[i]);
		CloseHandle(hPlayEvent[i]);
	}
	for (int i = 0; i < 3; i++)
		CloseHandle(hCaptureEvent[i]);

	// Release Objects
	pDSCB->Release();
	pDSB->Release();
	pDSFD->Release();
}
DWORD ReadCaptureBuffer(DWORD dwOffset, DataT* pData) {
	LPVOID	pbCaptureData;
	DWORD	dwCaptureLength;

	if (SUCCEEDED(hr = pDSCB->Lock(			// Lock Capture Buffer Part
		dwOffset,		// dwOffset
		SOUND_BUFFER,//wfx.nAvgBytesPerSec,	// dwBytes
		&pbCaptureData,		// ppvAudioPtr1
		&dwCaptureLength,	// pdwAudioBytes1	
		NULL,			// ppvAudioPtr2
		0,			// pdwAudioBytes2
		0)))			// dwFlags
	{
		memcpy(pData->dwDataBuffer, pbCaptureData, dwCaptureLength);	// Copy Data from Capture Buffer to Data Buffer

		hr = pDSCB->Unlock(		// Unlock Capture Buffer Part
			pbCaptureData,	             // ppvAudioPtr1
			dwCaptureLength,	// pdwAudioBytes1
			NULL,			// ppvAudioPtr2
			0);			// pdwAudioBytes

		pData->bFull = true;		// Set Buffer Full Variable
									// Create Wait for Play Events Thread 
		//hThread[1] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)WaitForPlayNotifications, NULL, 0, NULL);

		DispatchSound::Instance().play(0, SoundPrimary::SOUND_RIGHT_CHANNEL, 11, (char*)pbCaptureData, dwCaptureLength);

		return(0);
	}
	return(1);
}

DWORD WriteSoundBuffer(DWORD dwOffset, DataT* pData) {
	LPVOID	pbPlayData;
	DWORD	dwPlayLength;

	pData->bFull = false;			// Reset Buffer Full Variable
	if (SUCCEEDED(hr = pDSB->Lock(	// Lock Sound Buffer Part
		dwOffset,			// dwOffset
		SOUND_BUFFER,//wfx.nAvgBytesPerSec,		// dwBytes
		&pbPlayData,	           // ppvAudioPtr1
		&dwPlayLength,		              // pdwAudioBytes1	
		NULL,				// ppvAudioPtr2
		0,				// pdwAudioBytes2
		0)))				// dwFlags
	{
		memcpy(pbPlayData, pData->dwDataBuffer, dwPlayLength);		// Copy Data from Data Buffer to Sound Buffer

		hr = pDSB->Unlock(						// Unlock Sound Buffer Part
			pbPlayData,				// ppvAudioPtr1
			dwPlayLength,				// pdwAudioBytes1
			NULL,					// ppvAudioPtr2
			0);					// pdwAudioBytes2

		return(0);
	}
	return(1);
}

DWORD WINAPI WaitForCaptureNotifications(void) {
	DWORD dwResult;

	do {
		// Wait for Capture Buffer Event
		dwResult = WaitForMultipleObjects(3, hCaptureEvent, false, INFINITE) - WAIT_OBJECT_0;

		// Check witch Event is Signaled
		switch (dwResult) {
		case 0: {
			ReadCaptureBuffer(0, &sData1);				// Read First Part 
			ResetEvent(hCaptureEvent[0]);				// Reset Capture Event
			break; }
		case 1: {
			ReadCaptureBuffer(SOUND_BUFFER/*wfx.nAvgBytesPerSec*/, &sData2);	// Read Second Part		
			ResetEvent(hCaptureEvent[1]);				// Reaset Capture Event
			break; }
		case 2: {
			bStart = false;						// Stop Capure Buffer
			cout << "Stop filming!" << endl;
			break; }
		}
	} while (bStart);
	return(0);
}

DWORD WINAPI WaitForPlayNotifications(void) {
	DWORD dwResult;
	DataT* pData = NULL;

	if (sData1.bFull) pData = &sData1;
	if (sData2.bFull) pData = &sData2;

	// Wait for Play Buffer Events
	dwResult = WaitForMultipleObjects(2, hPlayEvent, false, INFINITE) - WAIT_OBJECT_0;

	// Check witch Event is Signaled
	switch (dwResult) {
	case 0: {
		WriteSoundBuffer(0, pData);					// Write First Part
		ResetEvent(hPlayEvent[0]);					// Reset Play Event
		break; }
	case 1: {
		WriteSoundBuffer(SOUND_BUFFER/*wfx.nAvgBytesPerSec*/, pData);			// Write Second Part
		ResetEvent(hPlayEvent[1]);					// Reset Play Event
		break; }
	}
	return(0);
}

HRESULT CreateFullDuplexDevice(void) {
	DSBUFFERDESC			dsbd;
	DSCBUFFERDESC			dscbd;
	HWND					CMDHwnd;

	// Set Wave Format
	ZeroMemory(&wfx, sizeof(WAVEFORMATEX));
	wfx.wFormatTag = WAVE_FORMAT_PCM;
	wfx.nChannels = CHANNELS;
	wfx.nSamplesPerSec = SAMPLESPERSEC;
	wfx.wBitsPerSample = BITSPERSAMPLE;
	wfx.nBlockAlign = wfx.nChannels * wfx.wBitsPerSample / 8;
	wfx.nAvgBytesPerSec = wfx.nBlockAlign * wfx.nSamplesPerSec;
	wfx.cbSize = 0;

	// Set Sound Buffer Attributes
	ZeroMemory(&dsbd, sizeof(DSBUFFERDESC));
	dsbd.dwSize = sizeof(DSBUFFERDESC);
	dsbd.dwFlags = DSBCAPS_GLOBALFOCUS | DSBCAPS_CTRLPOSITIONNOTIFY | DSBCAPS_GETCURRENTPOSITION2;
	dsbd.dwBufferBytes = SOUND_BUFFER * 2;//wfx.nAvgBytesPerSec * 2;
	dsbd.lpwfxFormat = &wfx;

	// Set Capture Buffer Attributes
	ZeroMemory(&dscbd, sizeof(DSCBUFFERDESC));
	dscbd.dwSize = sizeof(DSCBUFFERDESC);
	dscbd.dwFlags = 0;
	dscbd.dwBufferBytes = SOUND_BUFFER * 2;//wfx.nAvgBytesPerSec * 2;
	dscbd.dwReserved = 0;
	dscbd.lpwfxFormat = &wfx;
	dscbd.dwFXCount = 0;
	dscbd.lpDSCFXDesc = NULL;

	// Get Console Handle
	CMDHwnd = GetCMDHwnd();

	DispatchSound::stGUID* guidMic
		= DispatchSound::Instance().GetMicPool().Find(L"마이크(9- USB audio CODEC)");
	DispatchSound::stGUID* guidSpk
		= DispatchSound::Instance().GetSpkPool().Find(L"(우)스피커(10- USB audio CODEC)");

	// Create Full Duplex Device
	hr = DirectSoundFullDuplexCreate8(
		&guidMic->guid,			// pcGuidCaptureDevice
		NULL,//&guidSpk->guid,			// pcGuidRenderDevice
		&dscbd,					// pcDSCBufferDesc
		&dsbd,					// pcDSBufferDesc
		CMDHwnd,				// hWnd
		DSSCL_PRIORITY,			// dwLevel
		&pDSFD,					// ppDSFD
		&pDSCB,					// ppDSCBuffer8
		&pDSB,					// ppDSBuffer8
		NULL);					// pUnkOuter

	return hr;
}

HRESULT SetCaptureNotifications(void) {
	LPDIRECTSOUNDNOTIFY8	pDSNotify;
	DSBPOSITIONNOTIFY		cdsbpn[CEVENTS];

	if (NULL == pDSCB) return E_INVALIDARG;

	// Create Sound Notify Interface 
	if (FAILED(hr = pDSCB->QueryInterface(IID_IDirectSoundNotify, (LPVOID*)&pDSNotify))) {
		return hr;
	}

	// Create Events.
	for (int i = 0; i < CEVENTS; ++i) {
		hCaptureEvent[i] = CreateEvent(NULL, TRUE, FALSE, NULL);
		if (NULL == hCaptureEvent[i]) {
			hr = GetLastError();
			return hr;
		}
	}

	// Describe Notifications
	cdsbpn[0].dwOffset = SOUND_BUFFER/*wfx.nAvgBytesPerSec*/ - 1;
	cdsbpn[0].hEventNotify = hCaptureEvent[0];

	cdsbpn[1].dwOffset = SOUND_BUFFER/*wfx.nAvgBytesPerSec*/ * 2 - 1;
	cdsbpn[1].hEventNotify = hCaptureEvent[1];

	cdsbpn[2].dwOffset = DSBPN_OFFSETSTOP;
	cdsbpn[2].hEventNotify = hCaptureEvent[2];

	// Create Notifications
	hr = pDSNotify->SetNotificationPositions(CEVENTS, cdsbpn);

	// Release Notification Object
	pDSNotify->Release();
	return hr;
}

HRESULT SetPlayNotifications(void) {
	LPDIRECTSOUNDNOTIFY8	pDSNotify;
	DSBPOSITIONNOTIFY		pdsbpn[PEVENTS];

	if (NULL == pDSB) return E_INVALIDARG;

	// Create Sound Notify Interface 
	if (FAILED(hr = pDSB->QueryInterface(IID_IDirectSoundNotify, (LPVOID*)&pDSNotify))) {
		return hr;
	}

	// Create Events
	for (int i = 0; i < PEVENTS; ++i) {
		hPlayEvent[i] = CreateEvent(NULL, TRUE, FALSE, NULL);
		if (NULL == hPlayEvent[i]) {
			hr = GetLastError();
			return hr;
		}
	}

	// Describe Notifications
	pdsbpn[0].dwOffset = SOUND_BUFFER/*wfx.nAvgBytesPerSec*/ - 1;
	pdsbpn[0].hEventNotify = hPlayEvent[0];

	pdsbpn[1].dwOffset = SOUND_BUFFER/*wfx.nAvgBytesPerSec*/ * 2 - 1;
	pdsbpn[1].hEventNotify = hPlayEvent[1];

	// Create Notifications.
	hr = pDSNotify->SetNotificationPositions(PEVENTS, pdsbpn);

	// Release Notification Object
	pDSNotify->Release();
	return hr;
}

HWND GetCMDHwnd(void) {
	LPCWSTR newtitle = (LPCWSTR)L"DirectSound-Test";
	SetConsoleTitle(newtitle);
	Sleep(40);
	return(FindWindow(NULL, newtitle));
}
//===========================================================

//***********************************************************

//***********************************************************


void slice(TCHAR* buf, std::vector<std::wstring>& vec)
{
	TCHAR *token1 = NULL;
	TCHAR *next_token1 = NULL;

	token1 = _tcstok_s(buf, _T(" "), &next_token1);

	// While there are tokens in "string1" or "string2"
	while ((token1 != NULL))
	{
		// Get next token:
		if (token1 != NULL)
		{
			//_tprintf(_T(" %s\n"), token1);
			vec.push_back(token1);
			token1 = _tcstok_s(NULL, _T(" "), &next_token1);
		}
	}
}

void MenuPrint()
{
	_tprintf(_T("\n\n\n"));
	_tprintf(_T("===========================================\n"));
	_tprintf(_T("  Direct Sound sample\n"));
	_tprintf(_T("===========================================\n"));
	_tprintf(_T("    c -- capture start/stop\n"));
	_tprintf(_T("    p -- play(device,L/R,index)\n"));
	_tprintf(_T("    s -- stop(device,L/R,index)\n"));
	_tprintf(_T("    t -- test(device,L/R,index)\n"));
	_tprintf(_T("===========================================\n"));
}
int main(int argc, char* argv[])
{
	_tsetlocale(LC_ALL, _T(""));

	//(좌)스피커(9- USB audio CODEC)
	//(우)스피커(10- USB audio CODEC)
	//Realtek Digital Output(Realtek High Definition Audio)
	//주 사운드 드라이버

	////SoundStreaming* sound = new SoundStreaming(GetDesktopWindow());
	DispatchSound::Instance().init(GetDesktopWindow(), _T("(좌)스피커(9- USB audio CODEC)"), 0);
	DispatchSound::Instance().init(GetDesktopWindow(), _T("(우)스피커(10- USB audio CODEC)"), 1);
	DispatchSound::Instance().init(GetDesktopWindow(), _T("Realtek Digital Output(Realtek High Definition Audio)"), 2);
	DispatchSound::Instance().init(GetDesktopWindow(), _T("주 사운드 드라이버"), 3);
	//DispatchSound::Instance().LoadWaveFile(1, _T("2001_3subway2.wav"));
	//DispatchSound::Instance().LoadWaveFile(2, _T("ringtone.wav"));
	//DispatchSound::Instance().LoadWaveFile(3, _T("Inboundtone.wav"));

	//captureMain();

	DispatchSound::stGUID* guidMic
		= DispatchSound::Instance().GetMicPool().Find(L"마이크(9- USB audio CODEC)");
	DispatchCapture capture;
	capture.init(GetDesktopWindow(), guidMic->guid);
	//capture.play();
	bool bCapture = false;

	//SoundClass sound(GetDesktopWindow());
	//sound.LoadWaveFile(L"Inboundtone.wav");

	TCHAR buf[1000] = _T("");
	while (1) {
		MenuPrint();
		//_fputts(_T("메시지를 입력하세요(q to quit) : \n"), stdout);
		_tprintf(_T("메시지를 입력하세요(q to quit) : "));
		_fgetts(buf, sizeof(buf), stdin);
		buf[_tcslen(buf) - 1] = 0;//개행문자 제거


		if (!_tcscmp(buf, _T("q")))
			break;

		if (!_tcscmp(buf, _T("")))
		{
			//delete sound;

			//sound = new SoundStreaming(GetDesktopWindow());
			//sound->LoadWaveFile(L"sound01.wav");
		}

		std::vector<std::wstring> vecString;
		slice(buf, vecString);

		if(false == vecString.empty())
		{
			if (!_tcscmp(vecString[0].c_str(), _T("c")))
			{
				if (false == bCapture) {
					bCapture = true;
					capture.play();
					_tprintf(_T("음성 capture를 시작합니다.\n"));
				}
				else {
					bCapture = false;
					capture.stop();
					_tprintf(_T("음성 capture를 종료합니다.\n"));
				}

			}
			if (!_tcscmp(vecString[0].c_str(), _T("p")))
			{
//				if (2 <= vecString.size())	DispatchSound::Instance().play(_tstoi(vecString[1].c_str()));
				if (4 <= vecString.size())
				{
					DispatchSound::Instance().LoadWaveFile(_T("2001_3subway2.wav"));
					DispatchSound::Instance().play(_tstoi(vecString[1].c_str())
						, (SoundPrimary::_playType)_tstoi(vecString[2].c_str())
						, _tstoi(vecString[3].c_str()));
				}
			}
			if (!_tcscmp(vecString[0].c_str(), _T("s")))
			{
//				if (2 <= vecString.size())	DispatchSound::Instance().stop(_tstoi(vecString[1].c_str()));
				if (4 <= vecString.size())
					DispatchSound::Instance().stop(_tstoi(vecString[1].c_str())
						, (SoundPrimary::_playType)_tstoi(vecString[2].c_str())
						, _tstoi(vecString[3].c_str()));
			}
			if (!_tcscmp(vecString[0].c_str(), _T("t")))
			{
//				if (2 <= vecString.size())	DispatchSound::Instance().test(_tstoi(vecString[1].c_str()));
				if (4 <= vecString.size())
					DispatchSound::Instance().play(_tstoi(vecString[1].c_str())
						, (SoundPrimary::_playType)_tstoi(vecString[2].c_str())
						, _tstoi(vecString[3].c_str()));
			}
		}


		//buf[0] = 0;//개행문자 제거
		//MenuPrint();
	}//..while (1) {

	capture.stop();

	system("pause");
    return 0;
}

