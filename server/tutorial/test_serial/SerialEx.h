#pragma once

#include "../../util/serial/Serial.h"

class CSerialEx : public HisUtil::CSerial
{
public:
	CSerialEx() {}
	~CSerialEx() {}

	//데이타를 받으면 CALLBACK된다.
	virtual void OnReceiveData(BYTE* data, int length);

};

