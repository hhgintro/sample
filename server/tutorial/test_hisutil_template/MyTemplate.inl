#include "MyTemplate.h"
#include <iostream>

template <class T>
MyTemplate<T>::MyTemplate(const T& rt)
	: t(rt)
{
}

template <class T>
void MyTemplate<T>::dump()
{
	std::cout << t << std::endl;
}