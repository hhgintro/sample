#include "stdafx.h"
#include "dbconnect.h"

//============================================================================
//Ư�̻��� : mysql�� OUTPUT�� RETURN �� �������� �ʽ��ϴ�.
//			mssql�� RecordSet�� ��� �޾ƾ� OUTPUT�� RETURN�� ���� �� �ֽ��ϴ�.
//					��, mssql�� connection���� PutCursorLocation(ADODB::adUseClient)�� ������ �ָ�
//					������ ������� �޾ƿ� �� �ֽ��ϴ�.
//============================================================================


namespace HisUtil {

	void CAdoConnection::SetLastError(_com_error& e)
	{
		LOGEVENT("HG_RED", _T("------------------------------"));
		LOGEVENT("HG_RED", _T("ADODB Connect Error"));
		LOGEVENT("HG_RED", _T("------------------------------"));
		LOGEVENT("HG_RED", _T("ConnStr : %s"), m_wzConnStr.c_str());
		LOGEVENT("HG_RED", _T("Error Code : %x"), e.Error());
		LOGEVENT("HG_RED", _T("Source : %s"), (wchar_t*)e.Source());
		LOGEVENT("HG_RED", _T("Description : %s"), (wchar_t*)e.Description());
		LOGEVENT("HG_RED", _T("------------------------------"));
	}

	void CAdoConnection::SetLastError()
	{
		LOGEVENT("HG_RED", _T("------------------------------"));
		LOGEVENT("HG_RED", _T("ADODB Connect Error"));
		LOGEVENT("HG_RED", _T("------------------------------"));
		LOGEVENT("HG_RED", _T("ConnStr : %s"), m_wzConnStr.c_str());
		LOGEVENT("HG_RED", _T("Description : unknown error"));
		LOGEVENT("HG_RED", _T("------------------------------"));
	}

	//================================================
	//CAdoConnection
	//================================================

	CAdoConnection::CAdoConnection()
		: /*m_pAdoConn(NULL),*/ m_wzConnStr(L"")/*, m_bOpened(FALSE)*/
	{
		//m_pAdoConn.CreateInstance(__uuidof(ADODB::Connection));
		CreateInstance(__uuidof(ADODB::Connection));
	}
	CAdoConnection::~CAdoConnection()
	{
		Close();

		//���� Release�� �ʿ䰡 ������...������ Release()�ϸ� ���Ἥ ����â ��ϴ�.
		////if (m_pAdoConn)		m_pAdoConn.Release();
		//if (GetInterfacePtr())	GetInterfacePtr()->Release();
	}

	//mssql sample
	//"Provider=sqloledb;Data Source=127.0.0.1,1433;Network Library=DBMSSOCN;Initial Catalog=world;User ID=hhg;Password=1001"
	//mysql sample
	//"Driver={MySQL ODBC 5.3 Unicode Driver};server=127.0.0.1;port=3306;Database=world;User ID=hhg;Password=1001;";
	BOOL CAdoConnection::Open()
	{
		if (true == m_wzConnStr.empty())
			return FALSE;
		return Open((WCHAR*)m_wzConnStr.c_str());
	}

	BOOL CAdoConnection::Open(WCHAR* wzConnStr)
	{
		m_wzConnStr = wzConnStr;


		try {

			//HRESULT hRes = m_pAdoConn->Open(wzConnStr, L"", L"", ADODB::adConnectUnspecified);
			HRESULT hRes = GetInterfacePtr()->Open(wzConnStr, L"", L"", ADODB::adConnectUnspecified);
			if (FAILED(hRes))
			{
				LOGEVENT("HG_RED", _T("Error Opening Database object using ADO _ConnectionPtr(%s)"), wzConnStr);
				Close();
				return FALSE;
			}

			//m_bOpened = TRUE;
		}
		catch (_com_error& e) {
			SetLastError(e);
			return FALSE;
		}
		catch (...) {
			SetLastError();
			return FALSE;
		}

		//recordset�� ��� �о�� RETURN�� OUTPUT�� ������ �� �ִµ�,
		//PutCursorLocation(adUseClient) �� ������ �ָ� ������ ������� �޾ƿ� �� �ִ�.
		GetInterfacePtr()->PutCursorLocation(ADODB::adUseClient);
		return TRUE;
	}

	BOOL CAdoConnection::IsOpened()
	{
		return (ADODB::adStateClosed != GetInterfacePtr()->GetState());
	}

