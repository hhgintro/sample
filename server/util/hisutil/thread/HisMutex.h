#pragma once

#include <windows.h>

/* ��뿹
���� ����
CMutexBase _mx;

���
func()
{
	AUTO_MUTEX(_mx)
...
}
..��뿹*/

namespace HisUtil {

	class CMutexBase
	{
	public:
		CMutexBase(TCHAR* mutexName);
		CMutexBase() : _hMutex(INVALID_HANDLE_VALUE) {}
		~CMutexBase();

		void SetName(TCHAR* mutexName);

		inline void Lock();
		inline void Unlock();

	private:
		HANDLE	_hMutex = INVALID_HANDLE_VALUE;          // Permits exclusive access to other members

		friend class CHisMutex;

	};
	class CHisMutex
	{
	public:
		CHisMutex(CMutexBase& base);
		~CHisMutex();

	private:
		CMutexBase& _base;
	};

}//..namespace HisUtil


#define AUTO_MUTEX(a)		HisUtil::CHisMutex Lock(a)
