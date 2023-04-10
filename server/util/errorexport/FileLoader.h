#pragma once

class CFileLoader
{
public:
	CFileLoader();
	virtual ~CFileLoader();

	//enum ������ ����ִ� ���� ���
	bool LoadEnumFile(TCHAR* path);
	//������ ���� ���
	//bCS : cs ���� ��������
	bool MakeFile(CCommentOption& opt, TCHAR* path, BOOL bCS);
	//
	int Tokenize(CCommentOption& opt);
	bool IsComment(char* token, CCommentOption& opt);
	void SetEnumValue(char* token);

	char* GetBuff() { return m_buff; }

private:
	//enum������ ����ִ� ������ �о���� ����
	char* m_buff;

	//enum���� �ּ��� �����Ѵ�.
	std::map<int, std::string> m_pool;

	//enum�� ����
	int m_arraycount;
};

/**
����:

CFileLoader loader;
loader.LoadEnumFile("enum���� ����� ���� ������");

CCommentOption opt;
opt.SetEnumSymbol("enum�� �̸�-->����: enum GameResultCode");
opt.SetComment("�ּ�Ű����-->����: //[kr]");
loader.Tokenize(opt);

opt.AddStartSyntax("����� ������ ���๮�ڿ� -->����: #pragma once\n\n\n");
opt.AddStartSyntax("����� ������ ���๮�ڿ� -->����: static const wchar_t* GameResultCodeString[] = {");
opt.AddEndSyntax("����� ������ ���๮�ڿ� -->����: \n};\n");
loader.MakeFile(opt, "�����ڵ� ��Ʈ���� ����� ������ ������");

*/
