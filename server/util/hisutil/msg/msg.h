// Msg.h: interface for the CMsg class.
//
//////////////////////////////////////////////////////////////////////

#pragma once

#include "msgpack.h"
//#define PACKET_INCLUDE_PROTCOL_NUM	//프로토콜 헤더에 번호를 부여한다.

namespace HisUtil {

	typedef UINT16			PacketSize;
	typedef UINT32			PacketNum;
	typedef UINT16			PacketID;
	typedef UINT8			PacketContext;	//Reliable유무

	const PacketNum MAX_PACKET_NUM = 4294960000;	//4294967295




	//========== 필독 ===========//
	// 구조체를 packing할때는 std::vector에 담아서 처리하도록 하였습니다.
	// 구조체내 포인터및 동적공간(std::string)을 담지 못하는 문제로 인하여
	// packing 하고자 하는 구조체는 반드시
	// PackInfo(), UnpackInfo() 함수를 구현하여야 합니다.



	//===================================================
	//	패킷 구조
	//	사이즈(2) + 패킷번호(4) + 프로토콜(2) + Reliable유무(1) + 데이타(xxxx byte)
	//===================================================
	const int MSG_TOTAL_SIZE = 0x2000;//(0x1000=4096byte)
	const int MSG_HEADER_PROTOCOL_SIZE_POS = 0;

//#ifdef PACKET_INCLUDE_PROTCOL_NUM
	const int MSG_HEADER_PROTOCOL_NUM_POS = MSG_HEADER_PROTOCOL_SIZE_POS + sizeof(PacketSize);
	const int MSG_HEADER_PROTOCOL_ID_POS = MSG_HEADER_PROTOCOL_NUM_POS + sizeof(PacketNum);	//프로토콜 ID 위치
	const int MSG_HEADER_PROTOCOL_RELIABLE = MSG_HEADER_PROTOCOL_ID_POS + sizeof(PacketID);	//Reliable유무 위치
	const int MSG_HEADER_SIZE = MSG_HEADER_PROTOCOL_RELIABLE + sizeof(PacketContext);	//총 패킷 사이즈
//#else
//	const int MSG_HEADER_PROTOCOL_ID_POS	= MSG_HEADER_PROTOCOL_SIZE_POS + sizeof(PacketSize);	//ID 위치
//	const int MSG_HEADER_SIZE				= MSG_HEADER_PROTOCOL_ID_POS + sizeof(PacketID);	//총 패킷 사이즈
//#endif //PACKET_INCLUDE_PROTCOL_NUM

	class CMsgPack;
	class CMsg// : public CAutoAllocate<CMsg>
	{
	private:
		//내부에서만 사용허용
		void Read(const LPVOID pData, int n);
		void Write(LPVOID pData, int n);

		//사용하지 말라는 뜻(private선언)
		CMsg& operator << (const char*	arg)		{ return *this; }
		CMsg& operator << (const WCHAR*	arg)		{ return *this; }

		CMsg& operator >> (const char*	arg)		{ return *this; }
		CMsg& operator >> (const WCHAR*	arg)		{ return *this; }


	public:
		CMsg();
		CMsg(CMsg& msg);
		~CMsg();
		CMsg& ID(PacketID id);
		PacketID ID();

		LPVOID GetBuf();
		void SetBuf(LPVOID pBuf);
		PacketSize GetSize();
//#ifdef PACKET_INCLUDE_PROTCOL_NUM
		void SetNum(PacketNum num);
		PacketNum GetNum();
		void SetContext(PacketContext context);
		PacketContext GetContext();
//#endif //PACKET_INCLUDE_PROTCOL_NUM
		BOOL IsReadAll();
		void Copy(LPVOID pBuf, int length);
		void Clear();

		/**< buf에서 읽어야 하는 시점을 재설정할 수 있다.
		* @return
		*/
		void SetRdOff(int offset);


		// Archive Operators
		CMsg& operator << (CMsg*			arg);
		CMsg& operator << (CMsg&			arg);
		CMsg& operator >> (CMsg*			arg);
		CMsg& operator >> (CMsg&			arg);
		CMsg& operator =  (CMsg&			arg);

