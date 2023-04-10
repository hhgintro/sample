#pragma once


#pragma warning(push)
#pragma warning(disable:4146)

#import <C:\Program Files\Common Files\System\ado\msado15.dll> rename("EOF","adoEOF")

#pragma warning(pop)


namespace HisUtil {

	//�ʿ������ ������.
	// ���ڵ� �� ���� ���� ����
	enum OPENFOR { QREAD, QFASTREAD, QRW, QAPPEND };
	enum { defaultCacheSize = 100 };



	//ADO ���� ���� ���� �⺻ Ŭ����
	class CAdoConnection : public ADODB::_ConnectionPtr
	{
	public:
		CAdoConnection() {}
		virtual ~CAdoConnection() {}


		void			Open();
		void			Connect();
		void			Close();
		bool			IsOpen();
		long			Execute(LPCTSTR lpszSQL, ...);

		void SetConnectStr(WCHAR* wzConnStr) { _tcscpy_s(m_wzConnStr, wzConnStr); }


	private:

		WCHAR m_wzConnStr[MAX_PATH];
	};


	//����Ÿ ���̽� ���̺�� ��ġ�Ǿ� ������ ���� ������ Ŭ�����̴�.
	//���ڵ� �� ������ ����Ÿ�� ������, ���̺� ���� ����Ÿ�� update �ϱ⵵ �Ѵ�.
	class CAdoRecordset : public ADODB::_RecordsetPtr
	{
	private:

	public:
		CAdoRecordset();
		CAdoRecordset(ADODB::_Recordset *rc);
		~CAdoRecordset();

		void			Open(CAdoConnection* pCon, OPENFOR OpenFor, LPCTSTR lpszSQL, ...);
		void			Close();
		bool			IsEOF();
		void			Update();
		void			AddNew();
		void			Delete();

		_variant_t		GetFieldValue(LPCTSTR pszFieldName);
		void			SetFieldValue(LPCTSTR pszFieldName, const _variant_t &value);

		__declspec(property(get = GetFieldValue, put = SetFieldValue)) _variant_t fvs[];

	};



	// ADO Command object�� wrapping�� Ŭ�����̴�.
	//
	// �̰����� stored procedure�� ȣ���ϴ� ����� ������ ����.
	// 1. PrepareSP�� ȣ���� stored procedure, active connection�� �����Ѵ�.
	// 2. Parameters ����� �Է� �ƱԸ�Ʈ�� �����Ѵ�.
	// 3. ExecuteSP�� �غ�� stored procedure�� ȣ���Ѵ�.
	// 4. Parameters ����� ��� �ƱԸ�Ʈ�� ���Ѵ�.
	// ������ ������ ����.
	//	CAdoConnection db;
	//	db.Open("SERVER=server4;DATABASE=baehj;trusted_connection=yes");
	//	CAdoCommand co;
	//	co.PrepareSP(db,"sp_sum");
	//	co.Parameters[1]=1L;
	//	co.Parameters[2]=2L;
	//	co.ExecuteSP();
	//	long x=co.Parameters[3];
	class CAdoCommand : public ADODB::_CommandPtr
	{
	private:

	public:
		CAdoCommand();
		CAdoCommand(ADODB::_Command *conn);
		~CAdoCommand();

		void PrepareSP(CAdoConnection* pConnection, std::wstring strStoredProcName);

		ADODB::_ParameterPtr AppendParameter(std::wstring strParamName, ADODB::DataTypeEnum adoParamType, ADODB::ParameterDirectionEnum adoParamDirection, long lParamDataLength);
		ADODB::_ParameterPtr AppendParameter(std::wstring strParamName, ADODB::DataTypeEnum adoParamType, ADODB::ParameterDirectionEnum adoParamDirection, long lParamDataLength, const _variant_t &DefaultValue);

		ADODB::_RecordsetPtr ExecuteSP(long *RecordsAffected = NULL);

		_variant_t GetParam(int index);
		void SetParam(int index, const _variant_t &value);
		__declspec(property(get = GetParam, put = SetParam)) _variant_t Parameters[];
	};
};//..namespace HisUtil {