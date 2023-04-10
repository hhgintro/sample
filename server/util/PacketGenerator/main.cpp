// PacketGenerator.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "stdafx.h"
#include "PacketGenerator.h"

void help()
{
	//����μ� : ../pidl/X2G.txt -path ../../common/pidl/

	//�������� + xml��� + ��������(X2B.txt) + ������
	_tprintf(_T("�ؽ�Ʈ(*.txt) ������ �������� ����ü�� �Լ��� �����մϴ�.\n\n"));
	_tprintf(_T("PacketGenerator [source] [-path ���] [-cs]\n"));
	_tprintf(_T("    source      �������� �ؽ�Ʈ ��θ� �����մϴ�.\n"));
	_tprintf(_T("    -path       ��°�θ� �����մϴ�(default:������)\n"));
	_tprintf(_T("    -cs         cs ������ �����մϴ�.\n"));
	//system("pause");
}

BOOL parserArgment(int argc, _TCHAR* argv[], TCHAR** path, TCHAR** pidl, BOOL& bCS)
{
	for (int i = 1; i < argc; ++i)
	{
		if (argv[i][0] == _T('-'))
		{
			//target ��ΰ� �ִٸ�
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
				//�������� �ʴ� �ɼ�
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
	//	LOGEVENT("HG_RED", _T("%d / 3 ��� �μ��� �ʿ��մϴ�."), argc);
	//	LOGEVENT("HG_RED", _T("�ʿ����� : �������� + ��������(X2B.txt) + ������"));
	//	//_tprintf(_T("%d / 2 ��� �μ��� �ʿ��մϴ�.\n"), argc);
	//	//::system("pause");
	//	return 0;
	//}
/*
D:/work/HorseRacing/source/server/source/pidl/GM2.txt -path ./pidl/
../netcore/source/pidl/NetC2S.txt -cs -path ./pidl/
*/
	TCHAR* path = _T(".");//������(".")
	TCHAR* pidl = NULL;
	BOOL bCS = FALSE;	//cs ���ϻ�������

	//pidl�� NULLüũ�� parserArgment()���Ŀ� ������ �ش�.
	if (FALSE == parserArgment(argc, argv, &path, &pidl, bCS) || NULL == pidl)
	{
		help();
		return 0;
	}

	//stProtocolHeader header;
	//stProtocol* protocol = new stProtocol[MAX_PROTOCOL_COUNT];
	////stProtocol protocol[MAX_PROTOCOL_COUNT];

	//��� ��ȣ
	HisUtil::CModule module;
	if (FALSE == module.CheckValid())
	{
		LOGEVENT("HG_RED", _T("fail generator version check"));
		return 0;
	}

	CPacketGenerator gen;

	//xml ���� �ε�
	TCHAR xmlpath[MAX_PATH] = _T("");
	_stprintf_s(xmlpath, _T("%sconfig\\PacketGenerator.xml"), module.GetPathName());
	gen.LoadXmlConstValues(xmlpath);

	//�������� ���� ������ ����
	if (FALSE == gen.LoadProtocolFile(pidl))
	{
		LOGEVENT("HG_RED", _T("fail load protocol(%s) file"), pidl);
		return 0;
	}
	LOGEVENT("HG_GRAY", _T("success load protocol(%s)"), pidl);


	TCHAR StructFileName[MAX_PATH] = _T("");		//������ structure ���ϸ�
	TCHAR ProtocolFileName[MAX_PATH] = _T("");		//������ protocol offset ���ϸ�
	TCHAR ReadPacketFileName[MAX_PATH] = _T("");	//������ read �Լ� ���ϸ�
	TCHAR WritePacketFileName[MAX_PATH] = _T("");	//������ write �Լ� ���ϸ�

	_sntprintf(ProtocolFileName, MAX_PATH, _T("%s/%s_Protocol.h"), path, gen.GetHeader().name);
	_sntprintf(StructFileName, MAX_PATH, _T("%s/%s_Structure.h"), path, gen.GetHeader().name);
	_sntprintf(ReadPacketFileName, MAX_PATH, _T("%s/%s_RecvPacket.h"), path, gen.GetHeader().name);
	_sntprintf(WritePacketFileName, MAX_PATH, _T("%s/%s_SendPacket.h"), path, gen.GetHeader().name);
	//_sntprintf(StructFileName, MAX_PATH, argv[2], header.name);
	//_sntprintf(ProtocolFileName, MAX_PATH, argv[3], header.name);
	//_sntprintf(ReadPacketFileName, MAX_PATH, argv[4], header.name);
	//_sntprintf(WritePacketFileName, MAX_PATH, argv[5], header.name);



	//protocol.h ���� ����
	gen.CreateProtocolFile(path);

	//structure ���� ����
	gen.CreateStructFile(path);

	//recv �Լ� ���� ����
	gen.CreateRecvFile(path);

	//send �Լ� ���� ����
	gen.CreateSendFile(path);

	//cs : ������� ������ .h ���� ���� �Ŀ� �����ϵ��� �մϴ�.
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

