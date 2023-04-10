#pragma once
#define ENC_BLOCKSIZE			16								// encryption block size
#define ENC_IDLEN				16								// id 길이는 16 byte
#define ENC_CHECKVAL			4								// check value길이는 4 byte
#define ENC_E1DATABLOCK			(ENC_BLOCKSIZE-ENC_CHECKVAL)	// E1에서 check-value를 제외한 실제 data block 크기

// Initialize encryption engine..., return encryption handle
//
HANDLE InitializeEnc( UINT e1CheckVal );

// free resources...
//
void DeinitializeEnc( HANDLE hEnc );


// id/pwd를 기반으로 e0 encryption한 후 Out에 반환한다. 또한 id/pwd를 기반을 E1 encryption key를 설정한다.
//
//bool EncryptE0( HANDLE hEnc, const BYTE e0key[ENC_BLOCKSIZE], LPCSTR lpszId, LPCSTR lpszPwd, DWORD dwRand, BYTE Out[ENC_BLOCKSIZE*2] );


// input: 반드시 12의 배수크기여야함, output: 16 x block개수
//
bool EncryptE1( HANDLE hEnc, const BYTE *pIn, int nInSize, LPBYTE pOut, int nOutSize );
bool EncryptE1Plus( HANDLE hEnc, WORD wServiceCode, const BYTE *pIn, int nInSize, LPBYTE pOut, int nOutSize );


// input: 반드시 16의 배수크기여야함, output: 12 x block개수
//
bool DecryptE1( HANDLE hEnc, const BYTE *pIn, int nInSize, LPBYTE pOut, int nOutSize );
bool DecryptE1Plus( HANDLE hEnc, WORD wServiceCode, const BYTE *pIn, int nInSize, LPBYTE pOut, int nOutSize );

#ifdef _CUST_TERRA

// tid를 기반으로 e0 encryption한 후 Out에 반환한다. 또한 tid를 기반을 E1 encryption key를 설정한다.
//
bool EncryptE2( HANDLE hEnc, const BYTE e0key[ENC_BLOCKSIZE], LPCSTR lpszTid, DWORD dwRand, BYTE Out[ENC_BLOCKSIZE*4] );

#endif


#ifdef _RAS

#define ENC_USERNOLEN			4
#define ENC_RASCODELEN			128

// joyon (ras)용 로그인 암호패킷 생성
//
bool EncryptE3( HANDLE hEnc, const BYTE e0key[ENC_BLOCKSIZE], int nUserNo, LPCSTR lpszJoyonId, LPCSTR lpszGunboundId, LPCSTR lpszRasCode, DWORD dwRand, BYTE Out[ENC_BLOCKSIZE*11] )

#endif


#ifdef _GAC

#define ENC_PASSPORTLEN			20

// zhaoh (gac)용 로그인 암호패킷 생성
//
bool EncryptE4( HANDLE hEnc, const BYTE e0key[ENC_BLOCKSIZE], LPCSTR lpszId, DWORD dwRand, LPCSTR lpszPassport, BYTE Out[ENC_BLOCKSIZE*3] );

#endif


