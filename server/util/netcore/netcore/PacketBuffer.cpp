#include "stdafx.h"
#include "PacketBuffer.h"

namespace HisUtil {


	//===============================================
	//�����Ʈ
	//CPacketBuffer class�� �����۵��ϴ��� üũ�ϱ�����
	//	Pop(char* pData, int nSize)�� ������ pop �����׽�Ʈ�� �����Ͽ���
	// ���Ŀ� Pop(char* pData)�� ���ؼ�
	//	��Ŷ�� ����� Ȯ���ϰ�, ���� ����Ÿ ������ ������ �� �ֵ��� ó���Ͽ���.
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
			//���� ���۸� �����Ѵ�.
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

		//��ϵ� ���� ���ٴ� ��
		if (nReadOffset_ == nWriteOffset_)
			return FALSE;


		//================================================================
		//HEADER�� �����ؼ� �о�;� �ϴ� "�ϳ��� ��Ŷ" ũ��.
		int nSize = 0;
		//================================================================


		//=========================================================
		//nWriteOffset_�� FRONT�� ��ġ�� ���

		int nOffset = nWriteOffset_ - nReadOffset_;
		if (0 < nOffset)
		{
			//���� ����Ÿ�� Header ���� ���ٸ�...
			if (nOffset < MSG_HEADER_SIZE)
				return FALSE;

			//buffer���� ��Ŷ�� ���� ����Ÿ�� üũ�Ѵ�.
			//int nSize = *((PacketSize*)((&m_pBuffer[nReadOffset_]) + MSG_HEADER_PROTOCOL_SIZE_POS)) + MSG_HEADER_SIZE;
			nSize = *((PacketSize*)(&m_pBuffer[nReadOffset_])) + MSG_HEADER_SIZE;
			if (MSG_TOTAL_SIZE <= nSize)
			{
				Reset();
				LOGEVENT("PoolBuffer_Error", _T("��Ŷ �ش��� ������ �ǹٸ��� �ʾ� ��Ŷ�� ����մϴ�."));
				return FALSE;
			}
		}//..if(nReadOffset_ < nWriteOffset_)



		//=========================================================
		//=========================================================
		//nWriteOffset_�� �����Ǿ� nReadOffset_ REAR�� ��ġ�� ���
		else
		{
			//�а��� �ϴ� ����� ���� ��ϵ� ������ ���� ũ�ٸ�.
			nOffset = nTotalSize_ - nReadOffset_ + nWriteOffset_;

			//���� ����Ÿ�� Header ���� ���ٸ�...
			if (nOffset < MSG_HEADER_SIZE)
				return FALSE;

			//�ش��� �پ��ִٸ�...
			int nBackSize = nTotalSize_ - nReadOffset_;
			if (MSG_HEADER_SIZE <= nBackSize)
			{
				//buffer���� ��Ŷ�� ���� ����Ÿ�� üũ�Ѵ�.
				//int nSize = *((PacketSize*)((&m_pBuffer[nReadOffset_]) + MSG_HEADER_PROTOCOL_SIZE_POS)) + MSG_HEADER_SIZE;
				nSize = *((PacketSize*)(&m_pBuffer[nReadOffset_])) + MSG_HEADER_SIZE;
				if (MSG_TOTAL_SIZE <= nSize)
				{
					Reset();
					LOGEVENT("PoolBuffer_Error", _T("��Ŷ �ش��� ������ �ǹٸ��� �ʾ� ��Ŷ�� ����մϴ�."));
					return FALSE;
				}
			}
			//�ش��� �и��Ǿ� �ִٸ�
			else
			{
				//header�� ������ �˱����� �ӽú����� ����
				char temp[MSG_HEADER_SIZE] = "";
				CopyMemory(reinterpret_cast<PVOID>(temp), reinterpret_cast<const PVOID>(&m_pBuffer[nReadOffset_]), static_cast<UINT>(nBackSize));

				//�׸��� ©�� �κе� �ٿ��ش�.
				int nRemainSize = MSG_HEADER_SIZE - nBackSize;
				CopyMemory(reinterpret_cast<PVOID>(&temp[nBackSize]), reinterpret_cast<const PVOID>(m_pBuffer), static_cast<UINT>(nRemainSize));


				//buffer���� ��Ŷ�� ���� ����Ÿ�� üũ�Ѵ�.
				//int nSize = *((PacketSize*)((&m_pBuffer[nReadOffset_]) + MSG_HEADER_PROTOCOL_SIZE_POS)) + MSG_HEADER_SIZE;
				//nSize = *((PacketSize*)(&m_pBuffer[nReadOffset_])) + MSG_HEADER_SIZE;
				nSize = *((PacketSize*)(&temp)) + MSG_HEADER_SIZE;
				if (MSG_TOTAL_SIZE <= nSize)
				{
					Reset();
					LOGEVENT("PoolBuffer_Error", _T("��Ŷ �ش��� ������ �ǹٸ��� �ʾ� ��Ŷ�� ����մϴ�."));
					return FALSE;
				}
			}
		}


#ifdef _DEBUG 
		memset(pData, 0x33, nSize);//����üũ
#endif

