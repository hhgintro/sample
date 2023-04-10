#pragma once

namespace HisUtil {
	//#pragma warning(disable:4189)

	template <typename TYPE>
	class CSingleton
	{
	protected:
		/// �� �ϳ��� ��ü ������
		static TYPE* instance_;

		/// ���μ����� ����ִ� ���� �� �ѹ��� �����ǵ��� �Ѵ�.
		/// �Ҹ�� �Ŀ��� �ٽ� ������ �� ����.
		static bool  bAlreadyCreate_;

		/// ���� ������ ��Ȳ������ �޸� ������ �����ϱ� ���� Lock
		static CCritSecBase cs_;


		//public:
		//	/// \brief �Ҹ���
		//	virtual ~Singleton()
		//	{
		//		DeleteInstance();
		//	}


	public:
		/// \brief �ϳ����� ��ü�� �����͸� ��ȯ�Ѵ�.
		/// \return TYPE* �ϳ����� ��ü�� ������
		static TYPE& Instance()
		{
			if (instance_ == 0 && bAlreadyCreate_ == false)
			{
				AUTO_LOCK(cs_);
				if (instance_ == 0)
				{
					bAlreadyCreate_ = true;
					instance_ = new TYPE;
				}
			}
			return *instance_;
		}

		/// \brief �ϳ����� ��ü�� �����Ѵ�.
		static void Destroy()
		{
			if (instance_ != 0)
			{
				AUTO_LOCK(cs_);
				if (instance_ != 0)
				{
					TYPE *pInstance = instance_;

					// �̸� 0���� �������� ������ delete�Ǿ� clear�Լ��� ȣ��� ��
					// �Ǵٽ� ���⸦ ���´�.
					instance_ = 0;
					delete pInstance;
				}
			}
		}

	protected:
		/// \brief �⺻ �����ڴ� �ܺ� ������ ���� ���� protected�� �����Ѵ�.
		CSingleton() {}

		/// \brief �Ҹ��ڴ� Ŭ���̾�Ʈ�� delete�� ȣ���ϴ� ��� ���� ���� protected���� �����Ѵ�.
		virtual ~CSingleton()
		{
			Destroy();
		}

	private:
		/// \brief ���� �����ڴ� �ܺ� ������ ���� ���� private���� �����Ѵ�.
		CSingleton(const CSingleton<TYPE>&) {}

		/// \brief ���� �����ڴ� �ܺ� ������ ���� ���� private���� �����Ѵ�.
		const CSingleton<TYPE>& operator = (const CSingleton<TYPE>&) { return *this; }


	};

	template <typename TYPE> TYPE* CSingleton<TYPE>::instance_ = 0;
	template <typename TYPE> bool CSingleton<TYPE>::bAlreadyCreate_ = false;
	template <typename TYPE> CCritSecBase CSingleton<TYPE>::cs_;

}//namespace HisUtil {
