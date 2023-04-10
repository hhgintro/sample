#pragma once

namespace HisUtil {

	class CCrypto
	{
	public:
		static BOOL Encrypt(unsigned char *source, UINT32 length, unsigned char *destination);
		static BOOL Decrypt(unsigned char *source, UINT32 length, unsigned char *destination);
	};

};//..namespace HisUtil {
