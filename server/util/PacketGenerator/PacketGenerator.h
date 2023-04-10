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
	TCHAR buf[MAX_LINE_LENGTH];		//�Ķ����(type + name)
	TCHAR type[MAX_LINE_LENGTH];	//�Ķ������ ��
	TCHAR name[MAX_LINE_LENGTH];	//�Ķ������ ����
	TCHAR length[MAX_LINE_LENGTH];	//���ڿ� ����

	//tstring buf;	//�Ķ����(type + name)
	//tstring type;	//�Ķ������ ��
	//tstring name;	//�Ķ������ ����
	//tstring length;	//���ڿ� ����

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
	std::vector<HisUtil::TString> comment;	//�ּ���
	UINT16 id;						//�������� ��ȣ
	TCHAR name[MAX_LINE_LENGTH];	//�������� �̸�
	//tstring name;	//�������� �̸�
	int cntParam;					//�Ķ���� ����
	stParameter par[MAX_PARAMETER_COUNT];
	bool bUnreliable;		//PACKET_CONTEXT
	bool bEncrypt;			//encrpyt/decrypt
	bool bIsUdp;			//UDP ���� ó���� ����

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
	TCHAR name[MAX_LINE_LENGTH];	//X2L ������ ��� ������������ ����
	//tstring name;					//X2L ������ ��� ������������ ����
	UINT16 id;						//���������� ID�� �����Ѵ�.(������)
	UINT16 offset;					//���������� ID�� �����Ѵ�.
	HisUtil::TString  version;		//��������
	int cntProtocol;				//�������� ����

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

	const TCHAR* RenameCsType(TCHAR* type);	//c++ ����ŸŸ���� cs ����ŸŸ������ �����Ѵ�.
	const TCHAR* GenericType(TCHAR* type, OUT HisUtil::TString& key);	//cs List�� Ÿ���� �����ɴϴ�.(List<stRemote>���� stRemote�� ����)

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
