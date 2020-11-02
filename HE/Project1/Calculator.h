/*
Code by Adam Caulfield (ac7717@rit.edu) for CSCI759 Project 1    

Based on code from:
      Copyright SpiRITlab - Computations on Encrypted Data
      https://gitlab.com/SpiRITlab/coed

*/

#ifndef HELIBEXAMPLES_CALCULATOR_H
#define HELIBEXAMPLES_CALCULATOR_H

#include "Encryptor.h"

class Calculator {
public:
	static helib::Ctxt run_calculator(COED::Encryptor encryptor,unsigned long plaintext_prime_modulus);
};

#endif //HELIBEXAMPLES_CALCULATOR_H