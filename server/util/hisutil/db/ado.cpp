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

	//Ŀ�ؼ��� ���� �ִ°� ?
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
	// @Description : �����Ҷ� ���� ���ڵ������ Attach�Ѵ�.
	// @Argument : ADODB::_Recordset *RecordSet -> DB���ڵ��
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
	// @Description : ���ڵ� ���� ���� �Լ�. ������ ���� �ش� ���ڵ� ���� ������.
	// @Argument : CAdoConnection* pConn -> ADO ������ ��ü
	// @Argument : OPENFOR openFor -> ���ڵ� �� ���� ������
	// @Argument : LPCTSTR strSQL -> ������ ������
	// @Argument : ... -> �������� �ʿ��� ������~~~
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
			// �������� �ַ� ����ϴ� DB Read Access �ɼ�
			CursorType = ADODB::adOpenStatic;
			LockType = ADODB::adLockReadOnly;
			// RecordSet���� �����ϴ� Record ������ Client���� �����ϵ��� �Ѵ�.
			GetInterfacePtr()->PutCursorLocation(ADODB::adUseClient);// snapshot type���� record�� �б� ������, �̰� ���� ���̴�.
		}
		break;

		case QFASTREAD:
		{
			// �������� �ټ� ���ڵ带 ���� �ε��Ҷ� ����ϴ� �Լ�
			CursorType = ADODB::adOpenStatic;
			LockType = ADODB::adLockReadOnly;
			// RecordSet���� �����ϴ� Record ���餷�� Client���� �����ϵ��� �Ѵ�.
			GetInterfacePtr()->PutCursorLocation(ADODB::adUseClient);// snapshot type���� record�� �б� ������, �̰� ���� ���̴�.
			// Cache size�� �����Ѵ�.
			long Max_Open_Rows = GetInterfacePtr()->Properties->Item["Maximum Open Rows"];
			long Cache_Size;
			if (0 == Max_Open_Rows)
			{
				Cache_Size = defaultCacheSize;
				GetInterfacePtr()->CacheSize = Cache_Size;
			}
			else if (2 <= Max_Open_Rows)	// max_open_rows==1�� ��� ������ ��ġ�� ����.
			{
				Cache_Size = min(defaultCacheSize, Max_Open_Rows);
				GetInterfacePtr()->CacheSize = Cache_Size;
			}
		}
		break;

		case QRW:
		case QAPPEND:
		{
			// �������� �ַ� ����ϴ� DB Write Access �ɼ�
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
	// @Description : ���ڵ� ���� �ݴ��Լ�
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
	// @Description : ���ڵ� ���� ���������� üũ�ϴ� �Լ�
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
	// @Description : ���ڵ� ���� �����ϴ� �Լ�
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
	// @Description : ���ڵ� ���� ���ο� �߰��Ѵ�.
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
	// @Description : ���ڵ� ���� �����ϴ� �Լ�
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
	// @Description : ���ڵ���� Ư�� �ʵ��� ���� �����´�.
	// @Argument : LPCTSTR pszFieldName -> Ư�� �ʵ�
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
	// @Description : ���ڵ���� �����ϴ� �ʵ�� ��ġ�� �����Ѵ�.
	// @Argument : LPCTSTR pszFieldName -> Ư�� �ʵ�
	// @Argument : const _variant_t &value -> �ʵ��� ��ġ
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
	// @Description : �����Ҷ� ���� Command�� Attach�Ѵ�.
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
	// @Description : stored procedure�� ȣ���� �غ� �Ѵ�.
	//				ADO Connection, stored procedure name, inout argument �غ� �Ѵ�
	// @Argument : CAdoConnection* pCon -> ���ӵǾ��� DB
	// @Argument : LPCTSTR storedProcName ->  ������ ���ν��� �̸�
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
	// @Description : ���ν��� ȣ���Ҷ� �о���� �ʵ� ���ð� ������� ��ȯ�Ѵ�.
	// @Argument : string strParamName -> �ʵ� �̸�
	// @Argument : ADODB::DataTypeEnum adoParamType -> �ʵ� Ÿ��
	// @Argument : ong lParamDataLength -> �ʵ� ũ��
	// @Argument : ADODB::ParameterDirectionEnum adoParamDirection -> �ʵ��� Ÿ��
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
	// @Description : ���ν��� ȣ���Ҷ� �о���� �ʵ� ���ð� ������� ��ȯ�Ѵ�.
	// @Argument : string strParamName -> �ʵ� �̸�
	// @Argument : ADODB::DataTypeEnum adoParamType -> �ʵ� Ÿ��
	// @Argument : ong lParamDataLength -> �ʵ� ũ��
	// @Argument : ADODB::ParameterDirectionEnum adoParamDirection -> �ʵ��� Ÿ��
	// @Argument : const _variant_t &DefaultValue -> �ʵ� ��
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
	// @Description : ���ν��� ȣ���Ҷ� �о���� �ʵ� ���ð� ������� ��ȯ�Ѵ�.
	// @Argument : long *recordsAffected -> Stored Procedure�� ���� ������� Record�� ����
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
	// @Description : index�� ����Ű�� ��°�� parameter ���� �����Ѵ�. PrepareSP�� ȣ���� �Ŀ� ����� �� �ִ�.
	// @Argument : int index -> ���° parameter�� ���� ������ ��
	//			  0�� stored procedure�� return value��, ������ parameter�� 1-based index�̴�.
	// @Argument : const _variant_t &value -> ������ paramter ��
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
	// @Description : index�� ����Ű�� ��°�� paramter ���� ���Ѵ�. PrepareSP�� ȣ���� �Ŀ� ����� �� �ִ�.
	// @Argument : int index -> ���° parameter�� ���� ������ ��
	//			  0�� stored procedure�� return value��, ������ parameter�� 1-based index�̴�.
	// @author : 
	// @date : 
	// 
	_variant_t CAdoCommand::GetParam(int index)
	{
		return GetInterfacePtr()->Parameters->GetItem((long)index)->GetValue();
	}


};//..namespace HisUtil {