#include "StdAfx.h"
#include "PacketGenerator.h"

CPacketGenerator::CPacketGenerator(void)
{
	protocol_ = new stProtocol[MAX_PROTOCOL_COUNT];

	//ZeroMemory(&header_, sizeof(header_));
	//ZeroMemory(protocol_, sizeof(stProtocol) * MAX_PROTOCOL_COUNT);
}

CPacketGenerator::~CPacketGenerator(void)
{
}


BOOL CPacketGenerator::CheckComments(TCHAR* buf, UINT length)
{
	static BOOL bComment = FALSE;

	for(UINT i=0; i<length ; ++i)
	{
		if(buf[i] == '/')
		{
			if(buf[i+1] == '/')
				return TRUE;
			if(buf[i+1] == '*')
				bComment = TRUE;
		}
		else if(buf[i] == '*')
		{
			if(buf[i+1] == '/')
			{
				bComment = FALSE;
				return TRUE;
			}
		}
	}
	return bComment;
}


BOOL CPacketGenerator::LoadXmlConstValues(TCHAR* filename)
{
	if (NULL == filename)	return FALSE;

	///* xml 테스트
	TiXmlDocument doc;

	if (2 == sizeof(TCHAR))
	{
		char temp[MAX_PATH] = "";
		HisUtil::CW2A(CP_ACP, filename, temp, MAX_PATH);
		if (false == doc.LoadFile(temp))
		{
			//bool result = doc.LoadFile("./config/PacketGenerator.xml");
			LOGEVENT("HG_RED", _T("xml file(%s) load fail"), filename);
			return FALSE;
		}
	}
	else
	{
		if (false == doc.LoadFile((char*)filename))
		{
			//bool result = doc.LoadFile("./config/PacketGenerator.xml");
			LOGEVENT("HG_RED", _T("xml file(%s) load fail"), filename);
			return FALSE;
		}

	}


	TiXmlElement* root = doc.FirstChildElement( "TYPE" );
	if ( root )
	{
		TiXmlElement* elem = doc.FirstChildElement()->FirstChildElement();
		while(elem)
		{
			//printf("elem value:%s\n", elem->Value());
			TiXmlElement* child = elem->FirstChildElement();
			while (child) {
				//printf("\t\tchild value:%s\n", child->Value());

				//문자형
				if (0 == strcmp(elem->Value(), "String"))
				{
					//printf("\t\t\tSTRING\n");
					stParam* par = mapConstStrings_.Create();

					//mapConstValues_.Insert(elem->Value(), par);
					WCHAR wzString[256] = L"";
					HisUtil::CA2W(CP_ACP, (char*)child->Value(), wzString, sizeof(wzString));

					mapConstStrings_.Insert(HisUtil::TString(wzString), par);

				}
				//숫자형
				if (0 == strcmp(elem->Value(), "Value"))
				{
					//printf("\t\t\tVALUE\n");
					stParam* par = mapConstValues_.Create();

					//printf("%s console=%s file=%s dubug=%s color=%s\n"
					//	, elem->Value()
					//	, elem->Attribute( "console" )
					//	, elem->Attribute( "file" )
					//	, elem->Attribute( "debug" )
					//	, elem->Attribute( "color" ));

					//mapConstValues_.Insert(elem->Value(), par);
					WCHAR wzString[256] = L"";
					HisUtil::CA2W(CP_ACP, (char*)child->Value(), wzString, sizeof(wzString));

					mapConstValues_.Insert(HisUtil::TString(wzString), par);
				}
				child = child->NextSiblingElement();
			}
			elem = elem->NextSiblingElement();
		}
	}
	LOGEVENT("HG_GRAY", _T("success load xml(%s)"), filename);
	return TRUE;
}

//숫자형이면 TRUE;
BOOL CPacketGenerator::IsNumberType(TCHAR* type)
{
	if(NULL == mapConstValues_.Find(type))
		return FALSE;
	return TRUE;
}

BOOL CPacketGenerator::IsStringType(TCHAR* type)
{
	if (NULL == mapConstStrings_.Find(type))
		return FALSE;
	return TRUE;
}

BOOL CPacketGenerator::IsVectorType(TCHAR* type)
{
	HisUtil::TString input = type;
	if (HisUtil::TString::npos == input.find(_T("std::vector<")))
		return FALSE;
	return TRUE;
}


