#include "StdAfx.h"
#include "ado.h"


namespace HisUtil {


	void CAdoConnection::Open()
	{
		Close();
		Connect();
	}

	void CAdoConnection::Connect()
	{
		GetInterfacePtr()->PutProvider(_bstr_t("sqloledb"));
		//GetInterfacePtr()->Open(m_DBConnectionInfo.m_strDBConnectInfo.c_str(), "", "", -1);
		//Provider=SQLOLEDB; Data Source=server_name_or_address; Initial Catalog=database_name; User ID=username; Password=password
	}

	void CAdoConnection::Close()
	{
		GetInterfacePtr()->Close();
	}

	//커넥션이 열려 있는가 ?
	bool CAdoConnection::IsOpen()
	{
		return ADODB::adStateClosed != GetInterfacePtr()->State;
	}

	long CAdoConnection::Execute(LPCTSTR lpszSQL, ...)
	{
		_variant_t	noofAffectedRecords;
		TCHAR		sqlText[1280];
		va_list		pArg;

		va_start(pArg, lpszSQL);
		_vstprintf_s(sqlText, lpszSQL, pArg);
		va_end(pArg);

		GetInterfacePtr()->Execute(sqlText, &noofAffectedRecords, -1);

		return noofAffectedRecords;
	}





	///////////////////////////////////////////////////////////////////////////////
	// @Class : CAdoRecordset
	// @Name : CAdoRecordset
	// @Description : Construction
	// @author : 
	// @date : 
	// 
	CAdoRecordset::CAdoRecordset()
	{
		CreateInstance(__uuidof(ADODB::Recordset));
	}


	///////////////////////////////////////////////////////////////////////////////
	// @Class : CAdoRecordset
	// @Name : CAdoRecordset
	// @Description : 생성할때 얻어온 레코드셋으로 Attach한다.
	// @Argument : ADODB::_Recordset *RecordSet -> DB레코드셋
	// @author : 
	// @date : 
	// 
	CAdoRecordset::CAdoRecordset(ADODB::_Recordset *RecordSet)
	{
		if (RecordSet)
		{
			Attach(RecordSet, true); // AddRef, not Attach
		}
	}


	///////////////////////////////////////////////////////////////////////////////
	// @Class : CAdoRecordset
	// @Name : ~CAdoRecordset
	// @Description : Destruction
	// @author : 
	// @date : 
	// 
	CAdoRecordset::~CAdoRecordset()
	{
	}


	///////////////////////////////////////////////////////////////////////////////
	// @Class : CAdoRecordset
	// @Name : Open
	// @Description : 레코드 셋을 여는 함수. 쿼리에 따라 해당 레코드 셋이 열린다.
	// @Argument : CAdoConnection* pConn -> ADO 실행할 객체
	// @Argument : OPENFOR openFor -> 레코드 셋 여는 목적값
	// @Argument : LPCTSTR strSQL -> 실행할 퀴리문
	// @Argument : ... -> 퀴리문에 필요한 변수들~~~
	// @author : 
	// @date : 
	// 
	void CAdoRecordset::Open(CAdoConnection* pConn, OPENFOR OpenFor, LPCTSTR lpszSQL, ...)
	{
		// Open DB Connection
		pConn->Open();

		_variant_t noofAffectedRecords;

		va_list argList;
		TCHAR	sqlText[1280];
		va_start(argList, lpszSQL);
		_vstprintf_s(sqlText, lpszSQL, argList);
		va_end(argList);

		ADODB::CursorTypeEnum CursorType;
		ADODB::LockTypeEnum LockType;

		switch (OpenFor)
		{
		case QREAD:
		{
			// 서버에서 주로 사용하는 DB Read Access 옵션
			CursorType = ADODB::adOpenStatic;
			LockType = ADODB::adLockReadOnly;
			// RecordSet에서 보유하는 Record 값들을 Client에서 저장하도록 한다.
			GetInterfacePtr()->PutCursorLocation(ADODB::adUseClient);// snapshot type으로 record를 읽기 떄문에, 이게 빠를 것이다.
		}
		break;

		case QFASTREAD:
		{
			// 서버에서 다수 레코드를 빨리 로딩할때 사용하는 함수
			CursorType = ADODB::adOpenStatic;
			LockType = ADODB::adLockReadOnly;
			// RecordSet에서 보유하는 Record 값들ㅇ르 Client에서 저장하도록 한다.
			GetInterfacePtr()->PutCursorLocation(ADODB::adUseClient);// snapshot type으로 record를 읽기 떄문에, 이게 빠를 것이다.
			// Cache size를 조정한다.
			long Max_Open_Rows = GetInterfacePtr()->Properties->Item["Maximum Open Rows"];
			long Cache_Size;
			if (0 == Max_Open_Rows)
			{
				Cache_Size = defaultCacheSize;
				GetInterfacePtr()->CacheSize = Cache_Size;
			}
			else if (2 <= Max_Open_Rows)	// max_open_rows==1인 경우 세팅할 가치가 없다.
			{
				Cache_Size = min(defaultCacheSize, Max_Open_Rows);
				GetInterfacePtr()->CacheSize = Cache_Size;
			}
		}
		break;

		case QRW:
		case QAPPEND:
		{
			// 서버에서 주로 사용하는 DB Write Access 옵션
			CursorType = ADODB::adOpenStatic;
			LockType = ADODB::adLockReadOnly;
		}
		break;
		}

		GetInterfacePtr()->Open(sqlText, (ADODB::_Connection*)(*pConn), CursorType, LockType, -1);
	}


