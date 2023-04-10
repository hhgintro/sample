// md5.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


#include <iostream>
#include <string>
#include <fstream>
#include <cstdint>

using std::cin;
using std::cout;
using std::endl;
using std::fstream;
using std::string;

typedef struct  WAV_HEADER
{
	/* RIFF Chunk Descriptor */
	uint8_t         RIFF[4];        // RIFF Header Magic header
	uint32_t        ChunkSize;      // RIFF Chunk Size
	uint8_t         WAVE[4];        // WAVE Header
									/* "fmt" sub-chunk */
	uint8_t         fmt[4];         // FMT header
	uint32_t        Subchunk1Size;  // Size of the fmt chunk
	uint16_t        AudioFormat;    // Audio format 1=PCM,6=mulaw,7=alaw,     257=IBM Mu-Law, 258=IBM A-Law, 259=ADPCM
	uint16_t        NumOfChan;      // Number of channels 1=Mono 2=Sterio
	uint32_t        SamplesPerSec;  // Sampling Frequency in Hz
	uint32_t        bytesPerSec;    // bytes per second
	uint16_t        blockAlign;     // 2=16-bit mono, 4=16-bit stereo
	uint16_t        bitsPerSample;  // Number of bits per sample
									/* "data" sub-chunk */
	uint8_t         Subchunk2ID[4]; // "data"  string
	uint32_t        Subchunk2Size;  // Sampled data length
} wav_hdr;

// find the file size
int getFileSize(FILE* inFile)
{
	int fileSize = 0;
	fseek(inFile, 0, SEEK_END);

	fileSize = ftell(inFile);

	fseek(inFile, 0, SEEK_SET);
	return fileSize;
}

bool wav_detail(TCHAR* filePath)
{
	wav_hdr wavHeader;
	int headerSize = sizeof(wav_hdr), filelength = 0;
	_tprintf(_T("Input wave file name: %s\n"), filePath);

	FILE* wavFile = NULL;
	_tfopen_s(&wavFile, filePath, _T("r"));
	if (wavFile == nullptr)
	{
		_tprintf(_T("Unable to open wave file: %s\n"), filePath);
		return false;
	}

	//Read the header
	size_t bytesRead = fread(&wavHeader, 1, headerSize, wavFile);
	_tprintf(_T("Header Read %d\n"), bytesRead);
	if (bytesRead > 0)
	{
		//Read the data
		uint16_t bytesPerSample = wavHeader.bitsPerSample / 8;      //Number     of bytes per sample
		uint64_t numSamples = wavHeader.ChunkSize / bytesPerSample; //How many samples are in the wav file?
		static const uint16_t BUFFER_SIZE = 4096;
		int8_t* buffer = new int8_t[BUFFER_SIZE];
		while ((bytesRead = fread(buffer, sizeof buffer[0], BUFFER_SIZE / (sizeof buffer[0]), wavFile)) > 0)
		{
			/** DO SOMETHING WITH THE WAVE DATA HERE **/
			cout << "Read " << bytesRead << " bytes." << endl;
		}
		delete[] buffer;
		buffer = nullptr;
		filelength = getFileSize(wavFile);

		cout << "File is                    :" << filelength << " bytes." << endl;
		cout << "RIFF header                :" << wavHeader.RIFF[0] << wavHeader.RIFF[1] << wavHeader.RIFF[2] << wavHeader.RIFF[3] << endl;
		cout << "WAVE header                :" << wavHeader.WAVE[0] << wavHeader.WAVE[1] << wavHeader.WAVE[2] << wavHeader.WAVE[3] << endl;
		cout << "FMT                        :" << wavHeader.fmt[0] << wavHeader.fmt[1] << wavHeader.fmt[2] << wavHeader.fmt[3] << endl;
		cout << "Data size                  :" << wavHeader.ChunkSize << endl;

		// Display the sampling Rate from the header
		cout << "Sampling Rate              :" << wavHeader.SamplesPerSec << endl;
		cout << "Number of bits used        :" << wavHeader.bitsPerSample << endl;
		cout << "Number of channels         :" << wavHeader.NumOfChan << endl;
		cout << "Number of bytes per second :" << wavHeader.bytesPerSec << endl;
		cout << "Data length                :" << wavHeader.Subchunk2Size << endl;
		cout << "Audio Format               :" << wavHeader.AudioFormat << endl;
		// Audio format 1=PCM,6=mulaw,7=alaw, 257=IBM Mu-Law, 258=IBM A-Law, 259=ADPCM

		cout << "Block align                :" << wavHeader.blockAlign << endl;
		cout << "Data string                :" << wavHeader.Subchunk2ID[0] << wavHeader.Subchunk2ID[1] << wavHeader.Subchunk2ID[2] << wavHeader.Subchunk2ID[3] << endl;
	}
	fclose(wavFile);
	return true;
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
	_tprintf(_T("\n\n\n"));
	_tprintf(_T("===========================================\n"));
	_tprintf(_T("  Direct Sound sample\n"));
	_tprintf(_T("===========================================\n"));
	_tprintf(_T("    c -- capture start/stop\n"));
	_tprintf(_T("    d -- wav detail(wav/path)\n"));
	_tprintf(_T("    p -- play(device,L/R,index,wav/path)\n"));
	_tprintf(_T("    s -- stop(device,L/R,index)\n"));
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
			if (!_tcscmp(vecString[0].c_str(), _T("d")))
			{
				if (2 <= vecString.size())
					wav_detail((TCHAR*)vecString[1].c_str());
			}
			if (!_tcscmp(vecString[0].c_str(), _T("p")))
			{
//				if (2 <= vecString.size())	DispatchSound::Instance().play(_tstoi(vecString[1].c_str()));
				if (4 <= vecString.size())
				{
					//DispatchSound::Instance().LoadWaveFile(_T("2001_3subway2.wav"));
					DispatchSound::Instance().LoadWaveFile((TCHAR*)vecString[4].c_str());
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
		}


		//buf[0] = 0;//개행문자 제거
		//MenuPrint();
	}//..while (1) {

	capture.stop();

	system("pause");
    return 0;
}

