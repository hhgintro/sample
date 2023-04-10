#pragma once


class DispatchCapture : public SoundCapture// : public HisUtil::CSingleton<SoundCapture>
{
public:
	DispatchCapture();
	virtual ~DispatchCapture();

	//Mic로 부터 capture된 데이타를 받는다.
	virtual void ReadCaptureBuffer(byte* buff, DWORD dwBufferBytes);

};

