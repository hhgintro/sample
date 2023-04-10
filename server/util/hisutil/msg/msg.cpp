// Msg.cpp: implementation of the CMsg class.
//
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "Msg.h"


namespace HisUtil {

	//////////////////////////////////////////////////////////////////////
	// Construction/Destruction
	//////////////////////////////////////////////////////////////////////

	CMsg::CMsg()
	{
		memset(m_buf, 0, sizeof(m_buf));
		m_pHead = m_buf;
		m_pData = m_pHead + MSG_HEADER_SIZE;
		Clear();
	}

	CMsg::CMsg(CMsg& msg)
	{
		memset(m_buf, 0, sizeof(m_buf));
		m_pHead = m_buf;
		m_pData = m_pHead + MSG_HEADER_SIZE;

		m_nRdOff = 0;
		m_nWrOff = msg.m_nWrOff;
		memcpy(m_pHead, msg.m_pHead, MSG_TOTAL_SIZE);
	}

	CMsg::~CMsg()
	{
#ifdef _DEBUG
		if (m_nWrOff == m_nRdOff)
			return;

		if (m_nWrOff > m_nRdOff)
		{
			//send�� ����� Clear()�Լ��� ȣ���ϼ���.
			LOGEVENT("Critical_Msg_Error", _T("ERROR:�о�� �ҵ���Ÿ�� �����ִ�.(ID[%d], m_nWrOff[%d], m_nRdOff[%d])"), ID(), m_nWrOff, m_nRdOff);
		}
		else
			LOGEVENT("Critical_Msg_Error", _T("ERROR:�ʹ�����(�����Ⱚ����) �о���.(ID[%d], m_nWrOff[%d], m_nRdOff[%d])"), ID(), m_nWrOff, m_nRdOff);
#endif
	}
	//////////////////////////////////////////////////////////////////////
	// Operations
	//////////////////////////////////////////////////////////////////////

	void CMsg::Clear()
	{
		m_nRdOff = 0;
		m_nWrOff = 0;
		memset(m_buf, 0, sizeof(m_buf));
	}

	CMsg& CMsg::ID(PacketID id)
	{
		//Clear ();
		*((PacketID*)(m_pHead + MSG_HEADER_PROTOCOL_ID_POS)) = id;
		return *this;
	}

	PacketID CMsg::ID()
	{
		return *((PacketID*)(m_pHead + MSG_HEADER_PROTOCOL_ID_POS));
	}

	LPVOID CMsg::GetBuf()
	{
		return (LPVOID)m_pHead;
	}

	void CMsg::SetBuf(LPVOID pBuf)
	{
		m_pHead = (UCHAR*)pBuf;
		m_pData = (UCHAR*)pBuf + MSG_HEADER_SIZE;
	}

	WORD CMsg::GetSize()
	{
		return *((PacketSize*)(m_pHead + MSG_HEADER_PROTOCOL_SIZE_POS)) + MSG_HEADER_SIZE;
	}

//#ifdef PACKET_INCLUDE_PROTCOL_NUM
	void CMsg::SetNum(PacketNum num)
	{
		*((PacketNum*)(m_pHead + MSG_HEADER_PROTOCOL_NUM_POS)) = num;
	}

	PacketNum CMsg::GetNum()
	{
		return *((PacketNum*)(m_pHead + MSG_HEADER_PROTOCOL_NUM_POS));
	}
	void CMsg::SetContext(PacketContext context)
	{
		*((PacketContext*)(m_pHead + MSG_HEADER_PROTOCOL_RELIABLE)) = context;
	}

	PacketContext CMsg::GetContext()
	{
		return *((PacketContext*)(m_pHead + MSG_HEADER_PROTOCOL_RELIABLE));
	}
//#endif //PACKET_INCLUDE_PROTCOL_NUM

	BOOL CMsg::IsReadAll()
	{
		return (GetSize() - MSG_HEADER_SIZE <= m_nRdOff);
	}

	void CMsg::Copy(LPVOID pBuf, int length)
	{
		Clear();
		memcpy(m_pHead, pBuf, length);
	}

	void CMsg::SetRdOff(int offset)
	{
		m_nRdOff = offset;
	}

	void CMsg::Read(const LPVOID pData, int n)
	{
		if (n <= 0)		return;

		if (m_nRdOff + n + MSG_HEADER_SIZE > MSG_TOTAL_SIZE) {
			LOGEVENT("Critical_Msg_Error", _T("- Error : ���۸� �ʰ��Ͽ� �б� �õ�(size:%d)"), n);
			n = MSG_TOTAL_SIZE - (m_nRdOff + MSG_HEADER_SIZE);//�б� �ʴ� ũ��� �����Ѵ�.
			//return;

			throw 99;
		}
		if (n <= 0)		return;

#ifdef _DEBUG 
		memset(pData, 0x33, n);	//����üũ
#endif

		memcpy(pData, m_pData + m_nRdOff, n);
		m_nRdOff += n;
	}

