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
	*���� ������ �����Ͽ� ���ڿ��� ��ȯ�ϴ� �Լ�
	*@param input : �Է¹��� ���ڿ� char*
	*@return : ���� ������ ���ŵ� ���ڿ� char*
	*
	*/
	char*ltrim(char *input, char* sep);
	wchar_t*ltrim(wchar_t *input, wchar_t* sep);

	/**
	*���� ������ �����Ͽ� ���ڿ��� ��ȯ�ϴ� �Լ�
	*@param input : �Է¹��� ���ڿ� char*
	*@return : ���� ������ ���ŵ� ���ڿ� char*
	*
	*/
	char*rtrim(char* input, char* sep);
	wchar_t*rtrim(wchar_t* input, wchar_t* sep);

	/**
	*���� ������ �����Ͽ� ���ڿ��� ��ȯ�ϴ� �Լ�
	*@param input : �Է¹��� ���ڿ� char*
	*@return : ���� ������ ���ŵ� ���ڿ� char*
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

	#define TRIM_SPACE _T(" \n\t\v")	//����,������,������
	TString trim(TString& s, const TString& drop = TRIM_SPACE);
	TString rtrim(TString s, const TString& drop = TRIM_SPACE);
	TString ltrim(TString s, const TString& drop = TRIM_SPACE);


	TString toUpper(TString s);
	TString toLower(TString s);

	//16����( "0x1234" ) --> 10������ ��ȯ�Ѵ�.
	int Hex2Dec(TCHAR hex[]);

	//szKey�� size��ŭ 0~9, A~Z, a~z �� �����ϰ� �����ϴ� �Լ�
	//TCHAR transkey[11] = _T("")
	//GetRandomString(transkey, sizeof(transkey))
	void GetRandomString(TCHAR* szKey, int size);
	TString GetRandomString(int size);


	//tok�� ���ŵǾ� ���ڿ��� �и��˴ϴ�.(",,,��" --> (�Ѱ�����)"��")
	//buff : ���� ���ڿ�
	//tok : ���й��� (" ,.")
	//vec : �и��� ���ڿ�
	//���� : 
	//	TCHAR s1[30] = _T("The Little Prince");
	//	std::vector<HisUtil::TString> vec;
	//	StrToken(s1, _T(" "), vec);
	//	for (int i = 0; i < vec.size(); ++i)
	//		_tprintf(_T("%s\n"), vec[i]);
	void StrToken(IN TCHAR* buff, IN TCHAR* tok, OUT std::vector<HisUtil::TString>& vec);

	//delim�� ���еǴ� ���ڿ��� �и��˴ϴ�.(",,,��" --> (4������)"" "" "" "��")
	//buff : ���� ���ڿ�
	//delim : ���й��� (',')
	//vec : �и��� ���ڿ�
	//���� : 
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
		//len(���� byte ��)
		fwrite(&len, sizeof(len), 1, pf);
		//string
		fwrite(val, len * sizeof(T), 1, pf);
	}
	inline void WriteFileString(FILE* pf, HisUtil::TString& val)
	{
		//std::string t11 = "ab";	printf("size:%d, len:%d, real(%d)\n", t11.size(), t11.length(), t11.length() * sizeof(t11[0]));
		//std::string t12 = "����";	printf("size:%d, len:%d, real(%d)\n", t12.size(), t12.length(), t12.length() * sizeof(t12[0]));
		//std::wstring t21 = L"ab";	wprintf(L"size:%d, len:%d, real(%d)\n", t21.size(), t21.length(), t21.length() * sizeof(t21[0]));
		//std::wstring t22 = L"����";	wprintf(L"size:%d, len:%d, real(%d)\n", t22.size(), t22.length(), t22.length() * sizeof(t22[0]));

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


	/*	��뿹
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

		//���� �׽�Ʈ�� �غ��� ���߽��ϴ�.
		std::string& format(const char* fmt, ...);
		std::wstring& format(const wchar_t* fmt, ...);

	private:
		bool bw_;	//wchar�� �������°�
		bool bc_;	//char�� �������´�.
		std::wstring w_str_;
		std::string c_str_;

		CModule m_module;
	};
};//..namespace HisUtil {