//프로토콜 정의 파일을 연다
BOOL CPacketGenerator::LoadProtocolFile(TCHAR* filename)
{
	if (NULL == filename)	return FALSE;

	//stProtocolHeader header;
	//stProtocol* protocol = new stProtocol[MAX_PROTOCOL_COUNT];

	//프로토콜 정의 파일을 연다
	FILE* pf = _tfopen(filename, _T("r"));
	if(!pf)
	{
		//wprintf(_T("%s 파일을 찾지 못헀습니다."), filename);
		LOGEVENT("HG_RED", _T("%s 파일을 찾지 못헀습니다."), filename);
		return FALSE;
	}


	BOOL bGlobal = false;	//본문(protocol)을 파싱중에는 불필요한 부분은 체크하지 않는다.
	ON_PROTOCOL	onProtocol = enNone;//프로토콜이 시작되면 주석을 무시하지 않고, 코드에 포함시킨다.

	//한라인을 읽어서 저장할 버퍼
	TCHAR LineBuffer[MAX_LINE_LENGTH] = _T("");
	while (_fgetts(LineBuffer, MAX_LINE_LENGTH, pf))
	{
		TCHAR* posBuffer = NULL;
		TCHAR* posStart = NULL;
		TCHAR* posEnd = NULL;


		//불필요한 문자를 제거한다.
		posBuffer = HisUtil::trim(LineBuffer, _T(" \t\n"));


		//공문자열은 제외...
		if (0 == _tcscmp(posBuffer, _T("")))
			continue;

		if (enNone == onProtocol) {
			//주석을 제거한다.
			//주석 처리( //, /* */ )
			if (CheckComments(posBuffer, static_cast<UINT>(_tcslen(posBuffer))))
				continue;


			//using
			posStart = _tcsstr(posBuffer, PROTOCOL_USING_CS);
			if (posStart)
			{
				vecUsingCs_.push_back(posBuffer);
				continue;
			}


			//rename cs
			posStart = _tcsstr(posBuffer, PROTOCOL_RENAME_CS);
			if (posStart)
			{
				posStart += _tcslen(PROTOCOL_RENAME_CS);
				posEnd = _tcsstr(posStart, _T(",")) + 1;

				std::wstring temp = posStart;
				int p1 = temp.find(_T("("));
				int p2 = temp.find(_T(","));
				int p3 = temp.find(_T(")"));

				std::wstring key = HisUtil::trim(temp.substr(p1 + 1, p2 - (p1 + 1)));
				std::wstring value = HisUtil::trim(temp.substr(p2 + 1, p3 - (p2 + 1)));

				//mapRenameCs_.insert(std::pair<std::wstring, std::wstring>(key, value));
				mapRenameCs_[key] = value;
				continue;
			}

			//PT_VERSION
			posStart = _tcsstr(posBuffer, PROTOCOL_VERSION);
			if (posStart)
			{
				std::wstring temp = posStart;
				int p1 = temp.find(_T("="));
				int p2 = temp.find(_T(";"));
				int p3 = temp.find(_T(")"));

				header_.version = HisUtil::trim(temp.substr(p1 + 1));
				continue;
			}
		}

		//protocol의 접두어와 offset을 가져온다.(global NetC2S 0xFE00)
		posStart = _tcsstr(posBuffer, PROTOCOL_HEADER);
		if(posStart)
		{
			//protocol header name
			posStart +=  _tcslen(PROTOCOL_HEADER) + 1;
			posEnd = _tcsstr(posStart, MARK_EMPTY_BLOCK) + 1;

			_tcsncpy(header_.name, posStart, posEnd - posStart - 1);//-1:이름("NetC2S") 뒤에 공백문자를 빼기 위해
			//protocol offset
			header_.id = HisUtil::Hex2Dec(posEnd);
			continue;
		}

		// { -- 프로토콜의 시작
		if(_tcsstr(posBuffer, _T("{"))) 
		{
			onProtocol = enStart;
			continue;
		}

		// }; -- 프로토콜의 끝
		if(_tcsstr(posBuffer, _T("};"))) 
		{
			onProtocol = enEnd;
			//wprintf(_T("문장의 끝을 \"};\" 로 종료하여 주세요"));
			break;
		}


		//프로토콜이 시작되면 주석을 무시하지 않고, 코드에 포함시킨다.
		if(CheckComments(posBuffer, static_cast<UINT>(_tcslen(posBuffer))))
		{
			//std::vector<HisUtil::TString> temp;
			//temp.push_back(posBuffer);
			//protocol_[header_.cntProtocol].comment.insert(protocol_[header_.cntProtocol].comment.end(), temp.begin(), temp.end());
			protocol_[header_.cntProtocol].comment.push_back(posBuffer);
			continue;
		}


		//protocol name
		LoadProtocolName(posBuffer);

		//protocol option
		if (FALSE == LoadOption(posBuffer))
			break;

		//protocol id
		protocol_[header_.cntProtocol].id = header_.id + header_.offset++;


		//protocol param
		if (FALSE == LoadParam(posBuffer))
			break;


		//헤더에 프로토콜 개수를 갱신한다.
		++header_.cntProtocol;
	}//..while( _fgetts(LineBuffer, MAX_LINE_LENGTH, pf))


	BOOL bResult = TRUE;
	switch (onProtocol)
	{
	case enNone:
		LOGEVENT("HG_RED", _T("프로토콜(%s) 시작(\"{\")을 찾지 못헀습니다."), header_.name);
		bResult = FALSE;
		break;
	case enStart:
		LOGEVENT("HG_RED", _T("프로토콜(%s) 끝(\"};\")을 찾지 못헀습니다."), header_.name);
		bResult = FALSE;
		break;
	case enEnd:
	default:
		break;
	}

	//LOGEVENT("HG_GRAY", _T("====================================="));
	//LOGEVENT("HG_GRAY", _T("프로토콜 해더"));
	//LOGEVENT("HG_GRAY", _T("  name : %s"), header_.name);
	//LOGEVENT("HG_GRAY", _T("  offset : %d"), header.offset);
	//LOGEVENT("HG_GRAY", _T("  version : %d"), header.version);
	//LOGEVENT("HG_GRAY", _T("====================================="));

	//LOGEVENT("HG_GRAY", _T("프로토콜 %d 개"), header_.cntProtocol);
	//for(int i=0; i<header_.cntProtocol; ++i)
	//{
	//	LOGEVENT("HG_GRAY", _T("  name : %s"), protocol_[i].name);
	//	for(int j=0; j<protocol_[i].cntParam; ++j)
	//	{
	//		LOGEVENT("HG_GRAY", _T("%d    buf : %s"), j+1, protocol_[i].par[j].buf);
	//		LOGEVENT("HG_GRAY", _T("%d    type : %s"), j+1, protocol_[i].par[j].type);
	//		LOGEVENT("HG_GRAY", _T("%d    name : %s"), j+1, protocol_[i].par[j].name);
	//		LOGEVENT("HG_GRAY", _T("%d    length : %s"), j+1, protocol_[i].par[j].length);
	//	}
	//}
	//LOGEVENT("HG_GRAY", _T("====================================="));

	fclose(pf);
	//::system("pause");
	return bResult;
}

