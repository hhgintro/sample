// md5.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "sound/SoundStreaming.h"
#include "sound/SoundClass.h"

#include <vector>
#include <string.h>


void test()
{

}

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
	_tprintf(_T("===========================================\n"));
	_tprintf(_T("  Direct Sound sample\n"));
	_tprintf(_T("===========================================\n"));
	_tprintf(_T("    p -- play(index)\n"));
	_tprintf(_T("    s -- stop(index)\n"));
	_tprintf(_T("    t -- test(index)\n"));
	_tprintf(_T("===========================================\n"));
}
int main(int argc, char* argv[])
{
	_tsetlocale(LC_ALL, _T(""));
	test();

	MenuPrint();

	//SoundStreaming* sound = new SoundStreaming(GetDesktopWindow());
	SoundStreaming::Instance().init(GetDesktopWindow());
	SoundStreaming::Instance().LoadWaveFile(1, 960, L"2001_3subway2.wav");
	SoundStreaming::Instance().LoadWaveFile(2, 44100, L"ringtone.wav");
	SoundStreaming::Instance().LoadWaveFile(3, 44100, L"Inboundtone.wav");

	SoundClass sound(GetDesktopWindow());
	sound.LoadWaveFile(L"Inboundtone.wav");

	TCHAR buf[1000] = _T("");
	while (1) {
		//_fputts(_T("메시지를 입력하세요(q to quit) : \n"), stdout);
		_tprintf(_T("메시지를 입력하세요(q to quit) : \n"));
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
			if (!_tcscmp(vecString[0].c_str(), _T("a")))
			{
				sound.play();
			}
			if (!_tcscmp(vecString[0].c_str(), _T("p")))
			{
				if (2 <= vecString.size())	SoundStreaming::Instance().play(_tstoi(vecString[1].c_str()));
			}
			if (!_tcscmp(vecString[0].c_str(), _T("s")))
			{
				if (2 <= vecString.size())	SoundStreaming::Instance().stop(_tstoi(vecString[1].c_str()));
			}
			if (!_tcscmp(vecString[0].c_str(), _T("t")))
			{
				if (2 <= vecString.size())	SoundStreaming::Instance().test(_tstoi(vecString[1].c_str()));
			}
		}


		//buf[0] = 0;//개행문자 제거
		//MenuPrint();
	}//..while (1) {


	system("pause");
    return 0;
}

