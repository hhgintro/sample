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
		//	return (T*)poolWork_.Create();	//����
		//}
		//void AddWork(HisUtil::CAdoConnection* conn, HisUtil::CSPBase* base)
		//{
		//	base->SetDBConnection(conn);
		//	poolWork_.Push(base);				//���
		//}
		//HisUtil::CSPBase* GetWork()
		//{
		//	return poolWork_.Front_Pop();		//���
		//}
		//void ReleaseWork(HisUtil::CSPBase* base)
		//{
		//	base->CleanUp();
		//	poolWork_.Release(base);			//����
		//}
	private:

		//work thread�� ���� ó������
		//���� : 1. CSPBase::m_cmd �� ������ ����� Append�� ����Ÿ�� ��� ���̴� ����.
		//		2. pool�� �ٸ� Ÿ���� ��ü�� ���� ó���� �� ���(base�� ����� ���� A, B �� ��ü�� ���� ������ �� ���.)
		//void OnWorkerThread(int index);
		//HisUtil::CMemoryQueuePool<HisUtil::CSPBase> poolWork_;

		std::wstring m_wzConnStr;

		HisUtil::ADO_DATABASE_INFO _info;
		HisUtil::CMemoryQueuePool<HisUtil::CAdoConnection> poolConn_;

	};

};//..namespace HisUtil {