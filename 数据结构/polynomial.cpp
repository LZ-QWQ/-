#include"polynomial.h"
#include<stack>
#include<queue>
#include<sstream>

std::string temp;
std::stringstream temp_;

polynomial*  polynomial::operator+(polynomial & p)
{
	polynomial *temp = new polynomial;
	List temp_1 = this->polys->next, temp_2 = p.polys->next;
	while (temp_1 != nullptr)
	{
		temp->add(temp_1->exponent, temp_1->confficient);
		temp_1 = temp_1->next;
	}
	while (temp_2 != nullptr)
	{
		temp->add(temp_2->exponent, temp_2->confficient);
		temp_2 = temp_2->next;
	}
	temp->sort();
	/*temp->polys->next = this->polys->next;//至少有一项
	List pt = temp->polys;//拼接 副本 排序（合并同类）
	while (pt->next != nullptr)pt = pt->next;
	pt->next = p.polys->next;
	temp->length = p.length + this->length;
	p.polys->next = nullptr;
	polys->next = nullptr;
	temp->sort();*/
	return temp;
}

polynomial*  polynomial::operator-(polynomial & p)
{
	List temp_ = p.polys->next;
	while (temp_ != nullptr)
	{
		temp_->confficient = -temp_->confficient;
		temp_ = temp_->next;
	}
	return (*this) + p;
}

polynomial*  polynomial::operator*(polynomial & p)
{
	polynomial* temp = new polynomial;
	List temp_1 = this->polys->next, temp_2 = p.polys->next;
	while (temp_1 != nullptr)
	{
		while (temp_2 != nullptr)
		{
			temp->add(temp_1->exponent + temp_2->exponent, temp_1->confficient*temp_2->confficient);
			temp_2 = temp_2->next;
		}
		temp_1 = temp_1->next;
		temp_2 = p.polys->next;
	}
	temp->sort();
	return temp;
}

polynomial*  polynomial::operator/(polynomial & p)
{
	polynomial *temp__1 = new polynomial;
	polynomial *temp__2 = new polynomial;
	polynomial *temp__3 = new polynomial;
	polynomial *temp__4 = new polynomial;
	polynomial *temp__5 = new polynomial;
	(*temp__4) = (*this);
	temp__4->sort();
	p.sort();
	List temp_1 = this->polys->next, temp_2 = p.polys->next;
	if (temp_1->exponent < temp_2->exponent)
	{
		temp__1->add(0, 0.0);
		return temp__1;
	}
	while (temp_1 != nullptr && temp_1->exponent >= temp_2->exponent)
	{
		temp__1->add(temp_1->exponent - temp_2->exponent, temp_1->confficient / temp_2->confficient);
		temp__2->add(temp_1->exponent - temp_2->exponent, temp_1->confficient / temp_2->confficient);
		delete temp__3;
		temp__5 = ((*temp__2) * p);
		temp__3 = (*temp__4)-(*temp__5);
		delete temp__5;
		(*temp__4) = (*temp__3);
		temp__2->clear();
		temp_1 = temp__3->polys->next;
	}
	delete temp__2;
	delete temp__3;
	delete temp__4;
	return temp__1;
}

