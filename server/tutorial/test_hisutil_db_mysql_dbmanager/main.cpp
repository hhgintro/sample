// test_hisutil_db.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"



//#import "c:\Program Files\Common Files\system\ado\msado15.dll" rename("EOF", "adoEOF")

/*
void TestStoredProc()
{
	try{
		// 객체 생성 
		ADODB::_RecordsetPtr recordset;
		ADODB::_CommandPtr cmd;
		ADODB::_ConnectionPtr connection;
		connection.CreateInstance(__uuidof(Connection));
		recordset.CreateInstance(__uuidof(Recordset));
		cmd.CreateInstance(__uuidof(Command));

		// 커넥션 객체 오픈 
		connection->ConnectionTimeOut = 10;
		connection->open("provider=...", NULL, NULL, adOptionUnspecified);

		// 커맨트 객체 초기화 
		cmd->CommandType = adCmdStoredProc;

		cmd->CommandText = _bstr_t("spBeginJob");

		cmd->ActiveConnection = connection;

		// 저장프로시져의 리턴 값 및 파라메터값을 지정함. 
		_ParameterPtr  paramRet = cmd->CreateParameter("return", adInteger, adParamReturnValue, sizeof(int));
		_ParameterPtr  paramInput = cmd->CreateParameter("@inputData", adChar, adParamInput, 4);

		// adParamInput에 해당하는 파라메터에 입력 값 대입 
		ptr1->Value = _variant_t("Test");

		// 파라미터값을 command객체에 추가( returnValue를 처음에 append해야 함.) 
		cmd->Parameters->Append(paramRet);
		cmd->Parameters->Append(paramInput);

		// 명령실행 
		recordset = cmd->Execute(NULL, NULL, adCmdStoredProc);

		// Return값 읽어 옴. 방법#1 
		_variant_t retData(paramRet->Value);
		// Return값 읽어 옴. 방법#2 
		cmd->Parameters->GetItem("ret")->Value;
	}
	catch (_com_error &e){
		//에러처리 
	}
}
*/
void SetLastError(_com_error& e);
void LoadRecordset()
{
	CoInitialize(NULL);               // COM 초기화

	ADODB::_RecordsetPtr pAdoRs;
	pAdoRs.CreateInstance(__uuidof(ADODB::Recordset));

	//_bstr_t bstrSqlConn = "Provider=SQLOLEDB.1"
	//	";Password="
	//	";Persist Security Info=True"
	//	";User ID=sa"
	//	";Initial Catalog=tempdb"
	//	";Data Source=";
	//_bstr_t bstrSqlConn = "";
	//_bstr_t bstrSqlConn = "Provider=SQLOLEDB; Data Source=127.0.0.1; Initial Catalog=world; User ID=hhg; Password=1001;";
	//sprintf(szCon, "Provider=SQLOLEDB;Data Source=%s; Initial catalog=%s;User ID=%s;Password=%s;", szDBServerIP, szDBName, szUserID, szUserPW);
	//_bstr_t bstrSqlConn = "DRIVER={MYSQL ODBC 5.3 Unicode Driver};SERVER = 127.0.0.1; Port=3306; DATABASE = world; User ID = hhg; Password = 1001;";
	_bstr_t bstrSqlConn = "Driver={MySQL ODBC 5.3 Unicode Driver};server=127.0.0.1;port=3306;Database=world;User ID=hhg;Password=1001;";
	//_bstr_t bstrSqlConn = "";	
	_bstr_t bstrSQLText = "SELECT id,name FROM city limit 2;";

	try
	{
		pAdoRs->Open(bstrSQLText, bstrSqlConn, ADODB::adOpenForwardOnly, ADODB::adLockReadOnly, ADODB::adCmdText);

		while (!pAdoRs->adoEOF)
		{
			long    Id = pAdoRs->Fields->Item["id"]->Value.lVal;
			_bstr_t xtype = pAdoRs->Fields->Item["name"]->Value.bstrVal;

			std::cout << Id << " : " << (char*)xtype << std::endl;

			pAdoRs->MoveNext();
		}
		pAdoRs->Close();

		pAdoRs = NULL; // Release
	}
	catch (_com_error& e)
	{
		SetLastError(e);
	}

	CoUninitialize();                   // COM 해제
}
int RegisterParam()
{
	::CoInitialize(NULL);
	ADODB::_ConnectionPtr pAdoConn = NULL;
	bstr_t szConn = L"Driver={MySQL ODBC 5.3 Unicode Driver};server=127.0.0.1;port=3306;Database=world;User ID=hhg;Password=1001;";
	//bstr_t strSQLChange = L"INSERT INTO \`newtable\` (\`IntVal\`, \`FloatVal\`, \`StringVal\`) VALUES (12, 12.3, \'Hello\')"; 

	HRESULT hRes = pAdoConn.CreateInstance(__uuidof(ADODB::Connection));
	if (FAILED(hRes))
	{
		printf("Error instantiating Connection object\n");
		return FALSE;
	}

	pAdoConn->Open(szConn, "", "", 0);// ADODB::adConnectUnspecified);
	if (FAILED(hRes))
	{
		printf("Error Opening Database object using ADO _ConnectionPtr \n");
		return FALSE;
	}

	if(pAdoConn)
		pAdoConn.Release();

	pAdoConn.CreateInstance(__uuidof(ADODB::Connection));
	pAdoConn->Open(szConn, "", "", 0);

	ADODB::_CommandPtr pAdoCmd = NULL;
	pAdoCmd.CreateInstance(__uuidof(ADODB::Command));
	pAdoCmd->CommandType = ADODB::adCmdStoredProc;
	pAdoCmd->CommandText = L"sp_city_select";
	pAdoCmd->ActiveConnection = pAdoConn;

	// 저장프로시져의 리턴 값 및 파라메터값을 지정함. 
	//ADODB::_ParameterPtr  paramRet = pAdoCmd->CreateParameter("return", ADODB::adInteger, ADODB::adParamReturnValue, sizeof(int));
	
	//pAdoCmd->Parameters->Refresh();                 // passing string value as argument to stored procedure

	_variant_t val1 = (int)10;
	_variant_t val2 = "hhg";



	// 파라미터값을 command객체에 추가( returnValue를 처음에 append해야 함.) 
	////pAdoCmd->Parameters->Append(paramRet);
	//pAdoCmd->Parameters->Append(paramInput);
	//pAdoCmd->Parameters->Append(paramOutput);

	//pAdoCmd->Parameters->Append(pAdoCmd->CreateParameter(_bstr_t("return"), ADODB::adInteger, ADODB::adParamReturnValue, sizeof(val1), val1));
	pAdoCmd->Parameters->Append(pAdoCmd->CreateParameter(_bstr_t("i_id"), ADODB::adInteger, ADODB::adParamInput, sizeof(val1), val1));
	pAdoCmd->Parameters->Append(pAdoCmd->CreateParameter(_bstr_t("i_char"), ADODB::adVarChar, ADODB::adParamInput, sizeof(val2), val2));
	//pAdoCmd->Parameters->Append(pAdoCmd->CreateParameter(_bstr_t("o_id"), ADODB::adInteger, ADODB::adParamOutput, sizeof(val2), val2));


	VARIANT varValue;
	::VariantInit(&varValue);

	ADODB::_RecordsetPtr pAdoRs;

	//pAdoConn->BeginTrans();

	/* proc text
		CREATE DEFINER=`root`@`localhost` PROCEDURE `sp_city_select`(i_id int, out o_id int)
		BEGIN
			set o_id = i_id;
			select * from city where id = i_id;
			select * from city where id = i_id+1;
			select * from city where id = i_id+2;
			select o_id;
		END
	*/

	try {

		////bstr_t strSQLChange = L"SELECT id,name FROM city limit 2;";
		//bstr_t strSQLChange = L"call world.sp_city_select(1,@out);";
		////pAdoRs = pAdoConn->Execute(strSQLChange, &varValue, ADODB::adCmdText | ADODB::adExecuteNoRecords/*, &ptrRec*/);
		//pAdoRs = pAdoConn->Execute(strSQLChange, &varValue, ADODB::adCmdText);// | ADODB::adExecuteNoRecords/*, &ptrRec*/);

		//pAdoRs = pAdoConn->Execute(NULL, NULL, ADODB::adCmdStoredProc);// | ADODB::adExecuteNoRecords/*, &ptrRec*/);
		//pAdoRs = pAdoConn->Execute(L"sp_city_select", &varValue, ADODB::adCmdStoredProc);
		//pAdoRs = pAdoConn->Execute(NULL, NULL, NULL);
		pAdoRs = pAdoCmd->Execute(NULL, NULL, ADODB::adCmdStoredProc);

		//HRESULT hr = pAdoConn->raw_Execute(strSQLChange.copy(false), &varValue, ADODB::adCmdText | ADODB::adExecuteNoRecords, &ptrRec);
		//pAdoConn->CommitTrans();


		//// Return값 읽어 옴. 방법#1 
		//_variant_t retData(paramRet->Value);
		//// Return값 읽어 옴. 방법#2 
		//pAdoCmd->Parameters->GetItem("ret")->Value;


		while (!pAdoRs->adoEOF)
		{
			long    Id = pAdoRs->Fields->Item["id"]->Value.lVal;
			_bstr_t xtype = pAdoRs->Fields->Item["name"]->Value.bstrVal;

			std::cout << Id << " : " << (char*)xtype << std::endl;

			pAdoRs->MoveNext();
		}
		//pAdoRs = pAdoRs->NextRecordset(NULL);
		pAdoRs->NextRecordset(NULL);
		while (!pAdoRs->adoEOF)
		{
			long    Id = pAdoRs->Fields->Item["id"]->Value.lVal;
			_bstr_t xtype = pAdoRs->Fields->Item["name"]->Value.bstrVal;

			std::cout << Id << " : " << (char*)xtype << std::endl;

			pAdoRs->MoveNext();
		}
		//pAdoRs = pAdoRs->NextRecordset(NULL);
		pAdoRs->NextRecordset(NULL);
		while (!pAdoRs->adoEOF)
		{
			long    Id = pAdoRs->Fields->Item["id"]->Value;// .lVal;
			_bstr_t xtype = pAdoRs->Fields->Item["name"]->Value;// .bstrVal;

			std::cout << Id << " : " << (char*)xtype << std::endl;

			pAdoRs->MoveNext();
		}
		//pAdoRs = pAdoRs->NextRecordset(NULL);
		pAdoRs->NextRecordset(NULL);
		long    o_id = pAdoRs->Fields->Item["o_id"]->Value;// .lVal;
		_bstr_t name = pAdoRs->Fields->Item["o_char"]->Value;
		std::cout << "result: " << o_id << " : " << (char*)name << std::endl;

	}
	catch (_com_error& e)
	{
		SetLastError(e);
	}

	//pAdoConn->RollbackTrans(); 

	pAdoConn->Close();

	pAdoConn.Release();

	::CoUninitialize();

	return 0;
}

