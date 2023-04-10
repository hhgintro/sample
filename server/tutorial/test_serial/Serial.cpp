#include "stdafx.h"
#include "Serial.h"

#include <process.h>	//_beginthreadex

CSerial::CSerial()
{
	fConnected = FALSE;
}


CSerial::~CSerial()
{
	Destroy();
}

//컴포트 정보를 만든다. 
//이것을 만들 때 이전에 
// Set(); -> SetXonOff() ->SetDtrRts()한 다음 설정한다. 
BOOL CSerial::Create(int port, DWORD rate/*CBR_115200*/, BYTE bytesize/*8*/, BYTE stop/*0*/, BYTE parity/*8*/)
{
	osWrite.Offset = 0;
	osWrite.OffsetHigh = 0;
	osRead.Offset = 0;
	osRead.OffsetHigh = 0;

	//이벤트 창구 설정 
	osRead.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
	if (osRead.hEvent == NULL)
		return FALSE;

	osWrite.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
	if (NULL == osWrite.hEvent)
	{
		CloseHandle(osRead.hEvent);
		return FALSE;
	}

	Set(port, rate, bytesize, stop, parity);
	return TRUE;
}

//컴포트를 완전히 해제한다. 
BOOL CSerial::Destroy()
{
	if (fConnected)	Close();
	CloseHandle(osRead.hEvent);
	CloseHandle(osWrite.hEvent);
	return (TRUE);
}

//컴포트를 열고 연결을 시도한다. 
BOOL CSerial::Open()
{
	TCHAR szPort[15];
	if (bPort > MAXPORTS)	lstrcpy(szPort, _T("\\\\.\\TELNET"));
	else					wsprintf(szPort, _T("COM%d"), bPort);

	// COMM device를 파일 형식으로 연결한다. 
	idComDev = CreateFile(szPort, GENERIC_READ | GENERIC_WRITE,
							0, // exclusive access 
							NULL, // no security attrs 
							OPEN_EXISTING,
							FILE_ATTRIBUTE_NORMAL |
							FILE_FLAG_OVERLAPPED, // overlapped I/O 
							NULL);
	if((HANDLE)-1 == idComDev)
		return FALSE;


	//컴포트에서 데이터를 교환하는 방법을 char 단위를 기본으로 설정하자. 
	SetCommMask(idComDev, EV_RXCHAR);
	SetupComm(idComDev, 4096, 4096);
	//디바이스에 쓰레기가 있을지 모르니까 깨끗이 청소를 하자. 
	PurgeComm(idComDev, PURGE_TXABORT | PURGE_RXABORT | PURGE_TXCLEAR | PURGE_RXCLEAR);

	COMMTIMEOUTS CommTimeOuts;
	CommTimeOuts.ReadIntervalTimeout = 0xFFFFFFFF;
	CommTimeOuts.ReadTotalTimeoutMultiplier = 0;
	CommTimeOuts.ReadTotalTimeoutConstant = 1000;
	CommTimeOuts.WriteTotalTimeoutMultiplier = 0;
	CommTimeOuts.WriteTotalTimeoutConstant = 1000;
	SetCommTimeouts(idComDev, &CommTimeOuts);


	if (FALSE == Setup())//연결이 되었다면 fRetVal TRUE이므로 
	{
		fConnected = FALSE;
		CloseHandle(idComDev);
		return FALSE;
	}

	fConnected = TRUE;//연결되었다고 말해 줌. 

	//프로시저를 _Thread에 연결하니까 나중에 데이터가 왔다갔다 
	//하면 모든 내용은 _Thread가 담당한다. 
	hThread = (HANDLE)::_beginthreadex(NULL, 0, _Thread, this, 0, NULL);
	return TRUE;
}

//연결을 닫는다. 
BOOL CSerial::Close()
{
	// set connected flag to FALSE 
	fConnected = FALSE;
	// disable event notification and wait for thread 
	// to halt 
	SetCommMask(idComDev, 0);
	EscapeCommFunction(idComDev, CLRDTR);
	PurgeComm(idComDev, PURGE_TXABORT | PURGE_RXABORT |
		PURGE_TXCLEAR | PURGE_RXCLEAR);
	CloseHandle(idComDev);
	return (TRUE);
}

//컴포트를 설정한다. 
void CSerial::Set(int port, DWORD rate/*CBR_115200*/, BYTE bytesize/*8*/, BYTE stop/*0*/, BYTE parity/*8*/)
{
	bPort = port;
	dwBaudRate = rate;
	bByteSize = bytesize;
	bStopBits = stop;
	bParity = parity;
}

