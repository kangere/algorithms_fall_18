#include "point.hpp"
#include <iostream>
#include <math.h>

#define PI 3.14159265359


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
	// int dot = (v1->get_x() * v2->get_x()) + (v1->get_y() * v2->get_y());
	// float mag  = magnitude(v1) * magnitude(v2);
	// int det = (v1->get_x() * v2->get_y()) - (v1->get_y() * v2->get_x());
	// float degrees = acos(dot / mag) * (180.0 /  PI); 

	int x_diff = v2->get_x() - v1->get_x();
	int y_diff = v2->get_y() - v1->get_y();

	float degrees = atan2(static_cast<float>(x_diff),
					static_cast<float>(y_diff)) * (180.0/PI);

	return degrees > 0.0 ? degrees : 360.0 + degrees;
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

