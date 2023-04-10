#include "stdafx.h"
#include "SPBase.h"


namespace HisUtil {

	//BOOL CSPBase::Open(CAutoPtr<CDBConnection>* connection)
	//BOOL CSPBase::Open(ADODB::_Connection* connection)
	BOOL CSPBase::Open(CAdoConnection& conn)
	{
		if (NULL == conn)
			return FALSE;

		//모듈 보호
		if (FALSE == m_module.CheckValid())
			return TRUE;

		m_connection = conn;

		//m_connection->Close();


		//@!!:필요할때 연결하는 방식으로 변경합니다.
		if (false == conn.IsOpened())
		{
			conn.Open();
		}

		//m_cmd.Prepare(m_connection, m_storedProcName);
		m_cmd.Prepare(conn, m_storedProcName.c_str());


		_AppendParameter();


		if (FALSE == m_cmd.Execute(m_rs))
			return FALSE;

		//for mssql
			if (RESULT_OK != m_result)
				return FALSE;

		//for mssql
				_BindParam();

		_Fetch();
		return TRUE;
	}

	void CSPBase::CleanUp()
	{
		//m_rs.Close();

		m_result = 0;
		//m_outparams.clear();

		m_storedProcName = L"";

		////@!!:필요할때 연결하는 방식으로 변경합니다.
		//if(NULL != m_connection)
		//	m_connection->Close();
	}

	BOOL CSPBase::Fetch()
	{
		if (false == m_connection.IsOpened())//select구문이 없는 sp를 호출시에 예외발생차단.
			return FALSE;
		return (BOOL)(false == m_rs.IsEOF());
	}

	void CSPBase::MoveNext()
	{
		m_rs.MoveNext();
	}

	void CSPBase::NextRecordset()
	{
		m_rs.NextRecordset();
	}

	_variant_t CSPBase::GetFieldsValues(LPCWCHAR fileldname)
	{
		return m_rs.GetFieldsValues(fileldname);
	}

	void CSPBase::_AppendParameter()
	{
		//for mssql
		//ADODB::_ParameterPtr ret = AppendReturn();
		//m_result = ret->GetValue();
	};

	void CSPBase::_BindParam()
	{
		//0은 RETRUN값이므로 첫번째 OUTPUT은 1부터입니다.
		m_posGet = 0;
	}

	//ADODB::ParameterDirectionEnum CSPBase::_GetParamDirect(ADODB::ParameterDirectionEnum direct)
	//{
	//	switch (inout)
	//	{
	//	case eDB_IN:		return ADODB::adParamInput;
	//	case eDB_OUTPUT:	return ADODB::adParamOutput;
	//	case eDB_IN_OUT:	return ADODB::adParamInputOutput;
	//	}
	//	return ADODB::adParamInput;
	//}


