#pragma once
#include<iostream>
#include<queue>


class polynomial
{
public:
	char operand;
	polynomial();
	~polynomial();
	polynomial(const polynomial & p);
	void add(int, double);
	polynomial*  operator+(polynomial & p);
	polynomial*  operator-(polynomial & p);
	polynomial  operator*(polynomial & p);
	polynomial  operator/(polynomial & p);
	polynomial  operator%(polynomial & p);
	polynomial & operator=(const polynomial & p);
	void print();
private:
	typedef struct poly
	{
		int exponent;//ָ��
		double confficient;//ϵ��
		poly *next;
	}*List;
	List polys;
	int length;
	void sort()//������...
	{
		if (length == 1)return;
		List temp = polys->next->next;//ָ��ڶ���
		List pre_2 = polys->next;//�ƶ����ǰһ��
		while (temp != nullptr)
		{
			List insert = temp, pstart = polys->next, pre = polys;//pstart��ǰ������
			while (pstart != temp && pstart->exponent > temp->exponent)
			{
				pstart = pstart->next;
				pre = pre->next;
			}
			if (pstart == temp)
			{
				temp = temp->next;
				pre_2 = pre_2->next;
				break;
			}
			else if (pstart == pre_2)
			{
				if (pstart->exponent == insert->exponent)
				{
					if ((pstart->confficient + insert->confficient) != 0)
					{
						temp = temp->next;
						pre_2->next = temp;
						pstart->confficient += insert->confficient;
						delete insert;
						this->length--;
					}
					else
					{
						temp = temp->next;
						pre_2 = pre;
						pre_2->next = temp;
						delete insert;
						delete pstart;
					}
				}
				else
				{
					temp = temp->next;
					pre_2->next = temp;
					pre->next = insert;
					insert->next = pre_2;
				}
			}
			else 
			{
				if (pstart->exponent == insert->exponent)
				{
					if ((pstart->confficient + insert->confficient) != 0)
					{
						pstart->confficient += insert->confficient;
						temp = temp->next;
						pre_2->next = temp;
						delete insert;
						this->length--;
					}
					else
					{
						pre->next = pstart->next;
						temp = temp->next;
						pre_2->next = temp;
					}
				}
				else
				{
					pre->next = insert;
					temp = temp->next;
					pre_2->next = temp;
					insert->next = pstart;
				}
			}
		}
	}
};

std::queue<polynomial *> transform(std::string & s);

polynomial * Caculate(std::string &s);

