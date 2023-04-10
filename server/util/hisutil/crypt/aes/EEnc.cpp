#include "StdAfx.h"
#include "sha.h"
#include "aes.h"
#include "UtilEnc.h"
#include "EEnc.h"

struct EEnc
{
	aes		e1;
	UINT	e1CheckVal;
};

HANDLE InitializeEnc( UINT e1CheckVal )
{
	EEnc *pEnc = new EEnc;
	pEnc->e1CheckVal = e1CheckVal;

	return (HANDLE)pEnc;
}


void DeinitializeEnc( HANDLE hEnc )
{
	EEnc *pEnc = (EEnc *)hEnc;
	delete pEnc;
}

/*
bool EncryptE0( HANDLE hEnc, const BYTE e0key[BLOCK_SIZE], LPCSTR lpszId, LPCSTR lpszPwd, DWORD dwRand, BYTE Out[BLOCK_SIZE*2] )
{
	EEnc *pEnc = (EEnc *)hEnc;
	BYTE e0In[BLOCK_SIZE*2];

	// id, pwd를 기반으로 key를 설정한다.
	// sha0로 key를 생성한다.
	SHA_CTX ctx;

	SHA_Init( &ctx );
	SHA_Update( &ctx, lpszId, CStringIFT<ENC_IDLEN>::CalcLength(lpszId) );
	SHA_Update( &ctx, lpszPwd, strlen(lpszPwd) );
	SHA_Update( &ctx, &dwRand, sizeof(dwRand) );
	SHA_Final( NULL, &ctx );

	if( pEnc->e1.set_key((LPBYTE)&ctx, BLOCK_SIZE, aes_both) != aes_good )
		return false;

	// id와 rand는 e0로 encryption하여 Out에 넣는다.
	aes e0;
	e0.set_key( e0key, BLOCK_SIZE, aes_enc );

	strncpy( (char*)e0In, lpszId, ENC_IDLEN );
	*(DWORD*)(e0In+ENC_IDLEN) = dwRand;

	return (e0.encrypt(e0In, Out) == aes_good) && (e0.encrypt(e0In+BLOCK_SIZE, Out+BLOCK_SIZE) == aes_good);
}
*/

#ifdef _CUST_TERRA

bool EncryptE2( HANDLE hEnc, const BYTE e0key[BLOCK_SIZE], LPCSTR lpszTid, DWORD dwRand, BYTE Out[BLOCK_SIZE*4] )
{
	EEnc *pEnc = (EEnc *)hEnc;

	// tid를 기반으로 key를 설정한다.
	// sha0로 key를 생성한다.
	SHA_CTX ctx;

	SHA_Init( &ctx );
	SHA_Update( &ctx, lpszTid, strlen(lpszTid) );
	SHA_Update( &ctx, &dwRand, sizeof(dwRand) );
	SHA_Final( NULL, &ctx );

	if( pEnc->e1.set_key((LPBYTE)&ctx, BLOCK_SIZE, aes_both) != aes_good )
		return false;

	// tid는 e0로 encryption하여 Out에 넣는다.
	BYTE PlainText[BLOCK_SIZE*4];
	aes e0;
	e0.set_key( e0key, BLOCK_SIZE, aes_enc );

	strncpy( (char*)PlainText, lpszTid, sizeof(PlainText) );

	for( int i=0; i<sizeof(PlainText); i+=BLOCK_SIZE )
	{
		if( !e0.encrypt(PlainText+i, Out+i) )
			return false;
	}

	return true;
}

#endif


#ifdef _RAS

