#include<iostream>
#include<string>
#include"polynomial.h"


using namespace std;

int main()
{
	string s;
	polynomial * result;
	cout << "һԪ����ʽ����:�����ʽΪ x,x-x,x+(x,x*x,x/x,x%x,x)......\n��֧�ִ������롣�����ҳ�������Ϊ���������\n������Ҫ�����һԪ����ʽ(q to quit):\n";
	while ((cin >> s )&& s[0] != 'q')
	{
		cout << "���Ϊ" << endl;
		result = Caculate(s);
		result->print();
		delete result;
		cout << "������Ҫ�����һԪ����ʽ(q to quit):\n";
	}
	return 0;
}