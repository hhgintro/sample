#pragma once

//#include <windows.h>
//#include <string>

namespace HisUtil {

	BOOL LaunchService(LPCTSTR servicename);
	BOOL ShutdownService(LPCTSTR servicename);

	//TRUE �̸� ���� ������...
	BOOL ServiceStatus(LPCTSTR servicename);
		
	BOOL KillProcess(LPCTSTR servicename);

};//..namespace HisUtil {
