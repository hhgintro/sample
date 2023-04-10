#include "stdafx.h"
#include "PacketBuffer.h"

namespace HisUtil {


	//===============================================
	//빌드노트
	//CPacketBuffer class가 정상작동하는지 체크하기위해
	//	Pop(char* pData, int nSize)을 구성해 pop 로직테스트를 진행하였고
	// 이후에 Pop(char* pData)을 통해서
	//	패킷의 사이즈를 확인하고, 이하 데이타 정보를 가져올 수 있도록 처리하였다.
	//===============================================

	CPacketBuffer::CPacketBuffer()
		: nTotalSize_(0), nReadOffset_(0), nWriteOffset_(0), m_pBuffer(NULL)
	{
	}

	CPacketBuffer::~CPacketBuffer()
	{
		End();
		DELETE_SAFE_ARRAY(m_pBuffer);
	}

	BOOL CPacketBuffer::Begin(int nPoolSize)
	{
		AUTO_LOCK(csBuff_);


		nTotalSize_ = nPoolSize;
		if (nTotalSize_ < MSG_TOTAL_SIZE)	nTotalSize_ = MSG_TOTAL_SIZE;

		try
		{
			//기존 버퍼를 삭제한다.
			DELETE_SAFE_ARRAY(m_pBuffer);

			m_pBuffer = new char[nTotalSize_];
		}
		catch (std::bad_alloc& e)
		{
			printf("%s\n", e.what());
			return FALSE;
		}

		memset(m_pBuffer, 0, nTotalSize_);

		Reset();
		return TRUE;
	}

	BOOL CPacketBuffer::End()
	{
		Reset();
		return TRUE;
	}

	
	void CPacketBuffer::Reset()
	{
		AUTO_LOCK(csBuff_);

		nReadOffset_ = 0;
		nWriteOffset_ = 0;
	}

	BOOL CPacketBuffer::Pop(char* pData)
	{
		if (NULL == pData)
			return FALSE;


		AUTO_LOCK(csBuff_);

		//기록된 것이 없다는 뜻
		if (nReadOffset_ == nWriteOffset_)
			return FALSE;


		//================================================================
		//HEADER를 포함해서 읽어와야 하는 "하나의 패킷" 크기.
		int nSize = 0;
		//================================================================


		//=========================================================
		//nWriteOffset_이 FRONT에 위치한 경우

		int nOffset = nWriteOffset_ - nReadOffset_;
		if (0 < nOffset)
		{
			//받은 데이타가 Header 보다 적다면...
			if (nOffset < MSG_HEADER_SIZE)
				return FALSE;

			//buffer에서 패킷을 실제 데이타를 체크한다.
			//int nSize = *((PacketSize*)((&m_pBuffer[nReadOffset_]) + MSG_HEADER_PROTOCOL_SIZE_POS)) + MSG_HEADER_SIZE;
			nSize = *((PacketSize*)(&m_pBuffer[nReadOffset_])) + MSG_HEADER_SIZE;
			if (MSG_TOTAL_SIZE <= nSize)
			{
				Reset();
				LOGEVENT("PoolBuffer_Error", _T("패킷 해더의 정보가 옳바르지 않아 패킷을 폐기합니다."));
				return FALSE;
			}
		}//..if(nReadOffset_ < nWriteOffset_)



		//=========================================================
		//=========================================================
		//nWriteOffset_이 역전되어 nReadOffset_ REAR에 위치한 경우
		else
		{
			//읽고자 하는 사이즈가 실제 기록된 사이즈 보다 크다면.
			nOffset = nTotalSize_ - nReadOffset_ + nWriteOffset_;

			//받은 데이타가 Header 보다 적다면...
			if (nOffset < MSG_HEADER_SIZE)
				return FALSE;

			//해더가 붙어있다면...
			int nBackSize = nTotalSize_ - nReadOffset_;
			if (MSG_HEADER_SIZE <= nBackSize)
			{
				//buffer에서 패킷을 실제 데이타를 체크한다.
				//int nSize = *((PacketSize*)((&m_pBuffer[nReadOffset_]) + MSG_HEADER_PROTOCOL_SIZE_POS)) + MSG_HEADER_SIZE;
				nSize = *((PacketSize*)(&m_pBuffer[nReadOffset_])) + MSG_HEADER_SIZE;
				if (MSG_TOTAL_SIZE <= nSize)
				{
					Reset();
					LOGEVENT("PoolBuffer_Error", _T("패킷 해더의 정보가 옳바르지 않아 패킷을 폐기합니다."));
					return FALSE;
				}
			}
			//해더가 분리되어 있다면
			else
			{
				//header의 정보를 알기위해 임시변수에 저장
				char temp[MSG_HEADER_SIZE] = "";
				CopyMemory(reinterpret_cast<PVOID>(temp), reinterpret_cast<const PVOID>(&m_pBuffer[nReadOffset_]), static_cast<UINT>(nBackSize));

				//그리고 짤린 부분도 붙여준다.
				int nRemainSize = MSG_HEADER_SIZE - nBackSize;
				CopyMemory(reinterpret_cast<PVOID>(&temp[nBackSize]), reinterpret_cast<const PVOID>(m_pBuffer), static_cast<UINT>(nRemainSize));


				//buffer에서 패킷을 실제 데이타를 체크한다.
				//int nSize = *((PacketSize*)((&m_pBuffer[nReadOffset_]) + MSG_HEADER_PROTOCOL_SIZE_POS)) + MSG_HEADER_SIZE;
				//nSize = *((PacketSize*)(&m_pBuffer[nReadOffset_])) + MSG_HEADER_SIZE;
				nSize = *((PacketSize*)(&temp)) + MSG_HEADER_SIZE;
				if (MSG_TOTAL_SIZE <= nSize)
				{
					Reset();
					LOGEVENT("PoolBuffer_Error", _T("패킷 해더의 정보가 옳바르지 않아 패킷을 폐기합니다."));
					return FALSE;
				}
			}
		}


#ifdef _DEBUG 
		memset(pData, 0x33, nSize);//오류체크
#endif

		return Pop(pData, nSize);
	}

