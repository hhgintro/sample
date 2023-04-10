// MasterServer.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"

void Callback_OnIoRecvUdpPacket(void* owner, ADDR_IP remoteIP, ADDR_PORT remotePort, HisUtil::CMsg& msgRecv)
{
	//LOGEVENT("HG_WHITE", _T("received: main()"));

}

void Launch()
{
	DWORD result = CWorld::Instance().OnStart();
	if (SERVER_OK != result)
	{
		_tprintf(_T("error : 0x%x\n"), result);
		_tsystem(_T("pause"));
		return;
	}

	CWorld::Instance().GetServer().AddExtraUdp(htons(8888), 100, 100, &CWorld::Instance().GetServer(), &Callback_OnIoRecvUdpPacket);//+1))

	TCHAR buf[10] = _T("");
	while (1) {
		//_fputts(_T("메시지를 입력하세요(q to quit) : \n"), stdout);
		_tprintf(_T("메시지를 입력하세요(q to quit) : \n"));
		_fgetts(buf, sizeof(buf), stdin);

		if (!_tcscmp(buf, _T("q\n")))
			break;

		//*********************************************************************
		//Enter만 누르면 추가로 오픈된 UDP서버로 임의의 데이타를 보내는 테스트 로직임
		ADDR_IP ip = HisUtil::IP_wTon(L"127.0.0.1");

		HisUtil::CMsg msgSend;
		msgSend.SetContext(NetCore::RELIABLE);
		msgSend.ID(NetC2C_CORE_UDP_HOLE_PUNCHING_PEER_REQ)
			<< (byte)0xf1
			<< (byte)0xf2
			<< (byte)0xf3
			<< (byte)0xf4
			;

		CWorld::Instance().GetServer().SendExtraUdp(htons(8888), msgSend, ip, htons(9999));
		CWorld::Instance().GetServer().SendExtraUdp(htons(8888), msgSend, ip, htons(8888));
		msgSend.Clear();
		//*********************************************************************


	}//..while (1) {

	//CWorld::Destroy();
}

int _tmain(int argc, _TCHAR* argv[])
{
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
