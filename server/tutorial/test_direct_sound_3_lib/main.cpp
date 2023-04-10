// md5.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


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

