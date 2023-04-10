/*! 
CriticalSectionEx for the EpLibrary

The MIT License (MIT)

Copyright (c) 2008-2013 Woong Gyu La <juhgiyo@gmail.com>

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/
#include "stdafx.h"
#include "CriticalSectionEx.h"


CriticalSectionEx::CriticalSectionEx() :BaseLock()
{
	InitializeCriticalSection(&m_criticalSection);
	m_lockCounter=0;
}

CriticalSectionEx::CriticalSectionEx(const CriticalSectionEx& b):BaseLock()
{
	InitializeCriticalSection(&m_criticalSection);
	m_lockCounter=0;
}

CriticalSectionEx::~CriticalSectionEx()
{
	//assert(m_lockCounter==0);
	DeleteCriticalSection(&m_criticalSection);
}

bool CriticalSectionEx::Lock()
{
	EnterCriticalSection(&m_criticalSection);
	m_lockCounter++;
	return true;
}

long CriticalSectionEx::TryLock()
{
	long ret=TryEnterCriticalSection(&m_criticalSection);
	if(ret)
		m_lockCounter++;
	return ret;
}
long CriticalSectionEx::TryLockFor(const unsigned int dwMilliSecond)
{
	long ret=0;
	if(ret=TryEnterCriticalSection(&m_criticalSection))
	{
		m_lockCounter++;
		return ret;	
	}
	else
	{
		unsigned int startTime,timeUsed;
		unsigned int waitTime=dwMilliSecond;
		startTime=GetTickCount();
		while(WaitForSingleObject(m_criticalSection.LockSemaphore,waitTime)==WAIT_OBJECT_0)
		{
			if(ret=TryEnterCriticalSection(&m_criticalSection))
			{
				m_lockCounter++;
				return ret;	
			}		
			timeUsed=GetTickCount()-startTime;
			waitTime=waitTime-timeUsed;
			startTime=GetTickCount();
		}
		return 0;
	}
}
void CriticalSectionEx::Unlock()
{
	m_lockCounter--;
	assert(m_lockCounter>=0);
	LeaveCriticalSection(&m_criticalSection);
}

