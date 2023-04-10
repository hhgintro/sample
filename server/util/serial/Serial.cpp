#include "stdafx.h"
#include "Serial.h"

#include <process.h>	//_beginthreadex

namespace HisUtil {

	CSerial::CSerial()
	{
		m_fConnected = FALSE;
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
		m_osWrite.Offset		= 0;
		m_osWrite.OffsetHigh	= 0;
		m_osRead.Offset			= 0;
		m_osRead.OffsetHigh		= 0;

		//이벤트 창구 설정 
		m_osRead.hEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
		if (m_osRead.hEvent == NULL)
		{
			_tprintf(_T("Read CreateEvnet Fail\n"));
			return FALSE;
		}

		m_osWrite.hEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
		if (NULL == m_osWrite.hEvent)
		{
			CloseHandle(m_osRead.hEvent);
			_tprintf(_T("Write CreateEvnet Fail\n"));
			return FALSE;
		}

		Set(port, rate, bytesize, stop, parity);
		return TRUE;
	}

	//컴포트를 완전히 해제한다. 
	BOOL CSerial::Destroy()
	{
		if(m_hThread) CloseHandle(m_hThread);
		if (m_fConnected) Close();
		CloseHandle(m_osRead.hEvent);
		CloseHandle(m_osWrite.hEvent);
		return (TRUE);
	}

	//컴포트를 열고 연결을 시도한다. 
	BOOL CSerial::Open()
	{
		TCHAR szPort[16];
		if (m_Port > MAXPORTS)	_tcscpy_s(szPort, _T("\\\\.\\TELNET"));
		else					_stprintf_s(szPort, _T("COM%d"), m_Port);

		// COMM device를 파일 형식으로 연결한다. 
		m_hComDev = CreateFile(szPort, GENERIC_READ | GENERIC_WRITE
								, 0 // exclusive access 
								, NULL // no security attrs 
								, OPEN_EXISTING
								//, FILE_ATTRIBUTE_NORMAL
								, FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED // overlapped I/O 
								//, FILE_FLAG_OVERLAPPED // overlapped I/O 
								, NULL);
		if (INVALID_HANDLE_VALUE == m_hComDev)
		{
			_tprintf(_T("CreateFile FAILED : 0x%x\n"), GetLastError());
			return FALSE;
		}


		//컴포트에서 데이터를 교환하는 방법을 char 단위를 기본으로 설정하자. 
		SetCommMask(m_hComDev, EV_RXCHAR);
		SetupComm(m_hComDev, MAX_IO_QUEUE, MAX_IO_QUEUE);
		//디바이스에 쓰레기가 있을지 모르니까 깨끗이 청소를 하자. 
		PurgeComm(m_hComDev, PURGE_TXABORT | PURGE_RXABORT | PURGE_TXCLEAR | PURGE_RXCLEAR);

		COMMTIMEOUTS CommTimeOuts;
		CommTimeOuts.ReadIntervalTimeout			= 0xFFFFFFFF;
		CommTimeOuts.ReadTotalTimeoutMultiplier		= 0;
		CommTimeOuts.ReadTotalTimeoutConstant		= 1000;
		CommTimeOuts.WriteTotalTimeoutMultiplier	= 0;
		CommTimeOuts.WriteTotalTimeoutConstant		= 1000;
		SetCommTimeouts(m_hComDev, &CommTimeOuts);


		if (FALSE == Setup())//연결이 되었다면 fRetVal TRUE이므로 
		{
			m_fConnected = FALSE;
			CloseHandle(m_hComDev);
			_tprintf(_T("Setup() FAILED : 0x%x\n"), GetLastError());
			return FALSE;
		}
		m_fConnected = TRUE;//연결되었다고 말해 줌. 

		//프로시저를 _Thread에 연결하니까 나중에 데이터가 왔다갔다 
		//하면 모든 내용은 _Thread가 담당한다. 
		m_hThread = (HANDLE)::_beginthreadex(NULL, 0, _Thread, this, 0, NULL);
		_tprintf(_T("Success Serial Open\n"));
		
		Clear();
		return TRUE;
	}

	//연결을 닫는다. 
	BOOL CSerial::Close()
	{
		// set connected flag to FALSE 
		m_fConnected = FALSE;
		// disable event notification and wait for thread 
		// to halt 
		SetCommMask(m_hComDev, 0);
		EscapeCommFunction(m_hComDev, CLRDTR);
		PurgeComm(m_hComDev, PURGE_TXABORT | PURGE_RXABORT | PURGE_TXCLEAR | PURGE_RXCLEAR);
		CloseHandle(m_hComDev);
		return (TRUE);
	}

	//초기화
	void CSerial::Clear()
	{
		//memset(m_ReadDataPool, 0, sizeof(m_ReadDataPool));
		m_offsetRead	= 0;
		m_offsetWrite	= 0;

	}

	//컴포트를 설정한다. 
	void CSerial::Set(int port, DWORD rate/*CBR_115200*/, BYTE bytesize/*8*/, BYTE stop/*0*/, BYTE parity/*8*/)
	{
		m_Port			= port;
		m_dwBaudRate	= rate;
		m_bByteSize		= bytesize;
		m_bStopBits		= stop;
		m_bParity		= parity;
	}

