#pragma once
#define ENC_BLOCKSIZE			16								// encryption block size
#define ENC_IDLEN				16								// id ���̴� 16 byte
#define ENC_CHECKVAL			4								// check value���̴� 4 byte
#define ENC_E1DATABLOCK			(ENC_BLOCKSIZE-ENC_CHECKVAL)	// E1���� check-value�� ������ ���� data block ũ��

// Initialize encryption engine..., return encryption handle
//
HANDLE InitializeEnc( UINT e1CheckVal );

// free resources...
//
void DeinitializeEnc( HANDLE hEnc );


// id/pwd�� ������� e0 encryption�� �� Out�� ��ȯ�Ѵ�. ���� id/pwd�� ����� E1 encryption key�� �����Ѵ�.
//
//bool EncryptE0( HANDLE hEnc, const BYTE e0key[ENC_BLOCKSIZE], LPCSTR lpszId, LPCSTR lpszPwd, DWORD dwRand, BYTE Out[ENC_BLOCKSIZE*2] );


// input: �ݵ�� 12�� ���ũ�⿩����, output: 16 x block����
//
bool EncryptE1( HANDLE hEnc, const BYTE *pIn, int nInSize, LPBYTE pOut, int nOutSize );
bool EncryptE1Plus( HANDLE hEnc, WORD wServiceCode, const BYTE *pIn, int nInSize, LPBYTE pOut, int nOutSize );


// input: �ݵ�� 16�� ���ũ�⿩����, output: 12 x block����
//
bool DecryptE1( HANDLE hEnc, const BYTE *pIn, int nInSize, LPBYTE pOut, int nOutSize );
bool DecryptE1Plus( HANDLE hEnc, WORD wServiceCode, const BYTE *pIn, int nInSize, LPBYTE pOut, int nOutSize );

#ifdef _CUST_TERRA

// tid�� ������� e0 encryption�� �� Out�� ��ȯ�Ѵ�. ���� tid�� ����� E1 encryption key�� �����Ѵ�.
//
bool EncryptE2( HANDLE hEnc, const BYTE e0key[ENC_BLOCKSIZE], LPCSTR lpszTid, DWORD dwRand, BYTE Out[ENC_BLOCKSIZE*4] );

#endif


#ifdef _RAS

#define ENC_USERNOLEN			4
#define ENC_RASCODELEN			128

// joyon (ras)�� �α��� ��ȣ��Ŷ ����
//
bool EncryptE3( HANDLE hEnc, const BYTE e0key[ENC_BLOCKSIZE], int nUserNo, LPCSTR lpszJoyonId, LPCSTR lpszGunboundId, LPCSTR lpszRasCode, DWORD dwRand, BYTE Out[ENC_BLOCKSIZE*11] )

#endif


#ifdef _GAC

#define ENC_PASSPORTLEN			20

// zhaoh (gac)�� �α��� ��ȣ��Ŷ ����
//
bool EncryptE4( HANDLE hEnc, const BYTE e0key[ENC_BLOCKSIZE], LPCSTR lpszId, DWORD dwRand, LPCSTR lpszPassport, BYTE Out[ENC_BLOCKSIZE*3] );

#endif


