#pragma once

namespace HisUtil {
	//#pragma warning(disable:4189)

	template <typename TYPE>
	class CSingleton
	{
	protected:
		/// 단 하나의 객체 포인터
		static TYPE* instance_;

		/// 프로세스가 살아있는 동안 딱 한번반 생성되도록 한다.
		/// 소멸된 후에도 다시 생성할 수 없다.
		static bool  bAlreadyCreate_;

		/// 다중 스레드 상황에서의 메모리 누수를 방지하기 위한 Lock
		static CCritSecBase cs_;


		//public:
		//	/// \brief 소멸자
		//	virtual ~Singleton()
		//	{
		//		DeleteInstance();
		//	}


	public:
		/// \brief 하나뿐인 객체의 포인터를 반환한다.
		/// \return TYPE* 하나뿐인 객체의 포인터
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

		/// \brief 하나뿐인 객체를 삭제한다.
		static void Destroy()
		{
			if (instance_ != 0)
			{
				AUTO_LOCK(cs_);
				if (instance_ != 0)
				{
					TYPE *pInstance = instance_;

					// 미리 0으로 설정하지 않으면 delete되어 clear함수가 호출될 때
					// 또다시 여기를 들어온다.
					instance_ = 0;
					delete pInstance;
				}
			}
		}

	protected:
		/// \brief 기본 생성자는 외부 생성을 막기 위해 protected로 선언한다.
		CSingleton() {}

		/// \brief 소멸자는 클라이언트가 delete를 호출하는 사고를 막기 위해 protected으로 선언한다.
		virtual ~CSingleton()
		{
			Destroy();
		}

	private:
		/// \brief 복사 생성자는 외부 생성을 막기 위해 private으로 선언한다.
		CSingleton(const CSingleton<TYPE>&) {}

		/// \brief 대입 연산자는 외부 생성을 막기 위해 private으로 선언한다.
		const CSingleton<TYPE>& operator = (const CSingleton<TYPE>&) { return *this; }


	};

	template <typename TYPE> TYPE* CSingleton<TYPE>::instance_ = 0;
	template <typename TYPE> bool CSingleton<TYPE>::bAlreadyCreate_ = false;
	template <typename TYPE> CCritSecBase CSingleton<TYPE>::cs_;

}//namespace HisUtil {