int RegisterParamClass()
{
	::CoInitialize(NULL);


	bstr_t szConn = L"Driver={MySQL ODBC 5.3 Unicode Driver};server=127.0.0.1;port=3306;Database=world;User ID=hhg;Password=1001;";

	HisUtil::CAdoConnection conn;
	if (FALSE == conn.Open((WCHAR*)szConn))
		return 0;


	HisUtil::CAdoCommand cmd;
	cmd.Prepare(conn, L"sp_city_select");

	INT8 val = 10;
	cmd.AppendParameter(ADODB::adParamInput, val);


	
	HisUtil::CAdoRecordset rs;
	cmd.Execute(rs);

	while (false == rs.IsEOF())
	{
		int id = rs.GetFieldsValues(L"id").lVal;
		_bstr_t name = rs.GetFieldsValues(L"name").bstrVal;
		std::cout << id << " : " << (char*)name << std::endl;

		rs.MoveNext();
	}
	rs.NextRecordset();

	while (false == rs.IsEOF())
	{
		int id = rs.GetFieldsValues(L"id").lVal;
		_bstr_t name = rs.GetFieldsValues(L"name").bstrVal;
		std::cout << id << " : " << (char*)name << std::endl;

		rs.MoveNext();
	}
	rs.NextRecordset();

	while (false == rs.IsEOF())
	{
		int id = rs.GetFieldsValues(L"id").lVal;
		_bstr_t name = rs.GetFieldsValues(L"name").bstrVal;
		std::cout << id << " : " << (char*)name << std::endl;

		rs.MoveNext();
	}
	rs.NextRecordset();

	int o_id = rs.GetFieldsValues(L"o_id").lVal;
	std::cout << "result: " << o_id << std::endl;


	////pAdoConn->RollbackTrans(); 

	//pAdoConn->Close();

	//pAdoConn.Release();

	::CoUninitialize();

	return 0;
}



