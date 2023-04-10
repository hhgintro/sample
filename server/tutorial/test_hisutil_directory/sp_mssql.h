#pragma once

#include "../../../common/errorcode/ErrorCode.h"

class CSPMssqlSample : public HisUtil::CSPBase
{
public:
	int m_accountpk;
	std::wstring m_name;

	int o_id;
	//std::string o_name;
	wchar_t o_name[100];

public:
	CSPMssqlSample(LPCWCHAR spname) : HisUtil::CSPBase(spname)
		, m_accountpk(0), m_name(L""), o_id(7), o_name(L"7") {}


	// ***  sp �� ���� ������ Append() �� ȣ���� �ּ��� *** //
	virtual void _AppendParameter()
	{
		//CSPBase::_AppendParameter() ���� RETURN �� ���� �� �ֵ��� �����մϴ�.(for mssql)
		HisUtil::CSPBase::_AppendParameter();

		Append(ADODB::adParamInput, m_accountpk);
		Append(ADODB::adParamInput, m_name, 100);
		//Append(eDB_OUTPUT, m_avatarPk);
		Append(ADODB::adParamOutput, o_id);
		Append(ADODB::adParamOutput, o_name, 100);
	}

	// ***  ADODB::adParamOutput ���� ������ ������ ���� ��� �ɴϴ�. *** //
	virtual void _BindParam()
	{
		// ***  sp �� ���� ������ BindParam() �� ȣ���� �ּ��� *** //
		// *** OUT param ������ �ݵ�� 0 �ʱ�ȭ �Ǿ� �ִ��� Ȯ���� �ּ��� *** //

		//BindParam(m_avatarPk);
		BindParam(o_id);
		BindParam(o_name, 100);
	}

	// ***  CSPBase::_Return() ���� RETURN ���� ��� �ɴϴ�.(for mssql) *** //
	virtual BOOL _Return()
	{
		return HisUtil::CSPBase::_Return();//for mssql
		//return TRUE;	//for mysql
	}

	virtual void _Fetch()
	{
		//while (Fetch())
		//{
		//	int id = GetFieldsValues(L"id");
		//	_bstr_t name = GetFieldsValues(L"name");
		//	std::cout << id << " : " << (char*)name << std::endl;

		//	MoveNext();
		//}
		//NextRecordset();

		//while (Fetch())
		//{
		//	int id = GetFieldsValues(L"id").lVal;
		//	_bstr_t name = GetFieldsValues(L"name").bstrVal;
		//	std::cout << id << " : " << (char*)name << std::endl;

		//	MoveNext();
		//}
		//NextRecordset();

		//while (Fetch())
		//{
		//	int id = GetFieldsValues(L"id").lVal;
		//	_bstr_t name = GetFieldsValues(L"name").bstrVal;
		//	std::cout << id << " : " << (char*)name << std::endl;

		//	MoveNext();
		//}
		//NextRecordset();

		//int o_id = GetFieldsValues(L"o_id").lVal;
		//std::cout << "result: " << o_id << std::endl;
	}

	GAME_RESULT GetResult()
	{
		switch (m_result) {
		case 0:		return RESULT_OK;
		default:	return DB_NOT_FOUND_ERROR;
		}//..switch (m_result) {
	}
};