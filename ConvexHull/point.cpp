#include "point.hpp"
#include <iostream>


bool
point::operator==(const point& right)
{
	return ((m_x * right.m_y) == (m_y * right.m_x));
}

void
point::print()
{
	std::cout << *this << std::endl;
}

//find vector moving from first to second
point* find_vect(point* first, point* second)
{
	new point((second->get_x() - first->get_x()), (second->get_y() - first->get_y()));
}




std::ostream& operator<<(std::ostream& os, const point& p)
{
	os << p.m_x << " " << p.m_y;
}