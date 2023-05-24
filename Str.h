#pragma once
#include "_str.h"

class Str
{
	_str* m_pStr;
public:
	Str() //создание нового экземпл€ра
	{
		m_pStr = new _str;
	}
	Str(const char* p) //создание нового экземпл€ра
	{				   //с готовой строкой
		m_pStr = new _str(p);
	}
	Str(const Str &s) //копирование путЄм увеличени€
	{				  //счЄтчика ссылок
		m_pStr = s.m_pStr; //ссылаемс€ на тот же ресурс
		m_pStr->addRef(); //увеличиваем счЄтчик ссылок
	}
	Str& operator=(const Str &s)
	{
		if (this != &s) //если ссылки не одинаковые
		{
			s.m_pStr->addRef(); //увеличиваем счЄтчик ссылок
								//у сторонней строки

			m_pStr->Release();  //уменьшаем счЄтчик ссылок
								//у текущей строки

			m_pStr = s.m_pStr;	//теперь текущий указатель на объект
								//управлени€ ресурсами указывает на
								//другой адрес
		}
		return *this;
	}
	Str& operator+=(const Str& s)
	{
		if (s.len() != 0)
		{
			int lenght = len() + s.len(); //вычисл€ем длину новой строки
			_str* pstrTmp = new _str; //создаЄм новый указатель на объект _str
			delete[] pstrTmp->m_pszData; //удал€ем из него строку

			pstrTmp->m_pszData = new char[lenght + 1]; //создаЄм новую, с нужной длинной
			strcpy_s(pstrTmp->m_pszData, lenght + 1, m_pStr->m_pszData); //копирование
			strcat_s(pstrTmp->m_pszData, lenght + 1, s.m_pStr->m_pszData); //конкатенаци€

			m_pStr->Release(); //убираем прошлый указатель на объект _str
			m_pStr = pstrTmp; //обновл€ем
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