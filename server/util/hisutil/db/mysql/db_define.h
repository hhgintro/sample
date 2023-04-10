#pragma once


#define DEFINE_DB_CONNECTION(a,count)								\
	private:														\
	long m_index##a##DB;											\
	Proud::CriticalSection m_cs##a##DB;								\
	CAutoPtr<CDBConnection> m_db##a##[count];						\
	public:															\
	CAutoPtr<CDBConnection>& Get##a##DBConnect()					\
	{																\
	long index = InterlockedIncrement(&m_index##a##DB) % count;		\
	return m_db##a##[index];										\
	}

#define INIT_DB_CONNECTION(a)							\
	m_index##a##DB = -1;

#define START_DB_CONNECTION(a,info,count)				\
	for(int i=0; i<count; ++i)							\
	{													\
	if(FALSE == OnAttachToDB(m_db##a##[i], info))		\
	return SERVER_DB_AOD_CONNECT_FAIL;					\
	}

#define RELEAE_DB_CONNECTION(a,count)					\
	for(int i=0; i<count; ++i)							\
	{													\
	if(NULL != m_db##a##[i])							\
		{												\
		m_db##a##[i]->Close();							\
		m_db##a##[i].Free();							\
		}												\
	}

namespace HisUtil {

	//enum DB_DIRECT
	//{
	//	eDB_IN			//ADODB::adParamInput
	//	, eDB_OUTPUT	//ADODB::adParamOutput
	//	, eDB_IN_OUT	//ADODB::adParamInputOutput
	//};


	enum DB_TYPE
	{
		eDB_Type_None
		, eDB_Type_Admin
		, eDB_Type_Account
		, eDB_Type_Game
		, eDB_Type_Log
		, eDB_Type_Max
	};
	typedef UINT8		DB_TYPE_T;


	struct ADO_DATABASE_INFO
	{
		TString m_ip; 		//db ip
		UINT16 m_port; 				//db port
		//WORD m_portTcp; 			//tcp(lan) port
		TString m_database; 	//db 명
		TString m_user; 		//사용자
		TString m_passwd; 	//비번
	};

};//..namespace HisUtil {