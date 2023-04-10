#pragma once

#include <windows.h>


#define MAX_READ_DATA_POOL		1024	//read buff �ִ�ũ��
#define MAXPORTS				4
#define MAX_IO_QUEUE			4096
#define PROTOCOL_LENGTH			5		//��Ŷ�ϳ��� ����(5byte)�Դϴ�.

// ascii definitions 
#define ASCII_BEL				0x07 
#define ASCII_BS				0x08 
#define ASCII_LF				0x0A 
#define ASCII_CR				0x0D 
#define ASCII_XON				0x11 
#define ASCII_XOFF				0x13 


///����: https://blog.naver.com/hhgintro/221463761014
/**
��뿹��:
	<�������>
	class CSerialEx : public HisUtil::CSerial
	{
	public:
		CSerialEx() {}
		~CSerialEx() {}

		//����Ÿ�� ������ CALLBACK�ȴ�.
		virtual void OnReceiveData(BYTE* data);
	};
	<�ҽ�����>
	void CSerialEx::OnReceiveData(BYTE* data)
	{
		_tprintf(_T("data:[0x%x][0x%x][0x%x][0x%x][0x%x][0x%x][0x%x][0x%x]\n")
			, data[0], data[1], data[2], data[3], data[4], data[5], data[6], data[7]);
	}
	<main�Լ�>
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

namespace HisUtil {

	class CSerial
	{
	public:
		CSerial();
		virtual ~CSerial();


		//comm ��Ʈ�� �����. 
		BOOL Create(int port, DWORD rate = CBR_115200, BYTE bytesize = 8, BYTE stop = 0, BYTE parity = 0);
		//comm ��Ʈ�� �����Ѵ�. 
		BOOL Destroy();
		//����Ʈ�� ���� ������ �õ��Ѵ�.
		BOOL Open();
		//������ �����Ѵ�. 
		BOOL Close();
		//�ʱ�ȭ: ��Ʈ�� ���� �� �ʱ�ȭ�� �������� �����
		void Clear();

		//����Ʈ�� ������. 
		void Set(int port, DWORD rate = CBR_115200, BYTE bytesize = 8, BYTE stop = 0, BYTE parity = 0);

		//����Ʈ�� �����͸� �ִ´�. 
		BOOL Write(LPSTR, DWORD);

		//����Ÿ�� ������ CALLBACK�ȴ�.
		virtual void OnReceiveData(BYTE* data, int length) = 0;
		
	private:
		//��Ʈ�� �����Ѵ�. 
		BOOL Setup();
		//����Ʈ���� �����͸� �޴´�. 
		int Read(int nMaxLength);
	
		//��� ��Ŷ�� ������ ũ�⸦ ������ ó����ƾ
		void ReadStaticSize(int staticSize);

		static unsigned int CALLBACK _Thread(void* lpParam);
		virtual void OnThread();


	private:
		HANDLE m_hComDev;//����Ʈ ����̽� ���� �ڵ� 
		BOOL m_fConnected;//����Ʈ�� ����Ǹ� 1�� ���� 
		//HWND m_hwnd;//�޽����� ������ ���� �÷��� 

		BYTE m_Port;
		BYTE m_bByteSize, m_bFlowCtrl, m_bParity, m_bStopBits;
		DWORD m_dwBaudRate;

		HANDLE m_hThread;
		OVERLAPPED m_osWrite, m_osRead;


		BYTE m_ReadDataPool[MAX_READ_DATA_POOL];	//read�� data�� �����մϴ�.
		int m_offsetRead;	//����� ����Ÿ offset
		int m_offsetWrite;	//��������Ÿ offset

	};

};//..namespace HisUtil {
