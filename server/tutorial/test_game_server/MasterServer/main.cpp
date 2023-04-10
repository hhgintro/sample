// MasterServer.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"

void Launch()
{
	DWORD result = CWorld::Instance().OnStart();
	if (SERVER_OK != result)
	{
		_tprintf(_T("error : 0x%x\n"), result);
		_tsystem(_T("pause"));
		return;
	}

	TCHAR buf[10] = _T("");
	while (1) {
		//_fputts(_T("메시지를 입력하세요(q to quit) : \n"), stdout);
		_tprintf(_T("메시지를 입력하세요(q to quit) : \n"));
		_fgetts(buf, sizeof(buf), stdin);

		if (!_tcscmp(buf, _T("q\n")))
			break;

	}//..while (1) {

	//CWorld::Destroy();
}

int _tmain(int argc, _TCHAR* argv[])
{
	//system("pause");
	//return 0;

	_tsetlocale(LC_ALL, _T("korean"));

	HisUtil::CModule& module = CWorld::Instance().GetModule();
	HisUtil::CCrashHandler dump(module.GetPathName(), module.GetAppName());
	SetConsoleTitle(module.GetAppName());

	HisUtil::CServiceRegister service;
	if (2 == argc)
	{
		if (TRUE == service.Register(argv[1], module.GetAppName()))		_tprintf_s(_T("success %s(fileName:%s)\n"), argv[1], module.GetAppName());
		else															_tprintf_s(_T("fail %s(fileName:%s)\n"), argv[1], module.GetAppName());
		return 0;
	}

	service.Run(Launch);
	
	
	//CWorld::Destroy();

	return 0;
}