	void CMsg::Write(LPVOID pData, int n)
	{
		if (m_nWrOff + n + MSG_HEADER_SIZE > MSG_TOTAL_SIZE) {
			LOGEVENT("Critical_Msg_Error", _T("- Error : ���۰� �������� ���� ����(size:%d)"), n);
			return;
		}

		if (n <= 0)
			return;

		memcpy(m_pData + m_nWrOff, pData, n);
		m_nWrOff += n;
		memcpy(m_pHead, &m_nWrOff, sizeof(PacketSize));
	}


	//////////////////////////////////////////////////////////////////////
	// Stream Operators
	//////////////////////////////////////////////////////////////////////


	/*
	//HG[2010.06.16]
	//��Ŷ���� ������ ����Ÿ CMsg�� ������µ�
	//client���� Ȧ��Ī ���н� ������ ����Ÿ�� ��Ƽ� �ѱ���� �ϴ�
	//������Ŀ����� �Ѿ�� ����Ÿ�� HEADER(size,protocol)�� �����Ǿ� ���۵Ǳ⿡
	//������ ����Ÿ�� ������ �����Ҷ� ���
	//�������� client�� ���۵� ����Ÿ�� �������ؾ� �ϴ� ���ŷο����� ����
	//������
	//������ ���۵� ����Ÿ�� HEADER�� ������ ����Ÿ�� ��������
	//�����վ��� client�� �����ϱ� �����̴�.

	CMsg& CMsg::operator<<( CMsg* arg )
	{
	Write((LPVOID) ((UCHAR*) arg->GetBuf() + MSG_HEADER_SIZE + arg->m_nRdOff ),
	arg->GetSize() - (MSG_HEADER_SIZE + arg->m_nRdOff));
	arg->Clear();
	return *this;
	}

	CMsg& CMsg::operator<<( CMsg& arg )
	{
	Write((LPVOID) ((UCHAR*) arg.GetBuf() + MSG_HEADER_SIZE + arg.m_nRdOff ),
	arg.GetSize() - (MSG_HEADER_SIZE + arg.m_nRdOff));
	arg.Clear();
	return *this;
	}

	CMsg& CMsg::operator>>( CMsg* arg )
	{
	*arg << *this;
	return *this;
	}

	CMsg& CMsg::operator>>( CMsg& arg )
	{
	arg << *this;
	return *this;
	}
	*/
	CMsg& CMsg::operator<<(CMsg* arg)
	{
		//�������� ��ü�� �� ����ְ�
		Write(arg->GetBuf(), arg->GetSize());
		//arg->Clear();//clear()�� �ܺο��� �ض�(
		return *this;
	}

	CMsg& CMsg::operator<<(CMsg& arg)
	{
		//�������� ��ü�� �� ����ְ�
		Write(arg.GetBuf(), arg.GetSize());
		//arg.Clear();//clear()�� �ܺο��� �ض�(
		return *this;
	}

	CMsg& CMsg::operator>>(CMsg* arg)
	{
		//�����ö��� ���� �κ� ��ü�� �� �����´�.
		memcpy(arg->GetBuf(), (LPVOID)((UCHAR*) this->GetBuf() + MSG_HEADER_SIZE + this->m_nRdOff), this->GetSize() - (MSG_HEADER_SIZE + this->m_nRdOff));
		arg->m_nWrOff = this->GetSize() - (MSG_HEADER_SIZE + this->m_nRdOff);
		//Clear();//clear()�� �ܺο��� �ض�(
		return *this;
	}

	CMsg& CMsg::operator>>(CMsg& arg)
	{
		memcpy(arg.GetBuf(), (LPVOID)((UCHAR*) this->GetBuf() + MSG_HEADER_SIZE + this->m_nRdOff), this->GetSize() - (MSG_HEADER_SIZE + this->m_nRdOff));
		arg.m_nWrOff = this->GetSize() - (MSG_HEADER_SIZE + this->m_nRdOff);
		//Clear();//clear()�� �ܺο��� �ض�(
		return *this;
	}

	CMsg& CMsg::operator=(CMsg& arg)
	{
		m_nRdOff = arg.m_nRdOff;
		m_nWrOff = arg.m_nWrOff;
		memcpy(m_pHead, arg.m_pHead, arg.GetSize());
		return *this;
	}

	//CMsg& CMsg::operator+=( CMsg& arg )
	//{
	//	Write((LPVOID) ((UCHAR*) arg.GetBuf() + MSG_HEADER_SIZE + arg.m_nRdOff ), 
	//		arg.GetSize() - (MSG_HEADER_SIZE + arg.m_nRdOff));
	//	arg.Clear();
	//	return *this;
	//}
	//////////////////////////////////////////////////////////////////////
	// Stream Operators Input
	//////////////////////////////////////////////////////////////////////

	CMsg& CMsg::operator<<(INT8 arg)
	{
		Write((LPVOID)&arg, sizeof(arg));
		return *this;
	}

	CMsg& CMsg::operator<<(INT16 arg)
	{
		Write((LPVOID)&arg, sizeof(arg));
		return *this;
	}

	CMsg& CMsg::operator<<(INT32 arg)
	{
		Write((LPVOID)&arg, sizeof(arg));
		return *this;
	}

