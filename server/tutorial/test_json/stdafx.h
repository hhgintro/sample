// stdafx.h : ���� ��������� ���� ��������� �ʴ�
// ǥ�� �ý��� ���� ���� �� ������Ʈ ���� ���� ������
// ��� �ִ� ���� �����Դϴ�.
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>



// TODO: ���α׷��� �ʿ��� �߰� ����� ���⿡�� �����մϴ�.
#include <iostream>

#include "../../util/Json/Include/reader.h"






#ifdef _DEBUG
#pragma comment(lib, "../../bin/lib_json/lib_json_d.lib")
#else
#pragma comment(lib, "../../bin/lib_json/lib_json.lib")
#endif