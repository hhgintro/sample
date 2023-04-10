#pragma once

namespace HisUtil
{

	//IP 변환
	//665405 --> "61.39.10.0"

	//사용예
	//char szAddr[16] = "";
	//printf("ip : %s\n", HisUtil::IP_nToa(ip, szAddr, sizeof(szAddr)));
	const char* IP_nToa(IN unsigned long ip, OUT char* buff, IN int size);

	//사용예
	//wchar_t wzAddr[16] = L"";
	//wprintf(L"ip : %s\n", HisUtil::IP_nTow(ip, wzAddr, sizeof(wzAddr)));
	const WCHAR* IP_nTow(IN unsigned long ip, OUT WCHAR* wzAddr, IN int size);



	//"61.39.10.0" --> 665405
	
	//사용예
	//printf("ip : 0x%x\n", HisUtil::IP_aTon("127.0.0.1"));
	DWORD IP_aTon(char* szAddr IN);
	DWORD IP_wTon(wchar_t* wzAddr IN);


};
