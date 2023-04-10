#pragma once

namespace HisUtil {

	class CPacketBuffer// : public CMultiThreadSync<CPacketBuffer>
	{
	public:
		//nPoolSize : ��Ŷ �ϳ��� �ִ� ������
		//nPoolCnt : ��Ŷ ���� ����
		//���� �� ������ = nPoolSize * nPoolCnt
		CPacketBuffer();
		~CPacketBuffer();

		BOOL Begin(int nPoolSize = MSG_TOTAL_SIZE);
		BOOL End();

		void Reset();	//offset �ʱ�ȭ

		BOOL Pop(char* pData);	//������ ����Ÿ�� �о�´�.
		BOOL Pop(char* pData, int nSize);	//������ ����Ÿ�� �о�´�.
		BOOL Push(char* pData, int nSize);	//���ۿ� ����Ÿ�� ����Ѵ�.

	private:
		int nTotalSize_;	//���� �ִ� ������
		int nReadOffset_;	//read offset (�о�� ��ġ)
		int nWriteOffset_;	//write offset(����� ��ġ)
		char* m_pBuffer;	//���� pointer

		CCritSecBase csBuff_;
	};

};//..namespace HisUtil {
