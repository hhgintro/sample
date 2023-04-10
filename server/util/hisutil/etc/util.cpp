#include "stdafx.h"
#include "util.h"
#include <math.h>

namespace HisUtil {


	//#include <Windows.h>
	//#pragma comment(lib, "winmm.lib")
	//��ü�޸� ��뷮
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
	//���μ��� �޸� ��뷮
	UINT64 GetProcessMemoryUsage(HANDLE process, PROCESS_MEMORY_COUNTERS& pmc)
	{
		//process : GetCurrentProcess()

		//PROCESS_MEMORY_COUNTERS pmc;
		if (!GetProcessMemoryInfo(process, &pmc, sizeof(pmc))) {
			return 0;
		}
		return (UINT64)pmc.WorkingSetSize;
	}



	//���ǻ��� : application�� �����η� �����ϼ��� / command�� ��ó�� ���鹮�ڸ� �����ؾ� �մϴ�.
	BOOL CreateProcess(TCHAR* application, TCHAR* command)
	{
		//��뿹
		//���ǻ��� : application�� �����η� �����ϼ��� / command�� ��ó�� ���鹮�ڸ� �����ؾ� �մϴ�.
		//CreateProcess(L"c:/windows/system32/shutdown.exe", L" /r /t 100");
		//system("pause");
		//system("shutdown /a");
		//return 0;

		STARTUPINFO si = { 0, };    //����ü ����, �ʱ�ȭ
		PROCESS_INFORMATION pi = { 0, };

		si.cb = sizeof(si);
		//si.dwFlags = STARTF_USEPOSITION | STARTF_USESIZE;
		////Flags ������ ���������� �ֽ��ϴ�.
		////STARTF_USEPOSITION :: dwX, dwY ��ġ ���
		////STARTF_USESIZE     :: dwXSize, dwYSize ���
		////Flags ���� �־����� �ʴ� si����ü ����
		////���� ��������� ���μ����� ������ ���� �ʽ��ϴ�.
		//si.dwX = 100;
		//si.dwY = 100;
		//si.dwXSize = 300;
		//si.dwYSize = 300;  //dw ~ �� ��� �� ������ �ʽ��ϴ�.

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
	//	//���ٸ�...
	//	if(output.GetCount() <= 0)
	//		return L"";

	//	//�Ѱ��� ���
	//	if(output.GetCount() <= 1)
	//		return Proud::StringA2W(output[0].GetString());

	//	//2�� �̻��� ���
	//	for(int i=0; i<output.GetCount(); ++i)
	//	{
	//		//192.168. ���� ���۵Ǵ� ��� private�� �Ǵ��Ѵ�.

	//		//-1 : �ش繮�ڿ��� ã�� ����(public���� �Ǵܵ�)
	//		if(-1 == output[i].Find("192.168."))
	//			return Proud::StringA2W(output[i].GetString());
	//	}

	//	//��� private���� �Ǵܵȴٸ�...ó�������� ����.
	//	return Proud::StringA2W(output[0].GetString());
	//}


	// %APPDATA% �� ������� ��ġ�� �����´�.
	// name : %�� �����ϼ���( %APPDATA% --> APPDATA )
	HisUtil::TString GetEvnPath(IN TCHAR* name)
	{
		TCHAR path[1024] = _T("");
		size_t requiredSize;
		_tgetenv_s(&requiredSize, NULL, 0, name);
		_tgetenv_s(&requiredSize, path, requiredSize, name);
		return path;
	}

	//subpath�� ������̸� path + subpath
	//subpath�� �������̸� subpath
	HisUtil::TString GetAppendPath(IN TCHAR* path, IN TCHAR* subpath)
	{
		if (NULL == subpath)	return HisUtil::TString();

		//subpath�� �������̸�...�׳� ����.
		if (NULL != _tcsstr(subpath, _T(":")))
			return HisUtil::TString(subpath);

		if (NULL == path)	return HisUtil::TString(subpath);

		HisUtil::TString fullpath(path);
		return fullpath.append(subpath);
	}


	BOOL CheckRectCollision(float topA, float bottomA, float leftA, float rightA				//��ų ����
		, float topB, float bottomB, float leftB, float rightB)									//(object��) damage ����
	{
		//RECT A : ��ų ����
		//RECT B : (object��) damage ����

		//B�� A���� ���ʿ� �ִ�.
		if(bottomB < topA)
			return FALSE;
		//B�� A���� �Ʒ��ʿ� �ִ�.
		if(bottomA < topB)
			return FALSE;
		//B�� A���� ���ʿ� �ִ�.
		if(rightB < leftA)
			return FALSE;
		//B�� A���� �����ʿ� �ִ�.
		if(rightA < leftB)
			return FALSE;

		return TRUE;
	}








	//������ ������
	TIME_T GetFileLastWriteTime(TCHAR* FullPath)
	{
		if(NULL == FullPath)
			return 0;

		struct _stat buf;
		_tstat(FullPath, &buf);
		return (TIME_T)buf.st_mtime;
	}




	////	url : log�� ���� url
	////	countrycode : �����ڵ�
	////	gameid : ����id
	////	gameversion : 
	////	servicename : GetServiceNameFromType()
	////	logid : ��з�
	////	logdetailid : �Һз�
	////	market : ����
	////	accountid : ����id
	////	nickname :
	////	keyword : log�ĺ�Ű
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
	//		//url ���۽� ó��.
	//		//1�ܰ�:�����ڵ� -> utf8 ��ȯ
	//		//2�ܰ�:utf8 -> encode

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

