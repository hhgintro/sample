#pragma once


class Base64Tool 
{
	Base64Tool(void);
	~Base64Tool();



public:
	static int base64_decode(const char *text, unsigned char *dst, int numBytes );
	static int base64_encode(const wchar_t *text, int numBytes, Proud::String &encodeText);
};
