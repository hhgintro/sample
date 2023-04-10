#pragma once

#import "c:\Program Files\Common Files\system\ado\msado15.dll" rename("EOF", "adoEOF")

namespace HisUtil {

	//================================================
	//CAdoConnection
	// ***** CAdoConnection ��ü�� ::CoInitialize(NULL)�� ���� ȣ��Ǿ�� �մϴ�. *****//
	//================================================

	//ADO ���� ���� ���� �⺻ Ŭ����
	class CAdoConnection : public ADODB::_ConnectionPtr
	{
	public:
		CAdoConnection();
		~CAdoConnection();

		void SetLastError(_com_error& e);
		void SetLastError();

		/*������ ���� �̸� �� ���� �⺻ ����̹� �� ���� ���� �ʾҽ��ϴ�*/
		//�ش� ODBC ����̺긦 ��ġ�ϼ���. 64bit���� Ȯ�� ���ϼ���.
		//(mariadb 64bit odbc driver ��ġ�ؼ� �ذ���)

		//mssql
		//bstr_t szConn = L"Provider=sqloledb;Data Source=127.0.0.1,1433;Network Library=DBMSSOCN;Initial Catalog=world;User ID=hhg;Password=1001"
		//mysql
		//bstr_t szConn = L"Driver={MySQL ODBC 5.3 Unicode Driver};server=127.0.0.1;port=3306;Database=world;User ID=hhg;Password=1001;";
		//mariaDB: not working NextRecordset
		//bstr_t szConn = L"Driver={MariaDB ODBC 2.0 Driver};server=127.0.0.1;port=3306;Database=world;User ID=hhg;Password=1001;";
		BOOL Open(WCHAR* wzConnStr);
		BOOL Open();
		BOOL IsOpened();

		void Close();


	private:
		//ADODB::_ConnectionPtr m_pAdoConn;

		std::wstring m_wzConnStr;
	};



	//================================================
	//CAdoRecordset
	//================================================

	class CAdoRecordset : public ADODB::_RecordsetPtr
	{
	public:
		CAdoRecordset();
		~CAdoRecordset();


		bool IsEOF();
		void MoveNext();
		void NextRecordset();

		_variant_t GetFieldsValues(LPCWCHAR fieldname);


		void SetRecordSet(ADODB::_RecordsetPtr pAdoRs) { m_pAdoRs = pAdoRs; }
		//void SetRecordSet(ADODB::_RecordsetPtr pAdoRs) { GetInterfacePtr() = pAdoRs; }

	private:
		ADODB::_RecordsetPtr m_pAdoRs = NULL;

	};



	//================================================
	//CAdoCommand
	//================================================

	class CAdoCommand : public ADODB::_CommandPtr
	{
	public:
		CAdoCommand();
		~CAdoCommand();

		void Prepare(CAdoConnection& conn, const wchar_t* strStoredProcName);
		BOOL Execute(CAdoRecordset& rs);


		void SetLastError(_com_error& e);
		void SetLastError();

		ADODB::_ParameterPtr AppendReturn(ADODB::ParameterDirectionEnum adoParamDirection, INT32 values);

		ADODB::_ParameterPtr AppendParameter(ADODB::ParameterDirectionEnum adoParamDirection, INT8 values);
		ADODB::_ParameterPtr AppendParameter(ADODB::ParameterDirectionEnum adoParamDirection, UINT8 values);
		ADODB::_ParameterPtr AppendParameter(ADODB::ParameterDirectionEnum adoParamDirection, INT16 values);
		ADODB::_ParameterPtr AppendParameter(ADODB::ParameterDirectionEnum adoParamDirection, UINT16 values);
		ADODB::_ParameterPtr AppendParameter(ADODB::ParameterDirectionEnum adoParamDirection, INT32 values);
		ADODB::_ParameterPtr AppendParameter(ADODB::ParameterDirectionEnum adoParamDirection, UINT32 values);
		ADODB::_ParameterPtr AppendParameter(ADODB::ParameterDirectionEnum adoParamDirection, INT64 values);
		ADODB::_ParameterPtr AppendParameter(ADODB::ParameterDirectionEnum adoParamDirection, UINT64 values);
		ADODB::_ParameterPtr AppendParameter(ADODB::ParameterDirectionEnum adoParamDirection, float values);
		ADODB::_ParameterPtr AppendParameter(ADODB::ParameterDirectionEnum adoParamDirection, double values);
		ADODB::_ParameterPtr AppendParameter(ADODB::ParameterDirectionEnum adoParamDirection, const char* values, int length);
		ADODB::_ParameterPtr AppendParameter(ADODB::ParameterDirectionEnum adoParamDirection, const wchar_t* values, int length);
		ADODB::_ParameterPtr AppendParameter(ADODB::ParameterDirectionEnum adoParamDirection, std::string& values, int length);
		ADODB::_ParameterPtr AppendParameter(ADODB::ParameterDirectionEnum adoParamDirection, std::wstring& values, int length);


		_variant_t GetFieldsValues(LPCWCHAR fieldname);
		_variant_t GetFieldsValues(int index);

	private:
		//ADODB::_CommandPtr m_pAdoCmd = NULL;
		std::wstring m_storedProcName;	//sp��

	};

};//..namespace HisUtil {