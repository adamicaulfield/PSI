/*
Code by Adam Caulfield (ac7717@rit.edu) for CSCI759 Project 1    

Based on code from:
      Copyright SpiRITlab - Computations on Encrypted Data
      https://gitlab.com/SpiRITlab/coed

*/

#ifndef HELIBEXAMPLES_VECTOR_H
#define HELIBEXAMPLES_VECTOR_H

#include "Encryptor.h"

class Vector {
public:
	static helib::Ctxt dot_product(COED::Encryptor encryptor,std::vector<long> vec1,std::vector<long> vec2,int size);
};

#endif //HELIBEXAMPLES_VECTOR_H