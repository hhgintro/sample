#pragma once

#include <stdint.h>		//INT8_MAX

namespace HisUtil {

	//C:\Program Files (x86)\Microsoft SDKs\Windows\v7.0A\Include\intsafe.h 에정의된 값
	static INT8 MAX_TYPE_VALUE(INT8)		{ return INT8_MAX;}
	static INT16 MAX_TYPE_VALUE(INT16)		{ return INT16_MAX;}
	static INT32 MAX_TYPE_VALUE(INT32)		{ return INT32_MAX;}
	static INT64 MAX_TYPE_VALUE(INT64)		{ return INT64_MAX;}

	static UINT8 MAX_TYPE_VALUE(UINT8)		{ return UINT8_MAX;}
	static UINT16 MAX_TYPE_VALUE(UINT16)	{ return UINT16_MAX;}
	static UINT32 MAX_TYPE_VALUE(UINT32)	{ return UINT32_MAX;}
	static UINT64 MAX_TYPE_VALUE(UINT64)	{ return UINT64_MAX;}



	//==============================================================
	//Random function
	//returns a random integer between x and y
	inline int   RandInt(int x,int y)
	{
		if(x == y)	return x;
		if (y < x) { int temp = x; x = y; y = temp; }
		return rand()%(y-x+1)+x;
		//return abs(g_server_rand.GetInt())%(y-x+1)+x;
	}

	inline int   RandInt_D(int x,int y)
	{
		if(x == y)	return x; 
		if (y < x) { int temp = x; x = y; y = temp; }
		return rand() % (y - x + 1) + x;
		//return abs(g_server_rand.GetInt())%(y-x+1)+x;
	}

	//returns a random double between zero and 1
	inline double RandFloat()      
	{
		return ((rand())/(RAND_MAX+1.0));
		//return g_server_rand.GetFloat();

	}

	inline double RandInRange(double x, double y)
	{
		if(x == y)	return x;
		if (y < x) { double temp = x; x = y; y = temp; }
		return x + RandFloat()*(y - x);
	}
	inline float RandInRange(float x, float y)
	{
		if(x == y)	return x;
		if (y < x) { float temp = x; x = y; y = temp; }
		return x + (float)(RandFloat())*(y - x);
	}
	//returns a random bool
	inline bool   RandBool()
	{
		if (RandInt(0,1)) return true;
		else return false;
	}

	//returns a random double in the range -1 < n < 1
	inline double RandomClamped()    {return RandFloat() - RandFloat();}



	//==============================================================
	//rect 충돌체크
	template<class T>
	BOOL CheckRectCollision(T topA, T bottomA, T leftA, T rightA				//스킬 영역
		, T topB, T bottomB, T leftB, T rightB)									//(object의) damage 영역
	{
		//RECT A : 스킬 영역
		//RECT B : (object의) damage 영역

		//B가 A보다 위쪽에 있다.
		if (bottomB < topA)
			return FALSE;
		//B가 A보다 아래쪽에 있다.
		if (bottomA < topB)
			return FALSE;
		//B가 A보다 왼쪽에 있다.
		if (rightB < leftA)
			return FALSE;
		//B가 A보다 오른쪽에 있다.
		if (rightA < leftB)
			return FALSE;

		return TRUE;
	}


};//namespace HisUtil {