/***
   prepared for CS435 Project 1 part 2
**/

#include <string.h>
#include <iostream>
#include <fstream>
#include "sha256.h"
#include "BigIntegerLibrary.hh"

bool get_key(const std::string&, BigInteger&,BigInteger&);
void read_line(std::fstream&,BigInteger&);
void save_signature(std::string,BigUnsigned&);
BigUnsigned get_signature(std::string);

int main(int argc, char *argv[])
{

   //Second part of your project starts here
   if (argc < 3 || (argv[1][0]!='s' && argv[1][0]!='v')){ 
      std::cout << "wrong format! should be \"a.exe s filename\"" << std::endl;
   } else {
      std::string filename = argv[2];
      
            
      //read the file
      std::streampos begin,end;
      std::ifstream myfile (filename.c_str(), std::ios::binary);
      begin = myfile.tellg();
      myfile.seekg (0, std::ios::end);
      end = myfile.tellg();
      std::streampos size = end-begin;
      //std::cout << "size of the file: " << size << " bytes.\n"; //size of the file
      
      myfile.seekg (0, std::ios::beg);
      char * memblock = new char[size];
      myfile.read (memblock, size); //read file; it's saved in the char array memblock
      myfile.close();
      
      std::string copyOFfile = filename+".Copy"; 
      std::ofstream myfile2 (copyOFfile.c_str(), std::ios::binary);
      myfile2.write (memblock, size); //write to a file
      myfile2.close();
      
      //std::cout<<memblock;
        
      if (argv[1][0]=='s') {
         std::cout << "\n"<<"Need to sign the doc.\n";
         
         std::string hashed_file = sha256(memblock); 

         BigUnsigned  message  = BigUnsignedInABase(hashed_file, 16);
         
         BigInteger d,n;

         if(!get_key("d_n.txt",d,n)){
            std::cout << "Could not open file d_n.txt, failed to sign " << argv[2] << std::endl;
            return 0; 
         }

         BigUnsigned signature = modexp(message,BigUnsigned(d.getMagnitude()), BigUnsigned(n.getMagnitude()));
         
         save_signature(argv[2],signature);

         std::cout << "File signed succesfully" << std::endl;
      }
      else {
         std::cout << "\n"<<"Need to verify the doc.\n";
         
         //get hash value of file 
         std::string hashed_file = sha256(memblock);

         BigUnsigned signature = BigUnsignedInABase(hashed_file, 16);

         //get saved signature
         BigUnsigned saved = get_signature(argv[3]);

         BigInteger e,n;

         if(!get_key("e_n.txt",e,n)){
            std::cout << "Could not open file e_n.txt, failed to verify signature " << std::endl;
            return 0;
         }

         BigUnsigned saved_signature = modexp(saved,BigUnsigned(e.getMagnitude()), BigUnsigned(n.getMagnitude()));
         
         if(signature == saved_signature){
            std::cout << "Signature is verified " << std::endl;
         }
         else{
            std::cout << "Signature is not verified" <<std::endl;
            std::cout << "Saved signature: " << saved_signature << std::endl;
            std::cout << "Actual signature: " << signature <<std::endl;
         }
      }
      delete[] memblock;
    }
    return 0;
}

void read_line(std::fstream& in, BigInteger& num)
{
   std::string temp;

   std::getline(in,temp);

   num = stringToBigInteger(temp);
}

bool get_key(const std::string& filename, BigInteger& first, BigInteger& second)
{
   std::fstream in(filename.c_str(),std::fstream::in);

   if(!in.is_open()){
      in.close();
      return false;
   }
   

   read_line(in,first);
   read_line(in,second); 
      
   in.close();

   return true;
}

void save_signature(std::string filename, BigUnsigned& signature)
{
   filename.append(".signature");

   std::fstream out (filename.c_str(), std::fstream::out | std::fstream::trunc);

   if(out.is_open())
      out << signature;
   else
      std::cout << "Could not save signature" << std::endl;

   out.close();
}

BigUnsigned get_signature(std::string filename)
{
   std::fstream in(filename.c_str(), std::fstream::in);

   BigUnsigned saved_signature;

   if(in.is_open()){
      std::string temp;

      std::getline(in,temp);

      saved_signature = stringToBigUnsigned(temp);
   }
   else
      std::cout << "Could not open file file.txt.signature" << std::endl;

   in.close();

   return saved_signature;
}