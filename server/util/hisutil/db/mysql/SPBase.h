#pragma once
#include "dbconnect.h"

/*** SAMPLE **************************
class CSPSample : public HisUtil::CSPBase
{
public:
	int m_accountpk;

public:
	CSPSample(LPCWCHAR spname) : HisUtil::CSPBase(spname), m_accountpk(0) {}


	// ***  sp 의 인자 순으로 Append() 를 호출해 주세요 *** //
	virtual void _AppendParameter()
	{
		HisUtil::CSPBase::_AppendParameter();

		Append(eDB_IN, m_accountpk);
		//Append(eDB_OUTPUT, m_avatarPk);	//mysql은 output을 지원하지 않습니다.
	}

	// ***  eDB_OUTPUT 으로 설정된 변수에 값을 담아 옵니다. *** //
	//mysql은 output을 지원하지 않습니다.
	virtual void _BindParam()
	{
		HisUtil::CSPBase::_BindParam();

		// ***  sp 의 인자 순으로 BindParam() 를 호출해 주세요 *** //
		// *** OUT param 변수는 반드시 0 초기화 되어 있는지 확인해 주세요 *** //

		//BindParam(m_avatarPk);		//mysql은 output을 지원하지 않습니다.
	}

	// *** _Fetch()를 통해 class내에서 처리가 가능하다. *** //
	// *** Fetch()를 통해 class 외부애서도 처리가 가능하다. *** //
	virtual void _Fetch()
	{
		//while (TRUE == m_rs.IsEOF())
		//{
		//	int id = m_rs.GetFieldsValues(L"id").lVal;
		//	_bstr_t name = m_rs.GetFieldsValues(L"name").bstrVal;
		//	std::cout << id << " : " << (char*)name << std::endl;

		//	m_rs.MoveNext();
		//}
		////m_rs.NextRecordset();	//다중 recordset인경우
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

// *** Fetch()를 통해 class 외부애서도 처리가 가능하다. *** //
//while (TRUE == sp.Fetch())
//{
//	int id = sp.GetFieldsValues(L"id");
//	_bstr_t name = sp.GetFieldsValues(L"name");
//	std::cout << id << " : " << (char*)name << std::endl;
//
//	sp.MoveNext();
//}
////sp.NextRecordset();	//다중 recordset인경우

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

		// ***  sp 의 인자 순으로 Append() 를 호출해 주세요 *** //
		virtual void _AppendParameter();

		// ***  eDB_OUTPUT 으로 설정된 변수에 값을 담아 옵니다. *** //
		virtual void _BindParam();

		//sp 명
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
		////	sp 에서 OUT 파라미터를 전달되는 값들.
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
		//////	sp 에서 Table ROW 데이타
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
		int m_posGet;	//값을 대입할 출력변수의 index( BindParam() 에서 사용됨 )


		std::wstring m_storedProcName;	//sp명
		//CDBConnection* m_connection;

		CModule m_module;
	};

};//..namespace HisUtil {