polynomial*  polynomial:: operator%(polynomial & p)
{
	polynomial *temp__1 = new polynomial;
	polynomial *temp__2 = new polynomial;
	polynomial *temp__3 = new polynomial;
	polynomial *temp__4 = new polynomial;
	polynomial *temp__5 = new polynomial;
	(*temp__4) = (*this);
	temp__4->sort();
	p.sort();
	List temp_1 = this->polys->next, temp_2 = p.polys->next;
	if (temp_1->exponent < temp_2->exponent)
	{
		(*temp__3) = (*this);
		return temp__3;
	}
	while (temp_1 != nullptr && temp_1->exponent >= temp_2->exponent)
	{
		temp__1->add(temp_1->exponent - temp_2->exponent, temp_1->confficient / temp_2->confficient);
		temp__2->add(temp_1->exponent - temp_2->exponent, temp_1->confficient / temp_2->confficient);
		delete temp__3;
		temp__5 = ((*temp__2) * p);
		temp__3 = (*temp__4) - (*temp__5);
		delete temp__5;
		(*temp__4) = (*temp__3);
		temp__2->clear();
		temp_1 = temp__3->polys->next;
	}
	delete temp__2;
	delete temp__1;
	delete temp__4;
	return temp__3;
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

void polynomial::clear()
{
	List temp1 = nullptr, temp2 = polys->next;
	while (temp2 != nullptr)
	{
		temp1 = temp2;
		temp2 = temp2->next;
		delete temp1;
	}
	polys->next = nullptr;
	length = 0;
}


polynomial::polynomial(const polynomial & p)//浅复制（貌似没用）
{
	length = p.length;
	operand = p.operand;
	polys = p.polys;

}

polynomial & polynomial::operator=(const polynomial & p)//深复制
{
	this->clear();
	List temp = p.polys->next;
	while (temp != nullptr)
	{
		this->add(temp->exponent, temp->confficient);
		temp = temp->next;
	}
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
	while (polys != nullptr)
	{
		temp = polys->next;
		delete polys;
		polys = temp;
	}
}

int operand_(char c)
{
	if (c == '+' || c == '-')return 1;
	else return 2;
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
			if (i==0||s[i-1]=='(')
			{
				polynomial *p = new polynomial;
				p->add(0, 0.0);
				result.push(p);
			}
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
			while (operand.size() != 0 && operand.top() != '('&&(operand_(s[i])<=operand_(operand.top())))
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
				break;
			case '-':polys_0.push((*left) - (*right));
				break;
			case '*':polys_0.push((*left) * (*right));
				break;
			case '/':polys_0.push((*left) / (*right));
				break;
			case '%':polys_0.push((*left) % (*right));
				break;
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
	if (length == 0)std::cout << 0;
	else if (length == 1)
	{
		temp = temp->next;
		if (temp->confficient == 0)std::cout << 0;
		else if (temp->confficient > 0)
		{
			if (temp != this->polys->next)std::cout << '+';
			if (temp->confficient == 1)
			{
				if (temp->exponent == 0)std::cout << temp->confficient;
				else if (temp->exponent == 1)std::cout << 'X';
				else  std::cout << "X^" << temp->exponent;
			}
			else
			{
				if (temp->exponent == 0)std::cout << temp->confficient;
				else if (temp->exponent == 1)std::cout << temp->confficient << 'X';
				else std::cout << temp->confficient << "X^" << temp->exponent;
			}
		}
		else
		{
			if (temp->confficient == -1)
			{
				if (temp->exponent == 0)std::cout << temp->confficient;
				else if (temp->exponent == 1)std::cout << "-X";
				else  std::cout << "-X^" << temp->exponent;
			}
			else
			{
				if (temp->exponent == 0)std::cout << temp->confficient;
				else if (temp->exponent == 1)std::cout << temp->confficient << 'X';
				else std::cout << temp->confficient << "X^" << temp->exponent;
			}
		}
	}
	else
	{
		while (temp->next != nullptr)
		{
			temp = temp->next;
			if (temp->confficient == 0)continue;
			else if (temp->confficient > 0)
			{
				if (temp != this->polys->next)std::cout << '+';
				if (temp->confficient == 1)
				{
					if (temp->exponent == 0)std::cout << temp->confficient;
					else if (temp->exponent == 1)std::cout  << 'X';
					else  std::cout << "X^" << temp->exponent;
				}
				else
				{
					if (temp->exponent == 0)std::cout << temp->confficient;
					else if (temp->exponent == 1)std::cout << temp->confficient << 'X';
					else  std::cout << temp->confficient << "X^" << temp->exponent;
				}
			}
			else
			{
				if (temp->confficient == -1)
				{
					if (temp->exponent == 0)std::cout << temp->confficient;
					else if (temp->exponent == 1)std::cout << "-X";
					else  std::cout << "-X^" << temp->exponent;
				}
				else
				{
					if (temp->exponent == 0)std::cout << temp->confficient;
					else if (temp->exponent == 1)std::cout << temp->confficient << 'X';
					else std::cout << temp->confficient << "X^" << temp->exponent;
				}
			}
		}
	}
	std::cout << std::endl;
}