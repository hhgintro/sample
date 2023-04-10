#pragma once


namespace HisUtil {

	class CBaseDBManager// : public HisUtil::CThread
	{
	public:
		CBaseDBManager();
		~CBaseDBManager();



		void init(WCHAR* wzConnStr);
		BOOL connect(HisUtil::CAdoConnection* conn);

		HisUtil::CAdoConnection* GetConnection();
		void Release(HisUtil::CAdoConnection* conn);

		//template<typename T>
		//T* CreateWork()
		//{
		//	return (T*)poolWork_.Create();	//생성
		//}
		//void AddWork(HisUtil::CAdoConnection* conn, HisUtil::CSPBase* base)
		//{
		//	base->SetDBConnection(conn);
		//	poolWork_.Push(base);				//등록
		//}
		//HisUtil::CSPBase* GetWork()
		//{
		//	return poolWork_.Front_Pop();		//사용
		//}
		//void ReleaseWork(HisUtil::CSPBase* base)
		//{
		//	base->CleanUp();
		//	poolWork_.Release(base);			//해제
		//}
	private:

		//work thread를 통한 처리실패
		//원인 : 1. CSPBase::m_cmd 에 이전에 사용한 Append된 데이타가 계속 쌓이는 문제.
		//		2. pool에 다른 타입의 개체를 같이 처리할 수 없어서(base의 상속을 받은 A, B 두 개체를 같이 수용할 수 없어서.)
		//void OnWorkerThread(int index);
		//HisUtil::CMemoryQueuePool<HisUtil::CSPBase> poolWork_;

		std::wstring m_wzConnStr;

		HisUtil::ADO_DATABASE_INFO _info;
		HisUtil::CMemoryQueuePool<HisUtil::CAdoConnection> poolConn_;

	};

};//..namespace HisUtil {