	void CAdoConnection::Close()
	{
		//if (IsOpened())		m_pAdoConn->Close();
		if (IsOpened())
			GetInterfacePtr()->Close();
	}





	//================================================
	//CAdoRecordset
	//================================================

	CAdoRecordset::CAdoRecordset()
	{
		m_pAdoRs.CreateInstance(__uuidof(ADODB::Recordset));
		//CreateInstance(__uuidof(ADODB::Recordset));
	}
	CAdoRecordset::~CAdoRecordset()
	{
		//���� Release�� �ʿ䰡 ������...������ Release()�ϸ� ���Ἥ ����â ��ϴ�.
		//if (m_pAdoRs)		m_pAdoRs.Release();
	}

	//void Close()
	//{
	//	m_pAdoRs->Close();
	//}

	bool CAdoRecordset::IsEOF()
	{
		if (!m_pAdoRs) return false;
		return m_pAdoRs->adoEOF ? true : false;
		//return GetInterfacePtr()->adoEOF ? true : false;
	}

	void CAdoRecordset::MoveNext()
	{
		m_pAdoRs->MoveNext();
		//GetInterfacePtr()->MoveNext();
	}

	void CAdoRecordset::NextRecordset()
	{
		//m_pAdoRs = m_pAdoRs->NextRecordset(NULL);
		SetRecordSet(m_pAdoRs->NextRecordset(NULL));
		//SetRecordSet(GetInterfacePtr()->NextRecordset(NULL));
	}

	_variant_t CAdoRecordset::GetFieldsValues(LPCWCHAR fieldname)
	{
		////get column name
		//int cnt = m_pAdoRs->Fields->GetCount();
		//ADODB::FieldPtr pvObject = NULL;
		//VARIANT vIntegerType;
		//vIntegerType.vt = VT_I2; //Variant type for Integer
		////vIntegerType.intVal = 1;
		//for(int i=0; i<cnt; ++i)
		//{
		//	vIntegerType.intVal = i;
		//	m_pAdoRs->Fields->get_Item(vIntegerType, &pvObject);
		//	_bstr_t bstrVal = pvObject->GetName();
		//	//printf("%s\n", (char*)bstrVal);
		//	//_variant_t tmp = m_pAdoRs->Fields->GetItem(vIntegerType)->Value;
		//	_variant_t tmp = m_pAdoRs->Fields->Item[bstrVal]->Value;
		//	printf("=%s:%s\n", (char*)bstrVal, (char*)(_bstr_t)tmp);
		//}

		//DataTypeEnum type1 = m_pAdoRs->Fields->Item[fieldname]->Type;
		//_variant_t tmp = m_pAdoRs->Fields->Item[fieldname]->Value;
		return m_pAdoRs->Fields->Item[fieldname]->Value;
		//return GetInterfacePtr()->Fields->Item[fieldname]->Value;
	}





	//================================================
	//CAdoCommand
	//================================================
	void CAdoCommand::SetLastError(_com_error& e)
	{
		LOGEVENT("HG_RED", _T("------------------------------"));
		LOGEVENT("HG_RED", _T("ADODB Command Error"));
		LOGEVENT("HG_RED", _T("------------------------------"));
		LOGEVENT("HG_RED", _T("sp : %s"), m_storedProcName.c_str());
		LOGEVENT("HG_RED", _T("Error Code : %x"), e.Error());
		LOGEVENT("HG_RED", _T("Source : %s"), (wchar_t*)e.Source());
		LOGEVENT("HG_RED", _T("Description : %s"), (wchar_t*)e.Description());
		LOGEVENT("HG_RED", _T("------------------------------"));
	}

	void CAdoCommand::SetLastError()
	{
		LOGEVENT("HG_RED", _T("------------------------------"));
		LOGEVENT("HG_RED", _T("ADODB Command Error"));
		LOGEVENT("HG_RED", _T("------------------------------"));
		LOGEVENT("HG_RED", _T("sp : %s"), m_storedProcName.c_str());
		LOGEVENT("HG_RED", _T("Description : unknown error"));
		LOGEVENT("HG_RED", _T("------------------------------"));
	}