int mysql_sample_class(HisUtil::CAdoConnection* conn)
{
	if (NULL == conn)	return 0;
	
	try {

		int result = 0;

		CSPMysqlSample sp(L"sp_city_select");
		sp.m_accountpk = 10;
		sp.m_name = L"hhg";
		if (FALSE == sp.Open(conn))
		{
			result = sp.GetResult();
			return 0;
		}


		while (TRUE == sp.Fetch())
		{
			int id = sp.GetFieldsValues(L"id");
			_bstr_t name = sp.GetFieldsValues(L"name");
			std::cout << id << " : " << (char*)name << std::endl;

			sp.MoveNext();
		}
		sp.NextRecordset();

		while (TRUE == sp.Fetch())
		{
			int id = sp.GetFieldsValues(L"id").lVal;
			_bstr_t name = sp.GetFieldsValues(L"name").bstrVal;
			std::cout << id << " : " << (char*)name << std::endl;

			sp.MoveNext();
		}
		sp.NextRecordset();

		while (TRUE == sp.Fetch())
		{
			int id = sp.GetFieldsValues(L"id").lVal;
			_bstr_t name = sp.GetFieldsValues(L"name").bstrVal;
			std::cout << id << " : " << (char*)name << std::endl;

			sp.MoveNext();
		}
		sp.NextRecordset();

		int o_id = sp.GetFieldsValues(L"o_id").lVal;
		//_bstr_t name = sp.GetFieldsValues(L"o_char").bstrVal;
		_bstr_t name = sp.GetFieldsValues(L"o_char");
		std::cout << "result: " << o_id << " : " << (char*)name << std::endl;

		sp.CleanUp();


	}
	catch (_com_error& e)
	{
		SetLastError(e);
		conn->Close();
	}
	catch (...)
	{
		printf("unknown error\n");
	}

	return 0;
}
int mysql_sample_class_1(HisUtil::CAdoConnection* conn)
{
	if (NULL == conn)	return 0;

	try {

		int result = 0;

		CSPMysqlSample_1 sp(L"sp_city_select");
		sp.m_name = L"hhg";
		sp.m_pass = L"hhg";
		if (FALSE == sp.Open(conn))
		{
			result = sp.GetResult();
			return 0;
		}


		while (TRUE == sp.Fetch())
		{
			int id = sp.GetFieldsValues(L"id").lVal;
			_bstr_t name = sp.GetFieldsValues(L"name").bstrVal;
			std::cout << id << " : " << (char*)name << std::endl;

			sp.MoveNext();
		}
		sp.NextRecordset();

		while (TRUE == sp.Fetch())
		{
			int id = sp.GetFieldsValues(L"id").lVal;
			_bstr_t name = sp.GetFieldsValues(L"name").bstrVal;
			std::cout << id << " : " << (char*)name << std::endl;

			sp.MoveNext();
		}
		sp.NextRecordset();

		while (TRUE == sp.Fetch())
		{
			int id = sp.GetFieldsValues(L"id").lVal;
			_bstr_t name = sp.GetFieldsValues(L"name").bstrVal;
			std::cout << id << " : " << (char*)name << std::endl;

			sp.MoveNext();
		}
		sp.NextRecordset();

		//int o_id = sp.GetFieldsValues(L"o_id").lVal;
		////_bstr_t name = sp.GetFieldsValues(L"o_char").bstrVal;
		//_bstr_t name = sp.GetFieldsValues(L"o_char");
		//std::cout << "result: " << o_id << " : " << (char*)name << std::endl;

		sp.CleanUp();


	}
	catch (_com_error& e)
	{
		SetLastError(e);
		conn->Close();
	}
	catch (...)
	{
		printf("unknown error\n");
	}

	return 0;
}
int mysql_sample()
{
	::CoInitialize(NULL);

	//int result = 0;

	//HisUtil::CAdoConnection db_;
	//db_.Open(L"Driver={MySQL ODBC 5.3 Unicode Driver};server=127.0.0.1;port=3306;Database=world;User ID=hhg;Password=1001;");

	//CSPMysqlSample sp(L"sp_city_select");
	//sp.m_accountpk = 10;
	//if (FALSE == sp.Open((HisUtil::CAdoConnection*)&db_))
	//{
	//	result = sp.GetResult();
	//	return 0;
	//}

	////// *** 컬럼을 가져오지 않을 때는 Fetch() 을 사용하지 않는다. *** //
	//////int cnt = 0;
	////for (; TRUE == sp.Fetch(); sp.MoveNext())
	////{

	////	//++cnt;
	////}
	////sp.CleanUp();



	//bstr_t szConn = L"Driver={MySQL ODBC 5.3 Unicode Driver};server=127.0.0.1;port=3306;Database=world;User ID=hhg;Password=1001;";
	bstr_t szConn = L"Driver={MySQL ODBC 8.0 Unicode Driver};server=localhost;port=3306;Database=world;User ID=root;Password=star1001;";
	//mariaDB: not working NextRecordset
	//bstr_t szConn = L"Driver={MariaDB ODBC 2.0 Driver};server=112.171.173.154;port=3306;Database=i.c.t;User ID=ICT_USER;Password=Metaport2015;";

	HisUtil::CAdoConnection conn;

	if (FALSE == conn.Open((WCHAR*)szConn))
		return 0;

	conn.Close();
	if (FALSE == conn.Open((WCHAR*)szConn))
		return 0;


	mysql_sample_class_1((HisUtil::CAdoConnection*)&conn);
	mysql_sample_class_1((HisUtil::CAdoConnection*)&conn);
	//mysql_sample_class(conn);


	conn.Close();

	::CoUninitialize();

	system("pause");
	return 0;
}
int mssql_sample_class(HisUtil::CAdoConnection* conn)
{
	if (NULL == conn)	return 0;

	try {

		int result = 0;

		CSPMssqlSample sp(L"sp_city_select");
		sp.m_accountpk = 9;
		sp.m_name = L"hhg";
		if (FALSE == sp.Open(conn))
		{
			//result = sp.GetResult();
			std::cout << "return: " << sp.GetResult() << std::endl;
			return 0;
		}


		while (TRUE == sp.Fetch())
		{
			int id = sp.GetFieldsValues(L"id");
			_bstr_t name = sp.GetFieldsValues(L"name");
			std::cout << id << " : " << (char*)name << std::endl;

			sp.MoveNext();
		}
		sp.NextRecordset();

		while (TRUE == sp.Fetch())
		{
			int id = sp.GetFieldsValues(L"id").lVal;
			_bstr_t name = sp.GetFieldsValues(L"name").bstrVal;
			std::cout << id << " : " << (char*)name << std::endl;

			sp.MoveNext();
		}
		sp.NextRecordset();

		while (TRUE == sp.Fetch())
		{
			int id = sp.GetFieldsValues(L"id").lVal;
			_bstr_t name = sp.GetFieldsValues(L"name").bstrVal;
			std::cout << id << " : " << (char*)name << std::endl;

			sp.MoveNext();
		}
		sp.NextRecordset();

		int o_id = sp.GetFieldsValues(L"o_id").lVal;
		_bstr_t name = sp.GetFieldsValues(L"o_char").bstrVal;
		std::cout << o_id << " : " << (char*)name << std::endl;
		sp.NextRecordset();


		std::cout << "return: " << sp.GetResult() << std::endl;

		_bstr_t tmp = sp.o_name;// .c_str();
		std::cout << "output: " << sp.o_id << " : " << (char*)tmp << std::endl;

		sp.CleanUp();


	}
	catch (_com_error& e)
	{
		SetLastError(e);
		conn->Close();
	}
	catch (...)
	{
		printf("unknown error\n");
	}

	return 0;
}
int mssql_sample()
{
	::CoInitialize(NULL);


	bstr_t szConn = L"Provider=sqloledb;Data Source=127.0.0.1,1433;Network Library=DBMSSOCN;Initial Catalog=world;User ID=hhg;Password=1001;";

	HisUtil::CAdoConnection conn;

	if (FALSE == conn.Open((WCHAR*)szConn))
		return 0;

	conn.Close();
	if (FALSE == conn.Open((WCHAR*)szConn))
		return 0;


	mssql_sample_class((HisUtil::CAdoConnection*)&conn);
	//mssql_sample_class(conn);


	conn.Close();

	::CoUninitialize();

	system("pause");
	return 0;
}