		return Pop(pData, nSize);
	}

	BOOL CPacketBuffer::Pop(char* pData, int nSize)
	{
		if (NULL == pData)
			return FALSE;


		AUTO_LOCK(csBuff_);

		//��ϵ� ���� ���ٴ� ��
		if (nReadOffset_ == nWriteOffset_)
			return FALSE;


		//=========================================================
		//nWriteOffset_�� FRONT�� ��ġ�� ���

		int nOffset = nWriteOffset_ - nReadOffset_;
		if (0 < nOffset)
		{

			//�а��� �ϴ� ����� ���� ��ϵ� ������ ���� ũ�ٸ�.
			if (nOffset < nSize)
				return FALSE;

			CopyMemory(reinterpret_cast<PVOID>(pData), reinterpret_cast<const PVOID>(&m_pBuffer[nReadOffset_]), static_cast<UINT>(nSize));
			nReadOffset_ += nSize;

			if (nWriteOffset_ == nReadOffset_)
				Reset();

			return TRUE;
		}//..if(nReadOffset_ < nWriteOffset_)


		//=========================================================
		//nWriteOffset_�� �����Ǿ� nReadOffset_ REAR�� ��ġ�� ���

		//�а��� �ϴ� ����� ���� ��ϵ� ������ ���� ũ�ٸ�.
		nOffset = nTotalSize_ - nReadOffset_ + nWriteOffset_;
		if (nOffset < nSize)
			return FALSE;


		//������ ���� ũ��
		int nBackSize = nTotalSize_ - nReadOffset_;

		//�о�� �ϴ� ����Ÿ�� ���� ���۸� ���� ������, ��� �о� ����ȴ�.
		if (nSize <= nBackSize)
		{
			CopyMemory(reinterpret_cast<PVOID>(pData), reinterpret_cast<const PVOID>(&m_pBuffer[nReadOffset_]), static_cast<UINT>(nSize));
			nReadOffset_ += nSize;

			//�ʰ��� ��� 0���� ����
			if (nTotalSize_ <= nReadOffset_)	nReadOffset_ = 0;

			return TRUE;
		}


		//�о�� �ϴ� ����Ÿ��, ���� ���۸� ������, ���� ���ۿ� ���ʱ��� �о�� �Ѵٸ�.(��, �а��� �ϴ� ����� �������� ����.)

		//���� ���۱��� �а�,
		CopyMemory(reinterpret_cast<PVOID>(pData), reinterpret_cast<const PVOID>(&m_pBuffer[nReadOffset_]), static_cast<UINT>(nBackSize));
		nSize -= nBackSize;//���� ����Ÿ ũ��
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
		//nWriteOffset_�� FRONT�� ��ġ�� ���

		//=(��ȣ) �����մϴ�.(ó�� �����Ҷ��� ���� ���� ���´�.)
		if (nReadOffset_ <= nWriteOffset_)
		{
			//����� üũ

			//nWriteOffset_�� ���� ä��� nReadOffset_�� �������Ƿ� -1 ��ŭ�� ä���.
			int nFrontBlock = nTotalSize_ - nWriteOffset_;
			int nBlockSize = nFrontBlock + nReadOffset_;
			if (nBlockSize - 1 < nSize)//������� ������ ���
			{
				LOGEVENT("PoolBuffer_Error", _T("�ʹ� ū ����Ÿ�� ����� �� �����ϴ�."));
				return FALSE;
			}


			//����� ����Ÿ ������
			int nRemainSize = nSize;
			if (0 < nFrontBlock)//FRONT ������� ����մϴ�.
			{
				//FRONT���� ũ��, FRONT��ŭ�� ����Ѵ�.
				int nWriteSize = nSize;
				if (nFrontBlock < nSize)	nWriteSize = nFrontBlock;

				CopyMemory(reinterpret_cast<PVOID>(&m_pBuffer[nWriteOffset_]), reinterpret_cast<const PVOID>(pData), static_cast<UINT>(nWriteSize));
				nWriteOffset_ += nWriteSize;
				LOGEVENT("PoolBuffer_Info", _T("������ nWriteOffset_(%d)/nTotalSize_(%d)"), nWriteOffset_, nTotalSize_);

				//=(��ȣ)�� �����մϴ�.
				if (nTotalSize_ <= nWriteOffset_)	nWriteOffset_ = 0;

				nRemainSize -= nWriteSize;	//���� ����Ÿ ������ ����
				//return TRUE;
			} // if(wBackSize >= nSize)


			//����� ����Ÿ�� ���� �ִ°�?
			if (nRemainSize <= 0)
				return TRUE;

			//���� ����Ÿ ���.
			CopyMemory(reinterpret_cast<PVOID>(m_pBuffer), reinterpret_cast<const PVOID>(&pData[nFrontBlock]), static_cast<UINT>(nRemainSize));

			return TRUE;
		} // if(nWriteOffset_ >= nReadOffset_)





		//=========================================================
		//nWriteOffset_�� �����Ǿ� nReadOffset_ REAR�� ��ġ�� ���

		//nWriteOffset_�� ���� ä��� nReadOffset_�� �������Ƿ� -1 ��ŭ�� ä���.
		int nBlockSize = nReadOffset_ - nWriteOffset_;
		if (nBlockSize - 1 < nSize)//������� ������ ���
		{
			LOGEVENT("PoolBuffer_Error", _T("�ʹ� ū ����Ÿ�� ����� �� �����ϴ�."));
			return FALSE;
		}

		CopyMemory(reinterpret_cast<PVOID>(&m_pBuffer[nWriteOffset_]), reinterpret_cast<const PVOID>(pData), static_cast<UINT>(nSize));
		nWriteOffset_ += nSize;

		return TRUE;
	}

};//..namespace HisUtil {
