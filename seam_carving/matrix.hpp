#pragma once

#include <vector>
#include <utility>

//store coordinates of least vertical seam
//in vector of pairs containing x,y values
//for each point
using coord = std::vector<std::pair<int,int>>;


//holds only ints
//could be extended to become more generic
//using templates
class matrix{
private:
	const int w;
	const int h;

	int **data;

public:
	matrix(); //default constructor, matrix has fixed size of 10X10
	matrix(int total_w, int total_h);
	matrix(const matrix&); //copy constructor

	~matrix(){ delete [] data;}

	//returns max width of matrix
	int width() const {return w;}

	//returns max height of matrix
	int height() const {return h;}

	//inserts elem to matrix at pos (x,y)
	void insert(int elem, int x, int y);

	//gets element at pos (x,y)
	int get(int x, int y) const;

	//returns max number of numbers matrix can hold
	int capacity() const {return w * h;} 

	//prints content of matrix
	void print() const;
};


//returns a vertical seam of an energy matrix
coord get_vertical_seam(matrix& energy);

//return a transposed version of the matrix
matrix transpose(matrix& mat);