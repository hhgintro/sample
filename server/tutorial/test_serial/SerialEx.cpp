#include "stdafx.h"
#include "SerialEx.h"


void CSerialEx::OnReceiveData(BYTE* data, int length)
{
	TCHAR buf[1024] = _T("");
	TCHAR tmp[1024] = _T("");
	_stprintf_s(buf, _T("data(%d):"), length);

	for (int i = 0; i < length; ++i)
	{
		_stprintf_s(tmp, _T("[0x%02x],"), data[i]);
		_tcscat_s(buf, tmp);
	}
	//_tprintf(_T("data(%d):[0x%x][0x%x][0x%x][0x%x][0x%x][0x%x][0x%x][0x%x]\n")
	//	, length, data[0], data[1], data[2], data[3], data[4], data[5], data[6], data[7]);
	_tcscat_s(buf, _T("\n"));
	_tprintf(buf);
}
