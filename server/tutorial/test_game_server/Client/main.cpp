// Client.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"

//char* ip = "127.0.0.1";
//WORD portTcp = 5601;
//WORD portUdp = portTcp;
int const MAX_CLIENT = 1;


//extern GAMEOBJECTID g_objectindex;
BOOL g_bIsMove = TRUE;

void MenuPrint()
{
	_tprintf(_T("===========================================\n"));
	_tprintf(_T("    menu\n"));
	//_tprintf(_T("    %d. login\n"), X2B_AC_LOGIN_REQ);
	//_tprintf(_T("    %d. game certify\n"), X2G_AC_CERTIFY_REQ);
	//_tprintf(_T("    %d. load char\n"), X2G_CH_LOAD_ALL_CHAR_REQ);
	//_tprintf(_T("    %d. create char\n"), X2G_CH_CREATE_CHAR_REQ);
	//_tprintf(_T("    %d. delete char\n"), X2G_CH_DELETE_CHAR_REQ);

	//_tprintf(_T("    %d. world enter\n"), X2G_WD_WORLD_ENTER_REQ);
	//_tprintf(_T("    %d. world leave\n"), X2G_WD_WORLD_LEAVE_REQ);
	//_tprintf(_T("    %d. world move\n"), X2G_WD_MOVE_REQ);

	//_tprintf(_T("    %d. chat\n"), X2G_BD_CHAT_REQ);

	_tprintf(_T("===========================================\n"));
}

