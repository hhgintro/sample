// test_hisutil_template.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <windows.h>

//#include "MyInstantiatedTemplate.h"
#include "MyTemplate.inl"

/*
���:
	- ���(.h)���� ����� / �ҽ�(.inl)���� ������
	- �����ο� "#include ���" �߰�
	- ���� main()�� "#include �ҽ�" �߰� ( "*** ��� ***" �ƴ� )
*/
int main()
{
	//MyInstantiatedTemplate m(100);
	//m.dump();

	MyTemplate<int> t(100);
	t.dump();

	system("pause");
    return 0;
}