	CMsg& CMsg::operator<<(INT64 arg)
	{
		Write((LPVOID)&arg, sizeof(arg));
		return *this;
	}

	CMsg& CMsg::operator<<(UINT8 arg)
	{
		Write((LPVOID)&arg, sizeof(arg));
		return *this;
	}

	CMsg& CMsg::operator<<(UINT16 arg)
	{
		Write((LPVOID)&arg, sizeof(arg));
		return *this;
	}

	CMsg& CMsg::operator<<(UINT32 arg)
	{
		Write((LPVOID)&arg, sizeof(arg));
		return *this;
	}

	CMsg& CMsg::operator<<(UINT64 arg)
	{
		Write((LPVOID)&arg, sizeof(arg));
		return *this;
	}

	CMsg& CMsg::operator<<(float arg)
	{
		Write((LPVOID)&arg, sizeof(arg));
		return *this;
	}

	CMsg& CMsg::operator<<(const std::string arg)
	{
		//���ڿ� ������� 2byte�� ����
		WORD length = (WORD)arg.size();
		Write((LPVOID)&length, sizeof(length));
		Write((LPVOID)arg.c_str(), length);
		return *this;
	}

	CMsg& CMsg::operator<<(const std::wstring arg)
	{
		//���ڿ� ������� 2byte�� ����
		WORD length = (WORD)arg.size() * 2;//�����ڵ� 2Byte
		Write((LPVOID)&length, sizeof(length));
		Write((LPVOID)arg.c_str(), length);
		return *this;
	}

	CMsg& CMsg::operator << (CMsgPack&	arg )
	{
		if(arg.len <= 0)
			return *this;
	
		//���ڿ� ������� 2byte�� ����
		Write((void*) &arg.len, sizeof(arg.len));
		Write((void*) arg.buf, arg.len);
		return *this;
	}

	//////////////////////////////////////////////////////////////////////
	// Stream Operators Output
	//////////////////////////////////////////////////////////////////////

	CMsg& CMsg::operator>>(INT8& arg)
	{
		Read(&arg, sizeof(arg));
		return *this;
	}

	CMsg& CMsg::operator>>(INT16& arg)
	{
		Read(&arg, sizeof(arg));
		return *this;
	}

	CMsg& CMsg::operator>>(INT32& arg)
	{
		Read(&arg, sizeof(arg));
		return *this;
	}

	CMsg& CMsg::operator>>(INT64& arg)
	{
		Read(&arg, sizeof(arg));
		return *this;
	}

	CMsg& CMsg::operator>>(UINT8& arg)
	{
		Read(&arg, sizeof(arg));
		return *this;
	}

	CMsg& CMsg::operator>>(UINT16&	arg)
	{
		Read(&arg, sizeof(arg));
		return *this;
	}

	CMsg& CMsg::operator>>(UINT32& arg)
	{
		Read(&arg, sizeof(arg));
		return *this;
	}

	CMsg& CMsg::operator>>(UINT64& arg)
	{
		Read(&arg, sizeof(arg));
		return *this;
	}

	CMsg& CMsg::operator>>(float& arg)
	{
		Read(&arg, sizeof(arg));
		return *this;
	}

	CMsg& CMsg::operator>>(std::string& arg)
	{
		WORD length = 0;
		Read((void*)&length, sizeof(length));
		if (length) {
			arg.resize(length, '\0');
			void* buf = (void*)arg.c_str();
			Read(buf, length);
		}
		return *this;
	}

	CMsg& CMsg::operator>>(std::wstring& arg)
	{
		WORD length = 0;
		Read((void*)&length, sizeof(length));
		if (length) {
			arg.resize(length / 2, '\0');//�����ڵ� 2Byte
			void* buf = (void*)arg.c_str();
			Read(buf, length);
		}
		return *this;
	}

	CMsg& CMsg::operator >> (CMsgPack& arg )
	{
		//if(arg.size <= 0)	return *this;
	
		//���ڿ� ������� 2byte�� ����
		Read((void*)&arg.len, sizeof(arg.len));
	
		////���� üũ
		//int waste = 0;
		////s(������)�� "sizeof(A[])-1" �� ũ���̴�.
		//int nArraysize = arg.size;//(arg.size-nEndUCHARs) : �迭�� �ǳ��� ����д�.(char��)'\0'
		//if(arg.size > sizeof(arg.buf)) {//�迭ũ�⺸�� ��������Ÿ�� ũ�ٸ� �迭ũ�⸸ŭ�� �а� ������.
		//	waste = arg.size - sizeof(arg.buf);//���� ����Ÿ��(�������� ����Ÿ)
		//	length = arg.size;
		//}
	
		Read( arg.buf, arg.len);
	
		////log
		//if(waste) {
		//	m_nRdOff += waste;//���۰� �۾� �������� ���ڿ��� ���������� ����
		//	LOGEVENT("Critical_Msg_Error", _T("�������� ����Ÿ(size:%d)�� �����մϴ�."), waste);
		//}
		return *this;
	}

};//..namespace HisUtil {
