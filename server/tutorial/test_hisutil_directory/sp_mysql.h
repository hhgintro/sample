#pragma once

#include "../../../common/errorcode/ErrorCode.h"

class CSPMysqlSample : public HisUtil::CSPBase
{
public:
	int m_accountpk;
	std::wstring m_name;

public:
	CSPMysqlSample(LPCWCHAR spname) : HisUtil::CSPBase(spname), m_accountpk(0) {}


	// ***  sp 의 인자 순으로 Append() 를 호출해 주세요 *** //
	virtual void _AppendParameter()
	{
		//CSPBase::_AppendParameter() 에서 RETURN 을 받을 수 있도록 설정합니다.(for mssql)
		//HisUtil::CSPBase::_AppendParameter();

		Append(ADODB::adParamInput, m_accountpk);
		Append(ADODB::adParamInput, m_name, 100);
		//Append(eDB_OUTPUT, m_avatarPk);
	}

	// ***  eDB_OUTPUT 으로 설정된 변수에 값을 담아 옵니다. *** //
	virtual void _BindParam()
	{
		// ***  sp 의 인자 순으로 BindParam() 를 호출해 주세요 *** //
		// *** OUT param 변수는 반드시 0 초기화 되어 있는제 확인해 주세요 *** //

		//BindParam(m_avatarPk);
	}

	// ***  CSPBase::_Return() 으로 RETURN 값을 담아 옵니다.(for mssql) *** //
	virtual BOOL _Return()
	{
		//return HisUtil::CSPBase::_Return();//for mssql
		return TRUE;	//for mysql
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