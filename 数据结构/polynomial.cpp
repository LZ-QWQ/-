#include"polynomial.h"

polynomial  polynomial::operator+(polynomial & p)
{
	polynomial temp = *this;
	List pt = temp.polys;//拼接 副本 排序（合并同类）
	while (pt->next != nullptr)pt = pt->next;
	pt->next = p.polys;
	temp.length = p.length + this->length;
	p.polys = nullptr;
	polys = nullptr;
	p.~polynomial();
	this->~polynomial();
	temp.sort;
	return temp;
}

void polynomial::add(long e, long c)
{

}

polynomial::polynomial(const polynomial & p)
{
	length = p.length;

}

polynomial &  polynomial::operator=(polynomial & p)
{
	length = p.length;
	polys = p.polys;
	return *this;
}

polynomial::polynomial()
{
	polys = new poly;
	polys->next = nullptr;
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
