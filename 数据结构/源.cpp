#include<iostream>
#include<string>
#include"polynomial.h"


using namespace std;

int main()
{
	string s;
	polynomial * result;
	while ((cin >> s )&& s[0] != 'q')
	{
		result = Caculate(s);
		result->print();
		delete result;
	}
	return 0;
}