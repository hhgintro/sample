#pragma once

#include <vector>
#include <string>
#include <map>
#include <utility>


namespace HisUtil
{
	std::string format(const char *fmt, ...);
	std::string format_arg_list(const char *fmt, va_list args);
	std::wstring format(const wchar_t *fmt, ...);
	std::wstring format_arg_list(const wchar_t *fmt, va_list args);

	bool IsWow64();
	bool EnablePrivilege(LPCTSTR szPrivilege);

	class CHexToInt
	{
	public:
		CHexToInt();
		~CHexToInt();
	
		// HEX �ڵ�� 2���ھ� ���� �о ��ȯ, �Ǵ� 2���� ���� ���̿� �����ڰ� ���� ��� ������ ����
		std::vector<unsigned char> Convert(const std::string& strConvert, bool IsExistToken = false);
		std::vector<unsigned char> Convert(const std::wstring& strConvert, bool IsExistToken = false);

	private:
		char* pszTemp;
		std::map<std::string, int> m_HexData;
	};

	bool LaunchAppWithDesktop(LPCTSTR pszApplicationPath, LPTSTR pszDesktopName );

	// TCHAR -> UTF-8, UTF-8 -> WCHAR, UTF-8 -> CHAR �� ���� �Լ� ���
	class CT2U8
	{
	public:
		CT2U8(void);
		CT2U8(LPCSTR lpStr);
		CT2U8(LPCWSTR lpwStr);
		CT2U8(const CT2U8& str);

		~CT2U8(void);

		CT2U8& operator =(LPCSTR& pszString);
		CT2U8& operator =(LPCWSTR& pszString);
		CT2U8& operator =(const CT2U8& szString);

		// UTF-8 ���� ���ڿ� ��ȯ, �����ϸ� �ȵ�
		operator LPSTR ();				
		// UTF-8 ���� ���ڿ� ��ȯ
		operator std::string ();		
		// WCHAR ���� ���ڿ� ��ȯ
		operator std::wstring ();		

		size_t ConvertUTF8ToCHAR(std::string& strString);
		size_t ConvertUTF8ToWCHAR(std::wstring& strString);

		// ���� UTF8 ���ڿ��� ���̸� ��ȯ
		size_t GetLength()
		{
			return m_nLen;
		}
	
		// ���� UTF8 ���ڿ� ��ȯ
		std::string GetUTF8();
		std::wstring GetUTF16();

		// �ܺο��� �̹� ��ȯ�� UTF8 ���ڿ��� �Ҵ�
		void AssignUTF8(LPCSTR lpStr);

	private:
		void DeletePtr();
		size_t ConvertCHARToUTF8( LPCSTR pszString );
		size_t ConvertWCHARToUTF8( LPCWSTR pszString );

		char *m_pszUTF8;
		size_t m_nLen;
	};

};//..namespace HisUtil