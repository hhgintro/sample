#pragma once

//#include <windows.h>
//#include <string>

namespace HisUtil {

	BOOL LaunchService(LPCTSTR servicename);
	BOOL ShutdownService(LPCTSTR servicename);

	//TRUE 이면 서비스 실행중...
	BOOL ServiceStatus(LPCTSTR servicename);
		
	BOOL KillProcess(LPCTSTR servicename);

};//..namespace HisUtil {
