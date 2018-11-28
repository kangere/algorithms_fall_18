#include "matrix.hpp"
#include <cassert>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <cmath>
#include <iterator>


matrix::matrix()
:matrix(10,10)
{}


matrix::matrix(int total_w, int total_h)
:w(total_w), h(total_h)
{
	size = w * h;
	data.resize(h,std::vector<int>(w,0));

}

//copy constructor
matrix::matrix(const matrix& copy)
{
	w = copy.width();
	h = copy.height();

	size = w * h;

	std::copy(copy.data.begin(),copy.data.end(),std::back_inserter(data));
}

void
matrix::insert(int elem,int x, int y)
{
	assert(x < w);
	assert(y < h);

	data[y][x] = elem;
}


int 
matrix::get(int x, int y) const
{
	assert(x < w);
	assert(y < h);

	return data.at(y).at(x);
}

void 
matrix::print() const
{
	for(int row = 0; row < h; row++){
		for(int col = 0; col < w; col++){
			std::cout << get(col,row) << " ";
		}

		std::cout << std::endl;
	}
}

matrix&
matrix::operator=(const matrix& rhs){

	if(this != &rhs){
		w = rhs.width();
		h = rhs.height();
		size = rhs.size;

		data = rhs.data;
	}
	

	return *this;
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

matrix transpose(matrix& mat)
{
	int new_width = mat.height();
	int new_height = mat.width();

	matrix new_mat(new_width,new_height);

	for(int row = 0; row < new_height; row++){
		for(int col = 0; col < new_width; col++){

			int temp = mat.get(row,col);

			new_mat.insert(temp,col,row);
		}
	}

	return new_mat;
}


matrix min_energy(matrix& m)
{
	int width = m.width();
	int height = m.height();

	//create matrix with energies
	matrix new_mat(width,height);

	//calculate energy of pixels and it to new matrix
	for(int row = 0; row < height; row++){
		for(int col = 0; col < width; col++){
			
			int curr = m.get(col,row);
			int x_diff = 0;
			int y_diff = 0;

			

			if (col == 0)//for first columns left element doesn't exist 
				x_diff = 0 + std::abs(curr - m.get(col+1,row));
			else if(col == (width-1))//for last column right element does not exist
				x_diff = std::abs(curr - m.get(col-1,row)) + 0;
			else
				x_diff = std::abs(curr - m.get(col-1,row))
						+ std::abs(curr - m.get(col+1,row));

			if(row == 0)
				y_diff = 0 + std::abs(curr - m.get(col,row+1));
			else if(row == (height-1))
				y_diff = std::abs(curr - m.get(col,row-1)) + 0;
			else
				y_diff = std::abs(curr - m.get(col,row-1))
						+ std::abs(curr - m.get(col,row+1));		


			new_mat.insert(x_diff + y_diff, col,row);						

		}
	}


	//next calculate least cumulative energy from top to bottom
	for(int row = 1; row < height; row++){
		for(int col = 0; col < width; col++){

			int min_num;
			int top_elem = new_mat.get(col,row-1);
			int curr = new_mat.get(col,row);

			if(col == 0){
				min_num = std::min(top_elem,new_mat.get(col+1,row-1));
			} else if(col == (width-1)){
				min_num = std::min(top_elem,new_mat.get(col-1,row-1));
			} else {
				min_num = std::min({new_mat.get(col-1,row-1), top_elem, new_mat.get(col+1,row-1)});
			}

			new_mat.insert(min_num + curr,col,row);
		}
	}

	return new_mat;
}

matrix remove_seam(matrix& energy, matrix& actual)
{
	//ensure matrixes are same size
	assert(energy.capacity() == actual.capacity());

	if(energy.capacity() <= 0 or actual.capacity() <= 0 
		or energy.capacity() != actual.capacity())
		return matrix();

	coord vseam = get_vertical_seam(energy);


	matrix reduced(actual.width() - 1,actual.height());

	for(int row = 0; row < reduced.height(); row++){
		
		int offset = 0;

		for(int col = 0; col < reduced.width(); col++){

			auto iter = std::find(vseam.begin(), vseam.end(),std::make_pair(col,row));
			
			if(iter  != vseam.end())
				offset = 1;
				
			

			reduced.insert(actual.get(col+offset,row),col,row);
			
		}		
	}

	return reduced;
}

matrix read_file(char const* filename)
{
	std::fstream file(filename, std::ios::in);
 	
 	if(!file.is_open())
 	{
 		std::cout << "could not open file" << std::endl;
 		return matrix();
 	} 	

	//skip first two lines
	std::string dummy;

	std::getline(file,dummy);

	if(file.peek() == '#')
		std::getline(file,dummy);



	int width,height,max_grey;

	//read in first lines
	file >> width >> height >> max_grey;

	matrix mat(width,height);

	//read all pixels to matrix
	for(int row = 0; row < height; row++){
		for(int col = 0; col < width; col++){
			int temp;
			file >> temp;

			mat.insert(temp,col,row);
		}
	}


	return mat;
}

