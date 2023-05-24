#include <iostream>
#include "Str.h"

using namespace std;

int main()
{
	Str str1 = "02220", str2 = str1, str3 = str2;
	

	cout << str1 << endl;
	char old = '2', _new = '1';
	int a = str1.replace(old, _new);
	cout << str1 << " " << old << " " << _new << endl;
	str2 += "99";
	cout << str2 << endl;
	cout << str3 << endl;


	system("pause");
	
	return 0;
}