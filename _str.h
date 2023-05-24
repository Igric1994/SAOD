#pragma once
#include <string>

class Str;
class _str
{
	friend class Str;
	char* m_pszData;
	int m_nCount;

	_str()
	{
		m_pszData = new char[1]{ 0 };
		m_nCount = 1;
	}
	_str(const char *p)
	{
		m_pszData = new char[strlen(p) + 1];
		strcpy_s(m_pszData, strlen(p) + 1, p);
		m_nCount = 1;
	}
	~_str()
	{
		delete[] m_pszData;
	}
	void addRef()
	{
		m_nCount++;
	}
	void Release()
	{
		m_nCount--;
		if (m_nCount == 0) 
			delete this;
	}
};