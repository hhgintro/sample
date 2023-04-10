#include "stdafx.h"
#include "HisMutex.h"


namespace HisUtil {


	CMutexBase::CMutexBase(TCHAR* mutexName)
	{
		_hMutex = CreateMutex(NULL, FALSE, mutexName);
	}
	CMutexBase::~CMutexBase()
	{
		if (INVALID_HANDLE_VALUE != _hMutex)
			CloseHandle(_hMutex);
	}

	void CMutexBase::SetName(TCHAR* mutexName)
	{
		if(INVALID_HANDLE_VALUE != _hMutex)
			CloseHandle(_hMutex);
		_hMutex = CreateMutex(NULL, FALSE, mutexName);
	}

	void CMutexBase::Lock()
	{
		WaitForSingleObject(_hMutex, INFINITE);
	}
	void CMutexBase::Unlock()
	{
		ReleaseMutex(_hMutex);
	}


	CHisMutex::CHisMutex(CMutexBase& base)
		: _base(base)
	{
		_base.Lock();
	}
	CHisMutex::~CHisMutex()
	{
		_base.Unlock();
	}

}//..namespace HisUtil
