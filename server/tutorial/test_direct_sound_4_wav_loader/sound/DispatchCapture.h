#pragma once


class DispatchCapture : public SoundCapture// : public HisUtil::CSingleton<SoundCapture>
{
public:
	DispatchCapture();
	virtual ~DispatchCapture();

	//Mic�� ���� capture�� ����Ÿ�� �޴´�.
	virtual void ReadCaptureBuffer(byte* buff, DWORD dwBufferBytes);

};