void CPacketGenerator::CreateCsProtocolFile(TCHAR* path)
{
	TCHAR csPath[MAX_PATH] = _T("");
	_stprintf_s(csPath, _T("%s/cs/"), path);
	//폴더 생성 : log 폴더 아래 server 폴더를 만들려면 CreateDirectory()를 2번 호출하여야 한다.
	::CreateDirectory(csPath, 0);// Log/ 폴더 생성

	TCHAR filename[MAX_PATH] = _T("");
	_sntprintf(filename, MAX_PATH, _T("%s/%s_Protocol.cs"), csPath, GetHeader().name);

	FILE* pf = _tfopen(filename, _T("wt"));
	if (!pf)
	{
		LOGEVENT("HG_RED", _T("%s 파일 생성 실패"), filename);
		return;
	}

	_ftprintf(pf, _T("namespace %s\n{\n"), header_.name);

	//PT_VERSION
	_ftprintf(pf, _T("\tpublic class PT\n\t{\n\t\tstatic public uint %s = %s;\n\t};\n\n"), PROTOCOL_VERSION, header_.version.c_str());

	_ftprintf(pf, _T("\tpublic enum PROTOCOL : ushort\n\t{"));

	//protocol 개수
	for (int i = 0; i < header_.cntProtocol; ++i)
		_ftprintf(pf, _T("\n\t\t%s_%s\t\t\t= 0x%04x,"), header_.name, protocol_[i].name, protocol_[i].id);

	_ftprintf(pf, _T("\n\t}\n}"));

	fclose(pf);
	LOGEVENT("HG_GRAY", _T("success create file(%s)"), filename);
}
void CPacketGenerator::CreateCsStructFile(TCHAR* path)
{
	TCHAR csPath[MAX_PATH] = _T("");
	_stprintf_s(csPath, _T("%s/cs/"), path);
	//폴더 생성 : log 폴더 아래 server 폴더를 만들려면 CreateDirectory()를 2번 호출하여야 한다.
	::CreateDirectory(csPath, 0);// Log/ 폴더 생성

	TCHAR filename[MAX_PATH] = _T("");
	_sntprintf(filename, MAX_PATH, _T("%s/%s_Structure.cs"), csPath, GetHeader().name);

	FILE* pf = _tfopen(filename, _T("wt"));
	if (!pf)
	{
		LOGEVENT("HG_RED", _T("%s 파일 생성 실패"), filename);
		return;
	}

	//using
	for (int i = 0; i < (int)vecUsingCs_.size(); ++i)
	{
		_ftprintf(pf, _T("\n%s"), vecUsingCs_[i].c_str());

	}


	_ftprintf(pf, _T("\n\nnamespace %s\n{"), header_.name);


	//protocol 개수
	for (int i = 0; i < header_.cntProtocol; ++i)
	{
		_ftprintf(pf, _T("\n"));

		//주석문
		for (int cnt = 0; cnt < (int)protocol_[i].comment.size(); ++cnt)
		{
			_ftprintf(pf, _T("\n\t%s"), protocol_[i].comment[cnt].c_str());
		}

		//begin of class
		_ftprintf(pf, _T("\n\tpublic class st%s_%s : IDisposable\n\t{\n"), header_.name, protocol_[i].name);

		////생성자
		//_ftprintf(pf, _T("\tst%s_%s()"), header_.name, protocol_[i].name);

		//if (protocol_[i].cntParam)
		//{
		//	BOOL flag = FALSE;

		//	for (int k = 0; k < protocol_[i].cntParam; ++k)
		//	{
		//		if (protocol_[i].par[k].par == enValues)
		//		{
		//			if (!flag)
		//				_ftprintf(pf, _T("\n\t\t:"));
		//			else
		//				_ftprintf(pf, _T(","));
		//			_ftprintf(pf, _T(" %s(0)"), protocol_[i].par[k].name);
		//			flag = TRUE;
		//		}
		//	}
		//}
		//_ftprintf(pf, _T("\n\t{"));
		//if (protocol_[i].cntParam)
		//{
		//	for (int k = 0; k < protocol_[i].cntParam; ++k)
		//	{
		//		if (protocol_[i].par[k].par == enArray)
		//			_ftprintf(pf, _T("\n\t\tmemset(%s, 0, sizeof(%s));"), protocol_[i].par[k].name, protocol_[i].par[k].name);
		//	}
		//}
		//_ftprintf(pf, _T("\n\t}\n\n"));



		//parameter(맴버 변수) 개수
		for (int k = 0; k < protocol_[i].cntParam; ++k)
		{
			if(enStdVector == protocol_[i].par[k].par)
				_ftprintf(pf, _T("\t\tpublic %s %s = new %s();\n"), RenameCsType(protocol_[i].par[k].type), protocol_[i].par[k].name, RenameCsType(protocol_[i].par[k].type));
			else
				_ftprintf(pf, _T("\t\tpublic %s %s;\n"), RenameCsType(protocol_[i].par[k].type), protocol_[i].par[k].name);
		}

		//Dispose
		_ftprintf(pf, _T("\n\t\tpublic void Dispose()\n\t\t{"));
		for (int k = 0; k < protocol_[i].cntParam; ++k)
		{
			if (enStdVector == protocol_[i].par[k].par)
				_ftprintf(pf, _T("\n\t\t\t%s.Clear();"), protocol_[i].par[k].name);
		}
		_ftprintf(pf, _T("\n\t\t}"));


		//recv function
		_ftprintf(pf, _T("\n\n\t\tpublic void Recv(FreeNet.CPacket msgRecv)\n\t\t{"));

		//decrypt
		if (protocol_[i].bEncrypt)
			_ftprintf(pf, _T("\n\t\t\tmsgRecv.Decrypt();"));

		_ftprintf(pf, _T("\n\n\t\t\tmsgRecv.reset_pos(0);"));
		for (int k = 0; k < protocol_[i].cntParam; ++k)
		{
			switch (protocol_[i].par[k].par) {
			case enValues:
				_ftprintf(pf, _T("\n\t\t\tthis.%s = msgRecv.pop((%s)0);"), protocol_[i].par[k].name, RenameCsType(protocol_[i].par[k].type));
				break;
			case enArray:
				break;
			case enString:
				_ftprintf(pf, _T("\n\t\t\tthis.%s = msgRecv.pop_string();"), protocol_[i].par[k].name, RenameCsType(protocol_[i].par[k].type));
				break;
			case enStructure:
			case enStdVector:
				//_ftprintf(pf, _T("\n\t\t\tthis.%s = new %s();"), protocol_[i].par[k].name, RenameCsType(protocol_[i].par[k].type));
				HisUtil::TString keyGeneric;
				GenericType((TCHAR*)RenameCsType(protocol_[i].par[k].type), keyGeneric);
				_ftprintf(pf, _T("\n\t\t\tFreeNet.CPacket.pop<%s>(%s, ref msgRecv);"), keyGeneric.c_str(), protocol_[i].par[k].name);
				break;
			}
		}
		_ftprintf(pf, _T("\n\t\t}"));


		//send function
		_ftprintf(pf, _T("\n\n\t\tpublic void Send(FreeNet.CUserToken token)\n\t\t{"));
		_ftprintf(pf, _T("\n\t\t\tFreeNet.CPacket msgSend = FreeNet.CPacket.create((ushort)%s.PROTOCOL.%s_%s, 1);"), header_.name, header_.name, protocol_[i].name);

		for (int k = 0; k < protocol_[i].cntParam; ++k)
		{
			switch (protocol_[i].par[k].par) {
			case enValues:
				_ftprintf(pf, _T("\n\t\t\tmsgSend.push(%s);"), protocol_[i].par[k].name);
				break;
			case enArray:
				break;
			case enString:
				_ftprintf(pf, _T("\n\t\t\tmsgSend.push(%s);"), protocol_[i].par[k].name);
				break;
			case enStructure:
			case enStdVector:
				HisUtil::TString keyGeneric;
				GenericType((TCHAR*)RenameCsType(protocol_[i].par[k].type), keyGeneric);
				_ftprintf(pf, _T("\n\t\t\tFreeNet.CPacket.push<%s>(%s, ref msgSend);"), keyGeneric.c_str(), protocol_[i].par[k].name);
				break;
			}
		}
		//encrypt
		_ftprintf(pf, _T("\n"));
		if (protocol_[i].bEncrypt)
			_ftprintf(pf, _T("\n\t\t\tmsgSend.Encrypt();"));
		_ftprintf(pf, _T("\n\t\t\ttoken.send(msgSend);\n\t\t}"));


		//end of class
		_ftprintf(pf, _T("\n\t}//..%s;"), protocol_[i].name);
	}

	//end namespace
	_ftprintf(pf, _T("\n\n} //..namespace %s\n"), header_.name);

	fclose(pf);
	LOGEVENT("HG_GRAY", _T("success create file(%s)"), filename);
}

