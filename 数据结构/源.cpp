#include<iostream>
#include<string>
#include"polynomial.h"


using namespace std;

int main()
{
	string s;
	polynomial * result;
	cout << "一元多项式计算:输入格式为 x,x-x,x+(x,x*x,x/x,x%x,x)......\n不支持错误输入。。。且除法计算为不带余除法\n请输入要计算的一元多项式(q to quit):\n";
	while ((cin >> s )&& s[0] != 'q')
	{
		cout << "结果为" << endl;
		result = Caculate(s);
		result->print();
		delete result;
		cout << "请输入要计算的一元多项式(q to quit):\n";
	}
	return 0;
}