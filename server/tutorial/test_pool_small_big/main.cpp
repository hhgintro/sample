// pool.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"

//#include <windows.h>

#include "pool/HisCritSec.h"

#include "pool/MemoryPool.h"

struct AAA {
	int a = 0;
	int b = 0;
};
BOOL IS_BIG(AAA* a, void* val)
{
	return (a->a > (int)val);
}
BOOL IS_SMALL(AAA* a, void* val)
{
	return (a->a < (int)val);
}

int _tmain(int argc, _TCHAR* argv[])
{
	std::vector<int> vec;
	vec.reserve(10);
	vec.push_back(1);
	printf("vec size : %d\n", vec.size());

	HisUtil::CMemoryPool<int,AAA> pool, pool2;
	for (int i = 0; i < 5; ++i)
	{
		AAA* aaa = pool.Create();
		aaa->a = i + 1;
		pool.Insert(aaa->a, aaa);
	}

	AAA* aaa = pool2.Create();
	aaa->a = 6;
	pool2.Insert(aaa->a, aaa);

	AAA* a2 = pool.Pop(1);
	pool2.Insert(a2->a, a2);

	printf("total count : %d\n", pool.GetUsedMemSize());

	std::vector<AAA*> vecAll;
	//pool.GetAllList(vecAll, 0, 3, IS_SMALL, (void*)2);
	pool.GetAllList(vecAll);
	for (int i = 0; i < (int)vecAll.size(); ++i)
	{
		AAA* aaa = vecAll[i];
		if (NULL == aaa) continue;
		printf("pool a = %d\n", aaa->a);
	}

	std::vector<AAA*> vecAll2;
	pool2.GetAllList(vecAll2);
	for (int i = 0; i < (int)vecAll2.size(); ++i)
	{
		AAA* aaa = vecAll2[i];
		if (NULL == aaa) continue;
		printf("pool2 a = %d\n", aaa->a);
	}

	system("pause");
	return 0;
}