void CPacketGenerator::CreateProtocolFile(TCHAR* path)
{
	::CreateDirectory(path, 0);

	TCHAR filename[MAX_PATH] = _T("");
	_sntprintf(filename, MAX_PATH, _T("%s/%s_Protocol.h"), path, GetHeader().name);

	FILE* pf = _tfopen(filename, _T("wt"));
	if(!pf)
	{
		LOGEVENT("HG_RED", _T("%s 파일 생성 실패"), filename);
		return;
	}

	_ftprintf(pf, _T("#pragma once\n\n"));

	//VT_VERSION
	_ftprintf(pf, _T("const PROTOCOL_T %s_%s\t\t\t= %s;\n\n"), header_.name, PROTOCOL_VERSION, header_.version.c_str());

	//protocol 개수
	for(int i=0; i<header_.cntProtocol; ++i)
		_ftprintf(pf, _T("\nconst UINT16 %s_%s\t\t\t= 0x%04x;"), header_.name, protocol_[i].name, protocol_[i].id);


	fclose(pf);
	LOGEVENT("HG_GRAY", _T("success create file(%s)"), filename);
}

void CPacketGenerator::CreateStructFile(TCHAR* path)
{
	::CreateDirectory(path, 0);

	TCHAR filename[MAX_PATH] = _T("");
	_sntprintf(filename, MAX_PATH, _T("%s/%s_Structure.h"), path, GetHeader().name);

	FILE* pf = _tfopen(filename, _T("wt"));
	if(!pf)
	{
		LOGEVENT("HG_RED", _T("%s 파일 생성 실패"), filename);
		return;
	}

	_ftprintf(pf, _T("#pragma once\n\n"));

	//protocol 개수
	for(int i=0; i<header_.cntProtocol; ++i)
	{
		_ftprintf(pf, _T("\n"));

		//주석문
		for(int cnt=0; cnt<(int)protocol_[i].comment.size(); ++cnt)
		{
			_ftprintf(pf, _T("\n%s"), protocol_[i].comment[cnt].c_str());
		}

		_ftprintf(pf, _T("\nstruct st%s_%s\n{\n"), header_.name, protocol_[i].name);

		//생성자
		_ftprintf(pf, _T("\tst%s_%s()"), header_.name, protocol_[i].name);

		if(protocol_[i].cntParam)
		{
			BOOL flag = FALSE;

			for(int k=0; k<protocol_[i].cntParam; ++k)
			{
				if(protocol_[i].par[k].par == enValues)
				{
					if(!flag)
						_ftprintf(pf, _T("\n\t\t:"));
					else
						_ftprintf(pf, _T(","));
					_ftprintf(pf, _T(" %s(0)"), protocol_[i].par[k].name);
					flag = TRUE;
				}
			}
		}
		_ftprintf(pf, _T("\n\t{"));
		if(protocol_[i].cntParam)
		{
			for(int k=0; k<protocol_[i].cntParam; ++k)
			{
				if(protocol_[i].par[k].par == enArray)
					_ftprintf(pf, _T("\n\t\tmemset(%s, 0, sizeof(%s));"), protocol_[i].par[k].name, protocol_[i].par[k].name);
			}
		}
		_ftprintf(pf, _T("\n\t}\n\n"));



		//parameter(맴버 변수) 개수
		for(int k=0; k<protocol_[i].cntParam; ++k)
		{
			_ftprintf(pf, _T("\t%s;\n"), protocol_[i].par[k].buf);
		}

		_ftprintf(pf, _T("};\n"));
	}

	fclose(pf);
	LOGEVENT("HG_GRAY", _T("success create file(%s)"), filename);
}

