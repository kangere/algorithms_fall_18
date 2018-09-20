// You need to complete this program for a part of your first project.

// Standard libraries
#include <string>
#include <iostream>
#include <stdlib.h> 
#include <time.h>


// 'BigIntegerLibrary.hh' includes all of the library headers.
#include "BigIntegerLibrary.hh"

void prime_gen();

int main(){
	/* The library throws 'const char *' error messages when things go
	 * wrong.  It's a good idea to catch them using a 'try' block like this
	 * one.  Your C++ compiler might need a command-line option to compile
	 * code that uses exceptions. */
	
	prime_gen();
	/*try {
	  	
      std::cout << "a couple of test cases for 3460:435/535 Algorithms!!!\n";
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
      std::cout <<big3/big2<< std::endl;
      
	} catch(char const* err) {
		std::cout << "The library threw an exception:\n"
			<< err << std::endl;
	}*/

	return 0;
}

void prime_gen() {
	
	srand(time(0));

	BigUnsigned p = BigUnsigned(1);

	BigUnsigned q = BigUnsigned(1);

	for (int i=0; i<400; i++) {
        p = p*10 +rand();
      	q = q*10 +rand();
    }

	std::cout << p << std::endl;
	std::cout << q << std::endl;

}