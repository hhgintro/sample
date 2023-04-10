#include "stdafx.h"
#include "string.h"

namespace HisUtil {

	//codepage : CP_ACP(ansi) / CP_UTF8
	WCHAR* CA2W(UINT codepage, const CHAR* szString, WCHAR* wzString, int sizeWideChar)
	{
		//사용예
		//char szIP2[] = "abc가나abc";
		//wchar_t wzIP2[16] = L"";
		//wprintf(L"%s\n", CA2W(CP_ACP, szIP2, wzIP2, sizeof(wzIP2)));		// *** size: 문자열길이 + 1 *** //

		//returns 0 on fail
		//int result = ::MultiByteToWideChar(codepage, 0, szString, (int)strlen(szString) + 1, wzString, sizeWideChar);
		int result = ::MultiByteToWideChar(codepage, 0, szString, -1, wzString, sizeWideChar);
		return wzString;
	}

	//codepage : CP_ACP(ansi) / CP_UTF8
	CHAR* CW2A(UINT codepage, const WCHAR* wzString, CHAR* szString, int sizeMultiByte)
	{
		//사용예
		//wchar_t wzIP1[] = L"abc가나abc";
		//char szIP1[16] = "";
		//printf("%s\n", CW2A(CP_ACP, wzIP1, szIP1, sizeof(szIP1)));		// *** size: 문자열길이 * sizeof(wchar_t)) + 1 *** //

		//returns 0 on fail
		int result = ::WideCharToMultiByte(codepage, 0, wzString, -1, szString, sizeMultiByte, NULL, NULL);
		return szString;
	}

	//codepage : CP_ACP(ansi) / CP_UTF8
	CHAR* CA2Utf8(UINT codepage, const CHAR* szString, CHAR* szUtf8, int sizeUtf8)
	{
		//사용예 ( ansi -> utf8)
		//char szIP[] = "abc가나abc";
		//char szUtf8[16] = "";
		//HisUtil::CA2Utf8(CP_ACP, szIP, szUtf8, sizeof(szUtf8));
		////사용예 ( utf8 -> ansi)
		//char szAnsi[16] = "";
		//HisUtil::CUtf82A(CP_ACP, szUtf8, szAnsi, sizeof(szAnsi));

		wchar_t wzTemp[4096] = L"";
		//char szBuf[4096] = "";
		CA2W(codepage, szString, wzTemp, sizeof(wzTemp));
		return CW2A(CP_UTF8, wzTemp, szUtf8, sizeUtf8);
	}

	CHAR* CUtf82A(UINT codepage, const CHAR* szUtf8, CHAR* szString, int sizeAnsi)
	{
		//사용예 : 위 참조
		wchar_t wzTemp[4096] = L"";
		CA2W(CP_UTF8, szUtf8, wzTemp, sizeof(wzTemp));
		return CW2A(codepage, wzTemp, szString, sizeAnsi);
	}

	//codepage : CP_ACP(ansi) / CP_UTF8
	std::wstring CA2W(UINT codepage, const CHAR* szString)//, WCHAR* wzString, int sizeWideChar)
	{
		//사용예
		//char szIP2[] = "abc가나abc";
		//wchar_t wzIP2[16] = L"";
		//wprintf(L"%s\n", CA2W(CP_ACP, szIP2, wzIP2, sizeof(wzIP2)));		// *** size: 문자열길이 + 1 *** //

		WCHAR wzString[1024] = L"";

		//returns 0 on fail
		//int result = ::MultiByteToWideChar(codepage, 0, szString, (int)strlen(szString) + 1, wzString, sizeWideChar);
		int result = ::MultiByteToWideChar(codepage, 0, szString, -1, wzString, sizeof(wzString));
		return wzString;
	}

	//codepage : CP_ACP(ansi) / CP_UTF8
	std::string CW2A(UINT codepage, const WCHAR* wzString)// , CHAR* szString, int sizeMultiByte)
	{
		//사용예
		//wchar_t wzIP1[] = L"abc가나abc";
		//char szIP1[16] = "";
		//printf("%s\n", CW2A(CP_ACP, wzIP1, szIP1, sizeof(szIP1)));		// *** size: 문자열길이 * sizeof(wchar_t)) + 1 *** //

		CHAR szString[1024] = "";
		//returns 0 on fail
		int result = ::WideCharToMultiByte(codepage, 0, wzString, -1, szString, sizeof(szString), NULL, NULL);
		return szString;
	}