void CPacketGenerator::CreateRecvFile(TCHAR* path)
{
	::CreateDirectory(path, 0);

	TCHAR filename[MAX_PATH] = _T("");
	_sntprintf(filename, MAX_PATH, _T("%s/%s_RecvPacket.h"), path, GetHeader().name);

	FILE* pf = _tfopen(filename, _T("wt"));
	if(!pf)
	{
		LOGEVENT("HG_RED", _T("%s 파일 생성 실패"), filename);
		return;
	}

	_ftprintf(pf, _T("#pragma once\n\n"));

	//protocol 개수
	for(int i=0; i<header_.cntProtocol; ++i)
	{
		//함수의 시작
		_ftprintf(pf, _T("\n\ninline void RECV_%s_%s(HisUtil::CMsg& msgRecv, st%s_%s& st)\n{\n"), header_.name, protocol_[i].name, header_.name, protocol_[i].name);

		//decrypt
		if(protocol_[i].bEncrypt)
			_ftprintf(pf, _T("\tHisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);\n"));

		_ftprintf(pf, _T("\tmsgRecv\n"));

		//parameter 개수
		for(int k=0; k<protocol_[i].cntParam; ++k)
		{
			if(protocol_[i].par[k].par == enArray)
			{
				if (0 == _tcscmp(_T("CHAR"), protocol_[i].par[k].type) || 0 == _tcscmp(_T("char"), protocol_[i].par[k].type))
					_ftprintf(pf, _T("\t\t>> HisUtil::CMsg::CMsgPack(st.%s, (int)sizeof(st.%s))\n"), protocol_[i].par[k].name, protocol_[i].par[k].name);
				else if (0 == _tcscmp(_T("WCHAR"), protocol_[i].par[k].type) || 0 == _tcscmp(_T("wchar_t"), protocol_[i].par[k].type))
					_ftprintf(pf, _T("\t\t>> HisUtil::CMsg::CMsgPack(st.%s, (int)sizeof(st.%s))\n"), protocol_[i].par[k].name, protocol_[i].par[k].name);
			}
			else
				_ftprintf(pf, _T("\t\t>> st.%s\n"), protocol_[i].par[k].name);
		}
		_ftprintf(pf, _T("\t\t;\n"));
		//log
		if (_tcsstr(protocol_[i].name, HEART_BEAT_PROTOCOL))
			_ftprintf(pf, _T("\n\tLOGEVENT(\"Heart_Beat_Packet\", _T(\"<== recv %s_%s\"));\n"), header_.name, protocol_[i].name);
		else
			_ftprintf(pf, _T("\n\tLOGEVENT(\"Session_Base_Packet\", _T(\"<== recv %s_%s\"));\n"), header_.name, protocol_[i].name);
		//함수의 끝
		_ftprintf(pf, _T("}\n"));
	}

	fclose(pf);
	LOGEVENT("HG_GRAY", _T("success create file(%s)"), filename);
}

