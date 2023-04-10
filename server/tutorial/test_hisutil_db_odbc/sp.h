#pragma once

#include "../../../common/errorcode/ErrorCode.h"

class CSPSample : public HisUtil::CSPBase
{
public:
	int m_accountpk;
	std::wstring m_name;

public:
	CSPSample(LPCWCHAR spname) : HisUtil::CSPBase(spname), m_accountpk(0) {}


	// ***  sp 의 인자 순으로 Append() 를 호출해 주세요 *** //
	virtual void _AppendParameter()
	{
		HisUtil::CSPBase::_AppendParameter();

		m_cmd.Append(ADODB::adParamInput, m_accountpk);
		m_cmd.Append(ADODB::adParamInput, m_name.c_str(), 100);
		//Append(eDB_OUTPUT, m_avatarPk);
	}

	// ***  eDB_OUTPUT 으로 설정된 변수에 값을 담아 옵니다. *** //
	virtual void _BindParam()
	{
		HisUtil::CSPBase::_BindParam();

		// ***  sp 의 인자 순으로 BindParam() 를 호출해 주세요 *** //
		// *** OUT param 변수는 반드시 0 초기화 되어 있는제 확인해 주세요 *** //

		//BindParam(m_avatarPk);
	}

	virtual void _Fetch()
	{
		//while (Fetch())
		//{
		//	int id = m_rs.GetFieldsValues(L"id");
		//	_bstr_t name = m_rs.GetFieldsValues(L"name");
		//	std::cout << id << " : " << (char*)name << std::endl;

		//	MoveNext();
		//}
		//NextRecordset();

		//while (Fetch())
		//{
		//	int id = m_rs.GetFieldsValues(L"id").lVal;
		//	_bstr_t name = m_rs.GetFieldsValues(L"name").bstrVal;
		//	std::cout << id << " : " << (char*)name << std::endl;

		//	MoveNext();
		//}
		//NextRecordset();

		//while (Fetch())
		//{
		//	int id = m_rs.GetFieldsValues(L"id").lVal;
		//	_bstr_t name = m_rs.GetFieldsValues(L"name").bstrVal;
		//	std::cout << id << " : " << (char*)name << std::endl;

		//	MoveNext();
		//}
		//NextRecordset();

		//int o_id = m_rs.GetFieldsValues(L"o_id").lVal;
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