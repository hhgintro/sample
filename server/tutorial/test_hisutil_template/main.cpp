// test_hisutil_template.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <windows.h>

//#include "MyInstantiatedTemplate.h"
#include "MyTemplate.inl"

/*
결론:
	- 헤더(.h)에는 선언부 / 소스(.inl)에는 구현부
	- 구현부에 "#include 헤더" 추가
	- 사용시 main()에 "#include 소스" 추가 ( "*** 헤더 ***" 아님 )
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