	TString format_string(const TCHAR* fmt, ...)
	{
		TString buffer;
		buffer.resize(10000);

		int size = (int)_tcslen(fmt) * 2;
		va_list ap;
		while (1) {
			va_start(ap, fmt);
			int n = _vstprintf_s((TCHAR*)buffer.data(), buffer.size(), fmt, ap);
			va_end(ap);
			if (n > -1 && n < size) {
				buffer.resize(n);
				return buffer;
			}
			if (n > -1)
				size = n + 1;
			else
				size *= 2;
		}
		return buffer;
	}

	// 줄 앞뒤의 공백, 탭을 없애주는 함수, 전체 문자열 길이 반환
	//int Trim(char *line)
	//{
	//	int len = 0;
	//	char cpTrim[1024];
	//	int xMan = 0;
	//	int i;

	//	len = (int)strlen(line);
	//	if (len >= 1024)
	//	{
	//		puts("string too long");
	//		return -1;
	//	}

	//	strcpy_s(cpTrim, line);

	//	// 앞에거 잘라내기
	//	for (i = 0; i < len; i++)
	//	{
	//		if (cpTrim[i] == ' ' || cpTrim[i] == '\t')
	//			xMan++;
	//		else
	//			break;
	//	}

	//	// 뒤에거 잘라내기
	//	for (i = len - 2; i >= 0; i--)
	//	{
	//		if (cpTrim[i] == ' ' || cpTrim[i] == '\t' || cpTrim[i] == '\n')
	//			cpTrim[i] = '\0';
	//		else
	//			break;
	//	}

	//	strcpy_s(line, len, cpTrim + xMan);

	//	return (int)strlen(line);
	//}

	char* ltrim(char *input, char* sep)
	{
		int spacecount = 0;
		int len = (int)strlen(input) + 1;//문자끝 포함('\0' - memcpy에서 포함시키기 위해)
		for (int i = 0; i < len; ++i)
		{
			//분리할 문자열이 존재하면 true
			bool bfound = false;
			for (int cnt = 0; cnt < (int)strlen(sep); ++cnt)
			{
				if (*(input + i) == sep[cnt])
				{
					bfound = true;
					break;
				}
			}

			//찾았으면, 다음 문자 체크하자.
			if (true == bfound)
			{
				++spacecount;
				continue;
			}
			//못찾으면, 그만.
			break;
		}

		//strcpy는 왜이리 에러가 많은지. memcpy를 사용했다.
		//strcpy_s(input, 1024, input + spacecount);
		//memcpy_s(input, len, input + spacecount, len - spacecount);
		//strcpy_s(input, (len - spacecount), input + spacecount);
		//printf(input);
		return input + spacecount; //ltrim은 원본의 값을 변경하지 않는다.
	}
	wchar_t* ltrim(wchar_t *input, wchar_t* sep)
	{
		int spacecount = 0;
		int len = (int)wcslen(input) + 1;//문자끝 포함('\0' - memcpy에서 포함시키기 위해)
		for (int i = 0; i < len; ++i)
		{
			//분리할 문자열이 존재하면 true
			bool bfound = false;
			for (int cnt = 0; cnt < (int)wcslen(sep); ++cnt)
			{
				if (*(input + i) == sep[cnt])
				{
					bfound = true;
					break;
				}
			}

			//찾았으면, 다음 문자 체크하자.
			if (true == bfound)
			{
				++spacecount;
				continue;
			}
			//못찾으면, 그만.
			break;
		}

		//strcpy는 왜이리 에러가 많은지. memcpy를 사용했다.
		//strcpy_s(input, 1024, input + spacecount);
		//memcpy_s(input, len, input + spacecount, (len - spacecount));
		//wcscpy_s(input, (len - spacecount), input + spacecount);
		//printf(input);
		return input + spacecount; //ltrim은 원본의 값을 변경하지 않는다.
	}
	/**
	*우측 공백을 제거하여 문자열을 반환하는 함수
	*@param input : 입력받은 문자열 char*
	*@return : 우측 공백이 제거된 문자열 char*
	*
	*/
	char* rtrim(char* input, char* sep)
	{
		int spacecount = 0;
		int len = (int)strlen(input);
		for (int i = len - 1; i >= 0; --i)
		{
			//분리할 문자열이 존재하면 true
			bool bfound = false;
			for (int cnt = 0; cnt < (int)strlen(sep); ++cnt)
			{
				if (*(input + i) == sep[cnt])
				{
					bfound = true;
					break;
				}
			}

			//찾았으면, 다음 문자 체크하자.
			if (true == bfound)
			{
				++spacecount;
				continue;
			}

			//못찾으면, 문자열 끝(i+1) 설정해주고, 그만.
			input[i + 1] = '\0';
			break;
		}
		return input;
	}
	wchar_t* rtrim(wchar_t* input, wchar_t* sep)
	{
		int spacecount = 0;
		int len = (int)wcslen(input);
		for (int i = len - 1; i >= 0; --i)
		{
			//분리할 문자열이 존재하면 true
			bool bfound = false;
			for (int cnt = 0; cnt < (int)wcslen(sep); ++cnt)
			{
				if (*(input + i) == sep[cnt])
				{
					bfound = true;
					break;
				}
			}

			//찾았으면, 다음 문자 체크하자.
			if (true == bfound)
			{
				++spacecount;
				continue;
			}

			//못찾으면, 문자열 끝(i+1) 설정해주고, 그만.
			input[i + 1] = '\0';
			break;
		}
		return input;
	}
	/**
	*양쪽 공백을 제거하여 문자열을 반환하는 함수
	*@param input : 입력받은 문자열 char*
	*@return : 양쪽 공백이 제거된 문자열 char*
	*
	*/
	char* trim(char *input, char* sep)
	{
		return ltrim(rtrim(input, sep), sep);
	}
	wchar_t* trim(wchar_t *input, wchar_t* sep)
	{
		return ltrim(rtrim(input, sep), sep);
	}

