// MasterServer.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "stdafx.h"

void Launch()
{

}
#include <windows.h>

int _tmain(int argc, _TCHAR* argv[])
{
	//CPacketBuffer::Begin()�� 
	//if (nTotalSize_ < MSG_TOTAL_SIZE)	nTotalSize_ = MSG_TOTAL_SIZE;
	//�� ������ �ּ�ó���Ŀ� �׽�Ʈ�ϼ���
	const int total_size = 10;//header ������� 8�Դϴ�.

	HisUtil::CPacketBuffer buffer;
	buffer.Begin(total_size);

	char tmp[total_size] = "";

	//push test ===========================================
	/*
	//�Է��� ����Ÿ �ߺ�
	for (int i = 0; i < total_size; ++i)
	{
		tmp[i] = (i % 10) + 97;
	}


	//�ʹ� ū ����Ÿ
	//buffer.Push(tmp, sizeof(tmp)+1);

	//�� �� ����Ÿ
	//buffer.Push(tmp, sizeof(tmp));
	//buffer.Push(tmp, 1);

	////��ġ�� ����Ÿ
	//buffer.Push(tmp, sizeof(tmp)-1);
	//buffer.nReadOffset_ = 2;//���� �ְ� ����Ȯ��
	//buffer.Push(tmp+2, 2);

	//����Ÿ ����
	buffer.nWriteOffset_ = 2;//����� ��ġ ����Ȯ��
	buffer.nReadOffset_ = 10;//�о�� ��ġ ����Ȯ��
	buffer.Push(tmp + 2, 2);//���� ����Ÿ
	buffer.Push(tmp + 2, 5);//7 = 2 + 5
	buffer.Push(tmp + 2, 1);//8 = 2 + 5 + 1
	*/

	//pop test ===========================================
	//buffer.Push(tmp, sizeof(tmp)-1);
	//����Ÿ �ߺ�
	for (int i = 0; i < total_size; ++i)
	{
		*(buffer.m_pBuffer + i) = (i % 10) + 97;
	}

	//buffer.nWriteOffset_ = total_size - 1;//����� ��ġ ����Ȯ��
	//buffer.nReadOffset_ = 0;//�о�� ��ġ ����Ȯ��
	//buffer.Pop(tmp, total_size-1);

	buffer.nWriteOffset_ = 5;//����� ��ġ ����Ȯ��
	buffer.nReadOffset_ = 7;//�о�� ��ġ ����Ȯ��
	buffer.Pop(tmp, 3);

	system("pause");
	return 0;

}
