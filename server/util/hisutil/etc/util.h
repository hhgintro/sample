#pragma once 
#include <Psapi.h>


namespace HisUtil {


	//��ü�޸� ��뷮
		//typedef struct _MEMORYSTATUSEX {
		//	dwLength�� �ʱ� �Է� ��(����ü ũ��)
		//	dwMemoryLoad: �޸� ��뷮(%)
		//	ullTotalPhys: ���� �� ���� �޸� ũ��
		//	ullAvailPhys: ���� �޸� �߿� ��밡���� �޸�
		//	ullTotalPageFile: �� ������ ���� ũ��
		//	ullAvailPageFile: ��� ������ ������ ���� ũ��
		//	ullTotalVirtual: �� ���� �޸� ũ��
		//	ullAvailExtendedVirtual: Ȯ�� �޸� ũ��.
	/** ��뿹
		//��ü �޸� ��뷮 üũ
		MEMORYSTATUSEX memstatus;
		memstatus.dwLength = sizeof(memstatus);		
		GetGlobalMemoryUsage(&memstatus);
		//int memFull = memstatus.dwMemoryLoad;//(%)
	*/
	UINT64 GetGlobalMemoryUsage(MEMORYSTATUSEX& mem);

	//���μ��� �޸� ��뷮
		//typedef struct _PROCESS_MEMORY_COUNTERS {
		//	DWORD cb //����ü ũ��
		//	DWORD PageFaultCount; //������ ��Ʈ ����
		//	SIZE_T PeakWorkingSetSize; //�ִ� ��ŷ�� ũ��(byte)
		//	SIZE_T WorkingSetSize; //���� ��ŷ�� ũ��(byte)
		//	SIZE_T QuotaPeakPagedPoolUsage; //�ִ� ������ Ǯ ��뷮(byte)
		//	SIZE_T QuotaPagedPoolUsage; //���� ������ Ǯ ��뷮(byte)
		//	SIZE_T QuotaPeakNonPagedPoolUsage; //�ִ� �������� Ǯ ��뷮(byte)
		//	SIZE_T QuotaNonPagedPoolUsage; //���� �������� Ǯ ��뷮(byte)
		//	SIZE_T PagefileUsage; //�Ҵ�� �޸𸮷�(byte)
		//	SIZE_T PeakPagefileUsage; //�ִ� �Ҵ�� �޸𸮷�(byte)
	/** ��뿹
		//���μ��� �޸� ��뷮
		PROCESS_MEMORY_COUNTERS pmc;
		GetProcessMemoryUsage(pmc);
		//int memProcess = (int)(pmc.WorkingSetSize * 100 / memstatus.ullTotalPhys); //(%)
	*/
	//�ڽ��� ��� : process = GetCurrentProcess()
	//#include <Psapi.h>
	UINT64 GetProcessMemoryUsage(HANDLE process, PROCESS_MEMORY_COUNTERS& pmc);


	/** ��뿹
		���ǻ��� : application�� �����η� �����ϼ���
				/ command�� ��ó�� ���鹮�ڸ� �����ؾ� �մϴ�.
		CreateProcess(L"c:/windows/system32/shutdown.exe", L" /r /t 100");
		system("pause");
		system("shutdown /a");
		return 0;
	*/
	BOOL CreateProcess(TCHAR* application, TCHAR* command);


	////IP�߿��� �ϳ��� �����ɴϴ�.(public�� �켱���� �����ɴϴ�)
	//Proud::String GetLocalIPAddress();

	// %APPDATA% �� ������� ��ġ�� �����´�.
	// name : %�� �����ϼ���( %APPDATA% --> APPDATA )
	HisUtil::TString GetEvnPath(IN TCHAR* name);

	//subpath�� ������̸� path + subpath
	//subpath�� �������̸� subpath
	HisUtil::TString GetAppendPath(IN TCHAR* path, IN TCHAR* subpath);


	BOOL CheckRectCollision(float topA, float bottomA, float leftA, float rightA				//��ų ����
		, float topB, float bottomB, float leftB, float rightB);								//(object��) damage ����



	//���� Modify�ð��� �����ɴϴ�.
	TIME_T GetFileLastWriteTime(TCHAR* FullPath);



	////log�� url�� ������ ���� ����մϴ�.
	//void LogUrl(LPCTSTR url, int countrycode, int gameid, int gameversion, LPCTSTR servicename
	//	, int logid, int logdetailid, int market
	//	, LPCTSTR accountid, LPCTSTR nickname
	//	, char* keyword, const TCHAR* pFormat, ...);


	//std::string char2hex( char dec );
	//std::string urlencode(const std::string &c);


};//..namespace HisUtil {