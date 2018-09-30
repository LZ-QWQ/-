#pragma once
#include<iostream>
#include<list>//�Ժ��ð�



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
		long exponent;//ָ��
		long confficient;//ϵ��
		poly *next;
	}*List;
	List polys;
	int length;
	void sort()
	{
		if (length == 1)return;
		List temp = polys->next->next;//ָ��ڶ���
		List pre_2 = polys->next;//�ƶ����ǰһ��
		while (temp != nullptr)
		{
			List insert = temp, pstart = polys->next, pre = polys;//pstart��ǰ������
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
