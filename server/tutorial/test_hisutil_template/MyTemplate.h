#pragma once

template <class T>
class MyTemplate
{
public:
	MyTemplate(const T& rt);
	void dump();
	T t;
};