		//input
		CMsg& operator << (INT8				arg);
		CMsg& operator << (INT16			arg);
		CMsg& operator << (INT32			arg);
		CMsg& operator << (INT64			arg);
		CMsg& operator << (UINT8			arg);
		CMsg& operator << (UINT16			arg);
		CMsg& operator << (UINT32			arg);
		CMsg& operator << (UINT64			arg);

		CMsg& operator << (float			arg);

		CMsg& operator << (std::string		arg);
		CMsg& operator << (std::wstring		arg);
		CMsg& operator << (CMsgPack&		arg );//고정길이 입력할 때



		//========== 필독 ===========//
		// 구조체를 packing할때는 std::vector에 담아서 처리하도록 하였습니다.
		// 구조체내 포인터및 동적공간(std::string)을 담지 못하는 문제로 인하여
		// packing 하고자 하는 구조체는 반드시
		// PackInfo(), UnpackInfo() 함수를 구현하여야 합니다.

		//template<class T>
		//CMsg& operator << (T& arg)
		//{
		//	//std::string, std::wstring등 동적인 문자열을 관리하는 맴버를 포함하는 구조체에서는 절대로!!!!!
		//	//절대로!!!
		//	//구조체 자체를 넘겨서는 안됩니다.
		//	Write(&arg, sizeof(T));
		//	//arg.PackInfo(*this);
		//	return *this;
		//}

		//=============================================================================
		//단일 구조체를 전송할 경우에는 friend operator를 구현해줍니다.
		// 단. CMsgPack과의 충돌을 체크해 보지 않았기 때문에 적용여부를 신중히 체크하기 바람.
		//friend HisUtil::CMsg& operator << (HisUtil::CMsg& msg, stInven& inven)
		//friend HisUtil::CMsg& operator >> (HisUtil::CMsg& msg, stInven& inven)
		//=============================================================================

		template<class T>
		CMsg& operator << (T& arg)
		{
			arg.PackInfo(*this);
			return *this;
		}

		template<class T>
		CMsg& operator << (std::vector<T>& arg)
		{
			// 배열 크기를 기록한다.
			WORD length = (WORD)arg.size();
			Write(&length, sizeof(length));
			// 각 배열 인자를 기록한다.
			for (std::vector<T>::iterator iter = arg.begin(); iter != arg.end(); ++iter)
			{
				//*this << (*iter);
				(*iter).PackInfo(*this);
			}
			return *this;
		}


		//output
		CMsg& operator >> (INT8&			arg);
		CMsg& operator >> (INT16&			arg);
		CMsg& operator >> (INT32&			arg);
		CMsg& operator >> (INT64&			arg);
		CMsg& operator >> (UINT8&			arg);
		CMsg& operator >> (UINT16&			arg);
		CMsg& operator >> (UINT32&			arg);
		CMsg& operator >> (UINT64&			arg);

		CMsg& operator >> (float&			arg);

		CMsg& operator >> (std::string&		arg);
		CMsg& operator >> (std::wstring&	arg);
		CMsg& operator >> (CMsgPack&		arg );//고정길이, 문자열 출력할 때

		template<class T>
		CMsg& operator >> (T& arg)
		{
			//Read(&arg, sizeof(T));
			arg.UnpackInfo(*this);
			return *this;
		}

		template<class T>
		CMsg& operator >> (std::vector<T>& arg)
		{
			// 배열 크기를 얻는다.
			WORD length = 0;
			Read(&length, sizeof(length));
			// 배열 크기 조정
			//arg.reserve(length);	//메모리 frag를 줄이기 위해.
			arg.resize(length);
			// 각 배열 인자를 얻는다.
			for (int i = 0; i < length; ++i)
			{
				//T& elem = arg[i];
				//*this >> elem;
				//*this >> arg[i];
				arg[i].UnpackInfo(*this);
			}
			return *this;
		}


	private:
		UCHAR	m_buf[MSG_TOTAL_SIZE];
		UCHAR*	m_pHead;
		UCHAR*	m_pData;
		int		m_nWrOff;
		int		m_nRdOff;
	};

};//..namespace HisUtil {