	BOOL CPacketBuffer::Pop(char* pData, int nSize)
	{
		if (NULL == pData)
			return FALSE;


		AUTO_LOCK(csBuff_);

		//기록된 것이 없다는 뜻
		if (nReadOffset_ == nWriteOffset_)
			return FALSE;


		//=========================================================
		//nWriteOffset_이 FRONT에 위치한 경우

		int nOffset = nWriteOffset_ - nReadOffset_;
		if (0 < nOffset)
		{

			//읽고자 하는 사이즈가 실제 기록된 사이즈 보다 크다면.
			if (nOffset < nSize)
				return FALSE;

			CopyMemory(reinterpret_cast<PVOID>(pData), reinterpret_cast<const PVOID>(&m_pBuffer[nReadOffset_]), static_cast<UINT>(nSize));
			nReadOffset_ += nSize;

			if (nWriteOffset_ == nReadOffset_)
				Reset();

			return TRUE;
		}//..if(nReadOffset_ < nWriteOffset_)


		//=========================================================
		//nWriteOffset_이 역전되어 nReadOffset_ REAR에 위치한 경우

		//읽고자 하는 사이즈가 실제 기록된 사이즈 보다 크다면.
		nOffset = nTotalSize_ - nReadOffset_ + nWriteOffset_;
		if (nOffset < nSize)
			return FALSE;


		//버퍼의 남은 크기
		int nBackSize = nTotalSize_ - nReadOffset_;

		//읽어야 하는 데이타가 남은 버퍼를 넘지 않으면, 모두 읽어 오면된다.
		if (nSize <= nBackSize)
		{
			CopyMemory(reinterpret_cast<PVOID>(pData), reinterpret_cast<const PVOID>(&m_pBuffer[nReadOffset_]), static_cast<UINT>(nSize));
			nReadOffset_ += nSize;

			//초과한 경우 0으로 설정
			if (nTotalSize_ <= nReadOffset_)	nReadOffset_ = 0;

			return TRUE;
		}


		//읽어야 하는 데이타가, 남은 버퍼를 넘으면, 남은 버퍼와 앞쪽까지 읽어야 한다면.(단, 읽고자 하는 사이즈를 망각하지 마라.)

		//남은 버퍼까지 읽고,
		CopyMemory(reinterpret_cast<PVOID>(pData), reinterpret_cast<const PVOID>(&m_pBuffer[nReadOffset_]), static_cast<UINT>(nBackSize));
		nSize -= nBackSize;//남은 데이타 크기
		if (0 < nSize)
		{
			CopyMemory(reinterpret_cast<PVOID>(&pData[nBackSize]), reinterpret_cast<const PVOID>(m_pBuffer), static_cast<UINT>(nSize));
		}
		nReadOffset_ = nSize;
		if (nWriteOffset_ == nReadOffset_)			Reset();

		return TRUE;
	}

