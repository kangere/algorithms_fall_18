#include <iostream>
#include <algorithm>
#include <fstream>
#include <string>
#include <cmath>
#include "matrix.hpp"
#include <vector>
#include <utility>


matrix read_file(char const* filename);
matrix min_energy(matrix& m);
matrix remove_seam(matrix&,matrix&);



int main(int argc, char** argv)
{

	matrix mat = read_file("excelTestCase.pgm");
	std::cout << "original Matrix: \n";
	mat.print();
	
	//get leat cumulative energy for matrix
	matrix min_mat = min_energy(mat);
	std::cout << "Cumulateive energy for vertical seam: \n";
	min_mat.print();

	remove_seam(min_mat,mat).print();


	return 0;
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
	// std::getline(file,dummy);

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

	std::cout << "energy matrix: \n";
	new_mat.print();

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
	if(energy.capacity() <= 0 or actual.capacity() <= 0 
		or energy.capacity() != actual.capacity())
		return matrix();

	coord vseam = get_vertical_seam(energy);

	
	for(auto& lowest : vseam)
		std::cout << lowest.first << " " << lowest.second << std::endl;

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
