// MsgPack.h: interface for the CMsg class.
//
//////////////////////////////////////////////////////////////////////

#pragma once


namespace HisUtil {

	/////////////////////////////////////////
	//Ư�����̸� ��Ŷ�� �ǰ��� �Ҷ� ����Ѵ�.
	class CMsgPack
	{
	public:
		CMsgPack() : buf(NULL), len(0) {}
		CMsgPack(void* p) : buf(p) {}	//�б�����.
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
	//..//Ư�����̸� ��Ŷ�� �ǰ��� �Ҷ� ����Ѵ�.
	/////////////////////////////////////////

};//..namespace HisUtil {