int test(HisUtil::CAdoConnection conn)
{

	return 0;
}
int test_main()
{
	::CoInitialize(NULL);
	HisUtil::CAdoConnection conn;
	test(conn);
	::CoUninitialize();
	return 0;
}

void trycatch_4()
{
	printf("call:%s\n", __FUNCTION__);
	throw 9;
}
void trycatch_3()
{
	printf("call:%s\n", __FUNCTION__);
	trycatch_4();
}
void trycatch_2()
{
	printf("call:%s\n", __FUNCTION__);
	trycatch_3();
}
void trycatch_1()
{
	printf("call:%s\n", __FUNCTION__);
	trycatch_2();
}
void trycatch()
{
	try {
		trycatch_1();
	}
	catch (int err)
	{
		printf("exception error:%d\n", err);
	}
	system("pause");
}
int return_sample()
{
	::CoInitialize(NULL);


	bstr_t szConn = L"Provider=sqloledb;Data Source=127.0.0.1,1433;Network Library=DBMSSOCN;Initial Catalog=world;User ID=hhg;Password=1001;";

	HisUtil::CAdoConnection conn;

	if (FALSE == conn.Open((WCHAR*)szConn))
		return 0;

	conn.Close();
	if (FALSE == conn.Open((WCHAR*)szConn))
		return 0;

	//============================================
	ADODB::_CommandPtr   pCmd = NULL;

	pCmd.CreateInstance(__uuidof(ADODB::Command));
	pCmd->ActiveConnection = conn;
	pCmd->CommandText = "sp_city_select";
	pCmd->CommandType = ADODB::adCmdStoredProc;

	//리턴값 파라미터  추가 합니다        
	pCmd->Parameters->Append(pCmd->CreateParameter("@", ADODB::adInteger, ADODB::adParamReturnValue, 4));

	int i_id = 9;
	std::wstring i_name = L"hhg";

	int o_id = 0;
	std::wstring o_name = L"";

	pCmd->Parameters->Append(pCmd->CreateParameter("@", ADODB::adInteger, ADODB::adParamInput, 4, i_id));
	pCmd->Parameters->Append(pCmd->CreateParameter("@", ADODB::adVarWChar, ADODB::adParamInput, 100, i_name.c_str()));
	pCmd->Parameters->Append(pCmd->CreateParameter("@", ADODB::adInteger, ADODB::adParamOutput, 4, o_id));
	pCmd->Parameters->Append(pCmd->CreateParameter("@", ADODB::adVarWChar, ADODB::adParamOutput, 100, o_name.c_str()));

	try {
		HRESULT hr = pCmd->Execute(NULL, NULL, NULL);
		if (SUCCEEDED(hr))
		{
			for (int cnt = 0; cnt < pCmd->GetParameters()->GetCount(); ++cnt)
			{
				ADODB::_ParameterPtr pvObject = NULL;
				VARIANT vIntegerType;
				vIntegerType.vt = VT_I2; //Variant type for Integer
				vIntegerType.intVal = cnt;
				pCmd->GetParameters()->get_Item(vIntegerType, &pvObject);
				_variant_t tmp1 = pvObject->Value;

				//_variant_t tmp1 = m_cmd.GetFieldsValues(cnt);
				switch (tmp1.vt)
				{
				case VT_BSTR:
					wprintf(L"output value(%d): %s\n", cnt, tmp1.bstrVal);
					break;
				default:
					wprintf(L"output value(%d): %d\n", cnt, tmp1.iVal);
					break;
				}
			}

			//int result = pCmd->GetParameters()->GetItem("return")->Value;  //-> 리턴값을 받아 옴...
			//o_id = pCmd->GetParameters()->GetItem("@o_id")->Value;  //-> 리턴값을 받아 옴...
		}
	}
	catch (_com_error& e) {
		printf("%s\n", (char*)e.Description());
		return FALSE;
	}
	catch (...) {
		return FALSE;
	}
	//============================================

	conn.Close();

	::CoUninitialize();

	system("pause");
	return 0;
}

