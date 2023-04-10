#pragma once
#include "Aes.h"

namespace enc
{
	// �ش� ������ enc/dec �ϱ����� �ʿ��� block ������ ��ȯ
	inline int BlockCount( int nLen, int nBlockSize=BLOCK_SIZE )
	{
		return (nLen + nBlockSize - 1) / nBlockSize;
	}

	// �ش� ���̸� enc/dec �ϱ����� ����� buffer ũ�⸦ ��ȯ
	inline int EnoughSize( int nLen, int nBlockSize=BLOCK_SIZE )
	{
		return BlockCount(nLen, nBlockSize) * nBlockSize;
	}


	inline void Enc( aes *pAes, const BYTE *pIn, BYTE *pOut, int nBlock )
	{
		for( int i=0; i<nBlock; i++, pIn+=BLOCK_SIZE, pOut+=BLOCK_SIZE )
			pAes->encrypt( pIn, pOut );
	}

	inline void Dec( aes *pAes, const BYTE *pIn, BYTE *pOut, int nBlock )
	{
		for( int i=0; i<nBlock; i++, pIn+=BLOCK_SIZE, pOut+=BLOCK_SIZE )
			pAes->decrypt( pIn, pOut );
	}
}


