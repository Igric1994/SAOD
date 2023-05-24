#pragma once
#include "_str.h"

class Str
{
	_str* m_pStr;
public:
	Str() //�������� ������ ����������
	{
		m_pStr = new _str;
	}
	Str(const char* p) //�������� ������ ����������
	{				   //� ������� �������
		m_pStr = new _str(p);
	}
	Str(const Str &s) //����������� ���� ����������
	{				  //�������� ������
		m_pStr = s.m_pStr; //��������� �� ��� �� ������
		m_pStr->addRef(); //����������� ������� ������
	}
	Str& operator=(const Str &s)
	{
		if (this != &s) //���� ������ �� ����������
		{
			s.m_pStr->addRef(); //����������� ������� ������
								//� ��������� ������

			m_pStr->Release();  //��������� ������� ������
								//� ������� ������

			m_pStr = s.m_pStr;	//������ ������� ��������� �� ������
								//���������� ��������� ��������� ��
								//������ �����
		}
		return *this;
	}
	Str& operator+=(const Str& s)
	{
		if (s.len() != 0)
		{
			int lenght = len() + s.len(); //��������� ����� ����� ������
			_str* pstrTmp = new _str; //������ ����� ��������� �� ������ _str
			delete[] pstrTmp->m_pszData; //������� �� ���� ������

			pstrTmp->m_pszData = new char[lenght + 1]; //������ �����, � ������ �������
			strcpy_s(pstrTmp->m_pszData, lenght + 1, m_pStr->m_pszData); //�����������
			strcat_s(pstrTmp->m_pszData, lenght + 1, s.m_pStr->m_pszData); //������������

			m_pStr->Release(); //������� ������� ��������� �� ������ _str
			m_pStr = pstrTmp; //���������
		}
		return *this;
	}
	//---------------------------------------------------------------
	int replace(char ch_old, char ch_new) {
		
		if (ch_old != 0 || ch_new != 0){
			int n = 0;
			_str* pstrTmp = new _str;
			int lenght = len();

			pstrTmp->m_pszData = new char[lenght + 1];
			strcpy_s(pstrTmp->m_pszData, lenght + 1, m_pStr->m_pszData);
			
			m_pStr->Release();
			m_pStr = pstrTmp;
			char* p = m_pStr->m_pszData;
			while (*p)
			{
				if (*p == ch_old)
				{
					*p = ch_new;
				}
				p++;
				n++;
			}

			return n;
		}
		return ch_new ;
	}
	//---------------------------------------------------------------
	operator const char*()
	{
		return m_pStr->m_pszData;
	}
	~Str()
	{
		m_pStr->Release();
	}
	int len() const
	{
		return strlen(m_pStr->m_pszData);
	}
};