#include "stdafx.h"
#include "util.h"
#include <math.h>

namespace HisUtil {


	//#include <Windows.h>
	//#pragma comment(lib, "winmm.lib")
	//전체메모리 사용량
	UINT64 GetGlobalMemoryUsage(MEMORYSTATUSEX& mem)
	{
		//MEMORYSTATUSEX mem;
		mem.dwLength = sizeof(MEMORYSTATUSEX);
		if (0==GlobalMemoryStatusEx(&mem)) {
			return 0;
		}
		return (UINT64)mem.ullAvailPhys;
	}

	//#include <Psapi.h>
	#pragma comment(lib, "psapi.lib")
	//프로세스 메모리 사용량
	UINT64 GetProcessMemoryUsage(HANDLE process, PROCESS_MEMORY_COUNTERS& pmc)
	{
		//process : GetCurrentProcess()

		//PROCESS_MEMORY_COUNTERS pmc;
		if (!GetProcessMemoryInfo(process, &pmc, sizeof(pmc))) {
			return 0;
		}
		return (UINT64)pmc.WorkingSetSize;
	}



	//주의사항 : application은 절대경로로 설정하세요 / command는 맨처음 공백문자를 포함해야 합니다.
	BOOL CreateProcess(TCHAR* application, TCHAR* command)
	{
		//사용예
		//주의사항 : application은 절대경로로 설정하세요 / command는 맨처음 공백문자를 포함해야 합니다.
		//CreateProcess(L"c:/windows/system32/shutdown.exe", L" /r /t 100");
		//system("pause");
		//system("shutdown /a");
		//return 0;

		STARTUPINFO si = { 0, };    //구조체 선언, 초기화
		PROCESS_INFORMATION pi = { 0, };

		si.cb = sizeof(si);
		//si.dwFlags = STARTF_USEPOSITION | STARTF_USESIZE;
		////Flags 값들이 여러가지가 있습니다.
		////STARTF_USEPOSITION :: dwX, dwY 위치 사용
		////STARTF_USESIZE     :: dwXSize, dwYSize 사용
		////Flags 값이 주어지지 않는 si구조체 값은
		////새로 만들어지는 프로세스에 영향을 주지 않습니다.
		//si.dwX = 100;
		//si.dwY = 100;
		//si.dwXSize = 300;
		//si.dwYSize = 300;  //dw ~ 는 사실 잘 쓰이지 않습니다.

		//si.lpTitle = _T(" Child process! ");
		//TCHAR command[] = _T("CMD /C net stop \"DtGmAgent\" & timeout 10 & net start \"DtGmAgent\"");

		//If the function succeeds, the return value is nonzero.
		BOOL state = ::CreateProcess(
			application,		// No module name (use command line)
			command,			// Command line
			NULL,				// Process handle not inheritable
			NULL,				// Thread handle not inheritable
			FALSE,				// Set handle inheritance to FALSE
			0,					// No creation flags
			NULL,				// Use parent's environment block
			NULL,				// Use parent's starting directory 
			&si,				// Pointer to STARTUPINFO structure
			&pi					// Pointer to PROCESS_INFORMATION structure
		);

		//// Wait until child process exits.
		//WaitForSingleObject(pi.hProcess, INFINITE);

		//// Close process and thread handles. 
		//CloseHandle(pi.hProcess);
		//CloseHandle(pi.hThread);

		//if(state!=0){
		//	//NOTIFY_SYSTEM_LOG("HG_WHITE", _T("Creation OK!"));
		//}
		//else{
		//	NOTIFY_SYSTEM_LOG("HG_WHITE", _T("Creation Fail!"));
		//}

		//If the function fails, the return value is zero.
		// To get extended error information, call GetLastError.
		return state;
	}


	//Proud::String GetLocalIPAddress()
	//{
	//	//Proud::NamedAddrPort addr = Proud::NamedAddrPort::From(Proud::AddrPort::GetOneLocalAddress());
	//	//m_serverinfo.m_ip = Proud::StringA2W(addr.m_addr);

	//	Proud::CFastArray<Proud::StringA> output;
	//	Proud::CNetUtil::GetLocalIPAddresses(output);
	//
	//	//없다면...
	//	if(output.GetCount() <= 0)
	//		return L"";

	//	//한개인 경우
	//	if(output.GetCount() <= 1)
	//		return Proud::StringA2W(output[0].GetString());

	//	//2개 이상인 경우
	//	for(int i=0; i<output.GetCount(); ++i)
	//	{
	//		//192.168. 으로 시작되는 경우 private로 판단한다.

	//		//-1 : 해당문자열을 찾지 못함(public으로 판단됨)
	//		if(-1 == output[i].Find("192.168."))
	//			return Proud::StringA2W(output[i].GetString());
	//	}

	//	//모두 private으로 판단된다면...처음것으로 리턴.
	//	return Proud::StringA2W(output[0].GetString());
	//}


	// %APPDATA% 의 실제경로 위치를 가져온다.
	// name : %를 제거하세요( %APPDATA% --> APPDATA )
	HisUtil::TString GetEvnPath(IN TCHAR* name)
	{
		TCHAR path[1024] = _T("");
		size_t requiredSize;
		_tgetenv_s(&requiredSize, NULL, 0, name);
		_tgetenv_s(&requiredSize, path, requiredSize, name);
		return path;
	}