	ADODB::_ParameterPtr CSPBase::AppendReturn()
	{
		int values = 0;
		return m_cmd.AppendParameter(ADODB::adParamReturnValue, values);
	}
	ADODB::_ParameterPtr CSPBase::Append(ADODB::ParameterDirectionEnum direct, INT8 values)
	{
		//ADODB::ParameterDirectionEnum direct = _GetParamDirect(inout);
		//if(ADODB::adParamInput == direct) values = 0;//초기화 안해서 생기는 문제방지

		ADODB::_ParameterPtr temp = m_cmd.AppendParameter(direct, values);
		if (ADODB::adParamOutput == direct)
			m_outparams.push_back(temp);
		return temp;
	}
	ADODB::_ParameterPtr CSPBase::Append(ADODB::ParameterDirectionEnum direct, UINT8 values)
	{
		//ADODB::ParameterDirectionEnum direct = _GetParamDirect(inout);
		//if(ADODB::adParamInput == direct) values = 0;//초기화 안해서 생기는 문제방지

		ADODB::_ParameterPtr temp = m_cmd.AppendParameter(direct, values);
		if (ADODB::adParamOutput == direct)
			m_outparams.push_back(temp);
		return temp;
	}
	ADODB::_ParameterPtr CSPBase::Append(ADODB::ParameterDirectionEnum direct, INT16 values)
	{
		//ADODB::ParameterDirectionEnum direct = _GetParamDirect(inout);
		//if(ADODB::adParamInput == direct) values = 0;//초기화 안해서 생기는 문제방지

		ADODB::_ParameterPtr temp = m_cmd.AppendParameter(direct, values);
		if (ADODB::adParamOutput == direct)
			m_outparams.push_back(temp);
		return temp;
	}
	ADODB::_ParameterPtr CSPBase::Append(ADODB::ParameterDirectionEnum direct, UINT16 values)
	{
		//ADODB::ParameterDirectionEnum direct = _GetParamDirect(inout);
		//if(ADODB::adParamInput == direct) values = 0;//초기화 안해서 생기는 문제방지

		ADODB::_ParameterPtr temp = m_cmd.AppendParameter(direct, values);
		if (ADODB::adParamOutput == direct)
			m_outparams.push_back(temp);
		return temp;
	}
	ADODB::_ParameterPtr CSPBase::Append(ADODB::ParameterDirectionEnum direct, INT32 values)
	{
		//ADODB::ParameterDirectionEnum direct = _GetParamDirect(inout);
		//if(ADODB::adParamInput == direct) values = 0;//초기화 안해서 생기는 문제방지

		ADODB::_ParameterPtr temp = m_cmd.AppendParameter(direct, values);
		if (ADODB::adParamOutput == direct)
			m_outparams.push_back(temp);
		return temp;
	}
	ADODB::_ParameterPtr CSPBase::Append(ADODB::ParameterDirectionEnum direct, UINT32 values)
	{
		//ADODB::ParameterDirectionEnum direct = _GetParamDirect(inout);
		//if(ADODB::adParamInput == direct) values = 0;//초기화 안해서 생기는 문제방지

		ADODB::_ParameterPtr temp = m_cmd.AppendParameter(direct, values);
		if (ADODB::adParamOutput == direct)
			m_outparams.push_back(temp);
		return temp;
	}
	ADODB::_ParameterPtr CSPBase::Append(ADODB::ParameterDirectionEnum direct, INT64 values)
	{
		//ADODB::ParameterDirectionEnum direct = _GetParamDirect(inout);
		//if(ADODB::adParamInput == direct) values = 0;//초기화 안해서 생기는 문제방지

		ADODB::_ParameterPtr temp = m_cmd.AppendParameter(direct, values);
		if (ADODB::adParamOutput == direct)
			m_outparams.push_back(temp);
		return temp;
	}
	ADODB::_ParameterPtr CSPBase::Append(ADODB::ParameterDirectionEnum direct, UINT64 values)
	{
		//ADODB::ParameterDirectionEnum direct = _GetParamDirect(inout);
		//if(ADODB::adParamInput == direct) values = 0;//초기화 안해서 생기는 문제방지

		ADODB::_ParameterPtr temp = m_cmd.AppendParameter(direct, values);
		if (ADODB::adParamOutput == direct)
			m_outparams.push_back(temp);
		return temp;
	}
	ADODB::_ParameterPtr CSPBase::Append(ADODB::ParameterDirectionEnum direct, float values)
	{
		//ADODB::ParameterDirectionEnum direct = _GetParamDirect(inout);
		//if(eDB_OUTPUT == direct) values = 0.f;//초기화 안해서 생기는 문제방지

		ADODB::_ParameterPtr temp = m_cmd.AppendParameter(direct, values);
		if (ADODB::adParamOutput == direct)
			m_outparams.push_back(temp);
		return temp;
	}
	ADODB::_ParameterPtr CSPBase::Append(ADODB::ParameterDirectionEnum direct, double values)
	{
		//ADODB::ParameterDirectionEnum direct = _GetParamDirect(inout);
		//if(eDB_OUTPUT == direct) values = 0.f;//초기화 안해서 생기는 문제방지

		ADODB::_ParameterPtr temp = m_cmd.AppendParameter(direct, values);
		if (ADODB::adParamOutput == direct)
			m_outparams.push_back(temp);
		return temp;
	}
	ADODB::_ParameterPtr CSPBase::Append(ADODB::ParameterDirectionEnum direct, std::string& values, int length)
	{
		//ADODB::ParameterDirectionEnum direct = _GetParamDirect(inout);
		////if(ADODB::adParamInput == direct) values = 0;//초기화 안해서 생기는 문제방지

		ADODB::_ParameterPtr temp = m_cmd.AppendParameter(direct, values, length);
		if (ADODB::adParamOutput == direct)
			m_outparams.push_back(temp);
		return temp;
	}
	ADODB::_ParameterPtr CSPBase::Append(ADODB::ParameterDirectionEnum direct, std::wstring& values, int length)
	{
		//ADODB::ParameterDirectionEnum direct = _GetParamDirect(inout);
		////if(ADODB::adParamInput == direct) values = 0;//초기화 안해서 생기는 문제방지

		ADODB::_ParameterPtr temp = m_cmd.AppendParameter(direct, values, length);
		if (ADODB::adParamOutput == direct)
			m_outparams.push_back(temp);
		return temp;
	}
	ADODB::_ParameterPtr CSPBase::Append(ADODB::ParameterDirectionEnum direct, const char* values, int length)
	{
		//ADODB::ParameterDirectionEnum direct = _GetParamDirect(inout);
		////if(ADODB::adParamInput == direct) values = 0;//초기화 안해서 생기는 문제방지

		ADODB::_ParameterPtr temp = m_cmd.AppendParameter(direct, values, length);
		if (ADODB::adParamOutput == direct)
			m_outparams.push_back(temp);
		return temp;
	}
	ADODB::_ParameterPtr CSPBase::Append(ADODB::ParameterDirectionEnum direct, const wchar_t* values, int length)
	{
		//ADODB::ParameterDirectionEnum direct = _GetParamDirect(inout);
		////if(ADODB::adParamInput == direct) values = 0;//초기화 안해서 생기는 문제방지

		ADODB::_ParameterPtr temp = m_cmd.AppendParameter(direct, values, length);
		if (ADODB::adParamOutput == direct)
			m_outparams.push_back(temp);
		return temp;
	}