	CAdoCommand::CAdoCommand()
	{
		//m_pAdoCmd.CreateInstance(__uuidof(ADODB::Command));
		CreateInstance(__uuidof(ADODB::Command));
	}
	CAdoCommand::~CAdoCommand()
	{
		//���� Release�� �ʿ䰡 ������...������ Release()�ϸ� ���Ἥ ����â ��ϴ�.
		//if (m_pAdoCmd)		m_pAdoCmd.Release();
		//GetInterfacePtr()->Release();
	}

	void CAdoCommand::Prepare(CAdoConnection& conn, const wchar_t* strStoredProcName)
	{
		//m_pAdoCmd->CommandType = ADODB::adCmdStoredProc;
		//m_pAdoCmd->CommandText = strStoredProcName;
		//m_pAdoCmd->ActiveConnection = conn;// ->GetConnect();
		GetInterfacePtr()->CommandType = ADODB::adCmdStoredProc;
		GetInterfacePtr()->CommandText = strStoredProcName;
		GetInterfacePtr()->ActiveConnection = conn;

		m_storedProcName = strStoredProcName;
	}

	BOOL CAdoCommand::Execute(CAdoRecordset& rs)
	{
		//int i_id = 9;
		//std::wstring i_name = L"hhg";

		//int o_id = 0;
		//std::wstring o_name = L"";

		//GetInterfacePtr()->Parameters->Append(GetInterfacePtr()->CreateParameter(L"@", ADODB::adInteger, ADODB::adParamReturnValue, 4));
		//GetInterfacePtr()->Parameters->Append(GetInterfacePtr()->CreateParameter(L"@", ADODB::adInteger, ADODB::adParamInput, 4, i_id));
		//GetInterfacePtr()->Parameters->Append(GetInterfacePtr()->CreateParameter(L"@", ADODB::adVarWChar, ADODB::adParamInput, 100, i_name.c_str()));
		//GetInterfacePtr()->Parameters->Append(GetInterfacePtr()->CreateParameter(L"@", ADODB::adInteger, ADODB::adParamOutput, 4, o_id));
		//GetInterfacePtr()->Parameters->Append(GetInterfacePtr()->CreateParameter(L"@", ADODB::adVarWChar, ADODB::adParamOutput, 100, o_name.c_str()));

		//HRESULT hr;
		try {
			//Execute�� Rocordset�� �����ϸ� RETURN�� OUTPUT�� ���� ���Ѵ�.
			//PutCursorLocation(ADODB::adUseClient)�� �����ϸ� ���� �� �ִ�.
			//ADODB::_RecordsetPtr pAdoRs = m_pAdoCmd->Execute(NULL, NULL, ADODB::adCmdStoredProc);
			//hr = GetInterfacePtr()->Execute(NULL, NULL, NULL);
			ADODB::_RecordsetPtr pAdoRs = GetInterfacePtr()->Execute(NULL, NULL, NULL);
			rs.SetRecordSet(pAdoRs);

			//while(pAdoRs)
			//{
			//	pAdoRs = pAdoRs->NextRecordset(NULL);
			//}
		}
		catch (_com_error& e) {
			SetLastError(e);
			return FALSE;
		}
		catch (...) {
			SetLastError();
			return FALSE;
		}

		//for (int cnt = 0; cnt < GetInterfacePtr()->GetParameters()->GetCount(); ++cnt)
		//{
		//	ADODB::_ParameterPtr pvObject = NULL;
		//	VARIANT vIntegerType;
		//	vIntegerType.vt = VT_I2; //Variant type for Integer
		//	vIntegerType.intVal = cnt;
		//	GetInterfacePtr()->GetParameters()->get_Item(vIntegerType, &pvObject);
		//	_variant_t tmp1 = pvObject->Value;

		//	//_variant_t tmp1 = m_cmd.GetFieldsValues(cnt);
		//	switch (tmp1.vt)
		//	{
		//	case VT_BSTR:
		//		wprintf(L"output value(%d): %s\n", cnt, tmp1.bstrVal);
		//		break;
		//	default:
		//		wprintf(L"output value(%d): %d\n", cnt, tmp1.iVal);
		//		break;
		//	}
		//}
		return TRUE;
	}


