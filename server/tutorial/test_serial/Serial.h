#pragma once

#include <windows.h>


#define MAXBLOCK 80
#define MAXPORTS 4

// ascii definitions 
#define ASCII_BEL 0x07 
#define ASCII_BS 0x08 
#define ASCII_LF 0x0A 
#define ASCII_CR 0x0D 
#define ASCII_XON 0x11 
#define ASCII_XOFF 0x13 


///참조: https://blog.naver.com/hhgintro/221463761014
/**
사용예제:
	헤더파일
	class CSerialEx : public CSerial
	{
	public:
		CSerialEx() {}
		~CSerialEx() {}

		//데이타를 받으면 CALLBACK된다.
		virtual void OnReceiveData(BYTE* data);
	};
	소스파일
	void CSerialEx::OnReceiveData(BYTE* data)
	{
		_tprintf(_T("data:[0x%x][0x%x][0x%x][0x%x][0x%x][0x%x][0x%x][0x%x]\n")
			, data[0], data[1], data[2], data[3], data[4], data[5], data[6], data[7]);
	}
	main함수
	int main()
	{
		CSerialEx serial;
		serial.Create(3, CBR_115200, 8, 0, 0);
		serial.Open();

		while (1)
		{
			Sleep(1);
		}

		system("pause");
		return 0;
	}
*/

class CSerial
{
public:
	CSerial();
	virtual ~CSerial();


	//comm 포트를 만든다. 
	BOOL Create(int port, DWORD rate=CBR_115200, BYTE bytesize=8, BYTE stop=0, BYTE parity=0);
	//comm 포트를 해제한다. 
	BOOL Destroy();
	//컴포트를 열고 연결을 시도한다.
	BOOL Open();
	//연결을 해제한다. 
	BOOL Close();

	//컴포트를 설정함. 
	void Set(int port, DWORD rate = CBR_115200, BYTE bytesize = 8, BYTE stop = 0, BYTE parity = 0);

	//컴포트에 데이터를 넣는다. 
	BOOL Write(LPSTR, DWORD);

	//데이타를 받으면 CALLBACK된다.
	virtual void OnReceiveData(BYTE* data) = 0;

private:
	//포트를 연결한다. 
	BOOL Setup();
	//컴포트에서 데이터를 받는다. 
	int Read(LPSTR, int);

	static unsigned int CALLBACK _Thread(void* lpParam);
	virtual void OnThread();


public:
	HANDLE idComDev;//컴포트 디바이스 연결 핸들 
	BOOL fConnected;//컴포트가 연결되면 1로 설정 
	BYTE abIn[MAXBLOCK + 1];//컴포트에서 들어오는 데이터 
	HWND m_hwnd;//메시지를 전달할 윈도 플래그 

public:
	BYTE bPort;
	BYTE bByteSize, bFlowCtrl, bParity, bStopBits;
	DWORD dwBaudRate;

	HANDLE hThread;
	OVERLAPPED osWrite, osRead;

};