	//subpath가 상대경로이면 path + subpath
	//subpath가 절대경로이면 subpath
	HisUtil::TString GetAppendPath(IN TCHAR* path, IN TCHAR* subpath)
	{
		if (NULL == subpath)	return HisUtil::TString();

		//subpath가 절대경로이면...그냥 리턴.
		if (NULL != _tcsstr(subpath, _T(":")))
			return HisUtil::TString(subpath);

		if (NULL == path)	return HisUtil::TString(subpath);

		HisUtil::TString fullpath(path);
		return fullpath.append(subpath);
	}


	BOOL CheckRectCollision(float topA, float bottomA, float leftA, float rightA				//스킬 영역
		, float topB, float bottomB, float leftB, float rightB)									//(object의) damage 영역
	{
		//RECT A : 스킬 영역
		//RECT B : (object의) damage 영역

		//B가 A보다 위쪽에 있다.
		if(bottomB < topA)
			return FALSE;
		//B가 A보다 아래쪽에 있다.
		if(bottomA < topB)
			return FALSE;
		//B가 A보다 왼쪽에 있다.
		if(rightB < leftA)
			return FALSE;
		//B가 A보다 오른쪽에 있다.
		if(rightA < leftB)
			return FALSE;

		return TRUE;
	}








	//파일의 수정일
	TIME_T GetFileLastWriteTime(TCHAR* FullPath)
	{
		if(NULL == FullPath)
			return 0;

		struct _stat buf;
		_tstat(FullPath, &buf);
		return (TIME_T)buf.st_mtime;
	}




	////	url : log를 던질 url
	////	countrycode : 국가코드
	////	gameid : 게임id
	////	gameversion : 
	////	servicename : GetServiceNameFromType()
	////	logid : 대분류
	////	logdetailid : 소분류
	////	market : 마켓
	////	accountid : 계정id
	////	nickname :
	////	keyword : log식별키
	////	pFormat : 
	//void LogUrl(LPCTSTR url, int countrycode, int gameid, int gameversion, LPCTSTR servicename
	//	, int logid, int logdetailid, int market
	//	, LPCTSTR accountid, LPCTSTR nickname
	//	, char* keyword, const TCHAR* pFormat, ...)
	//{
	//	if(TRUE == IsBadReadPtr(url, sizeof(LPCTSTR)))
	//		return;

	//	TCHAR szLog[MAX_LOG_SIZE] = _T("");

	//	va_list	pArg;
	//	va_start(pArg, pFormat);
	//	_vstprintf_s(szLog, MAX_LOG_SIZE, pFormat, pArg);
	//	va_end(pArg);

	//	//url
	//	if(0 < _tcslen(url))
	//	{
	//		//url 전송시 처리.
	//		//1단계:유니코드 -> utf8 변환
	//		//2단계:utf8 -> encode

	//		
	//		std::string encode_nick = urlencode(CT2U8(nickname).GetUTF8());
	//		std::string encode_log = urlencode(CT2U8(szLog).GetUTF8());

	//		Proud::String urlmsg;
	//		urlmsg.Format(_T("%s?nid=%d&gid=%d&gver=%d&tel=%d&bc=%d&sc=%d&uidx=%s&sname=%s&nickname=%s&param=%s")
	//			, url, countrycode, gameid, gameversion
	//			, market, logid, logdetailid
	//			, accountid, servicename
	//			, Proud::StringA2W(encode_nick.c_str()).GetString()
	//			, Proud::StringA2W(encode_log.c_str()).GetString());

	//		//send...
	//		HisUtil::CHttpService http;
	//		http.OpenGet(urlmsg.GetString());

	//	}

	//	//etc
	//	LOGEVENT(keyword, szLog);
	//}




	//std::string char2hex( char dec )
	//{
	//	char dig1 = (dec&0xF0)>>4;
	//	char dig2 = (dec&0x0F);
	//	if ( 0<= dig1 && dig1<= 9) dig1+=48;    //0,48inascii
	//	if (10<= dig1 && dig1<=15) dig1+=97-10; //a,97inascii
	//	if ( 0<= dig2 && dig2<= 9) dig2+=48;
	//	if (10<= dig2 && dig2<=15) dig2+=97-10;

	//	string r;
	//	r.append( &dig1, 1);
	//	r.append( &dig2, 1);
	//	return r;
	//}

	//std::string urlencode(const std::string &c)
	//{

	//	std::string escaped="";
	//	int max = (int)c.length();
	//	for(int i=0; i<max; i++)
	//	{
	//		if ( (48 <= c[i] && c[i] <= 57) ||//0-9
	//			(65 <= c[i] && c[i] <= 90) ||//abc...xyz
	//			(97 <= c[i] && c[i] <= 122) || //ABC...XYZ
	//			(c[i]=='~' || c[i]=='!' || c[i]=='*' || c[i]=='(' || c[i]==')' || c[i]=='\'')
	//			)
	//		{
	//			escaped.append( &c[i], 1);
	//		}
	//		else
	//		{
	//			escaped.append("%");
	//			escaped.append( char2hex(c[i]) );//converts char 255 to string "ff"
	//		}
	//	}
	//	return escaped;
	//}


};//..namespace HisUtil {

