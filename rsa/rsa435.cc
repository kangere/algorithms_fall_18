// You need to complete this program for a part of your first project.

// Standard libraries
#include <string>
#include <iostream>
#include <stdlib.h> 
#include <time.h>
#include <fstream>


// 'BigIntegerLibrary.hh' includes all of the library headers.
#include "BigIntegerLibrary.hh"

BigInteger prime_gen();
bool fermat_test(const BigInteger&);
void keygen();
bool save_key(const std::string&, const BigInteger&, const BigInteger&);

int main(){
	/* The library throws 'const char *' error messages when things go
	 * wrong.  It's a good idea to catch them using a 'try' block like this
	 * one.  Your C++ compiler might need a command-line option to compile
	 * code that uses exceptions. */
	
	
	try {
		keygen();

		
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

	clock_t t = clock();

	do{
		prime  = BigInteger(1);

		for (int i=0; i< 400; i++) {
        	prime = prime*10 +rand(); 	
		}	

		t = clock() - t;
		std::cout << "Generating prime number, time elapsed " << ((float)t) / CLOCKS_PER_SEC << "s ..." << std::endl;
	
	}while(!(fermat_test(prime)));
	
	
	return prime;
}

bool fermat_test(const BigInteger &num) {

	BigUnsigned exponent = BigUnsigned(num.getMagnitude()) - BigUnsigned(1);

	for(int i = 2; i < 5; i++){
		if(modexp(BigInteger(i), exponent, BigUnsigned(num.getMagnitude())) != 1){
			return false;
		}
	}

	return true;
}

void keygen() {

	BigInteger p = prime_gen();

	BigInteger q = prime_gen();

	std::cout << "P = " << p << std::endl;
	std::cout << "Q = " << q << std::endl;

	if(save_key("p_q.txt", p,q)){
		std::cout << "file p_q.txt saved" <<std::endl;
	}

	BigInteger n = p * q;

	BigInteger e = 65537;

	BigUnsigned totient_n = BigUnsigned(p.getMagnitude() - BigUnsigned(1)) * 
					BigUnsigned(q.getMagnitude() - BigUnsigned(1));

	BigUnsigned d = modinv(e,totient_n);

	if(save_key("e_n.txt",e,n)){
		std::cout << "file e_n.txt saved" << std::endl;
	}

	if(save_key("d_n.txt",d,n)){
		std::cout << "file d_n.txt saved" << std::endl;
	}

}


bool save_key(const std::string& filename, const BigInteger& first, const BigInteger& second) {

	if(filename.empty()){
		std::cout << "filename is empty " << std::endl;
		return false;
	}

	std::fstream out (filename.c_str(), std::fstream::out | std::fstream::trunc);

	if(out.is_open()){
		out << first << std::endl;
		out << second ;

		out.close();
	} else {
		return false;
	}

	return true;
}

