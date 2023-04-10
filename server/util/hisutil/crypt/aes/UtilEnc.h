#pragma once
#include "Aes.h"

namespace enc
{
	// 해당 길이을 enc/dec 하기위해 필요한 block 개수를 반환
	inline int BlockCount( int nLen, int nBlockSize=BLOCK_SIZE )
	{
		return (nLen + nBlockSize - 1) / nBlockSize;
	}

	// 해당 길이를 enc/dec 하기위해 충분한 buffer 크기를 반환
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


