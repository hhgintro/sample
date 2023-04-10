#pragma once

//#include <windows.h>
//#include <string>
#include <winsvc.h>	//SERVICE_STATUS_HANDLE

namespace HisUtil {

	/**
	* @class ServiceRegister
	* @brief 프로그램을 windows에 service로 띄울 수 있기 위해 필요한 코드를 모아놓고, service로 실행이 편하게 내부 캡슐화한 클래스
	* @author
	*/
	class CServiceRegister
	{

		// ServiceRegister에서 호출할 프로그램의 실제 main함수 타입 선언.
		typedef void(__cdecl *GAMELOOP)(void);

	public:
		CServiceRegister();
		~CServiceRegister();

		/// StartServiceCtrlDispatcher API를 호출하는 함수로써, SCM에게 실제로 프로그램을 등록하는 작업. 등록이 실패하면 직접 ServiceMain()함수를 호출한다. (SCM을 통하지 않고 직접 실행했을 경우를 위해)
		/**
		* @param[in]  GameMain  실제 프로그램의 Main함수
		*/
		void Run( /*const char* ServiceName, */GAMELOOP GameMain);

		/// 서비스등록 / 삭제를 진행합니다.
		/**
		* @param[in]  cmd  (등록시 : -install, 삭제시 : -uninstall )
		* @param[in]  servicename  등록/삭제할 서비스이름
		* @return  : TRUE 이면 성공, FALSE 이면 실패
		*/
		BOOL Register(TCHAR* cmd, TCHAR* servicename);

		/// RegisterService()에서 StartServiceCtrlDispatcher API를 통해 SCM에 등록한 콜백함수. StartServiceCtrlDispatcher이 성공하면 SCM이 이 함수를 호출한다.
		/**
		* @param[in]  Argc  일반 main함수의 argument의 갯수와 동일
		* @param[in]  Argv  일반 main함수의 argument의 배열과 동일
		*/
		static void __stdcall ServiceMain(DWORD Argc, TCHAR** Argv);

		/// SCM에서 해당 serivce프로그램에 대한 명령을 처리하는 핸들러
		/**
		* @param[in]  Code  제어 코드
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
