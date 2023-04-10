#pragma once
#include "dbconnect.h"

/*** SAMPLE : DO NOT REMOVE ***
class CSPSample : public HisUtil::CSPBase
{
public:
	int m_accountpk;
	int m_avatarPk;

public:
	CSPSample(LPCWCHAR spname) : HisUtil::CSPBase(spname)
		, m_accountpk(0), m_avatarPk(0) {}


	// ***  sp 의 인자 순으로 Append() 를 호출해 주세요 *** //
	// ***  mysql은 output을 지원하지 않습니다 *** //
	virtual void _AppendParameter()
	{
		//CSPBase::_AppendParameter() 에서 RETURN 을 받을 수 있도록 설정합니다.(for mssql)
		HisUtil::CSPBase::_AppendParameter();

		Append(ADODB::adParamInput, m_accountpk);
		Append(ADODB::adParamOutput, m_avatarPk);	//mysql은 output을 지원하지 않습니다.
	}

	// ***  ADODB::adParamOutput 으로 설정된 변수에 값을 담아 옵니다. *** //
	// ***  mysql은 BindParam을 지원하지 않습니다 *** //
	virtual void _BindParam()
	{
		HisUtil::CSPBase::_BindParam();

		// ***  sp 의 인자 순으로 BindParam() 를 호출해 주세요 *** //
		// *** OUT param 변수는 반드시 0 초기화 되어 있는지 확인해 주세요 *** //

		BindParam(m_avatarPk);		//mysql은 output을 지원하지 않습니다.
	}

	// ***  CSPBase::_Return() 으로 RETURN 값을 담아 옵니다.(for mssql) *** //
	virtual BOOL _Return()
	{
		return HisUtil::CSPBase::_Return();	//for mssql
		//return TRUE;						//for mysql
	}

	// *** Fetch()를 통해 class 내/외부애서도 처리가 가능하다. *** //
	virtual void _Fetch()
	{
		//while (TRUE == m_rs.IsEOF())
		//{
		//	int id = GetFieldsValues(L"id");
		//	_bstr_t name = GetFieldsValues(L"name");
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

try {
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
catch (_com_error& e)
{
SetLastError(e);
conn->Close();
}
catch (...)
{
printf("unknown error\n");
}

/*** SAMPLE : DO NOT REMOVE ***/


namespace HisUtil {

	class CBaseDBManager;
	class CSPBase
	{
	public:
		//CSPBase() : m_conn(NULL), m_result(RESULT_OK), m_posGet(-1), m_storedProcName(L"")
		//{}
		CSPBase(LPCWCHAR spname) : m_base(NULL), m_conn(NULL), m_result(0), m_posGet(-1), m_storedProcName(spname)
		{}
		virtual ~CSPBase()
		{
			CleanUp();
		}

		void SetLastError(_com_error& e);
		void SetLastError();

		const wchar_t* GetStoredProcName() { return m_storedProcName.c_str(); }
		void SetStoredProcName(LPCWCHAR spname) { m_storedProcName = spname; }
		void SetDBConnection(CAdoConnection* conn) { m_conn = conn; }
		virtual BOOL Open() { return Open(m_base); }
		//virtual BOOL Open(CAdoConnection* conn);
		virtual BOOL Open(CBaseDBManager* base);
		//virtual BOOL Open(ADODB::_Connection* connection);
		virtual void CleanUp();

		// *** Fetch()를 통해 class 외부애서도 처리가 가능하다. *** //
		//EoF이면 FALSE를 리턴한다.
		virtual BOOL Fetch();

		//next ROW
		virtual void MoveNext();

		//다중 Recordset인 경우...
		virtual void NextRecordset();	
		
		//Recordset에서 컬럼명으로 정보를 가져온다.
		// 리턴값이 NULL인 경우 처리가 되지 않으므로
		// DB에서 IFNULL() 구문처리가 필요합니다.
		virtual _variant_t GetFieldsValues(LPCWCHAR fileldname);

		virtual GAME_RESULT GetResult() = 0;

	protected:
	
		//상속class 또는 class외수에서 Fetch를 구현해서 Recordset정보 가져올 수 있다.
		virtual void _Fetch() {};

		// ***  sp 의 인자 순으로 Append() 를 호출해 주세요 *** //
		virtual void _AppendParameter();

		// ***  ADODB::adParamOutput 으로 설정된 변수에 값을 담아 옵니다. *** //
		virtual void _BindParam() {};

		// ***  CSPBase::_Return() 으로 RETURN 값을 담아 옵니다.(for mssql) *** //
		virtual BOOL _Return();

		//sp 명
		//void SetStoredProcName(Proud::String name) { m_storedProcName = name; }



		//ADODB::ParameterDirectionEnum _GetParamDirect(ADODB::ParameterDirectionEnum direct);
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
		void BindParam(INT8& values);
		void BindParam(UINT8& values);
		void BindParam(INT16& values);
		void BindParam(UINT16& values);
		void BindParam(INT32& values);
		void BindParam(UINT32& values);
		void BindParam(INT64& values);
		void BindParam(UINT64& values);
		void BindParam(float& values);
		void BindParam(double& values);
		void BindParam(char* values, int length);
		void BindParam(wchar_t* values, int length);
		void BindParam(std::string& values);
		void BindParam(std::wstring& values);


	protected:
		GAME_RESULT m_result;

	private:
		CBaseDBManager* m_base;
		CAdoConnection* m_conn;
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