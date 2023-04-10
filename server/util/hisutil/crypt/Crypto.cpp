#include "stdafx.h"
#include "Crypto.h"

namespace HisUtil {

	const UINT32 C1 = 42875;
	const UINT32 C2 = 26119;
	const UINT32 KEY = 71957;

	BOOL CCrypto::Encrypt(unsigned char *source, UINT32 length, unsigned char *destination)
	{
		UINT32 Key = KEY;

		if (!source || !destination || length <= 0)
			return FALSE;

		for (UINT32 i = 0; i < length; ++i)
		{
			destination[i] = source[i] ^ (Key >> 8);
			
			//Encrypt된 값으로 생성되는 Key는
			//동일한 순서를 갖는다.
			Key = (destination[i] + Key) * C1 + C2;
			//printf("%d ", Key);
		}
		//printf("\n");

		return TRUE;
	}

	BOOL CCrypto::Decrypt(unsigned char *source, UINT32 length, unsigned char *destination)
	{
		unsigned char PreviousBlock = 0;
		UINT32 Key = KEY;

		if (!source || !destination || length <= 0)
			return FALSE;

		for (UINT32 i = 0; i < length; ++i)
		{
			PreviousBlock = source[i];
			destination[i] = source[i] ^ (Key >> 8);
			
			//Encrypt된 값으로 생성되는 Key는
			//동일한 순서를 갖는다.
			Key = (PreviousBlock + Key) * C1 + C2;
			//printf("%d ", Key);
		}
		//printf("\n");

		return TRUE;
	}

};//..namespace HisUtil {
