#pragma once
class CCommentOption
{
public:
	CCommentOption();
	~CCommentOption();

	//빠른검색을 위해 enum의 이름을 입력합니다.
	//(예시): enum GameResultCode
	char* GetEnumSymbol() { return m_enumsymbol; }
	void SetEnumSymbol(char* sym) { strcpy_s(m_enumsymbol, sym); }

	//주석이 여러개인 것중에서(다국어지원인경우) 해당정보를 가져온다.
	char* GetComment() { return m_comment; }
	void SetComment(char* commets) { strcpy_s(m_comment, commets); }

	//생성할 파일의 앞,뒤 구문을 추가한다.
	void AddStartSyntax(WCHAR* syntax) { m_startsyntax.push_back(std::wstring(syntax)); }
	void AddEndSyntax(WCHAR* syntax) { m_endsyntax.push_back(std::wstring(syntax)); }
	void ClearSyntax() { m_startsyntax.clear();	m_endsyntax.clear(); }

	std::vector<std::wstring>& GetStartSyntax() { return m_startsyntax; }
	std::vector<std::wstring>& GetEndSyntax() { return m_endsyntax; }

private:

	//enum의 이름(여러개인경우등등을 대비, 빠르게 검색하기 위해서)
	char m_enumsymbol[256];
	
	//검색하고자 하는 주석의 키워드(다국어지원)
	char m_comment[256];

	//파일 시작 구문
	std::vector<std::wstring> m_startsyntax;

	//파일 종료 구문
	std::vector<std::wstring> m_endsyntax;
};