	ADODB::_ParameterPtr CAdoCommand::AppendReturn(ADODB::ParameterDirectionEnum adoParamDirection, INT32 values)
	{
		ADODB::_ParameterPtr ret;
		//ret = m_pAdoCmd->CreateParameter(L"@param", ADODB::adTinyInt, adoParamDirection, sizeof(values), values);
		//m_pAdoCmd->Parameters->Append(ret);
		ret = GetInterfacePtr()->CreateParameter(L"return", ADODB::adInteger, adoParamDirection, sizeof(values));
		GetInterfacePtr()->Parameters->Append(ret);
		return ret;
	}

	ADODB::_ParameterPtr CAdoCommand::AppendParameter(ADODB::ParameterDirectionEnum adoParamDirection, INT8 values)
	{
		ADODB::_ParameterPtr ret;
		//ret = m_pAdoCmd->CreateParameter(L"@param", ADODB::adTinyInt, adoParamDirection, sizeof(values), values);
		//m_pAdoCmd->Parameters->Append(ret);
		ret = GetInterfacePtr()->CreateParameter(L"@param", ADODB::adTinyInt, adoParamDirection, sizeof(values), values);
		GetInterfacePtr()->Parameters->Append(ret);
		return ret;
	}
	ADODB::_ParameterPtr CAdoCommand::AppendParameter(ADODB::ParameterDirectionEnum adoParamDirection, UINT8 values)
	{
		ADODB::_ParameterPtr ret;
		ret = GetInterfacePtr()->CreateParameter(L"@param", ADODB::adUnsignedTinyInt, adoParamDirection, sizeof(values), values);
		GetInterfacePtr()->Parameters->Append(ret);
		return ret;
	}
	ADODB::_ParameterPtr CAdoCommand::AppendParameter(ADODB::ParameterDirectionEnum adoParamDirection, INT16 values)
	{
		ADODB::_ParameterPtr ret;
		ret = GetInterfacePtr()->CreateParameter(L"@param", ADODB::adSmallInt, adoParamDirection, sizeof(values), values);
		GetInterfacePtr()->Parameters->Append(ret);
		return ret;
	}
	ADODB::_ParameterPtr CAdoCommand::AppendParameter(ADODB::ParameterDirectionEnum adoParamDirection, UINT16 values)
	{
		ADODB::_ParameterPtr ret;
		ret = GetInterfacePtr()->CreateParameter(L"@param", ADODB::adUnsignedSmallInt, adoParamDirection, sizeof(values), values);
		GetInterfacePtr()->Parameters->Append(ret);
		return ret;
	}
	ADODB::_ParameterPtr CAdoCommand::AppendParameter(ADODB::ParameterDirectionEnum adoParamDirection, INT32 values)
	{
		ADODB::_ParameterPtr ret;
		ret = GetInterfacePtr()->CreateParameter(L"@param", ADODB::adInteger, adoParamDirection, sizeof(values), values);
		GetInterfacePtr()->Parameters->Append(ret);
		return ret;
	}
	ADODB::_ParameterPtr CAdoCommand::AppendParameter(ADODB::ParameterDirectionEnum adoParamDirection, UINT32 values)
	{
		ADODB::_ParameterPtr ret;
		ret = GetInterfacePtr()->CreateParameter(L"@param", ADODB::adUnsignedInt, adoParamDirection, sizeof(values), values);
		GetInterfacePtr()->Parameters->Append(ret);
		return ret;
	}
	ADODB::_ParameterPtr CAdoCommand::AppendParameter(ADODB::ParameterDirectionEnum adoParamDirection, INT64 values)
	{
		ADODB::_ParameterPtr ret;
		ret = GetInterfacePtr()->CreateParameter(L"@param", ADODB::adBigInt, adoParamDirection, sizeof(values), values);
		GetInterfacePtr()->Parameters->Append(ret);
		return ret;
	}
	ADODB::_ParameterPtr CAdoCommand::AppendParameter(ADODB::ParameterDirectionEnum adoParamDirection, UINT64 values)
	{
		ADODB::_ParameterPtr ret;
		ret = GetInterfacePtr()->CreateParameter(L"@param", ADODB::adUnsignedBigInt, adoParamDirection, sizeof(values), values);
		GetInterfacePtr()->Parameters->Append(ret);
		return ret;
	}
	ADODB::_ParameterPtr CAdoCommand::AppendParameter(ADODB::ParameterDirectionEnum adoParamDirection, float values)
	{
		ADODB::_ParameterPtr ret;
		ret = GetInterfacePtr()->CreateParameter(L"@param", ADODB::adDouble, adoParamDirection, sizeof(values), values);
		if(ADODB::adParamInput == adoParamDirection)
		GetInterfacePtr()->Parameters->Append(ret);
		return ret;
	}
	ADODB::_ParameterPtr CAdoCommand::AppendParameter(ADODB::ParameterDirectionEnum adoParamDirection, double values)
	{
		ADODB::_ParameterPtr ret;
		ret = GetInterfacePtr()->CreateParameter(L"@param", ADODB::adDouble, adoParamDirection, sizeof(values), values);
		GetInterfacePtr()->Parameters->Append(ret);
		return ret;
	}
	ADODB::_ParameterPtr CAdoCommand::AppendParameter(ADODB::ParameterDirectionEnum adoParamDirection, const char* values, int length)
	{
		ADODB::_ParameterPtr ret;
		ret = GetInterfacePtr()->CreateParameter(L"@param", ADODB::adVarChar, adoParamDirection, length, values);
		GetInterfacePtr()->Parameters->Append(ret);
		return ret;
	}
	ADODB::_ParameterPtr CAdoCommand::AppendParameter(ADODB::ParameterDirectionEnum adoParamDirection, const wchar_t* values, int length)
	{
		ADODB::_ParameterPtr ret;
		//HG_TODO : mysql���� utf-8�� ����� ��� wchar�� ��ȯ�ϴ� ������ �ʿ��ϴ�.
		ret = GetInterfacePtr()->CreateParameter(L"@param", ADODB::adVarWChar, adoParamDirection, length, values);
		//ret = GetInterfacePtr()->CreateParameter(L"@param", ADODB::adVarChar, adoParamDirection, length, values);
		GetInterfacePtr()->Parameters->Append(ret);
		return ret;
	}
	ADODB::_ParameterPtr CAdoCommand::AppendParameter(ADODB::ParameterDirectionEnum adoParamDirection, std::string& values, int length)
	{
		ADODB::_ParameterPtr ret;
		ret = GetInterfacePtr()->CreateParameter(L"@param", ADODB::adVarChar, adoParamDirection, length, values.c_str());
		GetInterfacePtr()->Parameters->Append(ret);
		return ret;
	}
	ADODB::_ParameterPtr CAdoCommand::AppendParameter(ADODB::ParameterDirectionEnum adoParamDirection, std::wstring& values, int length)
	{
		_variant_t tmp;
		ADODB::_ParameterPtr ret;
		//HG_TODO : mysql���� utf-8�� ����� ��� wchar�� ��ȯ�ϴ� ������ �ʿ��ϴ�.
		ret = GetInterfacePtr()->CreateParameter(L"@param", ADODB::adVarWChar, adoParamDirection, length, values.c_str());
		GetInterfacePtr()->Parameters->Append(ret);
		return ret;
	}

