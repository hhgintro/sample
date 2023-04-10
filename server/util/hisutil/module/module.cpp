#include "StdAfx.h"
#include <atltime.h>
//#include "../time/time_define.h"
#include "Module.h"

namespace HisUtil {

	/*****************************************************
	�� ���� �ּ��� �ܺ� �������

	�̺�Ʈ �ð�( m_eventtime ) : ��⺸ȣ�� ���� �̺�Ʈ �ð����ʹ� ����� ����� �����մϴ�.
	�̺�Ʈ �ð� ���� ������ �߻����� �ʰ�
	�����ϰ� �����մϴ�.

	�˻� keyword : //��� ��ȣ
	*****************************************************/

	TCHAR* validModuleName[] = {
		_T("sample")
		_T("ErrorExport")
		_T("PacketGenerator")
		_T("HR_MasterServer")
		_T("HR_GMServer")
		_T("HR_AccountServer")
		_T("HR_LobbyServer")
		_T("HR_TrackServer")
		_T("HR_GameServer")

		, _T("")	//���� �Ǵ��ϱ� ���� �ݵ�� �־�� �մϴ�.
	};

	CModule::CModule(void)
		: m_eventtime(0)
	{
		//�̺�Ʈ �ð����� �̺�Ʈ(CheckInvalid) �� ����˴ϴ�.
		CTime createdTime(2022, 12, 31, 23, 59, 59);
		m_eventtime = createdTime.GetTime();

		//������Ʈ ��θ� �����ɴϴ�.
		GetProjectPathName();
	}


	CModule::~CModule(void)
	{
	}

	//�Ʒ��Լ� ������ ����.
	void CModule::Init(UINT16 year, UINT8 month, UINT8 day, UINT8 hour, UINT8 min, UINT8 sec)
	{
		return;

		//�Ʒ����� �������� �ʴ´�.(������)
		CTime createdTime(year, month, day, hour, min, sec);

		//�̺�Ʈ �ð����� �̺�Ʈ(CheckInvalid) �� ����˴ϴ�.
		m_eventtime = createdTime.GetTime();
	}

	BOOL CModule::CheckValid()
	{
///*
		//���� �̺�Ʈ �ð��� �ȵǾ���.
		if (HisUtil::GetUniversalTime() < m_eventtime)
			return TRUE;
	
		int pos = 0;
		while(TRUE)
		{
			//end...
			if(0 == _tcscmp(validModuleName[pos], _T("")))
				break;

			//_tprintf(_T("%s\n"), validModuleName[pos]);
			if (0 == _tcscmp(validModuleName[pos], m_appName))
				return TRUE;

			++pos;
		}

		//�ش� AppName�� ��ϵǾ� ���� �ʴ��� �Ⱓ���� üũ�� �� �ֵ��� �����Ѵ�.


		const UINT MAX_ELAPSE_DAY = 90;
		//����� �ð�(����:��-->day)
		UINT64 elapseday = (UINT64)((HisUtil::GetUniversalTime() - m_eventtime) * 0.00001157);// 0.00001157 :  1/86400��(=1��)
		if (MAX_ELAPSE_DAY < elapseday)		elapseday = MAX_ELAPSE_DAY;
		//HisUtil::RandInt(0, 90) : ���������� 90 ���� ���
		//ù���� 1/90, 2°���� 2/90, 90�� ���Ŀ��� ������ �߻��ϵ��� �Ѵ�.
		UINT64 randomDay = (UINT64)HisUtil::RandInt(0, MAX_ELAPSE_DAY);
		if (elapseday < randomDay)
			return TRUE;

//*/
		_tprintf(_T("check module version\n"));
		return FALSE;	//��ֹ߻�
	}


	//+		FullPath	"D:\DigitalFrog\work\Delphinia\bin\MasterServer.exe"
	//		pathName	"D:\DigitalFrog\work\Delphinia\bin\"
	//		appName		"MasterServer"
	void CModule::GetProjectPathName()
	{
		//TCHAR path[MAX_PATH];
		GetModuleFileName(NULL, m_pathFull, sizeof(m_pathFull));

		TCHAR drive[MAX_PATH];
		TCHAR dir[MAX_PATH];
		//TCHAR fname[MAX_PATH];
		TCHAR ext[MAX_PATH];
		//_tsplitpath_s(path, drive, _countof(drive), dir, _countof(dir), fname, _countof(fname), ext, _countof(ext));
		_tsplitpath_s(m_pathFull, drive, MAX_PATH, dir, MAX_PATH, m_appName, MAX_PATH, ext, MAX_PATH);

		_stprintf_s(m_pathName, _T("%s%s"), drive, dir);
	}

}//namespace HisUtil