	//void CSPBase::BindParam(INT8& values)
	//{
	//	Proud::CVariant temp = m_outparams[++m_posGet]->GetValue();
	//	values = (char)ISNULL_VALUE(temp);
	//	//values = (char)m_outparams[++m_posGet]->GetValue();
	//}
	//void CSPBase::BindParam(UINT8& values)
	//{
	//	Proud::CVariant temp = m_outparams[++m_posGet]->GetValue();
	//	values = (unsigned char)ISNULL_VALUE(temp);
	//	//values = (unsigned char)m_outparams[++m_posGet]->GetValue();
	//}
	//void CSPBase::BindParam(INT16& values)
	//{
	//	Proud::CVariant temp = m_outparams[++m_posGet]->GetValue();
	//	values = (short)ISNULL_VALUE(temp);
	//	//values = (short)m_outparams[++m_posGet]->GetValue();
	//}
	//void CSPBase::BindParam(UINT16& values)
	//{
	//	Proud::CVariant temp = m_outparams[++m_posGet]->GetValue();
	//	values = (unsigned short)ISNULL_VALUE(temp);
	//	//values = (unsigned short)m_outparams[++m_posGet]->GetValue();
	//}
	//void CSPBase::BindParam(INT32& values)
	//{
	//	Proud::CVariant temp = m_outparams[++m_posGet]->GetValue();
	//	values = (int)ISNULL_VALUE(temp);
	//	//values = (int)m_outparams[++m_posGet]->GetValue();
	//}
	//void CSPBase::BindParam(UINT32& values)
	//{
	//	Proud::CVariant temp = m_outparams[++m_posGet]->GetValue();
	//	values = (unsigned int)ISNULL_VALUE(temp);
	//	//values = (unsigned int)m_outparams[++m_posGet]->GetValue();
	//}
	//void CSPBase::BindParam(INT64& values)
	//{
	//	Proud::CVariant temp = m_outparams[++m_posGet]->GetValue();
	//	values = (__int64)ISNULL_VALUE(temp);
	//	//values = (__int64)m_outparams[++m_posGet]->GetValue();
	//}
	//void CSPBase::BindParam(UINT64& values)
	//{
	//	Proud::CVariant temp = m_outparams[++m_posGet]->GetValue();
	//	values = (unsigned __int64)ISNULL_VALUE(temp);
	//	//values = (unsigned __int64)m_outparams[++m_posGet]->GetValue();
	//}
	//void CSPBase::BindParam(float& values)
	//{
	//	Proud::CVariant temp = m_outparams[++m_posGet]->GetValue();
	//	values = (float)ISNULL_VALUE(temp);
	//	//values = (float)m_outparams[++m_posGet]->GetValue();
	//}
	//void CSPBase::BindParam(CHAR* values)
	//{
	//	//NULL 처리후에 사용하세요
	//	//strcpy(values, (LPSTR)((_bstr_t)m_outparams[++m_posGet]->GetValue()));
	//}
	//void CSPBase::BindParam(WCHAR* values)
	//{
	//	//Proud::CVariant temp = m_outparams[++m_posGet]->GetValue();
	//	//Proud::String buff = ISNULL_WCHAR(temp);
	//	//_tcscpy(values, buff.GetString());
	//}
	//void CSPBase::BindParam(Proud::StringA& values)
	//{
	//	//NULL 처리후에 사용하세요
	//	//values = (LPSTR)((_bstr_t)m_outparams[++m_posGet]->GetValue());
	//}
	//void CSPBase::BindParam(Proud::String& values)
	//{
	//	//values = (LPCTSTR)((_bstr_t)m_outparams[++m_posGet]->GetValue());
	//	Proud::CVariant temp = m_outparams[++m_posGet]->GetValue();
	//	values = ISNULL_WCHAR(temp);
	//}