//파일로 설정된 컴포트와 실질 포트를 연결시킨다. 
//Setup 이전에 Create를 해주어야 한다. 
BOOL CSerial::Setup()
{
	DCB dcb;
	dcb.DCBlength = sizeof(DCB);
	GetCommState(idComDev, &dcb);//dcb의 기본값을 받는다. 

	//이 부분을 수정해야 한다. 
	dcb.BaudRate = dwBaudRate;//전송 속도 
	dcb.ByteSize = bByteSize;//데이터 비트 
	dcb.Parity = bParity;//패리티 체크 
	dcb.StopBits = bStopBits;//스톱 비트 
	dcb.fOutxDsrFlow = 0;//Dsr Flow 
	dcb.fDtrControl = DTR_CONTROL_ENABLE;//Dtr Control 
	dcb.fOutxCtsFlow = 0;//Cts Flow 
	dcb.fRtsControl = RTS_CONTROL_ENABLE; //Ctr Control 
	dcb.fInX = dcb.fOutX = 1; //XON/XOFF 관한 것 
	dcb.XonChar = ASCII_XON;
	dcb.XoffChar = ASCII_XOFF;
	dcb.XonLim = 100;
	dcb.XoffLim = 100;
	dcb.fBinary = TRUE;
	dcb.fParity = TRUE;
	dcb.fBinary = TRUE;
	dcb.fParity = TRUE;
	return SetCommState(idComDev, &dcb); //변경된 Dcb 설정
}

//컴포트로부터 데이터를 읽는다. 
int CSerial::Read(LPSTR lpszBlock, int nMaxLength)
{
	COMSTAT ComStat;
	DWORD dwErrorFlags;
	DWORD dwLength;
	// only try to read number of bytes in queue 
	ClearCommError(idComDev, &dwErrorFlags, &ComStat);
	dwLength = min((DWORD)nMaxLength, ComStat.cbInQue);
	if (dwLength <= 0)
		return dwLength;

	if (FALSE == ReadFile(idComDev, lpszBlock, dwLength, &dwLength, &osRead))
	{
		//이곳에 에러를 넣다. 
		//즉 ReadFile했을 때 데이터가 제대로 안 나오면 fReadState에 여러 
		//에러 코드를 리턴한다. 이 때 복구할 수 있으면 좋지만 실질적인 
		//복구가 불가능하다. 따라서, 재송출을 해달라는 메시지를 해주는 것이 
		//좋다.
		_tprintf(_T("Read fail\n"));
	}
	return dwLength;
}

BOOL CSerial::Write(LPSTR lpByte, DWORD dwBytesToWrite)
{
	DWORD dwBytesWritten;
	if (FALSE == WriteFile(idComDev, lpByte, dwBytesToWrite, &dwBytesWritten, &osWrite))
	{
		//컴포트에 데이터를 제대로 써넣지 못했을 경우이다. 
		//이 때는 어떻게 할까. 그것은 사용자 마음이다. 
		//다시 보내고 싶으면 재귀송출을 하면 된다. 
		//그러나 무한 루프를 돌 수 있다는 점을 주의하자. 
		_tprintf(_T("Write fail\n"));
	}
	return TRUE;
}

unsigned int CALLBACK CSerial::_Thread(void* param)
{
	if (NULL == param)
		return 0;

	((CSerial*)param)->OnThread();
	return 0;
}

void CSerial::OnThread()
{
	DWORD dwEvtMask;
	OVERLAPPED os;

	BYTE InData[MAXBLOCK + 1];
	int nLength;

	memset(&os, 0, sizeof(OVERLAPPED));
	os.hEvent = CreateEvent(NULL, // no security 
							TRUE, // explicit reset req 
							FALSE, // initial event reset 
							NULL); // no name 
	if (os.hEvent == NULL)
	{
		printf("Failed to create event for thread!\n");
		return;
	}

	if (!SetCommMask(idComDev, EV_RXCHAR))
		return;

	while (fConnected)
	{
		dwEvtMask = 0;
		WaitCommEvent(idComDev, &dwEvtMask, NULL);
		if (EV_RXCHAR != (dwEvtMask & EV_RXCHAR))
			continue;

		do {
			memset(InData, 0, sizeof(InData));
			if (nLength = Read((LPSTR)InData, MAXBLOCK))
			{
				//이곳에서 데이터를 받는다. 
				OnReceiveData(InData);
			}
		} while (nLength > 0);
	}
	CloseHandle(os.hEvent);
}

