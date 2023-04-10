#include "StdAfx.h"
#include "EEnc.h"
#include "aes.h"
#include "Encrypt.h"

CEncrypt::CEncrypt(ULONG ulCheckVal, PBYTE pKey)
{
	m_hEncrypt = InitializeEnc(ulCheckVal);
	static_cast<aes*>(m_hEncrypt)->set_key(pKey, 16, aes_both);
}

CEncrypt::~CEncrypt()
{
	DeinitializeEnc(m_hEncrypt);
}

void CEncrypt::Encrypt(const PCHAR pInData, WORD wInSize, PCHAR pOutData, WORD wOutSize)
{
	EncryptE1(m_hEncrypt, reinterpret_cast<const PBYTE>(pInData), static_cast<int>(wInSize), reinterpret_cast<LPBYTE>(pOutData),
		static_cast<int>(wOutSize));
}

void CEncrypt::Decrypt(const PCHAR pInData, WORD wInSize, PCHAR pOutData, WORD wOutSize)
{
	DecryptE1(m_hEncrypt, reinterpret_cast<const PBYTE>(pInData), static_cast<int>(wInSize), reinterpret_cast<LPBYTE>(pOutData),
		static_cast<int>(wOutSize));
}