	TString trim(TString& s, const TString& drop)
	{
		TString r = s.erase(s.find_last_not_of(drop) + 1);
		return r.erase(0, r.find_first_not_of(drop));
	}
	TString rtrim(TString s, const TString& drop)
	{
		return s.erase(s.find_last_not_of(drop) + 1);
	}
	TString ltrim(TString s, const TString& drop)
	{
		return s.erase(0, s.find_first_not_of(drop));
	}

	TString toUpper(TString s)
	{
		TString str = s;
		transform(str.begin(), str.end(), str.begin(), ::toupper);
		return str;
	}
	TString toLower(TString s)
	{
		TString str = s;
		transform(str.begin(), str.end(), str.begin(), ::tolower);
		return str;
	}


	//16진수( "0x1234" ) --> 10진수로 변환한다.
	int Hex2Dec(TCHAR hex[])
	{
		int num, total = 0;
		int i = 0;

		while (hex[i] != 0)
		{
			//0x1234 에서 앞부분 "0x" 부분을 제거한다.
			if (_T('x') == hex[i] || _T('X') == hex[i])
			{
				++i;
				continue;
			}

			if (_T('0') <= hex[i] && hex[i] <= _T('9'))
				num = hex[i] - 48;
			else if (_T('A') <= hex[i] && hex[i] <= _T('F'))
				num = hex[i] - 55;
			else if (_T('a') <= hex[i] && hex[i] <= _T('f'))
				num = hex[i] - 87;
			else
			{
				_tprintf(_T("\n Upper Case Only \n or Not Hex!!"));
				return 0;
			}
			total = total * 16 + num;
			++i;
		}
		return total;
	}

	//szKey에 size만큼 0~9, A~Z, a~z 중 랜덤하게 설정하는 함수
	//TCHAR transkey[11] = _T("")
	//GetRandomString(transkey, sizeof(transkey))
	void GetRandomString(TCHAR* szKey, int size)
	{
		for (int key = 0; key < size - 1;)
		{
			BYTE tmp = 0;
			while (!tmp)
			{
				tmp = (BYTE)(rand() % 75) + 48;
				if (('0' <= tmp && tmp <= '9') || ('A' <= tmp && tmp <= 'B') || ('a' <= tmp && tmp <= 'b'))
				{
					//sprintf(&szKey[key],"%c", tmp);
					//memcpy(&szKey[key], &tmp, 1);
					szKey[key] = tmp;
					++key;
					break;
				}
			}
		}
	}
	TString GetRandomString(int size)
	{
		TString szKey;
		for (int key = 0; key < size - 1;)
		{
			BYTE tmp = 0;
			while (!tmp)
			{
				tmp = (BYTE)(rand() % 75) + 48;
				if (('0' <= tmp && tmp <= '9') || ('A' <= tmp && tmp <= 'B') || ('a' <= tmp && tmp <= 'b'))
				{
					//sprintf(&szKey[key],"%c", tmp);
					//memcpy(&szKey[key], &tmp, 1);
					
					szKey += tmp;
					++key;
					break;
				}
			}
		}
		return szKey;
	}

