#pragma once

namespace HisUtil {

	//주로 Packet을 보내는 용도로 사용합니다
	class CPoolBuffer
	{
		struct _BufferNode
		{
			UINT length_;
			UCHAR buf_[MSG_TOTAL_SIZE];

			DWORD remotePublicIP_;
			WORD remotePort_;
			_BufferNode *pNext_;

			//생성자
			_BufferNode()
				: length_(0), pNext_(0), remotePublicIP_(0), remotePort_(0)	{}
		};

		INT cntPool_;		//pool 의 총 사이즈
		INT cntUsedPool_;	//pool 사용량

		//buff node의 맨처음(초기화를 목적으로 한다.)
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
