#pragma once

#include "../../util/serial/Serial.h"

class CSerialEx : public HisUtil::CSerial
{
public:
	CSerialEx() {}
	~CSerialEx() {}

	//����Ÿ�� ������ CALLBACK�ȴ�.
	virtual void OnReceiveData(BYTE* data, int length);

};