void  CPacketGenerator::CreateSendFile(TCHAR* path)
{
	::CreateDirectory(path, 0);

	TCHAR filename[MAX_PATH] = _T("");
	_sntprintf(filename, MAX_PATH, _T("%s/%s_SendPacket.h"), path, GetHeader().name);

	FILE* pf = _tfopen(filename, _T("wt"));
	if(!pf)
	{
		LOGEVENT("HG_RED", _T("%s 파일 생성 실패"), filename);
		return;
	}

	_ftprintf(pf, _T("#pragma once\n\n"));

	//class 시작
	_ftprintf(pf, _T("\n\nclass %s_SEND : public NetCore::INetCore\n{"), header_.name);
	_ftprintf(pf, _T("\npublic:\n\t%s_SEND() {}\n\tvirtual ~%s_SEND() {}\n\n"), header_.name, header_.name);

	//protocol 개수
	for(int i=0; i<header_.cntProtocol; ++i)
	{
		//함수와 인자들
		_ftprintf(pf, _T("\tinline void SEND_%s_%s(HOSTID remote, st%s_%s& st)\n\t{\n")
			, header_.name, protocol_[i].name, header_.name, protocol_[i].name);

		//Recv 대상자 체크
		//if(protocol_[i].bIsUdp)
			_ftprintf(pf, _T("\t\tNetCore::IRemote* peer = FindRemote(remote);\n\t\tif(NULL == peer)\n\t\t{\n\t\t\tLOGEVENT(\"Session_Base_Error\", _T(\"Fail send %s_%s not found peer(0x%%p)\"), remote);\n\t\t\treturn;\n\t\t}\n\n"), header_.name, protocol_[i].name);

		//Send packet session개체
		_ftprintf(pf, _T("\t\tNetCore::CPacketSession* session = FindPacketSession(peer,%s);\n\t\tif(NULL == session)\n\t\t{\n\t\t\tLOGEVENT(\"Session_Base_Error\", _T(\"Fail send %s_%s not found session(0x%%p)\"), remote);\n\t\t\treturn;\n\t\t}\n\n")
			, (protocol_[i].bIsUdp)?L"true":L"false", header_.name, protocol_[i].name);


		//함수 구현 부분
		if(true == protocol_[i].bUnreliable)
			_ftprintf(pf, _T("\t\tHisUtil::CMsg msgSend;\n\t\tmsgSend.SetContext(NetCore::UNRELIABLE);\n\t\tmsgSend.ID(%s_%s)\n"), header_.name, protocol_[i].name);
		else
			_ftprintf(pf, _T("\t\tHisUtil::CMsg msgSend;\n\t\tmsgSend.SetContext(NetCore::RELIABLE);\n\t\tmsgSend.ID(%s_%s)\n"), header_.name, protocol_[i].name);
		//parameter 개수
		for(int k=0; k<protocol_[i].cntParam; ++k)
		{
			if(protocol_[i].par[k].par == enArray)
			{
				if (0 == _tcscmp(_T("CHAR"), protocol_[i].par[k].type) || 0 == _tcscmp(_T("char"), protocol_[i].par[k].type))
					_ftprintf(pf, _T("\t\t\t<< HisUtil::CMsg::CMsgPack(st.%s, (int)strlen(st.%s))\n"), protocol_[i].par[k].name, protocol_[i].par[k].name);
				else if (0 == _tcscmp(_T("WCHAR"), protocol_[i].par[k].type) || 0 == _tcscmp(_T("wchar_t"), protocol_[i].par[k].type))
					_ftprintf(pf, _T("\t\t\t<< HisUtil::CMsg::CMsgPack(st.%s, (int)wcslen(st.%s) * 2)\n"), protocol_[i].par[k].name, protocol_[i].par[k].name);
			}
			else
				_ftprintf(pf, _T("\t\t\t<< st.%s\n"), protocol_[i].par[k].name);
		}
		_ftprintf(pf, _T("\t\t\t;\n"));
		//함수 구현 부분

		//encrypt
		if(protocol_[i].bEncrypt)
			_ftprintf(pf, _T("\t\tHisUtil::CCrypto::Encrypt((unsigned char*)msgSend.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgSend.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgSend.GetBuf() + HisUtil::MSG_HEADER_SIZE);\n\n"));

		//if(protocol_[i].bIsUdp)
		//{
		//	//peer간 홀펀칭을 시도할 경우이거나,
		//	//홀펀칭에 성공한 경우는 peer간 전송하는데...
		//	if(0 != _tcscmp(_T("CORE_UDP_HOLE_PUNCHING_PEER_REQ"), protocol_[i].name)
		//		&& 0 != _tcscmp(_T("CORE_UDP_HOLE_PUNCHING_PEER_ACK"), protocol_[i].name))
		//	{
		//		//Server와 통신이거나,
		//		//peer간 hole punching인 경우는 체크를 뺀다.
		//		_ftprintf(pf, _T("\t\tif(NetCore::Host_Server == remote || peer->stepHolePunching_ == NetCore::enSuccess)\n"));
	
		//		_ftprintf(pf, _T("\t\t{\n\t\t\tsession->SendToPacket(context, msgSend, peer->GetRemotePublicIP(), peer->GetRemotePublicPort());\n"));
		//		_ftprintf(pf, _T("\t\t\tmsgSend.Clear();\n\n"));

		//		//log
		//		_ftprintf(pf, _T("\t\t\tLOGEVENT(\"Session_Base_Packet\", _T(\"==> send %s_%s to peer(0x%%p)\"), remote);\n"), header_.name, protocol_[i].name);
		//		_ftprintf(pf, _T("\t\t\treturn;\n\t\t}\n\n"));
		//}


		//	//hole punching 실패한 경우는 서버를 경유한다.
		//	_ftprintf(pf, _T("\t\tSEND_CORE_UDP_RELAY_SERVER_TO_PEER_NTF(peer->GetHostID(), context, msgSend);\n\t\tmsgSend.Clear();\n\n"));
		//}
		//else
		//{
		//	_ftprintf(pf, _T("\t\tsession->SendPacket(msgSend);\n\t\tmsgSend.Clear();\n\n"));
		//}

		//_ftprintf(pf, _T("\t\t//hole punching 체크\n"));
		//_ftprintf(pf, _T("\t\tif (NetCore::enSuccess == peer->stepHolePunching_)\n\t\t{\n\t\t\tsession->SendToPacket(context, msgSend, peer->GetRemotePublicIP(), peer->GetRemotePublicPort());\n\t\t\tmsgSend.Clear();\n\n"));
		////log
		//_ftprintf(pf, _T("\t\t\tLOGEVENT(\"Session_Base_Packet\", _T(\"==> send %s_%s to peer(0x%%p)\"), remote);\n\t\t\treturn;\n\t\t}\n"), header_.name, protocol_[i].name);

		//_ftprintf(pf, _T("\t\t//hole punching 실패한 경우는 서버를 경유한다.\n"));
		//_ftprintf(pf, _T("\t\telse if (NetCore::enFailed == peer->stepHolePunching_)\n\t\t{\n\t\t\tSEND_CORE_UDP_RELAY_SERVER_TO_PEER_NTF(peer->GetHostID(), context, msgSend);\n\t\t\tmsgSend.Clear();\n\n"));
		////log
		//_ftprintf(pf, _T("\t\t\tLOGEVENT(\"Session_Base_Packet\", _T(\"==> send NetC2S_CORE_CONNECT_COMPLETED_NTF to peer(0x%08x)\"), remote);\n\t\t\treturn;\n\t\t}\n\n"));

		//_ftprintf(pf, _T("\t\tsession->SendPacket(msgSend);\n\t\tmsgSend.Clear();\n\n"));

		////_ftprintf(pf, _T("\t\t//to server\n"));
		////_ftprintf(pf, _T("\t\telse if (NetCore::Host_Server == peer->GetHostID())\n\t\t{\n\t\t\tsession->SendPacket(msgSend);\n\t\t\tmsgSend.Clear();\n\n"));
		//////log
		////_ftprintf(pf, _T("\t\t\tLOGEVENT(\"Session_Base_Packet\", _T(\"==> send %s_%s to peer(0x%%p)\"), remote);\n\t\t\treturn;\n\t\t}\n\n"), header_.name, protocol_[i].name);

		////_ftprintf(pf, _T("\t\t//hole punching 실패한 경우는 서버를 경유한다.\n"));
		////_ftprintf(pf, _T("\t\tSEND_CORE_UDP_RELAY_SERVER_TO_PEER_NTF(peer->GetHostID(), context, msgSend);\n\t\tmsgSend.Clear();\n\n"));


		if (protocol_[i].bIsUdp)
		{
			//_ftprintf(pf, _T("\t\tswitch (peer->GetHolePunchingStep())\n\t\t{\n"));
			//_ftprintf(pf, _T("\t\t//hole punching(public) 체크\n"));
			//_ftprintf(pf, _T("\t\tcase NetCore::enPublicAttempt:\n\t\tcase NetCore::enPublicSuccess:\n\t\t\tsession->SendToPacket(context, msgSend, peer->GetRemotePublicIP(), peer->GetRemotePublicUdpPort());\n\t\t\tbreak;\n\n"));
			//_ftprintf(pf, _T("\t\t//hole punching(private) 체크\n"));
			//_ftprintf(pf, _T("\t\tcase NetCore::enPrivateAttempt:\n\t\tcase NetCore::enPrivateSuccess:\n\t\t\tsession->SendToPacket(context, msgSend, peer->GetRemotePrivateIP(), peer->GetRemotePrivateUdpPort());\n\t\t\tbreak;\n\n"));
			//_ftprintf(pf, _T("\t\t//hole punching 실패(public실패/private실패)한 경우는 서버를 경유한다.\n"));
			//_ftprintf(pf, _T("\t\tcase NetCore::enPrivateFailed:\n\t\t\tSEND_CORE_UDP_RELAY_SERVER_TO_PEER_NTF(peer->GetHostID(), context, msgSend);\n\t\t\tbreak;\n\n"));
			//_ftprintf(pf, _T("\t\tdefault:\n\t\t\tsession->SendPacket(msgSend);\n\t\t\tbreak;\n\t\t}\n\n"));
			_ftprintf(pf, _T("\t\tSendUdpPacket(peer, session, msgSend);\n"));
		}
		else
		{
			_ftprintf(pf, _T("\t\tsession->SendPacket(msgSend);\n"));
		}
		_ftprintf(pf, _T("\t\tmsgSend.Clear();\n"));
		//log
		if (_tcsstr(protocol_[i].name, HEART_BEAT_PROTOCOL))
			_ftprintf(pf, _T("\t\tLOGEVENT(\"Heart_Beat_Packet\", _T(\"==> send %s_%s to peer(0x%%p)\"), remote);\n"), header_.name, protocol_[i].name);
		else
			_ftprintf(pf, _T("\t\tLOGEVENT(\"Session_Base_Packet\", _T(\"==> send %s_%s to peer(0x%%p)\"), remote);\n"), header_.name, protocol_[i].name);




		//함수 끝
		_ftprintf(pf, _T("\t};\n\n\n"));
	}

	//class 끝
	_ftprintf(pf, _T("};\n"));

	fclose(pf);
	LOGEVENT("HG_GRAY", _T("success create file(%s)"), filename);
}

