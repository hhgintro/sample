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
			//send할 경우라면 Clear()함수를 호출하세요.
			LOGEVENT("Critical_Msg_Error", _T("ERROR:읽어야 할데이타가 남아있다.(ID[%d], m_nWrOff[%d], m_nRdOff[%d])"), ID(), m_nWrOff, m_nRdOff);
		}
		else
			LOGEVENT("Critical_Msg_Error", _T("ERROR:너무많이(쓰레기값까지) 읽었다.(ID[%d], m_nWrOff[%d], m_nRdOff[%d])"), ID(), m_nWrOff, m_nRdOff);
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
			LOGEVENT("Critical_Msg_Error", _T("- Error : 버퍼를 초과하여 읽기 시도(size:%d)"), n);
			n = MSG_TOTAL_SIZE - (m_nRdOff + MSG_HEADER_SIZE);//읽기 초대 크기롤 수정한다.
			//return;

			throw 99;
		}
		if (n <= 0)		return;

#ifdef _DEBUG 
		memset(pData, 0x33, n);	//오류체크
#endif

		memcpy(pData, m_pData + m_nRdOff, n);
		m_nRdOff += n;
	}

	void CMsg::Write(LPVOID pData, int n)
	{
		if (m_nWrOff + n + MSG_HEADER_SIZE > MSG_TOTAL_SIZE) {
			LOGEVENT("Critical_Msg_Error", _T("- Error : 버퍼가 가득차서 쓰기 실패(size:%d)"), n);
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
	//패킷으로 전송할 데이타 CMsg를 만들었는데
	//client간의 홀펀칭 실패시 서버로 데이타를 담아서 넘기려고 하니
	//기존방식에서는 넘어가는 데이타가 HEADER(size,protocol)이 누락되어 전송되기에
	//누락된 데이타를 서버로 전송할때 담아
	//서버에서 client로 전송될 데이타를 재조합해야 하는 번거로움으로 인해
	//새로이
	//서버로 전송될 데이타에 HEADER를 포함한 데이타를 보냄으로
	//재조합없이 client로 전송하기 위함이다.

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
		//넣을때는 전체를 다 집어넣고
		Write(arg->GetBuf(), arg->GetSize());
		//arg->Clear();//clear()는 외부에서 해라(
		return *this;
	}

	CMsg& CMsg::operator<<(CMsg& arg)
	{
		//넣을때는 전체를 다 집어넣고
		Write(arg.GetBuf(), arg.GetSize());
		//arg.Clear();//clear()는 외부에서 해라(
		return *this;
	}

	CMsg& CMsg::operator>>(CMsg* arg)
	{
		//가져올때는 남은 부분 전체를 다 가져온다.
		memcpy(arg->GetBuf(), (LPVOID)((UCHAR*) this->GetBuf() + MSG_HEADER_SIZE + this->m_nRdOff), this->GetSize() - (MSG_HEADER_SIZE + this->m_nRdOff));
		arg->m_nWrOff = this->GetSize() - (MSG_HEADER_SIZE + this->m_nRdOff);
		//Clear();//clear()는 외부에서 해라(
		return *this;
	}

	CMsg& CMsg::operator>>(CMsg& arg)
	{
		memcpy(arg.GetBuf(), (LPVOID)((UCHAR*) this->GetBuf() + MSG_HEADER_SIZE + this->m_nRdOff), this->GetSize() - (MSG_HEADER_SIZE + this->m_nRdOff));
		arg.m_nWrOff = this->GetSize() - (MSG_HEADER_SIZE + this->m_nRdOff);
		//Clear();//clear()는 외부에서 해라(
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
		//문자열 사이즈는 2byte로 전송
		WORD length = (WORD)arg.size();
		Write((LPVOID)&length, sizeof(length));
		Write((LPVOID)arg.c_str(), length);
		return *this;
	}

	CMsg& CMsg::operator<<(const std::wstring arg)
	{
		//문자열 사이즈는 2byte로 전송
		WORD length = (WORD)arg.size() * 2;//유니코드 2Byte
		Write((LPVOID)&length, sizeof(length));
		Write((LPVOID)arg.c_str(), length);
		return *this;
	}

	CMsg& CMsg::operator << (CMsgPack&	arg )
	{
		if(arg.len <= 0)
			return *this;
	
		//문자열 사이즈는 2byte로 전송
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
			arg.resize(length / 2, '\0');//유니코드 2Byte
			void* buf = (void*)arg.c_str();
			Read(buf, length);
		}
		return *this;
	}

	CMsg& CMsg::operator >> (CMsgPack& arg )
	{
		//if(arg.size <= 0)	return *this;
	
		//문자열 사이즈는 2byte로 전송
		Read((void*)&arg.len, sizeof(arg.len));
	
		////길이 체크
		//int waste = 0;
		////s(사이즈)는 "sizeof(A[])-1" 의 크기이다.
		//int nArraysize = arg.size;//(arg.size-nEndUCHARs) : 배열의 맨끝은 비워둔다.(char형)'\0'
		//if(arg.size > sizeof(arg.buf)) {//배열크기보다 읽을데이타가 크다면 배열크기만큼만 읽고 버린다.
		//	waste = arg.size - sizeof(arg.buf);//잔존 데이타값(버려지는 데이타)
		//	length = arg.size;
		//}
	
		Read( arg.buf, arg.len);
	
		////log
		//if(waste) {
		//	m_nRdOff += waste;//버퍼가 작아 못가져온 문자열도 읽은것으로 간주
		//	LOGEVENT("Critical_Msg_Error", _T("버려지는 데이타(size:%d)가 존재합니다."), waste);
		//}
		return *this;
	}

};//..namespace HisUtil {
