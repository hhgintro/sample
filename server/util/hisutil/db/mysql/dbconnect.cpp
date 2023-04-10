#include "stdafx.h"
#include "dbconnect.h"


namespace HisUtil {


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

		//구지 Release할 필요가 없군요...오히려 Release()하면 종료서 오류창 뜹니다.
		////if (m_pAdoConn)		m_pAdoConn.Release();
		//if (GetInterfacePtr())	GetInterfacePtr()->Release();
	}

	//mssql
	//"Provider=sqloledb;Data Source=127.0.0.1,1433;Network Library=DBMSSOCN;Initial Catalog=world;User ID=hhg;Password=1001"
	//mysql
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
				printf("Error Opening Database object using ADO _ConnectionPtr \n");
				Close();
				return FALSE;
			}

			//m_bOpened = TRUE;
		}
		catch (_com_error& e) {
			printf("%s\n", (char*)e.Description());
			return FALSE;
		}
		catch (...) {
			return FALSE;
		}

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
		//구지 Release할 필요가 없군요...오히려 Release()하면 종료서 오류창 뜹니다.
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
		int cnt = m_pAdoRs->Fields->GetCount();
		ADODB::Field *pvObject = NULL;
		VARIANT vIntegerType;
		vIntegerType.vt = VT_I2; //Variant type for Integer
		//vIntegerType.intVal = 1;
		for(int i=0; i<cnt; ++i)
		{
			vIntegerType.intVal = i;
			m_pAdoRs->Fields->get_Item(vIntegerType, &pvObject);
			_bstr_t bstrVal = pvObject->GetName();
			//printf("%s\n", (char*)bstrVal);
			//_variant_t tmp = m_pAdoRs->Fields->GetItem(vIntegerType)->Value;
			_variant_t tmp = m_pAdoRs->Fields->Item[bstrVal]->Value;
			printf("=%s:%s\n", (char*)bstrVal, (char*)(_bstr_t)tmp);

		}
		//_variant_t tmp = m_pAdoRs->Fields->Item[fieldname]->Value;
		return m_pAdoRs->Fields->Item[fieldname]->Value;
		//return GetInterfacePtr()->Fields->Item[fieldname]->Value;
	}






	//================================================
	//CAdoCommand
	//================================================

	CAdoCommand::CAdoCommand()
	{
		//m_pAdoCmd.CreateInstance(__uuidof(ADODB::Command));
		CreateInstance(__uuidof(ADODB::Command));
	}
	CAdoCommand::~CAdoCommand()
	{
		//구지 Release할 필요가 없군요...오히려 Release()하면 종료서 오류창 뜹니다.
		//if (m_pAdoCmd)		m_pAdoCmd.Release();
		//GetInterfacePtr()->Release();
	}

	void CAdoCommand::Prepare(CAdoConnection& conn, const wchar_t* strStoredProcName)
	{
		//m_pAdoCmd->CommandType = ADODB::adCmdStoredProc;
		//m_pAdoCmd->CommandText = strStoredProcName;
		//m_pAdoCmd->ActiveConnection = conn;// ->GetConnect();
		GetInterfacePtr()->CommandType = ADODB::adCmdStoredProc;
		GetInterfacePtr()->CommandText = L"sp_city_select"; //strStoredProcName;
		GetInterfacePtr()->ActiveConnection = conn;
	}

	BOOL CAdoCommand::Execute(CAdoRecordset& rs)
	{
		try {
			//ADODB::_RecordsetPtr pAdoRs = m_pAdoCmd->Execute(NULL, NULL, ADODB::adCmdStoredProc);
			ADODB::_RecordsetPtr pAdoRs = GetInterfacePtr()->Execute(NULL, NULL, NULL);
			rs.SetRecordSet(pAdoRs);
		}
		catch (_com_error& e) {
			printf("%s\n", (char*)e.Description());
			return FALSE;
		}
		catch (...) {
			printf("unknown error\n");
			return FALSE;
		}
		return TRUE;
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
		//HG_TODO : mysql에서 utf-8로 저장된 경우 wchar로 변환하는 로직이 필요하다.
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
		//HG_TODO : mysql에서 utf-8로 저장된 경우 wchar로 변환하는 로직이 필요하다.
		ret = GetInterfacePtr()->CreateParameter(L"@param", ADODB::adVarWChar, adoParamDirection, length, values.c_str());
		GetInterfacePtr()->Parameters->Append(ret);
		return ret;
	}


};//..namespace HisUtil {