BOOL CPacketGenerator::LoadProtocolName(TCHAR* posBuffer)
{
	TCHAR* posStart = NULL;
	TCHAR* posEnd = NULL;

	//protocol name
	posStart = _tcsstr(posBuffer, PROTOCOL_OPTION_END);
	if (NULL == posStart)	posStart = posBuffer;
	else
	{
		posStart = HisUtil::ltrim(posStart + 1, _T(" \t"));
	}
	posEnd = _tcsstr(posBuffer, PARAMETER_OPEN);
	if (NULL == posEnd)
		return FALSE;

	_tcsncpy(protocol_[header_.cntProtocol].name, posStart, posEnd - posStart);
	return TRUE;
}

BOOL CPacketGenerator::LoadOption(TCHAR* posBuffer)
{
	TCHAR Option[1024] = _T("");//옵션의 문자열정보를 담는다.(너무 딱맞게하면 문자끝에 쓰레기값이 붙어서 크게 설정해준다.)
	TCHAR* posStart = NULL;
	TCHAR* posEnd = NULL;


	//옵션 ( [id=xxx,udp,encrypt] )
	posStart = _tcsstr(posBuffer, PROTOCOL_OPTION_START);
	if (NULL != posStart)
	{
		posEnd = _tcsstr(posBuffer, PROTOCOL_OPTION_END);//옵션의 닫힘']'을 뺴 주기 위해.
		if (NULL == posEnd)
		{
			LOGEVENT("HG_RED", _T("프로토콜(%s) 옵션 구문 오류"), protocol_[header_.cntProtocol].name);
			return FALSE;
		}

		_tcsncpy(Option, posStart, posEnd - posStart);//-1:이름("NetC2S") 뒤에 공백문자를 빼기 위해

		//UDP 여부
		if (_tcsstr(Option, PROTOCOL_UDP))		protocol_[header_.cntProtocol].bIsUdp		= true;
		//PACKET_CONTEXT 여부
		if (_tcsstr(Option, PROTOCOL_CONTEXT))	protocol_[header_.cntProtocol].bUnreliable	= true;
		//암호화 여부
		if (_tcsstr(Option, PROTOCOL_ENCRYPT))	protocol_[header_.cntProtocol].bEncrypt		= true;
		//id 설정여부
		if (_tcsstr(Option, PROTOCOL_ID))
		{
			posStart = _tcsstr(Option, _T("=")) + 1;
			TCHAR* temp = _tcsstr(posStart, _T(","));

			TCHAR pid[32] = _T("");//프로토콜 ID의 문자열정보를 담는다.(너무 딱맞게하면 문자끝에 쓰레기값이 붙어서 크게 설정해준다.)
			_tcsncpy(pid, posStart, min(temp, posEnd) - posStart);//-1:이름("NetC2S") 뒤에 공백문자를 빼기 위해
			temp = HisUtil::trim(pid, _T(" \t\n"));
			//protocol offset
			UINT16 id = HisUtil::Hex2Dec(temp);

			//HG[2021.02.17]프로토콜 ID를 증가하는 값으로 적용
			//if (id < header_.offset)//offset보다 작다는 애기는 중복되었거나, 범위밖일 가능성이 있어 오류처리함.
			//{
			//	LOGEVENT("HG_RED", _T("프로토콜(%s) ID(%d)값을 확인해 주세요"), protocol_[header_.cntProtocol].name, id);
			//	return FALSE;
			//}
			header_.offset = id;
			//..//HG[2021.02.17]프로토콜 ID를 증가하는 값으로 적용
		}
	}

	return TRUE;
}

