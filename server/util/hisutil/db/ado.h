#pragma once


#pragma warning(push)
#pragma warning(disable:4146)

#import <C:\Program Files\Common Files\System\ado\msado15.dll> rename("EOF","adoEOF")

#pragma warning(pop)


namespace HisUtil {

	//필요없으면 지워라.
	// 레코드 셋 여는 목적 셋팅
	enum OPENFOR { QREAD, QFASTREAD, QRW, QAPPEND };
	enum { defaultCacheSize = 100 };



	//ADO 접속 실행 관련 기본 클래스
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


	//데이타 베이스 테이블과 메치되어 쿼리를 직접 날리는 클래스이다.
	//레코드 셋 단위로 데이타를 얻어오고, 테이블에 직접 데이타를 update 하기도 한다.
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



	// ADO Command object를 wrapping한 클래스이다.
	//
	// 이것으로 stored procedure를 호출하는 방법은 다음과 같다.
	// 1. PrepareSP로 호출할 stored procedure, active connection을 설정한다.
	// 2. Parameters 멤버로 입력 아규먼트를 설정한다.
	// 3. ExecuteSP로 준비된 stored procedure를 호출한다.
	// 4. Parameters 멤버로 출력 아규먼트를 구한다.
	// 예제는 다음과 같다.
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