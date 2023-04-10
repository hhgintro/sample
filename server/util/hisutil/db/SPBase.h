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


	// ***  sp �� ���� ������ Append() �� ȣ���� �ּ��� *** //
	// ***  mysql�� output�� �������� �ʽ��ϴ� *** //
	virtual void _AppendParameter()
	{
		//CSPBase::_AppendParameter() ���� RETURN �� ���� �� �ֵ��� �����մϴ�.(for mssql)
		HisUtil::CSPBase::_AppendParameter();

		Append(ADODB::adParamInput, m_accountpk);
		Append(ADODB::adParamOutput, m_avatarPk);	//mysql�� output�� �������� �ʽ��ϴ�.
	}

	// ***  ADODB::adParamOutput ���� ������ ������ ���� ��� �ɴϴ�. *** //
	// ***  mysql�� BindParam�� �������� �ʽ��ϴ� *** //
	virtual void _BindParam()
	{
		HisUtil::CSPBase::_BindParam();

		// ***  sp �� ���� ������ BindParam() �� ȣ���� �ּ��� *** //
		// *** OUT param ������ �ݵ�� 0 �ʱ�ȭ �Ǿ� �ִ��� Ȯ���� �ּ��� *** //

		BindParam(m_avatarPk);		//mysql�� output�� �������� �ʽ��ϴ�.
	}

	// ***  CSPBase::_Return() ���� RETURN ���� ��� �ɴϴ�.(for mssql) *** //
	virtual BOOL _Return()
	{
		return HisUtil::CSPBase::_Return();	//for mssql
		//return TRUE;						//for mysql
	}

	// *** Fetch()�� ���� class ��/�ܺξּ��� ó���� �����ϴ�. *** //
	virtual void _Fetch()
	{
		//while (TRUE == m_rs.IsEOF())
		//{
		//	int id = GetFieldsValues(L"id");
		//	_bstr_t name = GetFieldsValues(L"name");
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

try {
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

		// *** Fetch()�� ���� class �ܺξּ��� ó���� �����ϴ�. *** //
		//EoF�̸� FALSE�� �����Ѵ�.
		virtual BOOL Fetch();

		//next ROW
		virtual void MoveNext();

		//���� Recordset�� ���...
		virtual void NextRecordset();	
		
		//Recordset���� �÷������� ������ �����´�.
		// ���ϰ��� NULL�� ��� ó���� ���� �����Ƿ�
		// DB���� IFNULL() ����ó���� �ʿ��մϴ�.
		virtual _variant_t GetFieldsValues(LPCWCHAR fileldname);

		virtual GAME_RESULT GetResult() = 0;

	protected:
	
		//���class �Ǵ� class�ܼ����� Fetch�� �����ؼ� Recordset���� ������ �� �ִ�.
		virtual void _Fetch() {};

		// ***  sp �� ���� ������ Append() �� ȣ���� �ּ��� *** //
		virtual void _AppendParameter();

		// ***  ADODB::adParamOutput ���� ������ ������ ���� ��� �ɴϴ�. *** //
		virtual void _BindParam() {};

		// ***  CSPBase::_Return() ���� RETURN ���� ��� �ɴϴ�.(for mssql) *** //
		virtual BOOL _Return();

		//sp ��
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
		////	sp ���� OUT �Ķ���͸� ���޵Ǵ� ����.
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
		int m_posGet;	//���� ������ ��º����� index( BindParam() ���� ���� )

		std::wstring m_storedProcName;	//sp��
		//CDBConnection* m_connection;

		CModule m_module;

	};

};//..namespace HisUtil {