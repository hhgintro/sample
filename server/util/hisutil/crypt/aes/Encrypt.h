#pragma once

class CEncrypt
{
public:
	CEncrypt(ULONG ulCheckVal, PBYTE pKey);
	~CEncrypt();

	void Encrypt(const PCHAR pInData, WORD wInSize, PCHAR pOutData, WORD wOutSize);
	void Decrypt(const PCHAR pInData, WORD wInSize, PCHAR pOutData, WORD wOutSize);

private:
	HANDLE	m_hEncrypt;
};