#pragma once


namespace HisUtil {

	template<class T>
	class CSingleton
	{
	public:
		static T& Instance()
		{
			if (NULL == m_instance)
				m_instance = new T;
			return *m_instance;
		}

		static void Destroy()
		{
			SAFE_DELETE(m_instance);
		}


	private:
		static T* m_instance;
	};

	template<class T> T* CSingleton<T>::m_instance = NULL;
};//namespace HisUtil {
