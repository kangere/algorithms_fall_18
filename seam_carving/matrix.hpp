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
	int w;
	int h;
	int size;
	int max_grey;

	std::vector<std::vector<int>> data;

public:
	matrix(); //default constructor, matrix has fixed size of 10X10
	matrix(int total_w, int total_h, int max);
	matrix(const matrix&); //copy constructor

	//returns max width of matrix
	int width() const {return w;}

	//returns max height of matrix
	int height() const {return h;}

	//return max grey scale color
	int max() const {return max_grey;}

	//inserts elem to matrix at pos (x,y)
	void insert(int elem, int x, int y);

	//gets element at pos (x,y)
	int get(int x, int y) const;

	//returns max number of numbers matrix can hold
	int capacity() const {return size;} 

	//prints content of matrix
	void print() const;


	//operator overloads
	matrix& operator=(const matrix& rhs);
};


//returns a vertical seam of an energy matrix
coord get_vertical_seam(matrix& energy);

//return a transposed version of the matrix
matrix transpose(matrix& mat);

//Calculate energy of pixels in matrix
matrix least_cumulative_energy(matrix& m);


//removes one vertical seam from actual
//using energies from energy
matrix remove_seam(matrix& energy, matrix& actual);


//Reads a bng file and stores pixel in a matrix
matrix read_file(char const* filename);

//Write matrix pixels to file
void write_file(matrix& mat);