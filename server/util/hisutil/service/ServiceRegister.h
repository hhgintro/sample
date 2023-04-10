#pragma once

//#include <windows.h>
//#include <string>
#include <winsvc.h>	//SERVICE_STATUS_HANDLE

namespace HisUtil {

	/**
	* @class ServiceRegister
	* @brief ���α׷��� windows�� service�� ��� �� �ֱ� ���� �ʿ��� �ڵ带 ��Ƴ���, service�� ������ ���ϰ� ���� ĸ��ȭ�� Ŭ����
	* @author
	*/
	class CServiceRegister
	{

		// ServiceRegister���� ȣ���� ���α׷��� ���� main�Լ� Ÿ�� ����.
		typedef void(__cdecl *GAMELOOP)(void);

	public:
		CServiceRegister();
		~CServiceRegister();

		/// StartServiceCtrlDispatcher API�� ȣ���ϴ� �Լ��ν�, SCM���� ������ ���α׷��� ����ϴ� �۾�. ����� �����ϸ� ���� ServiceMain()�Լ��� ȣ���Ѵ�. (SCM�� ������ �ʰ� ���� �������� ��츦 ����)
		/**
		* @param[in]  GameMain  ���� ���α׷��� Main�Լ�
		*/
		void Run( /*const char* ServiceName, */GAMELOOP GameMain);

		/// ���񽺵�� / ������ �����մϴ�.
		/**
		* @param[in]  cmd  (��Ͻ� : -install, ������ : -uninstall )
		* @param[in]  servicename  ���/������ �����̸�
		* @return  : TRUE �̸� ����, FALSE �̸� ����
		*/
		BOOL Register(TCHAR* cmd, TCHAR* servicename);

		/// RegisterService()���� StartServiceCtrlDispatcher API�� ���� SCM�� ����� �ݹ��Լ�. StartServiceCtrlDispatcher�� �����ϸ� SCM�� �� �Լ��� ȣ���Ѵ�.
		/**
		* @param[in]  Argc  �Ϲ� main�Լ��� argument�� ������ ����
		* @param[in]  Argv  �Ϲ� main�Լ��� argument�� �迭�� ����
		*/
		static void __stdcall ServiceMain(DWORD Argc, TCHAR** Argv);

		/// SCM���� �ش� serivce���α׷��� ���� ����� ó���ϴ� �ڵ鷯
		/**
		* @param[in]  Code  ���� �ڵ�
		*/
		static void __stdcall CtrlHandler(DWORD Code);


	private:

		BOOL Install(LPCTSTR serviceName);
		BOOL Uninstall(LPCTSTR serviceName);


	protected:
		static GAMELOOP m_GameMain;
		static SERVICE_STATUS_HANDLE m_ssh;
		static bool m_bRunedServiceMain;

	};

};//..namespace HisUtil {
