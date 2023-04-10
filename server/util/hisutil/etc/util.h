#pragma once 
#include <Psapi.h>


namespace HisUtil {


	//전체메모리 사용량
		//typedef struct _MEMORYSTATUSEX {
		//	dwLength은 초기 입력 값(구조체 크기)
		//	dwMemoryLoad: 메모리 사용량(%)
		//	ullTotalPhys: 실제 총 물리 메모리 크기
		//	ullAvailPhys: 물리 메모리 중에 사용가능한 메모리
		//	ullTotalPageFile: 총 페이지 파일 크기
		//	ullAvailPageFile: 사용 가능한 페이지 파일 크기
		//	ullTotalVirtual: 총 가상 메모리 크기
		//	ullAvailExtendedVirtual: 확장 메모리 크기.
	/** 사용예
		//전체 메모리 사용량 체크
		MEMORYSTATUSEX memstatus;
		memstatus.dwLength = sizeof(memstatus);		
		GetGlobalMemoryUsage(&memstatus);
		//int memFull = memstatus.dwMemoryLoad;//(%)
	*/
	UINT64 GetGlobalMemoryUsage(MEMORYSTATUSEX& mem);

	//프로세스 메모리 사용량
		//typedef struct _PROCESS_MEMORY_COUNTERS {
		//	DWORD cb //구조체 크기
		//	DWORD PageFaultCount; //페이지 폴트 개수
		//	SIZE_T PeakWorkingSetSize; //최대 워킹셋 크기(byte)
		//	SIZE_T WorkingSetSize; //현재 워킹셋 크기(byte)
		//	SIZE_T QuotaPeakPagedPoolUsage; //최대 페이지 풀 사용량(byte)
		//	SIZE_T QuotaPagedPoolUsage; //현재 페이지 풀 사용량(byte)
		//	SIZE_T QuotaPeakNonPagedPoolUsage; //최대 넌페이지 풀 사용량(byte)
		//	SIZE_T QuotaNonPagedPoolUsage; //현재 넌페이즈 풀 사용량(byte)
		//	SIZE_T PagefileUsage; //할당된 메모리량(byte)
		//	SIZE_T PeakPagefileUsage; //최대 할당된 메모리량(byte)
	/** 사용예
		//프로세스 메모리 사용량
		PROCESS_MEMORY_COUNTERS pmc;
		GetProcessMemoryUsage(pmc);
		//int memProcess = (int)(pmc.WorkingSetSize * 100 / memstatus.ullTotalPhys); //(%)
	*/
	//자신인 경우 : process = GetCurrentProcess()
	//#include <Psapi.h>
	UINT64 GetProcessMemoryUsage(HANDLE process, PROCESS_MEMORY_COUNTERS& pmc);


	/** 사용예
		주의사항 : application은 절대경로로 설정하세요
				/ command는 맨처음 공백문자를 포함해야 합니다.
		CreateProcess(L"c:/windows/system32/shutdown.exe", L" /r /t 100");
		system("pause");
		system("shutdown /a");
		return 0;
	*/
	BOOL CreateProcess(TCHAR* application, TCHAR* command);


	////IP중에서 하나를 가져옵니다.(public을 우선으로 가져옵니다)
	//Proud::String GetLocalIPAddress();

	// %APPDATA% 의 실제경로 위치를 가져온다.
	// name : %를 제거하세요( %APPDATA% --> APPDATA )
	HisUtil::TString GetEvnPath(IN TCHAR* name);

	//subpath가 상대경로이면 path + subpath
	//subpath가 절대경로이면 subpath
	HisUtil::TString GetAppendPath(IN TCHAR* path, IN TCHAR* subpath);


	BOOL CheckRectCollision(float topA, float bottomA, float leftA, float rightA				//스킬 영역
		, float topB, float bottomB, float leftB, float rightB);								//(object의) damage 영역



	//파일 Modify시간을 가져옵니다.
	TIME_T GetFileLastWriteTime(TCHAR* FullPath);



	////log를 url로 던지기 위해 사용합니다.
	//void LogUrl(LPCTSTR url, int countrycode, int gameid, int gameversion, LPCTSTR servicename
	//	, int logid, int logdetailid, int market
	//	, LPCTSTR accountid, LPCTSTR nickname
	//	, char* keyword, const TCHAR* pFormat, ...);


	//std::string char2hex( char dec );
	//std::string urlencode(const std::string &c);


};//..namespace HisUtil {