	///////////////////////////////////////////////////////////////////////////////
	// @Class : CAdoRecordset
	// @Name : Open
	// @Description : 레코드 셋을 닫는함수
	// @author : 
	// @date : 
	// 
	void CAdoRecordset::Close()
	{
		GetInterfacePtr()->Close();
	}


	///////////////////////////////////////////////////////////////////////////////
	// @Class : CAdoRecordset
	// @Name : Open
	// @Description : 레코드 셋이 마지막인지 체크하는 함수
	// @author : 
	// @date : 
	// 
	bool CAdoRecordset::IsEOF()
	{
		return GetInterfacePtr()->adoEOF ? true : false;
	}


	///////////////////////////////////////////////////////////////////////////////
	// @Class : CAdoRecordset
	// @Name : Update
	// @Description : 레코드 셋을 갱신하는 함수
	// @author : 
	// @date : 
	// 
	void CAdoRecordset::Update()
	{
		GetInterfacePtr()->Update();
	}


	///////////////////////////////////////////////////////////////////////////////
	// @Class : CAdoRecordset
	// @Name : AddNew
	// @Description : 레코드 셋을 새로운 추가한다.
	// @author : 
	// @date : 
	// 
	void CAdoRecordset::AddNew()
	{
		GetInterfacePtr()->AddNew();
	}


	///////////////////////////////////////////////////////////////////////////////
	// @Class : CAdoRecordset
	// @Name : Open
	// @Description : 레코드 셋을 삭제하는 함수
	// @author : 
	// @date : 
	// 
	void CAdoRecordset::Delete()
	{
		GetInterfacePtr()->Delete(ADODB::adAffectCurrent);
	}


	///////////////////////////////////////////////////////////////////////////////
	// @Class : CAdoRecordset
	// @Name : GetFieldValue
	// @Description : 레코드셋의 특정 필드의 값을 가져온다.
	// @Argument : LPCTSTR pszFieldName -> 특정 필드
	// @author : 
	// @date : 
	// 
	_variant_t CAdoRecordset::GetFieldValue(LPCTSTR pszFieldName)
	{
		return GetInterfacePtr()->GetCollect(pszFieldName);
	}


	///////////////////////////////////////////////////////////////////////////////
	// @Class : CAdoRecordset
	// @Name : SetFieldValue
	// @Description : 레코드셋을 세팅하는 필드와 수치를 세팅한다.
	// @Argument : LPCTSTR pszFieldName -> 특정 필드
	// @Argument : const _variant_t &value -> 필드의 수치
	// @author : 
	// @date : 
	// 
	void CAdoRecordset::SetFieldValue(LPCTSTR pszFieldName, const _variant_t &value)
	{
		GetInterfacePtr()->PutCollect(pszFieldName, value);
	}




	///////////////////////////////////////////////////////////////////////////////
	// @Class : CAdoCommand
	// @Name : CAdoCommand
	// @Description : Construction
	// @author : 
	// @date : 
	// 
	CAdoCommand::CAdoCommand()
	{
		CreateInstance(__uuidof(ADODB::Command));
	}


	///////////////////////////////////////////////////////////////////////////////
	// @Class : CAdoCommand
	// @Name : CAdoCommand
	// @Description : 생성할때 얻어온 Command로 Attach한다.
	// @Argument : ADODB::_Command * Command -> Command
	// @author : 
	// @date : 
	// 
	CAdoCommand::CAdoCommand(ADODB::_Command * Command)
	{
		if (Command)
			Attach(Command, true);		// AddRef, not Attach
	}


	///////////////////////////////////////////////////////////////////////////////
	// @Class : CAdoCommand
	// @Name : ~CAdoCommand
	// @Description : Destruction
	// @author : 
	// @date : 
	// 
	CAdoCommand::~CAdoCommand()
	{
	}


	///////////////////////////////////////////////////////////////////////////////
	// @Class : CAdoCommand
	// @Name : PrepareSP
	// @Description : stored procedure를 호출할 준비를 한다.
	//				ADO Connection, stored procedure name, inout argument 준비를 한다
	// @Argument : CAdoConnection* pCon -> 접속되어진 DB
	// @Argument : LPCTSTR storedProcName ->  실행할 프로시져 이름
	// @author : 
	// @date : 
	//
	void CAdoCommand::PrepareSP(CAdoConnection* pConnection, std::wstring strStoredProcName)
	{
		GetInterfacePtr()->ActiveConnection = *pConnection;
		GetInterfacePtr()->CommandText = strStoredProcName.c_str();
		GetInterfacePtr()->CommandType = ADODB::adCmdStoredProc;
	}


