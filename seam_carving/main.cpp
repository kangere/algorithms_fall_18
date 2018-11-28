#include <iostream>
#include <algorithm>
#include <string>
#include "matrix.hpp"





int main(int argc, char const* argv[])
{

	if(argc != 4){
		std::cout << "wrong format:" << std::endl;
		std::cout << "e.g ./seam filename vertical-seams horizontal-seams" <<std::endl;

		return 0;
	}

	int v_seams = std::stoi(argv[2]), h_seams = std::stoi(argv[3]);


	matrix mat = read_file(argv[1]);
	std::cout << "original Matrix: \n";
	mat.print();
	
	//get leat cumulative energy for matrix
	matrix min_mat = min_energy(mat);
	std::cout << "Cumulateive energy for vertical seam: \n";
	min_mat.print();

	while(v_seams > 0){
		matrix energy = min_energy(mat);
		matrix temp = remove_seam(energy,mat);
		mat = temp;
		--v_seams;
	}

	//transpose matrix to remove horizontal seams
	matrix tran = transpose(mat);

	while(h_seams > 0){
		matrix energy = min_energy(tran);
		matrix temp = remove_seam(energy,tran);
		tran = temp;
		--h_seams;
	}

	//tranpose matrix back 
	std::cout << "Final matrix" << std::endl;
	transpose(tran).print();

	return 0;
	
}