bool EncryptE3( HANDLE hEnc, const BYTE e0key[ENC_BLOCKSIZE], int nUserNo, LPCSTR lpszJoyonId, LPCSTR lpszGunboundId, LPCSTR lpszRasCode, DWORD dwRand, BYTE Out[ENC_BLOCKSIZE*11] )
{
	EEnc *pEnc = (EEnc *)hEnc;
	BYTE buffPlain[BLOCK_SIZE*11], *pFill=buffPlain;

	// joyon-id등을 기반으로 key를 설정한다.
	// sha0로 key를 생성한다.
	SHA_CTX ctx;

	SHA_Init( &ctx );
	SHA_Update( &ctx, lpszJoyonId, CStringIFT<ENC_IDLEN>::CalcLength(lpszJoyonId) );
	SHA_Update( &ctx, lpszRasCode, strlen(lpszRasCode) );
	SHA_Update( &ctx, &dwRand, sizeof(dwRand) );
	SHA_Final( NULL, &ctx );

	if( pEnc->e1.set_key((LPBYTE)&ctx, BLOCK_SIZE, aes_both) != aes_good )
		return false;

	// user-no, joyon-id, ras-code를 암호화하여 암호화한다.
	aes e0;
	e0.set_key( e0key, BLOCK_SIZE, aes_enc );

	// user-no
	*(int*)pFill = nUserNo;
	pFill += ENC_USERNOLEN;

	// joyon-id
	strncpy( (char*)pFill, lpszJoyonId, ENC_IDLEN );
	pFill += ENC_IDLEN;

	// gunbound-id
	strncpy( (char*)pFill, lpszGunboundId, ENC_IDLEN );
	pFill += ENC_IDLEN;

	// ras code
	strncpy( (char*)pFill, lpszRasCode, ENC_RASCODELEN );
	pFill += ENC_RASCODELEN;

	enc::Enc( &e0, buffPlain, Out, 11 );
	return true;
}

#endif


#ifdef _GAC

bool EncryptE4( HANDLE hEnc, const BYTE e0key[ENC_BLOCKSIZE], LPCSTR lpszId, DWORD dwRand, LPCSTR lpszPassport, BYTE Out[ENC_BLOCKSIZE*3] )
{
	EEnc *pEnc = (EEnc *)hEnc;
	BYTE buffPlain[BLOCK_SIZE*3], *pFill=buffPlain;

	// joyon-id등을 기반으로 key를 설정한다.
	// sha0로 key를 생성한다.
	SHA_CTX ctx;

	SHA_Init( &ctx );
	SHA_Update( &ctx, lpszId, CStringIFT<ENC_IDLEN>::CalcLength(lpszId) );
	SHA_Update( &ctx, &dwRand, sizeof(dwRand) );
	SHA_Final( NULL, &ctx );

	if( pEnc->e1.set_key((LPBYTE)&ctx, BLOCK_SIZE, aes_both) != aes_good )
		return false;

	// user-id, passort등을 암호화한다.
	aes e0;
	e0.set_key( e0key, BLOCK_SIZE, aes_enc );

	// id
	strncpy( (char*)pFill, lpszId, ENC_IDLEN );
	pFill += ENC_IDLEN;

	// passport
	strncpy( (char*)pFill, lpszPassport, ENC_PASSPORTLEN );
	pFill += ENC_PASSPORTLEN;

	enc::Enc( &e0, buffPlain, Out, 3 );
	return true;
}

#endif


// check-value를 모든 block의 앞에 추가하여 encryption한다.
//
bool EncryptE1Plus( HANDLE hEnc, WORD wServiceCode, const BYTE *pIn, int nInSize, LPBYTE pOut, int nOutSize )
{
	// 12 byte block단위로 encryption시킨다.
	EEnc *pEnc = (EEnc *)hEnc;
	BYTE in[BLOCK_SIZE];
	int i, nBlock;

	// input이 12의 배수가 아니면 실패
	if( nInSize % ENC_E1DATABLOCK != 0 )
		return false;

	nBlock = nInSize / ENC_E1DATABLOCK;

	// out buffer가 작으면 실패
	if( nOutSize < nBlock * BLOCK_SIZE )
		return false;

	// encrypt data...
	*(UINT*)in = pEnc->e1CheckVal + wServiceCode;

	for( i=0; i<nBlock; i++, pIn+=ENC_E1DATABLOCK, pOut+=BLOCK_SIZE )
	{
		memcpy( in+ENC_CHECKVAL, pIn, ENC_E1DATABLOCK );

		if( pEnc->e1.encrypt(in, pOut) != aes_good )
			return false;
	}

	return true;
}


