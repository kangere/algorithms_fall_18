#include "matrix.hpp"
#include <cassert>
#include <iostream>

matrix::matrix()
:matrix(10,10)
{}


matrix::matrix(int total_w, int total_h)
:w(total_w), h(total_h)
{
	data = new int*[h];

	for(int i = 0; i < h; i++)
		data[i] = new int[w];
}

//copy constructor
matrix::matrix(const matrix& copy)
:matrix(copy.width(),copy.height())
{

	for(int row = 0; row < h; row++){
		for(int col = 0; col < w; col++)
			data[col][row] = copy.get(col,row);
	}
}

void
matrix::insert(int elem,int x, int y)
{
	assert(x < w);
	assert(y < h);

	data[x][y] = elem;
}


int 
matrix::get(int x, int y) const
{
	assert(x < w);
	assert(y < h);

	return data[x][y];
}

void 
matrix::print() const
{
	for(int row = 0; row < h; row++){
		for(int col = 0; col < w; col++){
			std::cout << data[col][row] << " ";
		}

		std::cout << std::endl;
	}
}