	_variant_t CAdoCommand::GetFieldsValues(LPCWCHAR fieldname)
	{
		//return m_pAdoRs->Fields->Item[fieldname]->Value;
		return GetInterfacePtr()->GetParameters()->GetItem(fieldname)->Value;
	}
	_variant_t CAdoCommand::GetFieldsValues(int index)
	{
		ADODB::_ParameterPtr pvObject = NULL;
		VARIANT vIntegerType;
		vIntegerType.vt = VT_I2; //Variant type for Integer
		vIntegerType.intVal = index;
		GetInterfacePtr()->GetParameters()->get_Item(vIntegerType, &pvObject);
		return pvObject->Value;


		////get column name
		//int cnt = m_pAdoRs->Fields->GetCount();
		//ADODB::Field *pvObject = NULL;
		//VARIANT vIntegerType;
		//vIntegerType.vt = VT_I2; //Variant type for Integer
		////vIntegerType.intVal = 1;
		//for(int i=0; i<cnt; ++i)
		//{
		//	vIntegerType.intVal = i;
		//	m_pAdoRs->Fields->get_Item(vIntegerType, &pvObject);
		//	_bstr_t bstrVal = pvObject->GetName();
		//	//printf("%s\n", (char*)bstrVal);
		//	//_variant_t tmp = m_pAdoRs->Fields->GetItem(vIntegerType)->Value;
		//	_variant_t tmp = m_pAdoRs->Fields->Item[bstrVal]->Value;
		//	printf("=%s:%s\n", (char*)bstrVal, (char*)(_bstr_t)tmp);
		//}

	}
};//..namespace HisUtil {