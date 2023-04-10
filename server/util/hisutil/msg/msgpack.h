// MsgPack.h: interface for the CMsg class.
//
//////////////////////////////////////////////////////////////////////

#pragma once


namespace HisUtil {

	/////////////////////////////////////////
	//특정길이를 패킷에 실고자 할때 사용한다.
	class CMsgPack
	{
	public:
		CMsgPack() : buf(NULL), len(0) {}
		CMsgPack(void* p) : buf(p) {}	//읽기전용.
		CMsgPack(void* p, int l) {//p:buf, s:size
			Set(p, l);
		}
		void Set(void* p, int l) {
			//memcpy_s(buf, sizeof(buf), p, s);
			buf = p;
			len = l;
		}
	public:
		//char buf[0x2000];	//MSG_TOTAL_SIZE
		void* buf;
		WORD len;
	};
	//..//특정길이를 패킷에 실고자 할때 사용한다.
	/////////////////////////////////////////

};//..namespace HisUtil {