	void StrToken(IN TCHAR* buff, IN TCHAR* tok, OUT std::vector<HisUtil::TString>& vec)
	{

		TCHAR *ptrNext = NULL;
		TCHAR *ptr = _tcstok_s(buff, tok, &ptrNext);      // " " 공백 문자를 기준으로 문자열을 자름, 포인터 반환
														  //_tcstok
		while (ptr != NULL)               // 자른 문자열이 나오지 않을 때까지 반복
		{
			//_tprintf(_T("%s\n"), ptr);          // 자른 문자열 출력
			vec.push_back(ptr);
			ptr = _tcstok_s(NULL, tok, &ptrNext);      // 다음 문자열을 잘라서 포인터를 반환
		}
	}

	void split(IN const CHAR* buff, IN CHAR delim, OUT std::vector<std::string>& vec)
	{
		std::istringstream iss(buff);
		std::string token;

		while (std::getline(iss, token, delim)) {
			vec.push_back(token);
		}
	}
	void wsplit(IN const WCHAR* buff, IN WCHAR delim, OUT std::vector<std::wstring>& vec)
	{
		std::wstringstream wss(buff);
		std::wstring token;
		while (std::getline(wss, token, delim))
			vec.push_back(token);
	}






	String::String()
	{
		clear();
	}
	String::String(const char* buf)
	{
		clear();
		c_str_ = buf;
		bc_ = true;
	}
	String::String(const wchar_t* buf)
	{
		clear();
		w_str_ = buf;
		bw_ = true;
	}

	void String::clear()
	{
		bw_ = bc_ = false;
		c_str_.clear();
		w_str_.clear();
	}
	std::string& String::operator = (const char* buf)
	{
		c_str_ = buf;
		bc_ = true;
		return c_str_;
	}
	std::wstring& String::operator =(const wchar_t* buf)
	{
		w_str_ = buf;
		bw_ = true;
		return w_str_;
	}

	std::string String::c_string()
	{
		return c_str();
	}
	std::wstring String::w_string()
	{
		return w_str();
	}

	const char* String::c_str()
	{
		//모듈 보호
		if (FALSE == m_module.CheckValid())
			return "";

		if (true == bc_)
			return c_str_.c_str();
		if (true == bw_)
		{
			////convert
			//int len = (w_str_.length() * 2) + 1;
			//char* sz = new char[len];
			//HisUtil::CW2A(CP_ACP, w_str_.c_str(), sz, len);
			//push_back(sz);
			//delete[] sz;

			int len = ::WideCharToMultiByte(CP_ACP, 0, w_str_.c_str(), (int)w_str_.length() + 1, 0, 0, NULL, NULL);

			char* sz = new char[len];
			::WideCharToMultiByte(CP_ACP, 0, w_str_.c_str(), (int)w_str_.length() + 1, sz, len, NULL, NULL);
			c_str_ = sz;
			delete[] sz;

			return c_str_.c_str();
		}

		return "";
	}
	const wchar_t* String::w_str()
	{
		//모듈 보호
		if (FALSE == m_module.CheckValid())
			return L"";

		if (true == bw_)
			return w_str_.c_str();
		if (true == bc_)
		{
			int len = ::MultiByteToWideChar(CP_ACP, 0, c_str_.c_str(), (int)c_str_.length() + 1, 0, 0);

			wchar_t* wz = new wchar_t[len];
			::MultiByteToWideChar(CP_ACP, 0, c_str_.c_str(), (int)c_str_.length() + 1, wz, len);
			w_str_ = wz;
			delete[] wz;

			return w_str_.c_str();
		}

		return L"";

	}


	std::string& String::format(const char* fmt, ...)
	{
		c_str_.resize(10000);

		int size = (int)strlen(fmt);// *2;
		va_list ap;
		while (1) {
			//c_str_.resize(size);
			va_start(ap, fmt);
			int n = vsprintf_s((char*)c_str_.data(), c_str_.size(), fmt, ap);
			va_end(ap);
			if (n > -1 && n < size) {
				c_str_.resize(n);
				return c_str_;
			}
			if (n > -1)
				size = n + 1;
			else
				size *= 2;
		}
		return c_str_;
	}
	std::wstring& String::format(const wchar_t* fmt, ...)
	{
		w_str_.resize(10000);

		int size = (int)wcslen(fmt) * 2;
		va_list ap;
		while (1) {
			//w_str_.resize(size);
			va_start(ap, fmt);
			int n = vswprintf_s((wchar_t*)w_str_.data(), w_str_.size(), fmt, ap);
			va_end(ap);
			if (n > -1 && n < size) {
				w_str_.resize(n);
				return w_str_;
			}
			if (n > -1)
				size = n + 1;
			else
				size *= 2;
		}
		return w_str_;
	}

};//..namespace HisUtil {