	///////////////////////////////////////////////////////////////////////////////
	// @Class : CAdoCommand
	// @Name : AppendParameter
	// @Description : 프로시져 호출할때 읽어들일 필드 세팅과 결과값을 반환한다.
	// @Argument : string strParamName -> 필드 이름
	// @Argument : ADODB::DataTypeEnum adoParamType -> 필드 타입
	// @Argument : ong lParamDataLength -> 필드 크기
	// @Argument : ADODB::ParameterDirectionEnum adoParamDirection -> 필드명령 타입
	// @author : 
	// @date : 
	//
	ADODB::_ParameterPtr CAdoCommand::AppendParameter(std::wstring strParamName, ADODB::DataTypeEnum adoParamType, ADODB::ParameterDirectionEnum adoParamDirection, long lParamDataLength)
	{
		ADODB::_ParameterPtr ret;
		ret = GetInterfacePtr()->CreateParameter(strParamName.c_str(), adoParamType, adoParamDirection, lParamDataLength, _variant_t());
		GetInterfacePtr()->Parameters->Append(ret);
		return ret;
	}


	///////////////////////////////////////////////////////////////////////////////
	// @Class : CAdoCommand
	// @Name : AppendParameter
	// @Description : 프로시져 호출할때 읽어들일 필드 세팅과 결과값을 반환한다.
	// @Argument : string strParamName -> 필드 이름
	// @Argument : ADODB::DataTypeEnum adoParamType -> 필드 타입
	// @Argument : ong lParamDataLength -> 필드 크기
	// @Argument : ADODB::ParameterDirectionEnum adoParamDirection -> 필드명령 타입
	// @Argument : const _variant_t &DefaultValue -> 필드 값
	// @author : 
	// @date : 
	//
	ADODB::_ParameterPtr CAdoCommand::AppendParameter(std::wstring strParamName, ADODB::DataTypeEnum adoParamType, ADODB::ParameterDirectionEnum adoParamDirection, long lParamDataLength, const _variant_t &DefaultValue)
	{
		ADODB::_ParameterPtr ret;
		ret = AppendParameter(strParamName.c_str(), adoParamType, adoParamDirection, lParamDataLength);
		ret->Value = DefaultValue;
		return ret;
	}


	///////////////////////////////////////////////////////////////////////////////
	// @Class : CAdoCommand
	// @Name : ExecuteSP
	// @Description : 프로시져 호출할때 읽어들일 필드 세팅과 결과값을 반환한다.
	// @Argument : long *recordsAffected -> Stored Procedure에 의해 영향받은 Record의 갯수
	// @author : 
	// @date : 
	// 
	ADODB::_RecordsetPtr CAdoCommand::ExecuteSP(long *RecordsAffected)
	{
		ADODB::_RecordsetPtr ret;
		try{
			_variant_t ra2 = 0L;
			ret = GetInterfacePtr()->Execute(&ra2, NULL, ADODB::adCmdStoredProc);
			if (RecordsAffected)
				*RecordsAffected = ra2;
		}
		catch (_com_error &e)
		{
#ifdef _WINDOWS
			AfxMessageBox(e.Description());
#else
			//LOGEVENT("HG_RED", _T("DB Error = %s"), e.Description());
			wprintf_s(L"DB Error = %s\n", e.Description());
#endif _WINDOWS
		}

		return ret;
	}


	///////////////////////////////////////////////////////////////////////////////
	// @Class : CAdoCommand
	// @Name : SetParam
	// @Description : index가 가리키는 번째의 parameter 값을 설정한다. PrepareSP를 호출한 후에 사용할 수 있다.
	// @Argument : int index -> 몇번째 parameter의 값을 설정할 것
	//			  0은 stored procedure의 return value를, 나머지 parameter는 1-based index이다.
	// @Argument : const _variant_t &value -> 설정할 paramter 값
	// @author : 
	// @date : 
	// 
	void CAdoCommand::SetParam(int index, const _variant_t &value)
	{
		GetInterfacePtr()->Parameters->Item[(long)index]->PutValue(value);
	}


	///////////////////////////////////////////////////////////////////////////////
	// @Class : CAdoCommand
	// @Name : GetParam
	// @Description : index가 가리키는 번째의 paramter 값을 구한다. PrepareSP를 호출한 후에 사용할 수 있다.
	// @Argument : int index -> 몇번째 parameter의 값을 설정할 것
	//			  0은 stored procedure의 return value를, 나머지 parameter는 1-based index이다.
	// @author : 
	// @date : 
	// 
	_variant_t CAdoCommand::GetParam(int index)
	{
		return GetInterfacePtr()->Parameters->GetItem((long)index)->GetValue();
	}


};//..namespace HisUtil {