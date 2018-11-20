#include "matrix.hpp"
#include <cassert>
#include <iostream>
#include <algorithm>

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

coord get_vertical_seam(matrix& energy)
{
	coord vertical_seam;


	for(int row = (energy.height() -1); row >= 0; row--)
	{
		
		int min;
		std::pair<int,int> min_c;

		if(row == (energy.height() -1)){

			min = energy.get(0,row);
			min_c = std::make_pair(0,row);

			for(int col = 1; col < energy.width(); col++)
			{
				if(energy.get(col,row) < min){
					min = energy.get(col,row);
					min_c = std::make_pair(col,row);
				}
			}

		} else {
			std::pair<int,int> min_below = vertical_seam.back();

			int start,stop;

			if(min_below.first == 0){
				start = min_below.first;
				stop = min_below.first + 1;
			} else if( min_below.first == (energy.width() - 1)){
				start = min_below.first -1;
				stop = min_below.first;
			} else {
				start = min_below.first - 1;
				stop = min_below.first + 1;
			}

			//get leftmost point above minimum energy below
			min = energy.get(start,row);

			min_c = std::make_pair(start,row);

			for(int col = start; col <= stop; col++){

				if(energy.get(col,row) < min){
					min = energy.get(col,row);
					min_c = std::make_pair(col,row);
				}
			}

			

		}
			
		//insert coordinate to vertical seam
		vertical_seam.push_back(min_c);
		
	}

	//reverse order to start from top
	std::reverse(vertical_seam.begin(), vertical_seam.end());

	return vertical_seam;
}
