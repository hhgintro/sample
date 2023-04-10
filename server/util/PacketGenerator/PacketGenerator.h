#pragma once

#define PROTOCOL_USING_CS			_T("using")
#define PROTOCOL_RENAME_CS			_T("rename cs")
#define PROTOCOL_HEADER				_T("global")
#define PROTOCOL_VERSION			_T("PT_VERSION")
#define PROTOCOL_OPTION_START		_T("[")
#define PROTOCOL_OPTION_SEPERATOR	_T(",")
#define PROTOCOL_OPTION_END			_T("]")
#define PROTOCOL_CONTEXT			_T("unreliable")
#define PROTOCOL_ENCRYPT			_T("encrypt")
#define PROTOCOL_UDP				_T("udp")
#define PROTOCOL_ID					_T("id")
#define PROTOCOL_COMMA				_T(",")
#define MARK_EMPTY_BLOCK			_T(" ")
#define MARK_COMMA					_T(",")
#define MARK_EQUAL					_T("=")
#define PARAMETER_OPEN				_T("(")
#define PARAMETER_CLOSE				_T(")")
#define ARRAY_OPEN					_T("[")
#define ARRAY_CLOSE					_T("]")
#define HEART_BEAT_PROTOCOL			_T("CORE_HEART_BEAT_")

#define MAX_LINE_LENGTH			2048
#define MAX_PARAMETER_COUNT		256
#define MAX_PROTOCOL_COUNT		256

enum ON_PROTOCOL {
	enNone,
	enStart,
	enEnd
};
enum PARAM_TYPE {
	enValues,
	enArray,
	enString,
	enStructure,
	enStdVector
};
struct stParameter
{
	TCHAR buf[MAX_LINE_LENGTH];		//파라미터(type + name)
	TCHAR type[MAX_LINE_LENGTH];	//파라미터의 형
	TCHAR name[MAX_LINE_LENGTH];	//파라미터의 변수
	TCHAR length[MAX_LINE_LENGTH];	//문자열 길이

	//tstring buf;	//파라미터(type + name)
	//tstring type;	//파라미터의 형
	//tstring name;	//파라미터의 변수
	//tstring length;	//문자열 길이

	PARAM_TYPE par;

	stParameter()
	{
		memset(buf, 0, sizeof(buf));
		memset(type, 0, sizeof(type));
		memset(name, 0, sizeof(name));
		memset(length, 0, sizeof(length));

		par = enValues;
	}
};

struct stProtocol
{
	std::vector<HisUtil::TString> comment;	//주석문
	UINT16 id;						//프로토콜 번호
	TCHAR name[MAX_LINE_LENGTH];	//프로토콜 이름
	//tstring name;	//프로토콜 이름
	int cntParam;					//파라미터 개수
	stParameter par[MAX_PARAMETER_COUNT];
	bool bUnreliable;		//PACKET_CONTEXT
	bool bEncrypt;			//encrpyt/decrypt
	bool bIsUdp;			//UDP 별도 처리를 위해

	stProtocol()
	{
		comment.clear();
		id			= 0;
		memset(name, 0, sizeof(name));
		cntParam	= 0;
		bUnreliable = false;
		bEncrypt	= false;
		bIsUdp		= false;
	}
};

struct stProtocolHeader
{
	TCHAR name[MAX_LINE_LENGTH];	//X2L 어디어디랑 통신 프로토콜인지 정의
	//tstring name;					//X2L 어디어디랑 통신 프로토콜인지 정의
	UINT16 id;						//프로토콜의 ID를 설정한다.(시작점)
	UINT16 offset;					//프로토콜의 ID를 설정한다.
	HisUtil::TString  version;		//버전정보
	int cntProtocol;				//프로토콜 개수

	stProtocolHeader()
	{
		memset(name, 0, sizeof(name));
		id			= 0;
		offset		= 0;
		cntProtocol = 0;
	}
};


struct stParam
{
	int a;
};

class CPacketGenerator
{
	typedef std::map<std::wstring, std::wstring>	MAP_RENAME_CS;
	typedef std::vector<HisUtil::TString>			VEC_USING_CS;

public:
	CPacketGenerator(void);
	~CPacketGenerator(void);


	BOOL LoadXmlConstValues(TCHAR* filename);
	BOOL LoadProtocolFile(TCHAR* filename);

	void CreateCsProtocolFile(TCHAR* path);
	void CreateCsStructFile(TCHAR* path);

	void CreateProtocolFile(TCHAR* path);
	void CreateStructFile(TCHAR* path);
	void CreateRecvFile(TCHAR* path);
	void CreateSendFile(TCHAR* path);

	stProtocolHeader& GetHeader() { return header_; }

private:
	BOOL CheckComments(TCHAR* buf, UINT length);

	BOOL IsNumberType(TCHAR* type);
	BOOL IsStringType(TCHAR* type);
	BOOL IsVectorType(TCHAR* type);

	BOOL LoadProtocolName(TCHAR* posBuffer);
	BOOL LoadOption(TCHAR* posBuffer);
	BOOL LoadParam(TCHAR* posBuffer);
	void LoadParam0(TCHAR* posStart, TCHAR* posSeperator);

	const TCHAR* RenameCsType(TCHAR* type);	//c++ 데이타타입을 cs 데이타타입으로 변경한다.
	const TCHAR* GenericType(TCHAR* type, OUT HisUtil::TString& key);	//cs List의 타입을 가져옵니다.(List<stRemote>에서 stRemote을 리턴)

private:
	stProtocolHeader header_;
	stProtocol* protocol_;
	//stProtocol protocol[MAX_PROTOCOL_COUNT];


	HisUtil::CMemoryPool<HisUtil::TString, stParam> mapConstValues_;
	HisUtil::CMemoryPool<HisUtil::TString, stParam> mapConstStrings_;
	//HisUtil::CMemoryPool<std::wstring, stParam> mapConstValues_;

	MAP_RENAME_CS mapRenameCs_;
	VEC_USING_CS vecUsingCs_;

};
