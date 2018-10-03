#include"polynomial.h"
#include<stack>
#include<queue>
#include<sstream>

std::string temp;
std::stringstream temp_;

polynomial*  polynomial::operator+(polynomial & p)
{
	polynomial *temp = new polynomial;
	temp->polys->next = this->polys->next;//至少有一项
	List pt = temp->polys;//拼接 副本 排序（合并同类）
	while (pt->next != nullptr)pt = pt->next;
	pt->next = p.polys->next;
	temp->length = p.length + this->length;
	p.polys->next = nullptr;
	polys->next = nullptr;
	temp->sort();
	return temp;
}

polynomial*  operator-(polynomial & p)
{
	polynomial*temp = new polynomial;
	return temp;
}

void polynomial::add(int e, double c)
{
	List pt = this->polys;
	while (pt->next != nullptr)pt = pt->next;
	pt->next = new poly;
	pt->next->confficient = c;
	pt->next->exponent = e;
	pt->next->next = nullptr;
	this->length++;
}

polynomial::polynomial(const polynomial & p)//浅复制
{
	length = p.length;
	operand = p.operand;
	polys = p.polys;

}

polynomial & polynomial::operator=(const polynomial & p)//浅复制
{
	length = p.length;
	polys = p.polys;
	operand = p.operand;
	return *this;
}

polynomial::polynomial()
{
	polys = new poly{ 0,0,nullptr };
	polys->next = nullptr;
	operand = '#';
	length = 0;
}

polynomial::~polynomial()
{
	List temp = nullptr;
	while (polys->next != nullptr)
	{
		temp = polys->next;
		delete polys;
		polys = temp;
	}
	delete polys;
}

std::queue<polynomial *> transform(std::string & s)
{
	std::queue<polynomial *> result;
	std::stack<char> operand;
	for (int i = 0; i < s.length();)
	{
		if (s[i] == '(')
		{
			operand.push(s[i]);
			i++;
		}
		else if(s[i] == ')')
		{
			while (operand.top() != '(')
			{
				polynomial *p = new polynomial;
				p->operand = operand.top();
				result.push(p);
				operand.pop();
			}
			operand.pop();
			i++;
		}
		else if (s[i] == '+' || s[i] == '-')
		{
			while (operand.size() != 0 && operand.top() != '(')
			{
				polynomial *p = new polynomial;
				p->operand = operand.top();
				result.push(p);
				operand.pop();
			}
			operand.push(s[i]);
			i++;
		}
		else if (s[i] == '*' || s[i] == '/' || s[i] == '%')
		{
			while (operand.size() != 0 && operand.top() == '+'&&operand.top() == '-')
			{
				polynomial *p = new polynomial;
				p->operand = operand.top();
				result.push(p);
				operand.pop();
			}
			if (operand.size() != 0 && operand.top() != '(')
			{
				polynomial *p = new polynomial;
				p->operand = operand.top();
				result.push(p);
				operand.pop();
			}
			operand.push(s[i]);
			i++;
		}
		else
		{

			double temp_1 = 0;
			int temp_2 = 0;
			temp.clear();
			temp_.clear();
			temp_.str("");
			while (s[i] != ',')
			{
				temp += s[i];
				i++;
			}
			temp_ << temp;
			temp_ >> temp_1;
			i++;
			temp.clear();
			temp_.clear();
			temp_.str("");
			while (i!=s.length()&&(s[i]>='0'&&s[i]<='9'))
			{
				temp += s[i];
				i++;
			}
			temp_ << temp;
			temp_ >> temp_2;
			polynomial *p = new polynomial;
			p->add(temp_2, temp_1);
			result.push(p);
		}
	}
	while (operand.size() != 0)
	{
		polynomial *p = new polynomial;
		p->operand = operand.top();
		result.push(p);
		operand.pop();
	}
	return result;
}

polynomial * Caculate(std::string &s)
{
	std::queue <polynomial *> result = transform(s);
	std::stack<polynomial *> polys_0;
	polynomial * left = nullptr;
	polynomial * right = nullptr;
	polynomial *temp = nullptr;
	while (result.size() > 0)
	{
		temp = result.front();
		result.pop();
		if (temp->operand == '#')
		{
			polys_0.push(temp);
		}
		else
		{
			right = polys_0.top();
			polys_0.pop();
			left = polys_0.top();
			polys_0.pop();
			switch (temp->operand)
			{
			case '+':polys_0.push((*left) + (*right));
			}
			delete left;
			delete right;
		}
	}
	return polys_0.top();
}

void polynomial::print()
{
	List temp = this->polys;
	if (length == 1)
	{
		temp = temp->next;
		if (temp->confficient > 0)
		{
			if (temp != this->polys->next)std::cout << '+';
			std::cout << temp->confficient << "X^" << temp->exponent;
		}
		else
			std::cout << temp->confficient << "X^" << temp->exponent;
	}
	else
	{
		while (temp->next != nullptr)
		{
			temp = temp->next;
			if (temp->confficient > 0)
			{
				if (temp != this->polys->next)std::cout << '+';
				std::cout << temp->confficient << "X^" << temp->exponent;
			}
			else
				std::cout << temp->confficient << "X^" << temp->exponent;
		}
	}
	std::cout << std::endl;
}