#pragma once
#include "dbconnect.h"

/*** SAMPLE **************************
class CSPSample : public HisUtil::CSPBase
{
public:
	int m_accountpk;

public:
	CSPSample(LPCWCHAR spname) : HisUtil::CSPBase(spname), m_accountpk(0) {}


	// ***  sp �� ���� ������ Append() �� ȣ���� �ּ��� *** //
	virtual void _AppendParameter()
	{
		HisUtil::CSPBase::_AppendParameter();

		Append(eDB_IN, m_accountpk);
		//Append(eDB_OUTPUT, m_avatarPk);	//mysql�� output�� �������� �ʽ��ϴ�.
	}

	// ***  eDB_OUTPUT ���� ������ ������ ���� ��� �ɴϴ�. *** //
	//mysql�� output�� �������� �ʽ��ϴ�.
	virtual void _BindParam()
	{
		HisUtil::CSPBase::_BindParam();

		// ***  sp �� ���� ������ BindParam() �� ȣ���� �ּ��� *** //
		// *** OUT param ������ �ݵ�� 0 �ʱ�ȭ �Ǿ� �ִ��� Ȯ���� �ּ��� *** //

		//BindParam(m_avatarPk);		//mysql�� output�� �������� �ʽ��ϴ�.
	}

	// *** _Fetch()�� ���� class������ ó���� �����ϴ�. *** //
	// *** Fetch()�� ���� class �ܺξּ��� ó���� �����ϴ�. *** //
	virtual void _Fetch()
	{
		//while (TRUE == m_rs.IsEOF())
		//{
		//	int id = m_rs.GetFieldsValues(L"id").lVal;
		//	_bstr_t name = m_rs.GetFieldsValues(L"name").bstrVal;
		//	std::cout << id << " : " << (char*)name << std::endl;

		//	m_rs.MoveNext();
		//}
		////m_rs.NextRecordset();	//���� recordset�ΰ��
	}

	GAME_RESULT GetResult()
	{
		switch (m_result) {
			case 0:		return RESULT_OK;
			default:	return DB_NOT_FOUND_ERROR;
		}//..switch (m_result) {
	}
};

CSPSample sp(L"sp_sample");
sp.m_accountpk = m_avatar->GetObjectInfo().m_accountpk;
if(FALSE == sp.Open(db_))
{
	result_ = sp.GetResult();
	return;
}

// *** Fetch()�� ���� class �ܺξּ��� ó���� �����ϴ�. *** //
//while (TRUE == sp.Fetch())
//{
//	int id = sp.GetFieldsValues(L"id");
//	_bstr_t name = sp.GetFieldsValues(L"name");
//	std::cout << id << " : " << (char*)name << std::endl;
//
//	sp.MoveNext();
//}
////sp.NextRecordset();	//���� recordset�ΰ��

sp.CleanUp();
*/


namespace HisUtil {

	class CSPBase
	{
	public:
		CSPBase(LPCWCHAR spname) : m_result(RESULT_OK), m_posGet(0), m_storedProcName(spname)
		{
		}
		virtual ~CSPBase()
		{
			CleanUp();
		}

		virtual BOOL Open(CAdoConnection& conn);
		//virtual BOOL Open(ADODB::_Connection* connection);
		virtual void CleanUp();

		virtual BOOL Fetch();
		virtual void MoveNext();
		virtual void NextRecordset();
		
		virtual _variant_t GetFieldsValues(LPCWCHAR fileldname);


	protected:
	
		virtual void _Fetch() {};

		// ***  sp �� ���� ������ Append() �� ȣ���� �ּ��� *** //
		virtual void _AppendParameter();

		// ***  eDB_OUTPUT ���� ������ ������ ���� ��� �ɴϴ�. *** //
		virtual void _BindParam();

		//sp ��
		//void SetStoredProcName(Proud::String name) { m_storedProcName = name; }

	public:

		virtual GAME_RESULT GetResult() = 0;

		//ADODB::ParameterDirectionEnum _GetParamDirect(ADODB::ParameterDirectionEnum direct);
		ADODB::_ParameterPtr AppendReturn();
		//*************************************************************************************
		ADODB::_ParameterPtr Append(ADODB::ParameterDirectionEnum direct, INT8 values);
		ADODB::_ParameterPtr Append(ADODB::ParameterDirectionEnum direct, UINT8 values);
		ADODB::_ParameterPtr Append(ADODB::ParameterDirectionEnum direct, INT16 values);
		ADODB::_ParameterPtr Append(ADODB::ParameterDirectionEnum direct, UINT16 values);
		ADODB::_ParameterPtr Append(ADODB::ParameterDirectionEnum direct, INT32 values);
		ADODB::_ParameterPtr Append(ADODB::ParameterDirectionEnum direct, UINT32 values);
		ADODB::_ParameterPtr Append(ADODB::ParameterDirectionEnum direct, INT64 values);
		ADODB::_ParameterPtr Append(ADODB::ParameterDirectionEnum direct, UINT64 values);
		ADODB::_ParameterPtr Append(ADODB::ParameterDirectionEnum direct, float values);
		ADODB::_ParameterPtr Append(ADODB::ParameterDirectionEnum direct, double values);
		ADODB::_ParameterPtr Append(ADODB::ParameterDirectionEnum direct, std::string& values, int length);
		ADODB::_ParameterPtr Append(ADODB::ParameterDirectionEnum direct, std::wstring& values, int length);
		ADODB::_ParameterPtr Append(ADODB::ParameterDirectionEnum direct, const char* values, int length);
		ADODB::_ParameterPtr Append(ADODB::ParameterDirectionEnum direct, const wchar_t* values, int length);


//for mssql
		////*************************************************************************************
		////	sp ���� OUT �Ķ���͸� ���޵Ǵ� ����.
		//void BindParam(INT8& values);
		//void BindParam(UINT8& values);
		//void BindParam(INT16& values);
		//void BindParam(UINT16& values);
		//void BindParam(INT32& values);
		//void BindParam(UINT32& values);
		//void BindParam(INT64& values);
		//void BindParam(UINT64& values);
		//void BindParam(float& values);
		//void BindParam(CHAR* values);
		//void BindParam(WCHAR* values);
		////void BindParam(Proud::StringA& values);
		////void BindParam(Proud::String& values);


		//////*************************************************************************************
		//////	sp ���� Table ROW ����Ÿ
		////void GetData(INT8& values);
		////void GetData(UINT8& values);
		////void GetData(INT16& values);
		////void GetData(UINT16& values);
		////void GetData(INT32& values);
		////void GetData(UINT32& values);
		////void GetData(INT64& values);
		////void GetData(UINT64& values);
		////void GetData(float& values);
		////void GetData(CHAR* values);
		////void GetData(WCHAR* values);
		////void GetData(Proud::StringA& values);
		////void GetData(Proud::String& values);

	protected:
		GAME_RESULT m_result;

	private:
		CAdoConnection m_connection;
		CAdoRecordset m_rs;
		CAdoCommand m_cmd;

		//for mssql
		std::vector<ADODB::_ParameterPtr> m_outparams;
		int m_posGet;	//���� ������ ��º����� index( BindParam() ���� ���� )


		std::wstring m_storedProcName;	//sp��
		//CDBConnection* m_connection;

		CModule m_module;
	};

};//..namespace HisUtil {