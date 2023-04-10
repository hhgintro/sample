// test_hisutil_log.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "stdafx.h"

class MySingleton : public HisUtil::CThread, public HisUtil::CSingleton<MySingleton>
{
public:
	MySingleton() {}
	~MySingleton() {}
public:

	//while(TRUE == IsRunning()) {}
	void OnWorkerThread(int index)
	{
		while(TRUE == IsRunning())
		{
			Sleep(TIME_SEC(1));
			printf("thread(%d) is running\n", index);
		}
	}

};

int _tmain(int argc, _TCHAR* argv[])
{
	HisUtil::CModule module;

	//=============
	//log ���� ����
	//=============

	TCHAR logpath[MAX_PATH] = _T("");
	_stprintf_s(logpath, _T("%s\\Log\\"), module.GetPathName());
	//���� ���� : log ���� �Ʒ� server ������ ������� CreateDirectory()�� 2�� ȣ���Ͽ��� �Ѵ�.
	::CreateDirectory(logpath, 0);// Log/ ���� ����

	TCHAR szPath_[MAX_PATH] = _T("");
	//m_module.GetConfigFileName(projectpath, _T("\\"), szPath_);
	//memset(szPath_, 0, sizeof(szPath_));
	_stprintf_s(szPath_, _T("%s%s"), logpath, module.GetAppName());
	::CreateDirectory(szPath_, 0);// Log/Server/ ���� ����



	//=======================
	//�����ڵ� <--> ��Ƽ�ڵ�
	//=======================

	char inChar[10] = "���̻��";
	wchar_t inWChar[10] = L"����ĥ��";

	char outChar[10];
	wchar_t outWChar[10];

	HisUtil::CA2W(inChar, outWChar, _countof(outWChar));
	//HisUtil::CA2W(inChar, outWChar, sizeof(outWChar));//�Ѵ� ����ص� ���� ���

	HisUtil::CW2A(inWChar, outChar, _countof(outChar));
	//HisUtil::CW2A(inWChar, outChar, sizeof(outChar));



	//=============
	//Singleton
	//=============
	/*
	//MySingleton my;
	//my.BeginThread(4);
	MySingleton::Instance().BeginThread(4);

	while (1)
	{
		Sleep(TIME_SEC(5));
		printf("Main THREAD is running\n");

	}
	*/


	//=============
	//EventLog
	//=============

	HisUtil::CEventLog::Instance();

	while (1)
	{
		Sleep(TIME_SEC(5));
		HisUtil::CEventLog::Instance().LogEvent("HG_RED", L"Main THREAD is running");

		static int count = 0;
		if (++count > 5)
		{
			//HisUtil::CEventLog::Instance().End();
			break;
		}
	}
	HisUtil::CEventLog::Destroy();

	return 0;
}

