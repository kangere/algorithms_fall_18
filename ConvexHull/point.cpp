#include "point.hpp"
#include <iostream>
#include <math.h>


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
	return new point((second->get_x() - first->get_x()), (second->get_y() - first->get_y()));
}

int vec_direction(point* v1,point* v2)
{
	return (v1->get_x() * v2->get_y()) - (v2->get_x() * v1->get_y());
}

float polar_angle(point* v1, point* v2)
{
	int dot = (v1->get_x() * v2->get_x()) + (v1->get_y() * v2->get_y());
	float mag = magnitude(v1) * magnitude(v2);

	return acos(dot / mag) * (180.0 / 3.14159265);
}

float magnitude(point* p)
{
	int xy2 = (p->get_x() * p->get_x()) + (p->get_y() * p->get_y());


	return sqrt(static_cast<float>(xy2)); 
}

std::ostream& operator<<(std::ostream& os, const point& p)
{
	os << p.m_x << " " << p.m_y;
}

