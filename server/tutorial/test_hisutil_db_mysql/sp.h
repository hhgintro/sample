#pragma once

#include "../../../common/errorcode/ErrorCode.h"

class CSPSample : public HisUtil::CSPBase
{
public:
	int m_accountpk;
	std::wstring m_name;

public:
	CSPSample(LPCWCHAR spname) : HisUtil::CSPBase(spname), m_accountpk(0) {}


	// ***  sp �� ���� ������ Append() �� ȣ���� �ּ��� *** //
	virtual void _AppendParameter()
	{
		HisUtil::CSPBase::_AppendParameter();

		m_cmd.Append(ADODB::adParamInput, m_accountpk);
		m_cmd.Append(ADODB::adParamInput, m_name.c_str(), 100);
		//Append(eDB_OUTPUT, m_avatarPk);
	}

	// ***  eDB_OUTPUT ���� ������ ������ ���� ��� �ɴϴ�. *** //
	virtual void _BindParam()
	{
		HisUtil::CSPBase::_BindParam();

		// ***  sp �� ���� ������ BindParam() �� ȣ���� �ּ��� *** //
		// *** OUT param ������ �ݵ�� 0 �ʱ�ȭ �Ǿ� �ִ��� Ȯ���� �ּ��� *** //

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