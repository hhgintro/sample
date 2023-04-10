#pragma once

#include "../module/module.h"

namespace HisUtil {

	//숫자형을 가져올 때...성공유무를 판단하는 디폴트 값.
	const UINT32 DEFAULT_VALUE = 0xFAAAAAAA;

	class CIniLoader
	{
	public:
		CIniLoader();
		virtual ~CIniLoader();

	private:
		FILE* file_;

		TCHAR	m_filename[MAX_PATH];
		CModule m_module;

	private:
		BOOL	GetNormalValue(LPCTSTR keyName, LPCTSTR valueName, UINT32& values);

	public:
		BOOL	Open(LPCTSTR filename);
		BOOL	Close();

		BOOL	SetValue(LPCTSTR keyName, LPCTSTR valueName, LPCTSTR values);
		BOOL	SetValue(LPCTSTR keyName, LPCTSTR valueName, UINT32 values);
		BOOL	SetValue(LPCTSTR keyName, LPCTSTR valueName, FLOAT values);

		BOOL	GetValue(LPCTSTR keyName, LPCTSTR valueName, LPTSTR values, UINT32 bufferLength);
		BOOL	GetValue(LPCTSTR keyName, LPCTSTR valueName, FLOAT& values);


		template<class T>
		BOOL	GetValue(LPCTSTR keyName, LPCTSTR valueName, T& values)
		{
			if (!keyName || !valueName)
				return FALSE;

			UINT32 temp = 0;
			if(FALSE == GetNormalValue(keyName, valueName, temp))
				return FALSE;

			values = (T)temp;
			return TRUE;
		}
	};

};//..namespace HisUtil {
