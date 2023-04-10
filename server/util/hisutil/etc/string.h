#pragma once 

#include <string>
#include <tchar.h>
#include <algorithm> 
#include <functional> 
#include <cctype>
#include <locale>
#include <vector>
#include <sstream>

namespace HisUtil {

	typedef std::basic_string<TCHAR, std::char_traits<TCHAR>, std::allocator<TCHAR> > TString;


	//codepage : CP_ACP(ansi) / CP_UTF8
	WCHAR* CA2W(UINT codepage, const CHAR* szString, WCHAR* wzString, int sizeWideChar);
	CHAR* CW2A(UINT codepage, const WCHAR* wzString, CHAR* szString, int sizeMultiByte);
	CHAR* CA2Utf8(UINT codepage, const CHAR* szString, CHAR* szUtf8, int sizeUtf8);
	CHAR* CUtf82A(UINT codepage, const CHAR* szUtf8, CHAR* szString, int sizeAnsi);

	std::wstring CA2W(UINT codepage, const CHAR* szString);
	std::string CW2A(UINT codepage, const WCHAR* wzString);


	TString format_string(const TCHAR* fmt, ...);


	/**
	*좌측 공백을 제거하여 문자열을 반환하는 함수
	*@param input : 입력받은 문자열 char*
	*@return : 좌측 공백이 제거된 문자열 char*
	*
	*/
	char*ltrim(char *input, char* sep);
	wchar_t*ltrim(wchar_t *input, wchar_t* sep);

	/**
	*우측 공백을 제거하여 문자열을 반환하는 함수
	*@param input : 입력받은 문자열 char*
	*@return : 우측 공백이 제거된 문자열 char*
	*
	*/
	char*rtrim(char* input, char* sep);
	wchar_t*rtrim(wchar_t* input, wchar_t* sep);

	/**
	*양쪽 공백을 제거하여 문자열을 반환하는 함수
	*@param input : 입력받은 문자열 char*
	*@return : 양쪽 공백이 제거된 문자열 char*
	*
	*/
	char*trim(char *input, char* sep);
	wchar_t*trim(wchar_t *input, wchar_t* sep);


	// trim from start
	static inline std::string &LTrim(std::string &s) {
		s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
		return s;
	}

	// trim from end
	static inline std::string &RTrim(std::string &s) {
		s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
		return s;
	}

	// trim from both ends
	static inline std::string &Trim(std::string &s) {
		return LTrim(RTrim(s));
	}

	#define TRIM_SPACE _T(" \n\t\v")	//개행,수평탭,수직탭
	TString trim(TString& s, const TString& drop = TRIM_SPACE);
	TString rtrim(TString s, const TString& drop = TRIM_SPACE);
	TString ltrim(TString s, const TString& drop = TRIM_SPACE);


	TString toUpper(TString s);
	TString toLower(TString s);

	//16진수( "0x1234" ) --> 10진수로 변환한다.
	int Hex2Dec(TCHAR hex[]);

	//szKey에 size만큼 0~9, A~Z, a~z 중 랜덤하게 설정하는 함수
	//TCHAR transkey[11] = _T("")
	//GetRandomString(transkey, sizeof(transkey))
	void GetRandomString(TCHAR* szKey, int size);
	TString GetRandomString(int size);


	//tok이 제거되어 문자열이 분리됩니다.(",,,가" --> (한개문자)"가")
	//buff : 원본 문자열
	//tok : 구분문자 (" ,.")
	//vec : 분리된 문자열
	//예제 : 
	//	TCHAR s1[30] = _T("The Little Prince");
	//	std::vector<HisUtil::TString> vec;
	//	StrToken(s1, _T(" "), vec);
	//	for (int i = 0; i < vec.size(); ++i)
	//		_tprintf(_T("%s\n"), vec[i]);
	void StrToken(IN TCHAR* buff, IN TCHAR* tok, OUT std::vector<HisUtil::TString>& vec);

