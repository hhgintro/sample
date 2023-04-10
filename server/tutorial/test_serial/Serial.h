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


///����: https://blog.naver.com/hhgintro/221463761014
/**
��뿹��:
	�������
	class CSerialEx : public CSerial
	{
	public:
		CSerialEx() {}
		~CSerialEx() {}

		//����Ÿ�� ������ CALLBACK�ȴ�.
		virtual void OnReceiveData(BYTE* data);
	};
	�ҽ�����
	void CSerialEx::OnReceiveData(BYTE* data)
	{
		_tprintf(_T("data:[0x%x][0x%x][0x%x][0x%x][0x%x][0x%x][0x%x][0x%x]\n")
			, data[0], data[1], data[2], data[3], data[4], data[5], data[6], data[7]);
	}
	main�Լ�
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


	//comm ��Ʈ�� �����. 
	BOOL Create(int port, DWORD rate=CBR_115200, BYTE bytesize=8, BYTE stop=0, BYTE parity=0);
	//comm ��Ʈ�� �����Ѵ�. 
	BOOL Destroy();
	//����Ʈ�� ���� ������ �õ��Ѵ�.
	BOOL Open();
	//������ �����Ѵ�. 
	BOOL Close();

	//����Ʈ�� ������. 
	void Set(int port, DWORD rate = CBR_115200, BYTE bytesize = 8, BYTE stop = 0, BYTE parity = 0);

	//����Ʈ�� �����͸� �ִ´�. 
	BOOL Write(LPSTR, DWORD);

	//����Ÿ�� ������ CALLBACK�ȴ�.
	virtual void OnReceiveData(BYTE* data) = 0;

private:
	//��Ʈ�� �����Ѵ�. 
	BOOL Setup();
	//����Ʈ���� �����͸� �޴´�. 
	int Read(LPSTR, int);

	static unsigned int CALLBACK _Thread(void* lpParam);
	virtual void OnThread();


public:
	HANDLE idComDev;//����Ʈ ����̽� ���� �ڵ� 
	BOOL fConnected;//����Ʈ�� ����Ǹ� 1�� ���� 
	BYTE abIn[MAXBLOCK + 1];//����Ʈ���� ������ ������ 
	HWND m_hwnd;//�޽����� ������ ���� �÷��� 

public:
	BYTE bPort;
	BYTE bByteSize, bFlowCtrl, bParity, bStopBits;
	DWORD dwBaudRate;

	HANDLE hThread;
	OVERLAPPED osWrite, osRead;

};

