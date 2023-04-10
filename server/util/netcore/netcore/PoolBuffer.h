#pragma once

namespace HisUtil {

	//�ַ� Packet�� ������ �뵵�� ����մϴ�
	class CPoolBuffer
	{
		struct _BufferNode
		{
			UINT length_;
			UCHAR buf_[MSG_TOTAL_SIZE];

			DWORD remotePublicIP_;
			WORD remotePort_;
			_BufferNode *pNext_;

			//������
			_BufferNode()
				: length_(0), pNext_(0), remotePublicIP_(0), remotePort_(0)	{}
		};

		INT cntPool_;		//pool �� �� ������
		INT cntUsedPool_;	//pool ��뷮

		//buff node�� ��ó��(�ʱ�ȭ�� �������� �Ѵ�.)
		_BufferNode *root_;

		_BufferNode *headFree_;
		_BufferNode *tailFree_;
		_BufferNode *headUse_;
		_BufferNode *tailUse_;

		CCritSecBase csBuff_;

	public:
		CPoolBuffer();
		~CPoolBuffer();
		BOOL Begin(UINT cntPool = 1);
		BOOL End();
		void Reset();

		BYTE* Push(void* pData, UINT length);
		BYTE* Push(void* pData, UINT length, ADDR_IP remoteIP, ADDR_PORT remotePort);

		BOOL Pop(void* pData, UINT length);
		BOOL Pop(void* pData, UINT length, ADDR_IP& remoteIP, ADDR_PORT& remotePort);

		UINT GetPoolCount()					{ return cntPool_; }
		UINT GetCurPoolCount()				{ return cntUsedPool_; }

	private:
		void AllocBlock();

	};

};//..namespace HisUtil {