// pData, nSize is in/out ENC_E1DATABLOCK (12 bytes)단위로 출력이 된다.
//
bool DecryptE1Plus( HANDLE hEnc, WORD wServiceCode, const BYTE *pIn, int nInSize, LPBYTE pOut, int nOutSize )
{
	// 16 byte block단위로 decryption시킨다.
	EEnc *pEnc = (EEnc *)hEnc;
	BYTE out[BLOCK_SIZE];
	int i, nBlock;

	// 16의 배수가 아니면 실패
	if( nInSize % BLOCK_SIZE != 0 )
		return false;

	nBlock = nInSize / BLOCK_SIZE;

	// out buffer가 작으면 실패
	if( nOutSize < nBlock * ENC_E1DATABLOCK )
		return false;
	
	for( i=0; i<nBlock; i++, pIn+=BLOCK_SIZE, pOut+=ENC_E1DATABLOCK )
	{
		if( pEnc->e1.decrypt(pIn, out) != aes_good )
			return false;

		// check-value
		if( *(UINT*)out != pEnc->e1CheckVal + wServiceCode )
			return false;

		memcpy( pOut, out+ENC_CHECKVAL, ENC_E1DATABLOCK );
	}

	return true;
}


// check-value를 모든 block의 앞에 추가하여 encryption한다.
//
bool EncryptE1( HANDLE hEnc, const BYTE *pIn, int nInSize, LPBYTE pOut, int nOutSize )
{
	// 12 byte block단위로 encryption시킨다.
	EEnc *pEnc = (EEnc *)hEnc;
	BYTE in[BLOCK_SIZE];
	int i, nBlock;

	// input이 12의 배수가 아니면 실패
	if( nInSize % ENC_E1DATABLOCK != 0 )
		return false;

	nBlock = nInSize / ENC_E1DATABLOCK;

	// out buffer가 작으면 실패
	if( nOutSize < nBlock * BLOCK_SIZE )
		return false;

	// encrypt data...
	*(UINT*)in = pEnc->e1CheckVal;

	for( i=0; i<nBlock; i++, pIn+=ENC_E1DATABLOCK, pOut+=BLOCK_SIZE )
	{
		memcpy( in+ENC_CHECKVAL, pIn, ENC_E1DATABLOCK );

		if( pEnc->e1.encrypt(in, pOut) != aes_good )
			return false;
	}

	return true;
}


// pData, nSize is in/out ENC_E1DATABLOCK (12 bytes)단위로 출력이 된다.
//
bool DecryptE1( HANDLE hEnc, const BYTE *pIn, int nInSize, LPBYTE pOut, int nOutSize )
{
	// 16 byte block단위로 decryption시킨다.
	EEnc *pEnc = (EEnc *)hEnc;
	BYTE out[BLOCK_SIZE];
	int i, nBlock;

	// 16의 배수가 아니면 실패
	if( nInSize % BLOCK_SIZE != 0 )
		return false;

	nBlock = nInSize / BLOCK_SIZE;

	// out buffer가 작으면 실패
	if( nOutSize < nBlock * ENC_E1DATABLOCK )
		return false;
	
	for( i=0; i<nBlock; i++, pIn+=BLOCK_SIZE, pOut+=ENC_E1DATABLOCK )
	{
		if( pEnc->e1.decrypt(pIn, out) != aes_good )
			return false;

		// check-value
		if( *(UINT*)out != pEnc->e1CheckVal )
			return false;

		memcpy( pOut, out+ENC_CHECKVAL, ENC_E1DATABLOCK );
	}

	return true;
}