void CPacketGenerator::LoadParam0(TCHAR* posStart, TCHAR* posSeperator)
{
	//param
	TCHAR* bufParam = protocol_[header_.cntProtocol].par[protocol_[header_.cntProtocol].cntParam].buf;
	//posStart = HisUtil::ltrim(posStart, _T(" \t"));
	_tcsncpy(bufParam, posStart, posSeperator - posStart);

	//type
	TCHAR* posType = _tcsstr(bufParam, MARK_EMPTY_BLOCK);
	_tcsncpy(protocol_[header_.cntProtocol].par[protocol_[header_.cntProtocol].cntParam].type, bufParam, posType - bufParam);

	//변수명
	posType = HisUtil::ltrim(posType, _T(" \t"));

	//배열이면 문자로 인식
	if (_tcsstr(posType, ARRAY_OPEN))
	{
		//문자열이구나.
		protocol_[header_.cntProtocol].par[protocol_[header_.cntProtocol].cntParam].par = enArray;
		//name
		TCHAR* posStartArray = _tcsstr(posType, ARRAY_OPEN);
		_tcsncpy(protocol_[header_.cntProtocol].par[protocol_[header_.cntProtocol].cntParam].name, posType, posStartArray - posType);
		posStartArray += _tcslen(ARRAY_OPEN);

		//array size
		TCHAR* posEndArray = _tcsstr(posStartArray, ARRAY_CLOSE);
		if (!posEndArray)
		{
			//wprintf(_T("배열정의 \"]\" 누락되었습니다."));
			LOGEVENT("HG_RED", _T("배열정의 \"]\" 누락되었습니다."));
		}
		_tcsncpy(protocol_[header_.cntProtocol].par[protocol_[header_.cntProtocol].cntParam].length, posStartArray, posEndArray - posStartArray);
	}
	else
	{
		_tcscpy(protocol_[header_.cntProtocol].par[protocol_[header_.cntProtocol].cntParam].name, posType);

		if(IsStringType(protocol_[header_.cntProtocol].par[protocol_[header_.cntProtocol].cntParam].type))
			protocol_[header_.cntProtocol].par[protocol_[header_.cntProtocol].cntParam].par = enString;
		else if (IsVectorType(protocol_[header_.cntProtocol].par[protocol_[header_.cntProtocol].cntParam].type))
			protocol_[header_.cntProtocol].par[protocol_[header_.cntProtocol].cntParam].par = enStdVector;
		else if (!IsNumberType(protocol_[header_.cntProtocol].par[protocol_[header_.cntProtocol].cntParam].type))
			protocol_[header_.cntProtocol].par[protocol_[header_.cntProtocol].cntParam].par = enStructure;
	}
}

BOOL CPacketGenerator::LoadParam(TCHAR* posBuffer)
{
	TCHAR* posStart = NULL;
	TCHAR* posEnd = NULL;

	//parameter의 시작부분
	posStart = _tcsstr(posBuffer, PARAMETER_OPEN);
	if (NULL == posStart)
	{
		LOGEVENT("HG_RED", _T("프로토콜(%s)의 파라미터의 끝(\"(\")을 찾지 못헀습니다."), header_.name);
		return FALSE;
	}

	posEnd = _tcsstr(posBuffer, PARAMETER_CLOSE);
	if (NULL == posEnd)
	{
		LOGEVENT("HG_RED", _T("프로토콜(%s)의 파라미터의 끝(\")\")을 찾지 못헀습니다."), header_.name);
		return FALSE;
	}

	posStart = HisUtil::ltrim(posStart, _T(" \t"));
	while (posStart != posEnd)
	{
		posStart = HisUtil::ltrim(posStart + 1, _T(" \t"));
		
		//파라미터 구분을 "," 또는 ")"으로 확인한다.
		TCHAR* posSeperator = _tcsstr(posStart, MARK_COMMA);
		if (posSeperator)
		{
			//param
			LoadParam0(posStart, posSeperator);

			//next
			posStart = _tcsstr(posSeperator, MARK_COMMA);//next param
		}//..if(posSeperator)

		//","가 없다면 파라미터는 1개 이겠군
		else
		{
			//posStart = HisUtil::ltrim(posStart, _T(" \t"));
			TCHAR* posSeperator = _tcsstr(posStart, PARAMETER_CLOSE);
			if (posStart == posSeperator)
				break;//더이상 param 없다.

			//param
			LoadParam0(posStart, posSeperator);

			//next
			posStart = posSeperator;//end
		}//..if(posSeperator)

		++protocol_[header_.cntProtocol].cntParam;
	}//..while(posStart != posEnd)

	return TRUE;
}

const TCHAR* CPacketGenerator::RenameCsType(TCHAR* type)
{
	MAP_RENAME_CS::iterator it = mapRenameCs_.find(type);
	if (it == mapRenameCs_.end())
		return type;

	return (*it).second.c_str();
}

//cs List의 타입을 가져옵니다.(List<stRemote>에서 stRemote을 리턴)
const TCHAR* CPacketGenerator::GenericType(TCHAR* type, OUT HisUtil::TString& key)
{
	if (NULL == type)	return NULL;

	HisUtil::TString temp = type;
	int p1 = temp.find(_T("<"));
	int p2 = temp.find(_T(">"));

	key = HisUtil::trim(temp.substr(p1 + 1, p2 - (p1 + 1)));
	return key.c_str();
}