int _tmain(int argc, _TCHAR* argv[])
{
#ifdef _DEBUG
	//오류 블럭 확인할때
	//_CrtSetBreakAlloc(876);
#endif

	{
		////random 시간 설정
		//srand(timeGetTime());

		////Mini dump
		//ExceptionReport	except;
		//LOGEVENT("HG_WHITE", _T("MiniDump System Begin"));

		CClientWorld* mainclientworld = NULL;

		HisUtil::CMemoryPool<int,CClientWorld> clientpool;
		clientpool.Begin(MAX_CLIENT);
		for(int i=0; i<MAX_CLIENT; ++i)
		{
			CClientWorld* clientworld = clientpool.Create();
			if(NULL == clientworld)
			{
				LOGEVENT("HG_RED", _T("Client world invalid"));
				::system("pause");//로그가 기록되기 위한 시간
				return 0;
			}

			if(NULL == mainclientworld)
				mainclientworld = clientworld;//main client 설정

			clientpool.Insert((int)clientworld, clientworld);
			DWORD dwResult = clientworld->OnStart();
			if (dwResult)
			{
				LOGEVENT("HG_RED", _T("Client Stop 0x%08x"), dwResult);
				//Sleep(1000);//로그가 기록되기 위한 시간
				::system("pause");//로그가 기록되기 위한 시간
				return 0;
			}

		}

		if(NULL == mainclientworld)
		{
			LOGEVENT("HG_RED", _T("main Client world invalid"));
			::system("pause");//로그가 기록되기 위한 시간
			return 0;
		}

		//DWORD dwResult = clientworld.OnStart();
		//if (dwResult)
		//{
		//	LOGEVENT("HG_GRAY", _T("Client Stop 0x%08x"), dwResult);
		//	//Sleep(1000);//로그가 기록되기 위한 시간
		//	::system("pause");//로그가 기록되기 위한 시간
		//	return 0;
		//}
		//else
		{
			MenuPrint();

			// 한개의 명령어씩 계속 처리하기 위한 while문입니다.
			TCHAR buf[HisUtil::MSG_TOTAL_SIZE] = _T("");
			while (TRUE)
			{
				Sleep(1);

				_fputts(_T("전송할 메시지를 입력하세요(q to quit) : \n"), stdout);
				_fgetts(buf, HisUtil::MSG_TOTAL_SIZE, stdin);

				if(!_tcscmp(buf, _T("q\n")))
					break;

				if(!_tcscmp(buf, _T("create\n")))
				{
					CClientWorld* clientworld = clientpool.Create();
					clientpool.Insert((int)clientworld, clientworld);
					DWORD dwResult = clientworld->OnStart();
					if (dwResult)
					{
						LOGEVENT("HG_RED", _T("Client Stop 0x%08x"), dwResult);
						//Sleep(1000);//로그가 기록되기 위한 시간
						::system("pause");//로그가 기록되기 위한 시간
						return 0;
					}
					continue;
				}

				if(!_tcscmp(buf, _T("move\n")))
				{
					g_bIsMove = TRUE;
					continue;
				}

				if(!_tcscmp(buf, _T("not move\n")))
				{
					g_bIsMove = FALSE;
					continue;
				}

				if(!_tcscmp(buf, _T("disconnect\n")))
				{
					std::vector<CClientWorld*> vecAll;
					clientpool.GetAllList(vecAll);
					for(int i=0; i<(int)vecAll.size(); ++i)
					{
						CClientWorld* clientworld = vecAll[i];
						if(NULL == clientworld)
							continue;

						clientworld->OnStop();
					}
					clientpool.End();

					continue;
				}

				if(!_tcscmp(buf, _T("\n")))
					MenuPrint();

				int a = _ttoi(buf);
				buf[_tcslen(buf) - 1] = 0;//개행문자 제거
				//TCHAR* message = _tcsstr(buf, _T(" "));
				//if(NULL==message)
				//	continue;
				//message = HisUtil::LTrim(message);

				switch(a) {
					//case X2B_AC_LOGIN_REQ:
					//	{
					//		mainclientworld->GetBalanceClient().Login();
					//	}
					//	break;

					//case X2G_AC_CERTIFY_REQ:
					//	{
					//		mainclientworld->GetGameClient().Certify();
					//	}
					//	break;

					//case X2G_CH_LOAD_ALL_CHAR_REQ:
					//	{
					//		mainclientworld->GetGameClient().LoadAllChar();
					//	}
					//	break;

					//case X2G_CH_CREATE_CHAR_REQ:
					//	{
					//		mainclientworld->GetGameClient().CreateChar();
					//	}
					//	break;

					//case X2G_CH_DELETE_CHAR_REQ:
					//	{
					//		mainclientworld->GetGameClient().DeleteChar();
					//	}
					//	break;

					//case X2G_WD_WORLD_ENTER_REQ:
					//	{
					//		mainclientworld->GetGameClient().WorldEnter(1, mainclientworld->GetGameClient().GetObjectID());
					//	}
					//	break;

					//case X2G_WD_WORLD_LEAVE_REQ:
					//	{
					//		mainclientworld->GetGameClient().WorldLeave();
					//	}
					//	break;

					//case X2G_WD_MOVE_REQ:
					//	{
					//		TCHAR* x_buf = _tcsstr(buf, _T(" "));
					//		if(NULL==x_buf)
					//			continue;
					//		x_buf = HisUtil::LTrim(x_buf);
					//		float x = (float)_ttoi(x_buf);

					//		TCHAR* y_buf = _tcsstr(x_buf, _T(" "));
					//		if(NULL==y_buf)
					//			continue;
					//		y_buf = HisUtil::LTrim(y_buf);
					//		float y = (float)_ttoi(y_buf);
					//
					//		mainclientworld->GetGameClient().WorldMove(x, y);
					//	}
					//	break;

					//case X2G_BD_CHAT_REQ:
					//	{
					//		TCHAR* x_buf = _tcsstr(buf, _T(" "));
					//		if(NULL==x_buf)
					//			continue;
					//		//x_buf = HisUtil::LTrim(x_buf);
					//		//BYTE type = _ttoi(x_buf);

					//		TCHAR* chatmsg = _tcsstr(x_buf, _T(" "));
					//		if(NULL==chatmsg)
					//			continue;
					//		chatmsg = HisUtil::LTrim(chatmsg);

					//		mainclientworld->GetGameClient().Chat(1, chatmsg);
					//	}
					//	break;

					case 0:
					default:
						break;

				}//..switch(a)
			}//..while (TRUE)
		}
	}

#ifdef _DEBUG
	_CrtDumpMemoryLeaks();
#endif
	return 0;
}