	BOOL CPacketBuffer::Push(char* pData, int nSize)
	{
		if (NULL == pData || nSize <= 0)
			return FALSE;


		AUTO_LOCK(csBuff_);

		//=========================================================
		//nWriteOffset_이 FRONT에 위치한 경우

		//=(등호) 포함합니다.(처음 시작할때는 같은 값을 갖는다.)
		if (nReadOffset_ <= nWriteOffset_)
		{
			//빈공간 체크

			//nWriteOffset_을 가득 채우면 nReadOffset_과 겹쳐지므로 -1 만큼만 채운다.
			int nFrontBlock = nTotalSize_ - nWriteOffset_;
			int nBlockSize = nFrontBlock + nReadOffset_;
			if (nBlockSize - 1 < nSize)//빈공간이 부족한 경우
			{
				LOGEVENT("PoolBuffer_Error", _T("너무 큰 데이타는 기록할 수 없습니다."));
				return FALSE;
			}


			//기록할 데이타 사이즈
			int nRemainSize = nSize;
			if (0 < nFrontBlock)//FRONT 빈공간에 기록합니다.
			{
				//FRONT보다 크면, FRONT만큼만 기록한다.
				int nWriteSize = nSize;
				if (nFrontBlock < nSize)	nWriteSize = nFrontBlock;

				CopyMemory(reinterpret_cast<PVOID>(&m_pBuffer[nWriteOffset_]), reinterpret_cast<const PVOID>(pData), static_cast<UINT>(nWriteSize));
				nWriteOffset_ += nWriteSize;
				LOGEVENT("PoolBuffer_Info", _T("점유율 nWriteOffset_(%d)/nTotalSize_(%d)"), nWriteOffset_, nTotalSize_);

				//=(등호)는 포함합니다.
				if (nTotalSize_ <= nWriteOffset_)	nWriteOffset_ = 0;

				nRemainSize -= nWriteSize;	//남은 데이타 사이즈 갱신
				//return TRUE;
			} // if(wBackSize >= nSize)


			//기록할 데이타가 남아 있는가?
			if (nRemainSize <= 0)
				return TRUE;

			//남은 데이타 기록.
			CopyMemory(reinterpret_cast<PVOID>(m_pBuffer), reinterpret_cast<const PVOID>(&pData[nFrontBlock]), static_cast<UINT>(nRemainSize));

			return TRUE;
		} // if(nWriteOffset_ >= nReadOffset_)





		//=========================================================
		//nWriteOffset_이 역전되어 nReadOffset_ REAR에 위치한 경우

		//nWriteOffset_을 가득 채우면 nReadOffset_과 겹쳐지므로 -1 만큼만 채운다.
		int nBlockSize = nReadOffset_ - nWriteOffset_;
		if (nBlockSize - 1 < nSize)//빈공간이 부족한 경우
		{
			LOGEVENT("PoolBuffer_Error", _T("너무 큰 데이타는 기록할 수 없습니다."));
			return FALSE;
		}

		CopyMemory(reinterpret_cast<PVOID>(&m_pBuffer[nWriteOffset_]), reinterpret_cast<const PVOID>(pData), static_cast<UINT>(nSize));
		nWriteOffset_ += nSize;

		return TRUE;
	}

};//..namespace HisUtil {
