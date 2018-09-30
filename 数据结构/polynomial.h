#pragma once
#include<iostream>
#include<list>//以后用吧



class polynomial
{
public:
	polynomial();
	~polynomial();
	polynomial(const polynomial & p);
	void add(long, long);
	polynomial  operator+(polynomial & p);
	polynomial  operator-(polynomial & p);
	polynomial  operator*(polynomial & p);
	polynomial  operator/(polynomial & p);
	polynomial  operator%(polynomial & p);
	polynomial &  operator=(polynomial & p);
private:
	typedef struct poly
	{
		long exponent;//指数
		long confficient;//系数
		poly *next;
	}*List;
	List polys;
	int length;
	void sort()
	{
		if (length == 1)return;
		List temp = polys->next->next;//指向第二项
		List pre_2 = polys->next;//移动项的前一项
		while (temp != nullptr)
		{
			List insert = temp, pstart = polys->next, pre = polys;//pstart从前向后遍历
			while (pstart!= temp && pstart->exponent >= insert->exponent)
			{
				pstart = pstart->next;
				pre = pre->next;
			}

			if (pstart->exponent == insert->exponent)
			{
				if ((pstart->confficient + insert->confficient) != 0)
				{
					pstart->confficient += insert->confficient;
					delete insert;
					this->length--;
				}
				else
				{
					pre->next = pstart->next;
				}
			}
			else
			{
				pre->next = insert;
				insert->next = pstart;
			}
			if (temp->next = nullptr)pre_2->next = nullptr;
			else pre_2->next = temp->next;
			temp = temp->next;
			pre_2 = pre_2->next;
		}
	}
};
