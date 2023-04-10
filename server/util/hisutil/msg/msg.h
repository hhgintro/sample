// Msg.h: interface for the CMsg class.
//
//////////////////////////////////////////////////////////////////////

#pragma once

#include "msgpack.h"
//#define PACKET_INCLUDE_PROTCOL_NUM	//�������� ����� ��ȣ�� �ο��Ѵ�.

namespace HisUtil {

	typedef UINT16			PacketSize;
	typedef UINT32			PacketNum;
	typedef UINT16			PacketID;
	typedef UINT8			PacketContext;	//Reliable����

	const PacketNum MAX_PACKET_NUM = 4294960000;	//4294967295




	//========== �ʵ� ===========//
	// ����ü�� packing�Ҷ��� std::vector�� ��Ƽ� ó���ϵ��� �Ͽ����ϴ�.
	// ����ü�� �����͹� ��������(std::string)�� ���� ���ϴ� ������ ���Ͽ�
	// packing �ϰ��� �ϴ� ����ü�� �ݵ��
	// PackInfo(), UnpackInfo() �Լ��� �����Ͽ��� �մϴ�.



	//===================================================
	//	��Ŷ ����
	//	������(2) + ��Ŷ��ȣ(4) + ��������(2) + Reliable����(1) + ����Ÿ(xxxx byte)
	//===================================================
	const int MSG_TOTAL_SIZE = 0x2000;//(0x1000=4096byte)
	const int MSG_HEADER_PROTOCOL_SIZE_POS = 0;

//#ifdef PACKET_INCLUDE_PROTCOL_NUM
	const int MSG_HEADER_PROTOCOL_NUM_POS = MSG_HEADER_PROTOCOL_SIZE_POS + sizeof(PacketSize);
	const int MSG_HEADER_PROTOCOL_ID_POS = MSG_HEADER_PROTOCOL_NUM_POS + sizeof(PacketNum);	//�������� ID ��ġ
	const int MSG_HEADER_PROTOCOL_RELIABLE = MSG_HEADER_PROTOCOL_ID_POS + sizeof(PacketID);	//Reliable���� ��ġ
	const int MSG_HEADER_SIZE = MSG_HEADER_PROTOCOL_RELIABLE + sizeof(PacketContext);	//�� ��Ŷ ������
//#else
//	const int MSG_HEADER_PROTOCOL_ID_POS	= MSG_HEADER_PROTOCOL_SIZE_POS + sizeof(PacketSize);	//ID ��ġ
//	const int MSG_HEADER_SIZE				= MSG_HEADER_PROTOCOL_ID_POS + sizeof(PacketID);	//�� ��Ŷ ������
//#endif //PACKET_INCLUDE_PROTCOL_NUM

	class CMsgPack;
	class CMsg// : public CAutoAllocate<CMsg>
	{
	private:
		//���ο����� ������
		void Read(const LPVOID pData, int n);
		void Write(LPVOID pData, int n);

		//������� ����� ��(private����)
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

		/**< buf���� �о�� �ϴ� ������ �缳���� �� �ִ�.
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
		CMsg& operator << (CMsgPack&		arg );//�������� �Է��� ��



		//========== �ʵ� ===========//
		// ����ü�� packing�Ҷ��� std::vector�� ��Ƽ� ó���ϵ��� �Ͽ����ϴ�.
		// ����ü�� �����͹� ��������(std::string)�� ���� ���ϴ� ������ ���Ͽ�
		// packing �ϰ��� �ϴ� ����ü�� �ݵ��
		// PackInfo(), UnpackInfo() �Լ��� �����Ͽ��� �մϴ�.

		//template<class T>
		//CMsg& operator << (T& arg)
		//{
		//	//std::string, std::wstring�� ������ ���ڿ��� �����ϴ� �ɹ��� �����ϴ� ����ü������ �����!!!!!
		//	//�����!!!
		//	//����ü ��ü�� �Ѱܼ��� �ȵ˴ϴ�.
		//	Write(&arg, sizeof(T));
		//	//arg.PackInfo(*this);
		//	return *this;
		//}

		//=============================================================================
		//���� ����ü�� ������ ��쿡�� friend operator�� �������ݴϴ�.
		// ��. CMsgPack���� �浹�� üũ�� ���� �ʾұ� ������ ���뿩�θ� ������ üũ�ϱ� �ٶ�.
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
			// �迭 ũ�⸦ ����Ѵ�.
			WORD length = (WORD)arg.size();
			Write(&length, sizeof(length));
			// �� �迭 ���ڸ� ����Ѵ�.
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
		CMsg& operator >> (CMsgPack&		arg );//��������, ���ڿ� ����� ��

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
			// �迭 ũ�⸦ ��´�.
			WORD length = 0;
			Read(&length, sizeof(length));
			// �迭 ũ�� ����
			//arg.reserve(length);	//�޸� frag�� ���̱� ����.
			arg.resize(length);
			// �� �迭 ���ڸ� ��´�.
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