	//파일로 설정된 컴포트와 실질 포트를 연결시킨다. 
	//Setup 이전에 Create를 해주어야 한다. 
	BOOL CSerial::Setup()
	{
		DCB dcb;
		dcb.DCBlength = sizeof(DCB);
		GetCommState(m_hComDev, &dcb);//dcb의 기본값을 받는다. 

		//이 부분을 수정해야 한다.
		dcb.BaudRate		= m_dwBaudRate;//전송 속도
		dcb.ByteSize		= m_bByteSize;//데이터 비트
		dcb.Parity			= m_bParity;//패리티 체크
		dcb.StopBits		= m_bStopBits;//스톱 비트
		dcb.fOutxDsrFlow	= 0;//Dsr Flow
		dcb.fDtrControl		= DTR_CONTROL_ENABLE;//Dtr Control
		dcb.fOutxCtsFlow	= 0;//Cts Flow
		dcb.fRtsControl		= RTS_CONTROL_ENABLE; //Ctr Control
		dcb.fInX			= 1; //XON/XOFF 관한 것
		dcb.fOutX			= 1; //XON/XOFF 관한 것
		dcb.XonChar			= ASCII_XON;
		dcb.XoffChar		= ASCII_XOFF;
		dcb.XonLim			= 100;
		dcb.XoffLim			= 100;
		dcb.fBinary			= TRUE;
		dcb.fParity			= TRUE;
		dcb.fBinary			= TRUE;
		dcb.fParity			= TRUE;
		return SetCommState(m_hComDev, &dcb); //변경된 Dcb 설정
	}

	//컴포트로부터 데이터를 읽는다. 
	int CSerial::Read(int nMaxLength)
	{
		COMSTAT ComStat;
		DWORD dwErrorFlags;
		DWORD dwLength;
		// only try to read number of bytes in queue 
		ClearCommError(m_hComDev, &dwErrorFlags, &ComStat);
		dwLength = min((DWORD)nMaxLength, ComStat.cbInQue);
		if (dwLength <= 0)	return dwLength;

		//입력된 데이타의 length가 nMaxLength를 넘으면 기록할 수 가 없다.
		if (nMaxLength <= m_offsetWrite + dwLength)
		{
			_tprintf(_T("pool is overflow !!!\n"));
			return 0;
		}

		if (FALSE == ReadFile(m_hComDev, &m_ReadDataPool[m_offsetWrite], dwLength, &dwLength, &m_osRead))
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
		if (FALSE == WriteFile(m_hComDev, lpByte, dwBytesToWrite, 0, &m_osWrite))
		{
			//컴포트에 데이터를 제대로 써넣지 못했을 경우이다. 
			//이 때는 어떻게 할까. 그것은 사용자 마음이다. 
			//다시 보내고 싶으면 재귀송출을 하면 된다. 
			//그러나 무한 루프를 돌 수 있다는 점을 주의하자. 
			//_tprintf(_T("Write fail(0x%x,%d)\n"), GetLastError(), GetLastError());

			DWORD dwErrorCode = GetLastError();
			if (ERROR_IO_PENDING != dwErrorCode)
			{
				_tprintf(_T("Write fail(0x%x)\n"), dwErrorCode);
				return FALSE;
			}
		}

		//DWORD dwBytesWritten = 0;
		//GetOverlappedResult(m_hComDev, &osWrite, &dwBytesWritten, TRUE);
		////infinitely wait for WriteFile() operation compelete

		return TRUE;
	}

	void CSerial::ReadStaticSize(int staticSize)
	{
		//printf("offsetW=%d, offsetR=%d\n", m_offsetWrite, m_offsetRead);
		//모든 패킷이 동일한 크기를 가질때 처리루틴
		while (staticSize <= (m_offsetWrite - m_offsetRead))
		{
			OnReceiveData(&m_ReadDataPool[m_offsetRead], staticSize);
			m_offsetRead += staticSize;
		}
		//printf("offsetW=%d, offsetR=%d\n", m_offsetWrite, m_offsetRead);

		//모두 읽었으면 offset 초기화.
		if(m_offsetWrite == m_offsetRead)
		{
			m_offsetRead = m_offsetWrite = 0;
			//printf("offsetW=%d, offsetR=%d\n", m_offsetWrite, m_offsetRead);
		}
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
		int nLength = 0;

		memset(&os, 0, sizeof(OVERLAPPED));
		os.hEvent = CreateEvent(NULL, // no security 
								FALSE, // explicit reset req 
								FALSE, // initial event reset 
								NULL); // no name 
		if (os.hEvent == NULL)
		{
			_tprintf(_T("Failed to create event for thread!\n"));
			return;
		}

		if (!SetCommMask(m_hComDev, EV_RXCHAR))
			return;

		while (m_fConnected)
		{
			dwEvtMask = 0;
			WaitCommEvent(m_hComDev, &dwEvtMask, NULL);
			if (EV_RXCHAR != (dwEvtMask & EV_RXCHAR))
				continue;

			do {
				if (nLength = Read(MAX_READ_DATA_POOL))
				{
					m_offsetWrite += nLength;

					//이곳에서 데이터를 받는다.
					//OnReceiveData(ReadDataPool, nLength);
					
					//모든 패킷이 동일한 크기를 가질때 가능한 루틴입니다.
					//패킷하나가 고정(5byte)입니다.
					ReadStaticSize(PROTOCOL_LENGTH);
				}
			} while (nLength > 0);

		}//..while (m_fConnected)
		CloseHandle(os.hEvent);
	}

};//..namespace HisUtil {
