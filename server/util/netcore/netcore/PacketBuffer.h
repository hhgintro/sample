#pragma once

namespace HisUtil {

	class CPacketBuffer// : public CMultiThreadSync<CPacketBuffer>
	{
	public:
		//nPoolSize : 패킷 하나의 최대 사이즈
		//nPoolCnt : 패킷 수용 개수
		//버퍼 총 사이즈 = nPoolSize * nPoolCnt
		CPacketBuffer();
		~CPacketBuffer();

		BOOL Begin(int nPoolSize = MSG_TOTAL_SIZE);
		BOOL End();

		void Reset();	//offset 초기화

		BOOL Pop(char* pData);	//버퍼의 데이타를 읽어온다.
		BOOL Pop(char* pData, int nSize);	//버퍼의 데이타를 읽어온다.
		BOOL Push(char* pData, int nSize);	//버퍼에 데이타를 기록한다.

	private:
		int nTotalSize_;	//버퍼 최대 사이즈
		int nReadOffset_;	//read offset (읽어올 위치)
		int nWriteOffset_;	//write offset(기록할 위치)
		char* m_pBuffer;	//버퍼 pointer

		CCritSecBase csBuff_;
	};

};//..namespace HisUtil {
