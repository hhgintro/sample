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

	///* xml �׽�Ʈ
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

				//������
				if (0 == strcmp(elem->Value(), "String"))
				{
					//printf("\t\t\tSTRING\n");
					stParam* par = mapConstStrings_.Create();

					//mapConstValues_.Insert(elem->Value(), par);
					WCHAR wzString[256] = L"";
					HisUtil::CA2W(CP_ACP, (char*)child->Value(), wzString, sizeof(wzString));

					mapConstStrings_.Insert(HisUtil::TString(wzString), par);

				}
				//������
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

//�������̸� TRUE;
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


//�������� ���� ������ ����
BOOL CPacketGenerator::LoadProtocolFile(TCHAR* filename)
{
	if (NULL == filename)	return FALSE;

	//stProtocolHeader header;
	//stProtocol* protocol = new stProtocol[MAX_PROTOCOL_COUNT];

	//�������� ���� ������ ����
	FILE* pf = _tfopen(filename, _T("r"));
	if(!pf)
	{
		//wprintf(_T("%s ������ ã�� �������ϴ�."), filename);
		LOGEVENT("HG_RED", _T("%s ������ ã�� �������ϴ�."), filename);
		return FALSE;
	}


	BOOL bGlobal = false;	//����(protocol)�� �Ľ��߿��� ���ʿ��� �κ��� üũ���� �ʴ´�.
	ON_PROTOCOL	onProtocol = enNone;//���������� ���۵Ǹ� �ּ��� �������� �ʰ�, �ڵ忡 ���Խ�Ų��.

	//�Ѷ����� �о ������ ����
	TCHAR LineBuffer[MAX_LINE_LENGTH] = _T("");
	while (_fgetts(LineBuffer, MAX_LINE_LENGTH, pf))
	{
		TCHAR* posBuffer = NULL;
		TCHAR* posStart = NULL;
		TCHAR* posEnd = NULL;


		//���ʿ��� ���ڸ� �����Ѵ�.
		posBuffer = HisUtil::trim(LineBuffer, _T(" \t\n"));


		//�����ڿ��� ����...
		if (0 == _tcscmp(posBuffer, _T("")))
			continue;

		if (enNone == onProtocol) {
			//�ּ��� �����Ѵ�.
			//�ּ� ó��( //, /* */ )
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

		//protocol�� ���ξ�� offset�� �����´�.(global NetC2S 0xFE00)
		posStart = _tcsstr(posBuffer, PROTOCOL_HEADER);
		if(posStart)
		{
			//protocol header name
			posStart +=  _tcslen(PROTOCOL_HEADER) + 1;
			posEnd = _tcsstr(posStart, MARK_EMPTY_BLOCK) + 1;

			_tcsncpy(header_.name, posStart, posEnd - posStart - 1);//-1:�̸�("NetC2S") �ڿ� ���鹮�ڸ� ���� ����
			//protocol offset
			header_.id = HisUtil::Hex2Dec(posEnd);
			continue;
		}

		// { -- ���������� ����
		if(_tcsstr(posBuffer, _T("{"))) 
		{
			onProtocol = enStart;
			continue;
		}

		// }; -- ���������� ��
		if(_tcsstr(posBuffer, _T("};"))) 
		{
			onProtocol = enEnd;
			//wprintf(_T("������ ���� \"};\" �� �����Ͽ� �ּ���"));
			break;
		}


		//���������� ���۵Ǹ� �ּ��� �������� �ʰ�, �ڵ忡 ���Խ�Ų��.
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


		//����� �������� ������ �����Ѵ�.
		++header_.cntProtocol;
	}//..while( _fgetts(LineBuffer, MAX_LINE_LENGTH, pf))


	BOOL bResult = TRUE;
	switch (onProtocol)
	{
	case enNone:
		LOGEVENT("HG_RED", _T("��������(%s) ����(\"{\")�� ã�� �������ϴ�."), header_.name);
		bResult = FALSE;
		break;
	case enStart:
		LOGEVENT("HG_RED", _T("��������(%s) ��(\"};\")�� ã�� �������ϴ�."), header_.name);
		bResult = FALSE;
		break;
	case enEnd:
	default:
		break;
	}

	//LOGEVENT("HG_GRAY", _T("====================================="));
	//LOGEVENT("HG_GRAY", _T("�������� �ش�"));
	//LOGEVENT("HG_GRAY", _T("  name : %s"), header_.name);
	//LOGEVENT("HG_GRAY", _T("  offset : %d"), header.offset);
	//LOGEVENT("HG_GRAY", _T("  version : %d"), header.version);
	//LOGEVENT("HG_GRAY", _T("====================================="));

	//LOGEVENT("HG_GRAY", _T("�������� %d ��"), header_.cntProtocol);
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
	//���� ���� : log ���� �Ʒ� server ������ ������� CreateDirectory()�� 2�� ȣ���Ͽ��� �Ѵ�.
	::CreateDirectory(csPath, 0);// Log/ ���� ����

	TCHAR filename[MAX_PATH] = _T("");
	_sntprintf(filename, MAX_PATH, _T("%s/%s_Protocol.cs"), csPath, GetHeader().name);

	FILE* pf = _tfopen(filename, _T("wt"));
	if (!pf)
	{
		LOGEVENT("HG_RED", _T("%s ���� ���� ����"), filename);
		return;
	}

	_ftprintf(pf, _T("namespace %s\n{\n"), header_.name);

	//PT_VERSION
	_ftprintf(pf, _T("\tpublic class PT\n\t{\n\t\tstatic public uint %s = %s;\n\t};\n\n"), PROTOCOL_VERSION, header_.version.c_str());

	_ftprintf(pf, _T("\tpublic enum PROTOCOL : ushort\n\t{"));

	//protocol ����
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
	//���� ���� : log ���� �Ʒ� server ������ ������� CreateDirectory()�� 2�� ȣ���Ͽ��� �Ѵ�.
	::CreateDirectory(csPath, 0);// Log/ ���� ����

	TCHAR filename[MAX_PATH] = _T("");
	_sntprintf(filename, MAX_PATH, _T("%s/%s_Structure.cs"), csPath, GetHeader().name);

	FILE* pf = _tfopen(filename, _T("wt"));
	if (!pf)
	{
		LOGEVENT("HG_RED", _T("%s ���� ���� ����"), filename);
		return;
	}

	//using
	for (int i = 0; i < (int)vecUsingCs_.size(); ++i)
	{
		_ftprintf(pf, _T("\n%s"), vecUsingCs_[i].c_str());

	}


	_ftprintf(pf, _T("\n\nnamespace %s\n{"), header_.name);


	//protocol ����
	for (int i = 0; i < header_.cntProtocol; ++i)
	{
		_ftprintf(pf, _T("\n"));

		//�ּ���
		for (int cnt = 0; cnt < (int)protocol_[i].comment.size(); ++cnt)
		{
			_ftprintf(pf, _T("\n\t%s"), protocol_[i].comment[cnt].c_str());
		}

		//begin of class
		_ftprintf(pf, _T("\n\tpublic class st%s_%s : IDisposable\n\t{\n"), header_.name, protocol_[i].name);

		////������
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



		//parameter(�ɹ� ����) ����
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
		LOGEVENT("HG_RED", _T("%s ���� ���� ����"), filename);
		return;
	}

	_ftprintf(pf, _T("#pragma once\n\n"));

	//VT_VERSION
	_ftprintf(pf, _T("const PROTOCOL_T %s_%s\t\t\t= %s;\n\n"), header_.name, PROTOCOL_VERSION, header_.version.c_str());

	//protocol ����
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
		LOGEVENT("HG_RED", _T("%s ���� ���� ����"), filename);
		return;
	}

	_ftprintf(pf, _T("#pragma once\n\n"));

	//protocol ����
	for(int i=0; i<header_.cntProtocol; ++i)
	{
		_ftprintf(pf, _T("\n"));

		//�ּ���
		for(int cnt=0; cnt<(int)protocol_[i].comment.size(); ++cnt)
		{
			_ftprintf(pf, _T("\n%s"), protocol_[i].comment[cnt].c_str());
		}

		_ftprintf(pf, _T("\nstruct st%s_%s\n{\n"), header_.name, protocol_[i].name);

		//������
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



		//parameter(�ɹ� ����) ����
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
		LOGEVENT("HG_RED", _T("%s ���� ���� ����"), filename);
		return;
	}

	_ftprintf(pf, _T("#pragma once\n\n"));

	//protocol ����
	for(int i=0; i<header_.cntProtocol; ++i)
	{
		//�Լ��� ����
		_ftprintf(pf, _T("\n\ninline void RECV_%s_%s(HisUtil::CMsg& msgRecv, st%s_%s& st)\n{\n"), header_.name, protocol_[i].name, header_.name, protocol_[i].name);

		//decrypt
		if(protocol_[i].bEncrypt)
			_ftprintf(pf, _T("\tHisUtil::CCrypto::Decrypt((unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgRecv.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgRecv.GetBuf() + HisUtil::MSG_HEADER_SIZE);\n"));

		_ftprintf(pf, _T("\tmsgRecv\n"));

		//parameter ����
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
		//�Լ��� ��
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
		LOGEVENT("HG_RED", _T("%s ���� ���� ����"), filename);
		return;
	}

	_ftprintf(pf, _T("#pragma once\n\n"));

	//class ����
	_ftprintf(pf, _T("\n\nclass %s_SEND : public NetCore::INetCore\n{"), header_.name);
	_ftprintf(pf, _T("\npublic:\n\t%s_SEND() {}\n\tvirtual ~%s_SEND() {}\n\n"), header_.name, header_.name);

	//protocol ����
	for(int i=0; i<header_.cntProtocol; ++i)
	{
		//�Լ��� ���ڵ�
		_ftprintf(pf, _T("\tinline void SEND_%s_%s(HOSTID remote, st%s_%s& st)\n\t{\n")
			, header_.name, protocol_[i].name, header_.name, protocol_[i].name);

		//Recv ����� üũ
		//if(protocol_[i].bIsUdp)
			_ftprintf(pf, _T("\t\tNetCore::IRemote* peer = FindRemote(remote);\n\t\tif(NULL == peer)\n\t\t{\n\t\t\tLOGEVENT(\"Session_Base_Error\", _T(\"Fail send %s_%s not found peer(0x%%p)\"), remote);\n\t\t\treturn;\n\t\t}\n\n"), header_.name, protocol_[i].name);

		//Send packet session��ü
		_ftprintf(pf, _T("\t\tNetCore::CPacketSession* session = FindPacketSession(peer,%s);\n\t\tif(NULL == session)\n\t\t{\n\t\t\tLOGEVENT(\"Session_Base_Error\", _T(\"Fail send %s_%s not found session(0x%%p)\"), remote);\n\t\t\treturn;\n\t\t}\n\n")
			, (protocol_[i].bIsUdp)?L"true":L"false", header_.name, protocol_[i].name);


		//�Լ� ���� �κ�
		if(true == protocol_[i].bUnreliable)
			_ftprintf(pf, _T("\t\tHisUtil::CMsg msgSend;\n\t\tmsgSend.SetContext(NetCore::UNRELIABLE);\n\t\tmsgSend.ID(%s_%s)\n"), header_.name, protocol_[i].name);
		else
			_ftprintf(pf, _T("\t\tHisUtil::CMsg msgSend;\n\t\tmsgSend.SetContext(NetCore::RELIABLE);\n\t\tmsgSend.ID(%s_%s)\n"), header_.name, protocol_[i].name);
		//parameter ����
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
		//�Լ� ���� �κ�

		//encrypt
		if(protocol_[i].bEncrypt)
			_ftprintf(pf, _T("\t\tHisUtil::CCrypto::Encrypt((unsigned char*)msgSend.GetBuf() + HisUtil::MSG_HEADER_SIZE, msgSend.GetSize() - HisUtil::MSG_HEADER_SIZE, (unsigned char*)msgSend.GetBuf() + HisUtil::MSG_HEADER_SIZE);\n\n"));

		//if(protocol_[i].bIsUdp)
		//{
		//	//peer�� Ȧ��Ī�� �õ��� ����̰ų�,
		//	//Ȧ��Ī�� ������ ���� peer�� �����ϴµ�...
		//	if(0 != _tcscmp(_T("CORE_UDP_HOLE_PUNCHING_PEER_REQ"), protocol_[i].name)
		//		&& 0 != _tcscmp(_T("CORE_UDP_HOLE_PUNCHING_PEER_ACK"), protocol_[i].name))
		//	{
		//		//Server�� ����̰ų�,
		//		//peer�� hole punching�� ���� üũ�� ����.
		//		_ftprintf(pf, _T("\t\tif(NetCore::Host_Server == remote || peer->stepHolePunching_ == NetCore::enSuccess)\n"));
	
		//		_ftprintf(pf, _T("\t\t{\n\t\t\tsession->SendToPacket(context, msgSend, peer->GetRemotePublicIP(), peer->GetRemotePublicPort());\n"));
		//		_ftprintf(pf, _T("\t\t\tmsgSend.Clear();\n\n"));

		//		//log
		//		_ftprintf(pf, _T("\t\t\tLOGEVENT(\"Session_Base_Packet\", _T(\"==> send %s_%s to peer(0x%%p)\"), remote);\n"), header_.name, protocol_[i].name);
		//		_ftprintf(pf, _T("\t\t\treturn;\n\t\t}\n\n"));
		//}


		//	//hole punching ������ ���� ������ �����Ѵ�.
		//	_ftprintf(pf, _T("\t\tSEND_CORE_UDP_RELAY_SERVER_TO_PEER_NTF(peer->GetHostID(), context, msgSend);\n\t\tmsgSend.Clear();\n\n"));
		//}
		//else
		//{
		//	_ftprintf(pf, _T("\t\tsession->SendPacket(msgSend);\n\t\tmsgSend.Clear();\n\n"));
		//}

		//_ftprintf(pf, _T("\t\t//hole punching üũ\n"));
		//_ftprintf(pf, _T("\t\tif (NetCore::enSuccess == peer->stepHolePunching_)\n\t\t{\n\t\t\tsession->SendToPacket(context, msgSend, peer->GetRemotePublicIP(), peer->GetRemotePublicPort());\n\t\t\tmsgSend.Clear();\n\n"));
		////log
		//_ftprintf(pf, _T("\t\t\tLOGEVENT(\"Session_Base_Packet\", _T(\"==> send %s_%s to peer(0x%%p)\"), remote);\n\t\t\treturn;\n\t\t}\n"), header_.name, protocol_[i].name);

		//_ftprintf(pf, _T("\t\t//hole punching ������ ���� ������ �����Ѵ�.\n"));
		//_ftprintf(pf, _T("\t\telse if (NetCore::enFailed == peer->stepHolePunching_)\n\t\t{\n\t\t\tSEND_CORE_UDP_RELAY_SERVER_TO_PEER_NTF(peer->GetHostID(), context, msgSend);\n\t\t\tmsgSend.Clear();\n\n"));
		////log
		//_ftprintf(pf, _T("\t\t\tLOGEVENT(\"Session_Base_Packet\", _T(\"==> send NetC2S_CORE_CONNECT_COMPLETED_NTF to peer(0x%08x)\"), remote);\n\t\t\treturn;\n\t\t}\n\n"));

		//_ftprintf(pf, _T("\t\tsession->SendPacket(msgSend);\n\t\tmsgSend.Clear();\n\n"));

		////_ftprintf(pf, _T("\t\t//to server\n"));
		////_ftprintf(pf, _T("\t\telse if (NetCore::Host_Server == peer->GetHostID())\n\t\t{\n\t\t\tsession->SendPacket(msgSend);\n\t\t\tmsgSend.Clear();\n\n"));
		//////log
		////_ftprintf(pf, _T("\t\t\tLOGEVENT(\"Session_Base_Packet\", _T(\"==> send %s_%s to peer(0x%%p)\"), remote);\n\t\t\treturn;\n\t\t}\n\n"), header_.name, protocol_[i].name);

		////_ftprintf(pf, _T("\t\t//hole punching ������ ���� ������ �����Ѵ�.\n"));
		////_ftprintf(pf, _T("\t\tSEND_CORE_UDP_RELAY_SERVER_TO_PEER_NTF(peer->GetHostID(), context, msgSend);\n\t\tmsgSend.Clear();\n\n"));


		if (protocol_[i].bIsUdp)
		{
			//_ftprintf(pf, _T("\t\tswitch (peer->GetHolePunchingStep())\n\t\t{\n"));
			//_ftprintf(pf, _T("\t\t//hole punching(public) üũ\n"));
			//_ftprintf(pf, _T("\t\tcase NetCore::enPublicAttempt:\n\t\tcase NetCore::enPublicSuccess:\n\t\t\tsession->SendToPacket(context, msgSend, peer->GetRemotePublicIP(), peer->GetRemotePublicUdpPort());\n\t\t\tbreak;\n\n"));
			//_ftprintf(pf, _T("\t\t//hole punching(private) üũ\n"));
			//_ftprintf(pf, _T("\t\tcase NetCore::enPrivateAttempt:\n\t\tcase NetCore::enPrivateSuccess:\n\t\t\tsession->SendToPacket(context, msgSend, peer->GetRemotePrivateIP(), peer->GetRemotePrivateUdpPort());\n\t\t\tbreak;\n\n"));
			//_ftprintf(pf, _T("\t\t//hole punching ����(public����/private����)�� ���� ������ �����Ѵ�.\n"));
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




		//�Լ� ��
		_ftprintf(pf, _T("\t};\n\n\n"));
	}

	//class ��
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
	TCHAR Option[1024] = _T("");//�ɼ��� ���ڿ������� ��´�.(�ʹ� ���°��ϸ� ���ڳ��� �����Ⱚ�� �پ ũ�� �������ش�.)
	TCHAR* posStart = NULL;
	TCHAR* posEnd = NULL;


	//�ɼ� ( [id=xxx,udp,encrypt] )
	posStart = _tcsstr(posBuffer, PROTOCOL_OPTION_START);
	if (NULL != posStart)
	{
		posEnd = _tcsstr(posBuffer, PROTOCOL_OPTION_END);//�ɼ��� ����']'�� �� �ֱ� ����.
		if (NULL == posEnd)
		{
			LOGEVENT("HG_RED", _T("��������(%s) �ɼ� ���� ����"), protocol_[header_.cntProtocol].name);
			return FALSE;
		}

		_tcsncpy(Option, posStart, posEnd - posStart);//-1:�̸�("NetC2S") �ڿ� ���鹮�ڸ� ���� ����

		//UDP ����
		if (_tcsstr(Option, PROTOCOL_UDP))		protocol_[header_.cntProtocol].bIsUdp		= true;
		//PACKET_CONTEXT ����
		if (_tcsstr(Option, PROTOCOL_CONTEXT))	protocol_[header_.cntProtocol].bUnreliable	= true;
		//��ȣȭ ����
		if (_tcsstr(Option, PROTOCOL_ENCRYPT))	protocol_[header_.cntProtocol].bEncrypt		= true;
		//id ��������
		if (_tcsstr(Option, PROTOCOL_ID))
		{
			posStart = _tcsstr(Option, _T("=")) + 1;
			TCHAR* temp = _tcsstr(posStart, _T(","));

			TCHAR pid[32] = _T("");//�������� ID�� ���ڿ������� ��´�.(�ʹ� ���°��ϸ� ���ڳ��� �����Ⱚ�� �پ ũ�� �������ش�.)
			_tcsncpy(pid, posStart, min(temp, posEnd) - posStart);//-1:�̸�("NetC2S") �ڿ� ���鹮�ڸ� ���� ����
			temp = HisUtil::trim(pid, _T(" \t\n"));
			//protocol offset
			UINT16 id = HisUtil::Hex2Dec(temp);

			//HG[2021.02.17]�������� ID�� �����ϴ� ������ ����
			//if (id < header_.offset)//offset���� �۴ٴ� �ֱ�� �ߺ��Ǿ��ų�, �������� ���ɼ��� �־� ����ó����.
			//{
			//	LOGEVENT("HG_RED", _T("��������(%s) ID(%d)���� Ȯ���� �ּ���"), protocol_[header_.cntProtocol].name, id);
			//	return FALSE;
			//}
			header_.offset = id;
			//..//HG[2021.02.17]�������� ID�� �����ϴ� ������ ����
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

	//������
	posType = HisUtil::ltrim(posType, _T(" \t"));

	//�迭�̸� ���ڷ� �ν�
	if (_tcsstr(posType, ARRAY_OPEN))
	{
		//���ڿ��̱���.
		protocol_[header_.cntProtocol].par[protocol_[header_.cntProtocol].cntParam].par = enArray;
		//name
		TCHAR* posStartArray = _tcsstr(posType, ARRAY_OPEN);
		_tcsncpy(protocol_[header_.cntProtocol].par[protocol_[header_.cntProtocol].cntParam].name, posType, posStartArray - posType);
		posStartArray += _tcslen(ARRAY_OPEN);

		//array size
		TCHAR* posEndArray = _tcsstr(posStartArray, ARRAY_CLOSE);
		if (!posEndArray)
		{
			//wprintf(_T("�迭���� \"]\" �����Ǿ����ϴ�."));
			LOGEVENT("HG_RED", _T("�迭���� \"]\" �����Ǿ����ϴ�."));
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

	//parameter�� ���ۺκ�
	posStart = _tcsstr(posBuffer, PARAMETER_OPEN);
	if (NULL == posStart)
	{
		LOGEVENT("HG_RED", _T("��������(%s)�� �Ķ������ ��(\"(\")�� ã�� �������ϴ�."), header_.name);
		return FALSE;
	}

	posEnd = _tcsstr(posBuffer, PARAMETER_CLOSE);
	if (NULL == posEnd)
	{
		LOGEVENT("HG_RED", _T("��������(%s)�� �Ķ������ ��(\")\")�� ã�� �������ϴ�."), header_.name);
		return FALSE;
	}

	posStart = HisUtil::ltrim(posStart, _T(" \t"));
	while (posStart != posEnd)
	{
		posStart = HisUtil::ltrim(posStart + 1, _T(" \t"));
		
		//�Ķ���� ������ "," �Ǵ� ")"���� Ȯ���Ѵ�.
		TCHAR* posSeperator = _tcsstr(posStart, MARK_COMMA);
		if (posSeperator)
		{
			//param
			LoadParam0(posStart, posSeperator);

			//next
			posStart = _tcsstr(posSeperator, MARK_COMMA);//next param
		}//..if(posSeperator)

		//","�� ���ٸ� �Ķ���ʹ� 1�� �̰ڱ�
		else
		{
			//posStart = HisUtil::ltrim(posStart, _T(" \t"));
			TCHAR* posSeperator = _tcsstr(posStart, PARAMETER_CLOSE);
			if (posStart == posSeperator)
				break;//���̻� param ����.

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

//cs List�� Ÿ���� �����ɴϴ�.(List<stRemote>���� stRemote�� ����)
const TCHAR* CPacketGenerator::GenericType(TCHAR* type, OUT HisUtil::TString& key)
{
	if (NULL == type)	return NULL;

	HisUtil::TString temp = type;
	int p1 = temp.find(_T("<"));
	int p2 = temp.find(_T(">"));

	key = HisUtil::trim(temp.substr(p1 + 1, p2 - (p1 + 1)));
	return key.c_str();
}