	////void CSPBase::GetData(LPCWCHAR fileldname, INT8& values)
	////{
	////	values = ISNULL_VALUE(m_rs.FieldValues[fileldname]);
	////}
	////void CSPBase::GetData(LPCWCHAR fileldname, UINT8& values)
	////{
	////	values = ISNULL_VALUE(m_rs.FieldValues[fileldname]);
	////}
	////void CSPBase::GetData(LPCWCHAR fileldname, INT16& values)
	////{
	////	values = ISNULL_VALUE(m_rs.FieldValues[fileldname]);
	////}
	////void CSPBase::GetData(LPCWCHAR fileldname, UINT16& values)
	////{
	////	values = ISNULL_VALUE(m_rs.FieldValues[fileldname]);
	////}
	////void CSPBase::GetData(LPCWCHAR fileldname, INT32& values)
	////{
	////	values = ISNULL_VALUE(m_rs.FieldValues[fileldname]);
	////}
	////void CSPBase::GetData(LPCWCHAR fileldname, UINT32& values)
	////{
	////	values = ISNULL_VALUE(m_rs.FieldValues[fileldname]);
	////}
	////void CSPBase::GetData(LPCWCHAR fileldname, INT64& values)
	////{
	////	values = ISNULL_VALUE(m_rs.FieldValues[fileldname]);
	////}
	////void CSPBase::GetData(LPCWCHAR fileldname, UINT64& values)
	////{
	////	values = ISNULL_VALUE(m_rs.FieldValues[fileldname]);
	////}
	////void CSPBase::GetData(LPCWCHAR fileldname, float& values)
	////{
	////	values = ISNULL_VALUE(m_rs.FieldValues[fileldname]);
	////}
	////void CSPBase::GetData(LPCWCHAR fileldname, CHAR* values)
	////{
	////	values = ISNULL_CHAR(m_rs.FieldValues[fileldname]);
	////}
	////void CSPBase::GetData(LPCWCHAR fileldname, WCHAR* values)
	////{
	////	values = ISNULL_WCHAR(m_rs.FieldValues[fileldname]);
	////}
	////void CSPBase::GetData(LPCWCHAR fileldname, Proud::StringA& values)
	////{
	////	values = ISNULL_CHAR(m_rs.FieldValues[fileldname]);
	////}
	////void CSPBase::GetData(LPCWCHAR fileldname, Proud::String& values)
	////{
	////	values = ISNULL_WCHAR(m_rs.FieldValues[fileldname]);
	////}

};//..namespace HisUtil {