#include "stdafx.h"
#include "PoolBuffer.h"


namespace HisUtil {

	CPoolBuffer::CPoolBuffer()
		: cntPool_(0), cntUsedPool_(0), root_(0), headFree_(0), tailFree_(0), headUse_(0), tailUse_(0)
	{
	}

	CPoolBuffer::~CPoolBuffer()
	{
		while (headUse_)
		{
			_BufferNode *pTemp = headUse_;
			headUse_ = pTemp->pNext_;

			delete pTemp;
			pTemp = NULL;
		}

		while (headFree_)
		{
			_BufferNode *pTemp = headFree_;
			headFree_ = pTemp->pNext_;

			delete pTemp;
			pTemp = NULL;
		}
	}

	BOOL CPoolBuffer::Begin(UINT cntPool)
	{
		AUTO_LOCK(csBuff_);

		if (NULL == root_)
		{
			assert(cntPool);

			cntUsedPool_ = 0;
			cntPool_ = 1;//무조건 1개 만들고 for문 돈다.

			root_ = new _BufferNode;
			headFree_ = root_;
			tailFree_ = root_;
			headUse_ = NULL;
			tailUse_ = NULL;

			for (UINT cnt = 1; cnt < cntPool; ++cnt)
				AllocBlock();
		}

		LOGEVENT("PoolBuffer_Info", _T("INFO cntPool_(%d)"), cntPool_);
		return TRUE;
	}

	BOOL CPoolBuffer::End()
	{
		return TRUE;
	}

	void CPoolBuffer::Reset()
	{
		AUTO_LOCK(csBuff_);
		cntUsedPool_ = 0;

		headFree_ = root_;

		headUse_ = NULL;
		tailUse_ = NULL;
	}

	BYTE* CPoolBuffer::Push(void* pData, UINT length)
	{
		AUTO_LOCK(csBuff_);

		if (NULL == pData || NULL == length || NULL == headFree_)
			return NULL;

		if (MSG_TOTAL_SIZE <= length)
		{
			LOGEVENT("PoolBuffer_Error", _T("- Error Too large size(%d)"), length);
			return NULL;
		}

		headFree_->length_ = length;
		memcpy(headFree_->buf_, pData, length);
		BYTE* buff = headFree_->buf_;

		++cntUsedPool_;
		LOGEVENT("PoolBuffer_Info", _T("INFO add cntUsedPool_(%d)"), cntUsedPool_);

		if (headFree_ == tailFree_)
			AllocBlock();

		if (headUse_)
		{
			tailUse_->pNext_ = headFree_;
			tailUse_ = headFree_;
		}
		else
		{
			headUse_ = headFree_;
			tailUse_ = headFree_;
		}

		headFree_ = headFree_->pNext_;
		tailUse_->pNext_ = NULL;

		return buff;
	}

	BOOL CPoolBuffer::Pop(void* pData, UINT length)
	{
		AUTO_LOCK(csBuff_);

		if (NULL == pData || NULL == headUse_ || NULL == tailFree_ || cntUsedPool_ <= 0)
			return FALSE;

		//length = headFree_->length_;
#ifdef _DEBUG
		memset(pData, 0x33, length); //오류체크
#endif
		memcpy(pData, headUse_->buf_, min(length, headUse_->length_));

		--cntUsedPool_;
		LOGEVENT("PoolBuffer_Info", _T("INFO sub cntUsedPool_(%d)"), cntUsedPool_);

		tailFree_->pNext_ = headUse_;
		tailFree_ = headUse_;

		if (headUse_ == tailUse_)
		{
			headUse_ = tailUse_ = NULL;
		}
		else
		{
			headUse_ = headUse_->pNext_;
			tailFree_->pNext_ = NULL;
		}
		return TRUE;
	}

	BYTE* CPoolBuffer::Push(void* pData, UINT length, ADDR_IP remoteIP, ADDR_PORT remotePort)
	{
		AUTO_LOCK(csBuff_);

		if (NULL == pData || NULL == length || NULL == headFree_)
			return NULL;

		headFree_->remotePublicIP_ = remoteIP;
		headFree_->remotePort_ = remotePort;

		return Push(pData, length);
	}

	BOOL CPoolBuffer::Pop(void* pData, UINT length, ADDR_IP& remoteIP, ADDR_PORT& remotePort)
	{
		AUTO_LOCK(csBuff_);

		if (NULL == pData || NULL == headUse_)
			return FALSE;

		remoteIP = headUse_->remotePublicIP_;
		remotePort = headUse_->remotePort_;

		return Pop(pData, length);
	}

	void CPoolBuffer::AllocBlock()
	{
		AUTO_LOCK(csBuff_);
		_BufferNode *pTemp = new _BufferNode;

		tailFree_->pNext_ = pTemp;
		tailFree_ = pTemp;

		++cntPool_;
	}

};//..namespace HisUtil {
