#include "stdafx.h"
#include "SPBase.h"


namespace HisUtil {

	void CSPBase::SetLastError(_com_error& e)
	{
		//std::cout << "------------------------------" << std::endl
		//	<< "ADODB Error" << std::endl
		//	<< "------------------------------" << std::endl
		//	<< "Error Code : " << std::showbase << std::hex << e.Error() << std::endl
		//	<< "Source : " << (char*)e.Source() << std::endl
		//	<< "Description : " << (char*)e.Description() << std::endl
		//	<< "------------------------------" << std::endl;

		LOGEVENT("HG_RED", _T("------------------------------"));
		LOGEVENT("HG_RED", _T("ADODB SP Error"));
		LOGEVENT("HG_RED", _T("------------------------------"));
		LOGEVENT("HG_RED", _T("sp : %s"), GetStoredProcName());
		LOGEVENT("HG_RED", _T("Error Code : %x"), e.Error());
		LOGEVENT("HG_RED", _T("Source : %s"), (wchar_t*)e.Source());
		LOGEVENT("HG_RED", _T("Description : %s"), (wchar_t*)e.Description());
		LOGEVENT("HG_RED", _T("------------------------------"));
	}

	void CSPBase::SetLastError()
	{
		LOGEVENT("HG_RED", _T("------------------------------"));
		LOGEVENT("HG_RED", _T("ADODB SP Error"));
		LOGEVENT("HG_RED", _T("------------------------------"));
		LOGEVENT("HG_RED", _T("sp : %s"), GetStoredProcName());
		LOGEVENT("HG_RED", _T("Description : unknown error"));
		LOGEVENT("HG_RED", _T("------------------------------"));
	}

	//BOOL CSPBase::Open(CAutoPtr<CDBConnection>* connection)
	//BOOL CSPBase::Open(ADODB::_Connection* connection)
	//BOOL CSPBase::Open(CAdoConnection* conn)
	BOOL CSPBase::Open(CBaseDBManager* base)
	{
		if (NULL == base)
			return FALSE;
		m_base = base;

		//모듈 보호
		if (FALSE == m_module.CheckValid())
			return TRUE;

		m_conn = base->GetConnection();
		if (NULL == m_conn)
			return FALSE;

		//m_conn->Close();


		//@!!:필요할때 연결하는 방식으로 변경합니다.
		if (false == m_conn->IsOpened())
		{
			m_conn->Open();
		}

		//m_cmd.Prepare(m_conn, m_storedProcName);
		m_cmd.Prepare(*m_conn, m_storedProcName.c_str());


		//RETURN값을 받아오도록 설정한다.(for mssql)
		_AppendParameter();


		if (FALSE == m_cmd.Execute(m_rs))
			return FALSE;
		
		//for (int cnt = 0; cnt < m_cmd->GetParameters()->GetCount(); ++cnt)
		//{
		//	_variant_t tmp1 = m_cmd.GetFieldsValues(cnt);
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
		//for (int i = 0; i < m_outparams.size(); ++i)
		//{
		//	_variant_t tmp = m_outparams[i]->GetValue();
		//	switch (tmp.vt)
		//	{
		//	case VT_BSTR:
		//		wprintf(L"output value(%d): %s\n", i, tmp.bstrVal);
		//		break;
		//	default:
		//		wprintf(L"output value(%d): %d\n", i, tmp.iVal);
		//		break;
		//	}
		//}

		//RETURN값을 받아와서 체크
		if (FALSE == _Return())
			return FALSE;

		_BindParam();

		_Fetch();
		return TRUE;
	}

	void CSPBase::CleanUp()
	{
		//m_rs.Close();
		//m_cmd->Cancel();
		m_cmd->Cancel();

		m_result = 0;
		//m_outparams.clear();

		m_storedProcName = L"";

		////@!!:필요할때 연결하는 방식으로 변경합니다.
		//if(NULL != m_conn)
		//	m_conn->Close();
		if (NULL != m_base) {
			m_base->Release(m_conn);
			m_base = NULL;
		}
	}

