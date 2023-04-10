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

//����Ʈ ������ �����. 
//�̰��� ���� �� ������ 
// Set(); -> SetXonOff() ->SetDtrRts()�� ���� �����Ѵ�. 
BOOL CSerial::Create(int port, DWORD rate/*CBR_115200*/, BYTE bytesize/*8*/, BYTE stop/*0*/, BYTE parity/*8*/)
{
	osWrite.Offset = 0;
	osWrite.OffsetHigh = 0;
	osRead.Offset = 0;
	osRead.OffsetHigh = 0;

	//�̺�Ʈ â�� ���� 
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

//����Ʈ�� ������ �����Ѵ�. 
BOOL CSerial::Destroy()
{
	if (fConnected)	Close();
	CloseHandle(osRead.hEvent);
	CloseHandle(osWrite.hEvent);
	return (TRUE);
}

//����Ʈ�� ���� ������ �õ��Ѵ�. 
BOOL CSerial::Open()
{
	TCHAR szPort[15];
	if (bPort > MAXPORTS)	lstrcpy(szPort, _T("\\\\.\\TELNET"));
	else					wsprintf(szPort, _T("COM%d"), bPort);

	// COMM device�� ���� �������� �����Ѵ�. 
	idComDev = CreateFile(szPort, GENERIC_READ | GENERIC_WRITE,
							0, // exclusive access 
							NULL, // no security attrs 
							OPEN_EXISTING,
							FILE_ATTRIBUTE_NORMAL |
							FILE_FLAG_OVERLAPPED, // overlapped I/O 
							NULL);
	if((HANDLE)-1 == idComDev)
		return FALSE;


	//����Ʈ���� �����͸� ��ȯ�ϴ� ����� char ������ �⺻���� ��������. 
	SetCommMask(idComDev, EV_RXCHAR);
	SetupComm(idComDev, 4096, 4096);
	//����̽��� �����Ⱑ ������ �𸣴ϱ� ������ û�Ҹ� ����. 
	PurgeComm(idComDev, PURGE_TXABORT | PURGE_RXABORT | PURGE_TXCLEAR | PURGE_RXCLEAR);

	COMMTIMEOUTS CommTimeOuts;
	CommTimeOuts.ReadIntervalTimeout = 0xFFFFFFFF;
	CommTimeOuts.ReadTotalTimeoutMultiplier = 0;
	CommTimeOuts.ReadTotalTimeoutConstant = 1000;
	CommTimeOuts.WriteTotalTimeoutMultiplier = 0;
	CommTimeOuts.WriteTotalTimeoutConstant = 1000;
	SetCommTimeouts(idComDev, &CommTimeOuts);


	if (FALSE == Setup())//������ �Ǿ��ٸ� fRetVal TRUE�̹Ƿ� 
	{
		fConnected = FALSE;
		CloseHandle(idComDev);
		return FALSE;
	}

	fConnected = TRUE;//����Ǿ��ٰ� ���� ��. 

	//���ν����� _Thread�� �����ϴϱ� ���߿� �����Ͱ� �Դٰ��� 
	//�ϸ� ��� ������ _Thread�� ����Ѵ�. 
	hThread = (HANDLE)::_beginthreadex(NULL, 0, _Thread, this, 0, NULL);
	return TRUE;
}

//������ �ݴ´�. 
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

//����Ʈ�� �����Ѵ�. 
void CSerial::Set(int port, DWORD rate/*CBR_115200*/, BYTE bytesize/*8*/, BYTE stop/*0*/, BYTE parity/*8*/)
{
	bPort = port;
	dwBaudRate = rate;
	bByteSize = bytesize;
	bStopBits = stop;
	bParity = parity;
}

//���Ϸ� ������ ����Ʈ�� ���� ��Ʈ�� �����Ų��. 
//Setup ������ Create�� ���־�� �Ѵ�. 
BOOL CSerial::Setup()
{
	DCB dcb;
	dcb.DCBlength = sizeof(DCB);
	GetCommState(idComDev, &dcb);//dcb�� �⺻���� �޴´�. 

	//�� �κ��� �����ؾ� �Ѵ�. 
	dcb.BaudRate = dwBaudRate;//���� �ӵ� 
	dcb.ByteSize = bByteSize;//������ ��Ʈ 
	dcb.Parity = bParity;//�и�Ƽ üũ 
	dcb.StopBits = bStopBits;//���� ��Ʈ 
	dcb.fOutxDsrFlow = 0;//Dsr Flow 
	dcb.fDtrControl = DTR_CONTROL_ENABLE;//Dtr Control 
	dcb.fOutxCtsFlow = 0;//Cts Flow 
	dcb.fRtsControl = RTS_CONTROL_ENABLE; //Ctr Control 
	dcb.fInX = dcb.fOutX = 1; //XON/XOFF ���� �� 
	dcb.XonChar = ASCII_XON;
	dcb.XoffChar = ASCII_XOFF;
	dcb.XonLim = 100;
	dcb.XoffLim = 100;
	dcb.fBinary = TRUE;
	dcb.fParity = TRUE;
	dcb.fBinary = TRUE;
	dcb.fParity = TRUE;
	return SetCommState(idComDev, &dcb); //����� Dcb ����
}

//����Ʈ�κ��� �����͸� �д´�. 
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
		//�̰��� ������ �ִ�. 
		//�� ReadFile���� �� �����Ͱ� ����� �� ������ fReadState�� ���� 
		//���� �ڵ带 �����Ѵ�. �� �� ������ �� ������ ������ �������� 
		//������ �Ұ����ϴ�. ����, ������� �ش޶�� �޽����� ���ִ� ���� 
		//����.
		_tprintf(_T("Read fail\n"));
	}
	return dwLength;
}

BOOL CSerial::Write(LPSTR lpByte, DWORD dwBytesToWrite)
{
	DWORD dwBytesWritten;
	if (FALSE == WriteFile(idComDev, lpByte, dwBytesToWrite, &dwBytesWritten, &osWrite))
	{
		//����Ʈ�� �����͸� ����� ����� ������ ����̴�. 
		//�� ���� ��� �ұ�. �װ��� ����� �����̴�. 
		//�ٽ� ������ ������ ��ͼ����� �ϸ� �ȴ�. 
		//�׷��� ���� ������ �� �� �ִٴ� ���� ��������. 
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
				//�̰����� �����͸� �޴´�. 
				OnReceiveData(InData);
			}
		} while (nLength > 0);
	}
	CloseHandle(os.hEvent);
}