	//delim로 구분되는 문자열이 분리됩니다.(",,,가" --> (4개문자)"" "" "" "가")
	//buff : 원본 문자열
	//delim : 구분문자 (',')
	//vec : 분리된 문자열
	//예제 : 
	//	TCHAR s1[30] = _T(",,,The Little Prince");
	//	std::vector<std::wstring> vec;
	//	wsplit(s1, L',', vec);
	//	for (int i = 0; i < vec.size(); ++i)
	//		_tprintf(_T("%s\n"), vec[i]);
	void split(IN const CHAR* buff, IN CHAR delim, OUT std::vector<std::string>& vec);
	void wsplit(IN const WCHAR* buff, IN WCHAR delim, OUT std::vector<std::wstring>& vec);


	template<typename T>
	inline void WriteFileValue(FILE* pf, T val)
	{
		fwrite(&val, sizeof(T), 1, pf);
	}
	template<typename T>
	inline void WriteFileString(FILE* pf, const T* val, UINT16 len)
	{
		//len(실제 byte 수)
		fwrite(&len, sizeof(len), 1, pf);
		//string
		fwrite(val, len * sizeof(T), 1, pf);
	}
	inline void WriteFileString(FILE* pf, HisUtil::TString& val)
	{
		//std::string t11 = "ab";	printf("size:%d, len:%d, real(%d)\n", t11.size(), t11.length(), t11.length() * sizeof(t11[0]));
		//std::string t12 = "하하";	printf("size:%d, len:%d, real(%d)\n", t12.size(), t12.length(), t12.length() * sizeof(t12[0]));
		//std::wstring t21 = L"ab";	wprintf(L"size:%d, len:%d, real(%d)\n", t21.size(), t21.length(), t21.length() * sizeof(t21[0]));
		//std::wstring t22 = L"하하";	wprintf(L"size:%d, len:%d, real(%d)\n", t22.size(), t22.length(), t22.length() * sizeof(t22[0]));

		UINT16 len = (UINT16)(val.length() * sizeof(val[0]));
		WriteFileString(pf, val.c_str(), len);
	}

	template<typename T>
	inline T ReadFileValue(FILE* pf, T& val)
	{
		fread(&val, sizeof(T), 1, pf);
		return val;
	}
	template<typename T>
	inline void ReadFileString(FILE* pf, T val[])
	{
		UINT16 len = 0;
		fread(&len, sizeof(len), 1, pf);

		fread(val, len, 1, pf);
	}
	inline void ReadFileString(FILE* pf, HisUtil::TString& val)
	{
		UINT16 len = 0;
		fread(&len, sizeof(len), 1, pf);

		val.resize(len / sizeof(TCHAR));
		TCHAR* buf = (TCHAR*)val.c_str();
		fread(buf, len * sizeof(TCHAR), 1, pf);
	}


	/*	사용예
		HisUtil::TString buf1 = HisUtil::format_string(_T("Unkwon Type[%d]"), 5);

		HisUtil::String buf2, buf3;
		buf2.format(_T("Unkwon Type[%d]"), 5);
		buf3.format("Unkwon Type[%d]", 5);
	*/
	class String
	{
	public:
		String();
		String(const char* buf);
		String(const wchar_t* buf);


		void clear();
		std::string& operator = (const char* buf);
		std::wstring& operator = (const wchar_t* buf);

		std::string c_string();
		std::wstring w_string();

		const char* c_str();
		const wchar_t* w_str();

		//아직 테스트를 해보지 못했습니다.
		std::string& format(const char* fmt, ...);
		std::wstring& format(const wchar_t* fmt, ...);

	private:
		bool bw_;	//wchar가 쓰여졌는가
		bool bc_;	//char가 쓰여졌는다.
		std::wstring w_str_;
		std::string c_str_;

		CModule m_module;
	};
};//..namespace HisUtil {