	BOOL CSPBase::Fetch()
	{
		if (false == m_conn->IsOpened())//select구문이 없는 sp를 호출시에 예외발생차단.
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
		_variant_t var = m_rs.GetFieldsValues(fileldname);
		return var;
	}

	void CSPBase::_AppendParameter()
	{
		//for mssql
		m_outparams.push_back(m_cmd.AppendReturn(ADODB::adParamReturnValue, (int)0));
	};

	BOOL CSPBase::_Return()
	{
		//for mssql
		//0은 RETRUN값이므로 첫번째 OUTPUT은 1부터입니다.
		m_posGet = -1;
		BindParam(m_result);
		if (RESULT_OK != m_result)
			return FALSE;
		return TRUE;
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




	void CSPBase::BindParam(INT8& values)
	{
		if (m_outparams.size() <= ++m_posGet)
			return;
		values = (char)m_outparams[m_posGet]->GetValue();
	}
	void CSPBase::BindParam(UINT8& values)
	{
		if (m_outparams.size() <= ++m_posGet)
			return;
		values = (unsigned char)m_outparams[m_posGet]->GetValue();
	}
	void CSPBase::BindParam(INT16& values)
	{
		if (m_outparams.size() <= ++m_posGet)
			return;
		values = m_outparams[m_posGet]->GetValue();
	}
	void CSPBase::BindParam(UINT16& values)
	{
		if (m_outparams.size() <= ++m_posGet)
			return;
		values = m_outparams[m_posGet]->GetValue();
	}
	void CSPBase::BindParam(INT32& values)
	{
		if (m_outparams.size() <= ++m_posGet)
			return;
		values = m_outparams[m_posGet]->GetValue();
	}
	void CSPBase::BindParam(UINT32& values)
	{
		if (m_outparams.size() <= ++m_posGet)
			return;
		values = m_outparams[m_posGet]->GetValue();
	}
	void CSPBase::BindParam(INT64& values)
	{
		if (m_outparams.size() <= ++m_posGet)
			return;
		values = m_outparams[m_posGet]->GetValue();
	}
	void CSPBase::BindParam(UINT64& values)
	{
		if (m_outparams.size() <= ++m_posGet)
			return;
		values = m_outparams[m_posGet]->GetValue();
	}
	void CSPBase::BindParam(float& values)
	{
		if (m_outparams.size() <= ++m_posGet)
			return;
		values = m_outparams[m_posGet]->GetValue();
	}
	void CSPBase::BindParam(double& values)
	{
		if (m_outparams.size() <= ++m_posGet)
			return;
		values = m_outparams[m_posGet]->GetValue();
	}
	void CSPBase::BindParam(char* values, int length)
	{
		if (m_outparams.size() <= ++m_posGet)
			return;
		//values = m_outparams[m_posGet]->GetValue();
		memcpy(values, (char*)(bstr_t)m_outparams[m_posGet]->GetValue(), length);
	}
	void CSPBase::BindParam(wchar_t* values, int length)
	{
		if (m_outparams.size() <= ++m_posGet)
			return;
		//values = m_outparams[m_posGet]->GetValue();
		_variant_t tmp = m_outparams[m_posGet]->GetValue();
		memcpy(values, (wchar_t*)(bstr_t)m_outparams[m_posGet]->GetValue(), length);
	}
	void CSPBase::BindParam(std::string& values)
	{
		if (m_outparams.size() <= ++m_posGet)
			return;
		values = (bstr_t)m_outparams[m_posGet]->GetValue();
	}
	void CSPBase::BindParam(std::wstring& values)
	{
		if (m_outparams.size() <= ++m_posGet)
			return;
		values = (bstr_t)m_outparams[m_posGet]->GetValue();
	}


};//..namespace HisUtil {