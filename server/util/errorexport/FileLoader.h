#pragma once

class CFileLoader
{
public:
	CFileLoader();
	virtual ~CFileLoader();

	//enum 정보를 담고있는 파일 경로
	bool LoadEnumFile(TCHAR* path);
	//생성할 파일 경로
	//bCS : cs 파일 생성유무
	bool MakeFile(CCommentOption& opt, TCHAR* path, BOOL bCS);
	//
	int Tokenize(CCommentOption& opt);
	bool IsComment(char* token, CCommentOption& opt);
	void SetEnumValue(char* token);

	char* GetBuff() { return m_buff; }

private:
	//enum정보를 담고있는 파일을 읽어오는 버퍼
	char* m_buff;

	//enum값의 주석을 저장한다.
	std::map<int, std::string> m_pool;

	//enum형 개수
	int m_arraycount;
};

/**
예시:

CFileLoader loader;
loader.LoadEnumFile("enum형이 선언된 파일 절대경로");

CCommentOption opt;
opt.SetEnumSymbol("enum형 이름-->예시: enum GameResultCode");
opt.SetComment("주석키워드-->예시: //[kr]");
loader.Tokenize(opt);

opt.AddStartSyntax("출력할 파일의 선행문자열 -->예시: #pragma once\n\n\n");
opt.AddStartSyntax("출력할 파일의 선행문자열 -->예시: static const wchar_t* GameResultCodeString[] = {");
opt.AddEndSyntax("출력할 파일의 후행문자열 -->예시: \n};\n");
loader.MakeFile(opt, "오류코드 스트링을 출력할 파일의 절대경로");

*/
