#pragma once
class CCommentOption
{
public:
	CCommentOption();
	~CCommentOption();

	//�����˻��� ���� enum�� �̸��� �Է��մϴ�.
	//(����): enum GameResultCode
	char* GetEnumSymbol() { return m_enumsymbol; }
	void SetEnumSymbol(char* sym) { strcpy_s(m_enumsymbol, sym); }

	//�ּ��� �������� ���߿���(�ٱ��������ΰ��) �ش������� �����´�.
	char* GetComment() { return m_comment; }
	void SetComment(char* commets) { strcpy_s(m_comment, commets); }

	//������ ������ ��,�� ������ �߰��Ѵ�.
	void AddStartSyntax(WCHAR* syntax) { m_startsyntax.push_back(std::wstring(syntax)); }
	void AddEndSyntax(WCHAR* syntax) { m_endsyntax.push_back(std::wstring(syntax)); }
	void ClearSyntax() { m_startsyntax.clear();	m_endsyntax.clear(); }

	std::vector<std::wstring>& GetStartSyntax() { return m_startsyntax; }
	std::vector<std::wstring>& GetEndSyntax() { return m_endsyntax; }

private:

	//enum�� �̸�(�������ΰ������ ���, ������ �˻��ϱ� ���ؼ�)
	char m_enumsymbol[256];
	
	//�˻��ϰ��� �ϴ� �ּ��� Ű����(�ٱ�������)
	char m_comment[256];

	//���� ���� ����
	std::vector<std::wstring> m_startsyntax;

	//���� ���� ����
	std::vector<std::wstring> m_endsyntax;
};