void GetConnection(HisUtil::CBaseDBManager& db)
{
	HisUtil::CAdoConnection* conn = db.GetConnection();
	if (NULL == conn) {
		_tprintf(_T("db connect failed\n"));
		return;
	}

	_tprintf(_T("db connect success\n"));
	mysql_sample_class_1(conn);
	db.Release(conn);
}

int _tmain(int argc, _TCHAR* argv[])
{
	////*pint = val;
	////LoadRecordset();
	////RegisterParam();
	////RegisterParamClass();
	//mysql_sample();
	////mssql_sample();
	////test_main();
	////trycatch();
	////return_sample();


	TCHAR szConn[1024] = _T("");
	_stprintf_s(szConn, _T("Driver={MySQL ODBC 8.0 Unicode Driver};server=%s;port=%d;Database=%s;User ID=%s;Password=%s;")
		, _T("localhost"), 3306, _T("HorseRacing"), _T("horse"), _T("horse"));
	HisUtil::CBaseDBManager db;
	db.init(szConn);

	//GetConnection(db);
	//GetConnection(db);
	//GetConnection(db);


	HisUtil::CAdoConnection* conn = db.GetConnection();
	int tick = 0;
	while (1) {
		Sleep(1);
		if (GetTickCount() < tick)	continue;

		tick = GetTickCount() + 1000;

		//work thread를 통한 처리실패
		//원인 : 1. CSPBase::m_cmd 에 이전에 사용한 Append된 데이타가 계속 쌓이는 문제.
		//		2. pool에 다른 타입의 개체를 같이 처리할 수 없어서(base의 상속을 받은 A, B 두 개체를 같이 수용할 수 없어서.)
		//CSPMysqlSample_1* sp = db.CreateWork<CSPMysqlSample_1>();
		//sp->SetStoredProcName(L"sp_city_select");
		//sp->m_name = L"hhg";
		//sp->m_pass = L"hhg";
		//db.AddWork(conn, sp);


		mysql_sample_class_1(conn);

	}
	db.Release(conn);


	system("pause");
	return 0;
}
void SetLastError(_com_error& e)
{
	std::cout << "------------------------------" << std::endl
		<< "ADODB Error" << std::endl
		<< "------------------------------" << std::endl
		<< "Error Code : " << std::showbase << std::hex << e.Error() << std::endl
		<< "Source : " << (char*)e.Source() << std::endl
		<< "Description : " << (char*)e.Description() << std::endl
		<< "------------------------------" << std::endl;
}

