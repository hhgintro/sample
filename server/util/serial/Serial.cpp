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

	//����Ʈ ������ �����. 
	//�̰��� ���� �� ������ 
	// Set(); -> SetXonOff() ->SetDtrRts()�� ���� �����Ѵ�. 
	BOOL CSerial::Create(int port, DWORD rate/*CBR_115200*/, BYTE bytesize/*8*/, BYTE stop/*0*/, BYTE parity/*8*/)
	{
		m_osWrite.Offset		= 0;
		m_osWrite.OffsetHigh	= 0;
		m_osRead.Offset			= 0;
		m_osRead.OffsetHigh		= 0;

		//�̺�Ʈ â�� ���� 
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

	//����Ʈ�� ������ �����Ѵ�. 
	BOOL CSerial::Destroy()
	{
		if(m_hThread) CloseHandle(m_hThread);
		if (m_fConnected) Close();
		CloseHandle(m_osRead.hEvent);
		CloseHandle(m_osWrite.hEvent);
		return (TRUE);
	}

	//����Ʈ�� ���� ������ �õ��Ѵ�. 
	BOOL CSerial::Open()
	{
		TCHAR szPort[16];
		if (m_Port > MAXPORTS)	_tcscpy_s(szPort, _T("\\\\.\\TELNET"));
		else					_stprintf_s(szPort, _T("COM%d"), m_Port);

		// COMM device�� ���� �������� �����Ѵ�. 
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


		//����Ʈ���� �����͸� ��ȯ�ϴ� ����� char ������ �⺻���� ��������. 
		SetCommMask(m_hComDev, EV_RXCHAR);
		SetupComm(m_hComDev, MAX_IO_QUEUE, MAX_IO_QUEUE);
		//����̽��� �����Ⱑ ������ �𸣴ϱ� ������ û�Ҹ� ����. 
		PurgeComm(m_hComDev, PURGE_TXABORT | PURGE_RXABORT | PURGE_TXCLEAR | PURGE_RXCLEAR);

		COMMTIMEOUTS CommTimeOuts;
		CommTimeOuts.ReadIntervalTimeout			= 0xFFFFFFFF;
		CommTimeOuts.ReadTotalTimeoutMultiplier		= 0;
		CommTimeOuts.ReadTotalTimeoutConstant		= 1000;
		CommTimeOuts.WriteTotalTimeoutMultiplier	= 0;
		CommTimeOuts.WriteTotalTimeoutConstant		= 1000;
		SetCommTimeouts(m_hComDev, &CommTimeOuts);


		if (FALSE == Setup())//������ �Ǿ��ٸ� fRetVal TRUE�̹Ƿ� 
		{
			m_fConnected = FALSE;
			CloseHandle(m_hComDev);
			_tprintf(_T("Setup() FAILED : 0x%x\n"), GetLastError());
			return FALSE;
		}
		m_fConnected = TRUE;//����Ǿ��ٰ� ���� ��. 

		//���ν����� _Thread�� �����ϴϱ� ���߿� �����Ͱ� �Դٰ��� 
		//�ϸ� ��� ������ _Thread�� ����Ѵ�. 
		m_hThread = (HANDLE)::_beginthreadex(NULL, 0, _Thread, this, 0, NULL);
		_tprintf(_T("Success Serial Open\n"));
		
		Clear();
		return TRUE;
	}

	//������ �ݴ´�. 
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

	//�ʱ�ȭ
	void CSerial::Clear()
	{
		//memset(m_ReadDataPool, 0, sizeof(m_ReadDataPool));
		m_offsetRead	= 0;
		m_offsetWrite	= 0;

	}

	//����Ʈ�� �����Ѵ�. 
	void CSerial::Set(int port, DWORD rate/*CBR_115200*/, BYTE bytesize/*8*/, BYTE stop/*0*/, BYTE parity/*8*/)
	{
		m_Port			= port;
		m_dwBaudRate	= rate;
		m_bByteSize		= bytesize;
		m_bStopBits		= stop;
		m_bParity		= parity;
	}

	//���Ϸ� ������ ����Ʈ�� ���� ��Ʈ�� �����Ų��. 
	//Setup ������ Create�� ���־�� �Ѵ�. 
	BOOL CSerial::Setup()
	{
		DCB dcb;
		dcb.DCBlength = sizeof(DCB);
		GetCommState(m_hComDev, &dcb);//dcb�� �⺻���� �޴´�. 

		//�� �κ��� �����ؾ� �Ѵ�.
		dcb.BaudRate		= m_dwBaudRate;//���� �ӵ�
		dcb.ByteSize		= m_bByteSize;//������ ��Ʈ
		dcb.Parity			= m_bParity;//�и�Ƽ üũ
		dcb.StopBits		= m_bStopBits;//���� ��Ʈ
		dcb.fOutxDsrFlow	= 0;//Dsr Flow
		dcb.fDtrControl		= DTR_CONTROL_ENABLE;//Dtr Control
		dcb.fOutxCtsFlow	= 0;//Cts Flow
		dcb.fRtsControl		= RTS_CONTROL_ENABLE; //Ctr Control
		dcb.fInX			= 1; //XON/XOFF ���� ��
		dcb.fOutX			= 1; //XON/XOFF ���� ��
		dcb.XonChar			= ASCII_XON;
		dcb.XoffChar		= ASCII_XOFF;
		dcb.XonLim			= 100;
		dcb.XoffLim			= 100;
		dcb.fBinary			= TRUE;
		dcb.fParity			= TRUE;
		dcb.fBinary			= TRUE;
		dcb.fParity			= TRUE;
		return SetCommState(m_hComDev, &dcb); //����� Dcb ����
	}

	//����Ʈ�κ��� �����͸� �д´�. 
	int CSerial::Read(int nMaxLength)
	{
		COMSTAT ComStat;
		DWORD dwErrorFlags;
		DWORD dwLength;
		// only try to read number of bytes in queue 
		ClearCommError(m_hComDev, &dwErrorFlags, &ComStat);
		dwLength = min((DWORD)nMaxLength, ComStat.cbInQue);
		if (dwLength <= 0)	return dwLength;

		//�Էµ� ����Ÿ�� length�� nMaxLength�� ������ ����� �� �� ����.
		if (nMaxLength <= m_offsetWrite + dwLength)
		{
			_tprintf(_T("pool is overflow !!!\n"));
			return 0;
		}

		if (FALSE == ReadFile(m_hComDev, &m_ReadDataPool[m_offsetWrite], dwLength, &dwLength, &m_osRead))
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
		if (FALSE == WriteFile(m_hComDev, lpByte, dwBytesToWrite, 0, &m_osWrite))
		{
			//����Ʈ�� �����͸� ����� ����� ������ ����̴�. 
			//�� ���� ��� �ұ�. �װ��� ����� �����̴�. 
			//�ٽ� ������ ������ ��ͼ����� �ϸ� �ȴ�. 
			//�׷��� ���� ������ �� �� �ִٴ� ���� ��������. 
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
		//��� ��Ŷ�� ������ ũ�⸦ ������ ó����ƾ
		while (staticSize <= (m_offsetWrite - m_offsetRead))
		{
			OnReceiveData(&m_ReadDataPool[m_offsetRead], staticSize);
			m_offsetRead += staticSize;
		}
		//printf("offsetW=%d, offsetR=%d\n", m_offsetWrite, m_offsetRead);

		//��� �о����� offset �ʱ�ȭ.
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

					//�̰����� �����͸� �޴´�.
					//OnReceiveData(ReadDataPool, nLength);
					
					//��� ��Ŷ�� ������ ũ�⸦ ������ ������ ��ƾ�Դϴ�.
					//��Ŷ�ϳ��� ����(5byte)�Դϴ�.
					ReadStaticSize(PROTOCOL_LENGTH);
				}
			} while (nLength > 0);

		}//..while (m_fConnected)
		CloseHandle(os.hEvent);
	}

};//..namespace HisUtil {
