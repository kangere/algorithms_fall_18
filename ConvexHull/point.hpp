#pragma once
#include <iosfwd>

class point {
private:
	int m_x = 0,m_y = 0;

public:
	point(){}

	point(int x, int y)
	:m_x(x), m_y(y)
	{}

	int get_x () const
	{return m_x;}

	int get_y () const
	{return m_y;}

	friend std::ostream& operator<<(std::ostream&, const point&);

	bool operator==(const point&);

	void print();
};

point* find_vect(point*,point*);
int vec_direction(point*,point*);
