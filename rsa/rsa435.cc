// You need to complete this program for a part of your first project.

// Standard libraries
#include <string>
#include <iostream>
#include <stdlib.h> 
#include <time.h>
#include <assert.h>
#include <vector>


// 'BigIntegerLibrary.hh' includes all of the library headers.
#include "BigIntegerLibrary.hh"

BigInteger prime_gen();
bool fermat_test(BigInteger&);


int main(){
	/* The library throws 'const char *' error messages when things go
	 * wrong.  It's a good idea to catch them using a 'try' block like this
	 * one.  Your C++ compiler might need a command-line option to compile
	 * code that uses exceptions. */
	
	
	try {
		std::cout << prime_gen() << std::endl;

		/*for(int i = 1; i < 23; i++)
			std::cout << modexp(i,22,23) << std::endl;*/
      /*std::cout << "a couple of test cases for 3460:435/535 Algorithms!!!\n";
      BigUnsigned big1 = BigUnsigned(1);
      for (int i=0;i<400;i++) {
         big1 = big1*10 +rand();
      }
      std::cout << "my big1 !!!\n";
      std::cout << big1 << std::endl;

      BigUnsigned big2 = BigUnsigned(1);
      for (int i=0;i<400;i++) {
         big2 = big2*10 +rand();
      }
      std::cout << "my big2 !!!\n";
      std::cout << big2<< std::endl;
      std::cout << "my big3 = big1*big2 !!!\n";
      BigUnsigned big3 = big1*big2;
      std::cout <<big3<< std::endl;
      std::cout << "my big3/big2 !!!\n";
      std::cout <<big3/big2<< std::endl;*/
      
	} catch(char const* err) {
		std::cout << "The library threw an exception:\n"
			<< err << std::endl;
	}

	return 0;
}

BigInteger prime_gen() {
	
	srand(time(0));

	BigInteger prime;

	do{
		prime  = BigInteger(1);

		for (int i=0; i< 400; i++) {
        	prime = prime*10 +rand(); 	
		}	

	}while(!(fermat_test(prime)));
	
	
	return prime;
}

bool fermat_test(BigInteger &num) {

	BigUnsigned exponent = BigUnsigned(num.getMagnitude()) - BigUnsigned(1);

	for(int i = 2; i < 5; i++){
		if(modexp(BigInteger(i), exponent, BigUnsigned(num.getMagnitude())) != 1){
			std::cout <<"Is Not Prime " << std::endl;
			return false;
			
		}
	}

	return true;
}

