#include "stdafx.h"
#include "net.h"

#include <ws2tcpip.h>	//inet_ntop

namespace HisUtil
{
	//IP 변환
	//665405 --> "61.39.10.0"
	const char* IP_nToa(IN unsigned long ip, OUT char* buff, IN int size)
	{
		inet_ntop(AF_INET, (void*)&ip, buff, size);
		return buff;
	}

	//665405 --> "61.39.10.0"
	const WCHAR* IP_nTow(IN unsigned long ip, OUT WCHAR* wzAddr, IN int size)
	{
		//WCHAR wzAddr[16]//16이상 배열 확보할것
		char szAddr[16] = "";
		CA2W(CP_ACP, IP_nToa(ip, szAddr, sizeof(szAddr)), wzAddr, size);
		return wzAddr;
	}

	//"61.39.10.0" --> 665405
	DWORD IP_aTon(char* szAddr IN)
	{
		DWORD ip = 0;

		//returns 1 on success
		int result = inet_pton(AF_INET, szAddr, (void*)&ip);
		return ip;
	}

	//"61.39.10.0" --> 665405
	DWORD IP_wTon(wchar_t* wzAddr IN)
	{
		char szAddr[256] = "";
		return IP_aTon(HisUtil::CW2A(CP_ACP, wzAddr, szAddr, sizeof(szAddr)));
	}

};
