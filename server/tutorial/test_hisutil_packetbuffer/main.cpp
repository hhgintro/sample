// MasterServer.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"

void Launch()
{

}
#include <windows.h>

int _tmain(int argc, _TCHAR* argv[])
{
	//CPacketBuffer::Begin()내 
	//if (nTotalSize_ < MSG_TOTAL_SIZE)	nTotalSize_ = MSG_TOTAL_SIZE;
	//위 구문을 주석처리후에 테스트하세요
	const int total_size = 10;//header 사이즈는 8입니다.

	HisUtil::CPacketBuffer buffer;
	buffer.Begin(total_size);

	char tmp[total_size] = "";

	//push test ===========================================
	/*
	//입력할 데이타 견본
	for (int i = 0; i < total_size; ++i)
	{
		tmp[i] = (i % 10) + 97;
	}


	//너무 큰 데이타
	//buffer.Push(tmp, sizeof(tmp)+1);

	//꽉 찬 데이타
	//buffer.Push(tmp, sizeof(tmp));
	//buffer.Push(tmp, 1);

	////넘치는 데이타
	//buffer.Push(tmp, sizeof(tmp)-1);
	//buffer.nReadOffset_ = 2;//들어갈수 있게 공간확보
	//buffer.Push(tmp+2, 2);

	//데이타 역전
	buffer.nWriteOffset_ = 2;//기록할 위치 공간확보
	buffer.nReadOffset_ = 10;//읽어올 위치 공간확보
	buffer.Push(tmp + 2, 2);//작은 데이타
	buffer.Push(tmp + 2, 5);//7 = 2 + 5
	buffer.Push(tmp + 2, 1);//8 = 2 + 5 + 1
	*/

	//pop test ===========================================
	//buffer.Push(tmp, sizeof(tmp)-1);
	//데이타 견본
	for (int i = 0; i < total_size; ++i)
	{
		*(buffer.m_pBuffer + i) = (i % 10) + 97;
	}

	//buffer.nWriteOffset_ = total_size - 1;//기록할 위치 공간확보
	//buffer.nReadOffset_ = 0;//읽어올 위치 공간확보
	//buffer.Pop(tmp, total_size-1);

	buffer.nWriteOffset_ = 5;//기록할 위치 공간확보
	buffer.nReadOffset_ = 7;//읽어올 위치 공간확보
	buffer.Pop(tmp, 3);

	system("pause");
	return 0;

}
