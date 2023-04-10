// PacketGenerator.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include "PacketGenerator.h"

void help()
{
	//명령인수 : ../pidl/X2G.txt -path ../../common/pidl/

	//실행파일 + xml경로 + 프로토콜(X2B.txt) + 저장경로
	_tprintf(_T("텍스트(*.txt) 정보로 프로토콜 구조체와 함수를 생성합니다.\n\n"));
	_tprintf(_T("PacketGenerator [source] [-path 경로] [-cs]\n"));
	_tprintf(_T("    source      프로토콜 텍스트 경로를 지정합니다.\n"));
	_tprintf(_T("    -path       출력경로를 지정합니다(default:현재경로)\n"));
	_tprintf(_T("    -cs         cs 파일을 생성합니다.\n"));
	//system("pause");
}

BOOL parserArgment(int argc, _TCHAR* argv[], TCHAR** path, TCHAR** pidl, BOOL& bCS)
{
	for (int i = 1; i < argc; ++i)
	{
		if (argv[i][0] == _T('-'))
		{
			//target 경로가 있다면
			if (0 == _tcscmp(argv[i], _T("-path")))
			{
				if (++i < argc)
				{
					*path = argv[i];
					continue;
				}
			}
			else if (0 == _tcscmp(argv[i], _T("-cs")))
			{
				bCS = TRUE;
				continue;
			}
			else
			{
				//존재하지 않는 옵션
				//help();
				return FALSE;
			}
		}
		else if (0 == _tcscmp(argv[i], _T("/?")))
		{
			//help();
			return FALSE;
		}

		*pidl = argv[i];
	}

	return TRUE;
}
int run(int argc, _TCHAR* argv[])
{
	//for (int i = 0; i < argc; ++i)
	//{
	//	LOGEVENT("HG_YELLOW", _T("%d: %s"), i,argv[i]);
	//}
	//if (argc != 3)
	//{
	//	LOGEVENT("HG_RED", _T("%d / 3 명령 인수가 필요합니다."), argc);
	//	LOGEVENT("HG_RED", _T("필요인자 : 실행파일 + 프로토콜(X2B.txt) + 저장경로"));
	//	//_tprintf(_T("%d / 2 명령 인수가 필요합니다.\n"), argc);
	//	//::system("pause");
	//	return 0;
	//}
/*
D:/work/HorseRacing/source/server/source/pidl/GM2.txt -path ./pidl/
../netcore/source/pidl/NetC2S.txt -cs -path ./pidl/
*/
	TCHAR* path = _T(".");//현재경로(".")
	TCHAR* pidl = NULL;
	BOOL bCS = FALSE;	//cs 파일생성유무

	//pidl의 NULL체크는 parserArgment()이후에 진행해 준다.
	if (FALSE == parserArgment(argc, argv, &path, &pidl, bCS) || NULL == pidl)
	{
		help();
		return 0;
	}

	//stProtocolHeader header;
	//stProtocol* protocol = new stProtocol[MAX_PROTOCOL_COUNT];
	////stProtocol protocol[MAX_PROTOCOL_COUNT];

	//모듈 보호
	HisUtil::CModule module;
	if (FALSE == module.CheckValid())
	{
		LOGEVENT("HG_RED", _T("fail generator version check"));
		return 0;
	}

	CPacketGenerator gen;

	//xml 파일 로드
	TCHAR xmlpath[MAX_PATH] = _T("");
	_stprintf_s(xmlpath, _T("%sconfig\\PacketGenerator.xml"), module.GetPathName());
	gen.LoadXmlConstValues(xmlpath);

	//프로토콜 정의 파일을 연다
	if (FALSE == gen.LoadProtocolFile(pidl))
	{
		LOGEVENT("HG_RED", _T("fail load protocol(%s) file"), pidl);
		return 0;
	}
	LOGEVENT("HG_GRAY", _T("success load protocol(%s)"), pidl);


	TCHAR StructFileName[MAX_PATH] = _T("");		//저장할 structure 파일명
	TCHAR ProtocolFileName[MAX_PATH] = _T("");		//저장할 protocol offset 파일명
	TCHAR ReadPacketFileName[MAX_PATH] = _T("");	//저장할 read 함수 파일명
	TCHAR WritePacketFileName[MAX_PATH] = _T("");	//저장할 write 함수 파일명

	_sntprintf(ProtocolFileName, MAX_PATH, _T("%s/%s_Protocol.h"), path, gen.GetHeader().name);
	_sntprintf(StructFileName, MAX_PATH, _T("%s/%s_Structure.h"), path, gen.GetHeader().name);
	_sntprintf(ReadPacketFileName, MAX_PATH, _T("%s/%s_RecvPacket.h"), path, gen.GetHeader().name);
	_sntprintf(WritePacketFileName, MAX_PATH, _T("%s/%s_SendPacket.h"), path, gen.GetHeader().name);
	//_sntprintf(StructFileName, MAX_PATH, argv[2], header.name);
	//_sntprintf(ProtocolFileName, MAX_PATH, argv[3], header.name);
	//_sntprintf(ReadPacketFileName, MAX_PATH, argv[4], header.name);
	//_sntprintf(WritePacketFileName, MAX_PATH, argv[5], header.name);



	//protocol.h 파일 생성
	gen.CreateProtocolFile(path);

	//structure 파일 생성
	gen.CreateStructFile(path);

	//recv 함수 파일 생성
	gen.CreateRecvFile(path);

	//send 함수 파일 생성
	gen.CreateSendFile(path);

	//cs : 생성경로 때문에 .h 먼저 만든 후에 생성하도록 합니다.
	if (TRUE == bCS) {
		gen.CreateCsProtocolFile(path);
		gen.CreateCsStructFile(path);
	}

	LOGEVENT("HG_GRAY", _T("finish"));

	return 0;
}

int _tmain(int argc, _TCHAR* argv[])
{
	_wsetlocale(LC_ALL, L"");//#include <locale.h>
	HisUtil::CEventLog::Instance().Begin();

	run(argc, argv);

	HisUtil::CEventLog::Instance().End();
}

