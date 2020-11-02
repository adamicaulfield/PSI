/*
Code by Adam Caulfield (ac7717@rit.edu) for CSCI759 Project 1    

Based on code from:
      Copyright SpiRITlab - Computations on Encrypted Data
      https://gitlab.com/SpiRITlab/coed

*/

#ifndef HELIBEXAMPLES_MATRIX_H
#define HELIBEXAMPLES_MATRIX_H

#include "Encryptor.h"

class Matrix {
public:
	static helib::Ctxt mult_3by3_standard(COED::Encryptor encryptor, std::vector<std::vector<long>> A, std::vector<std::vector<long>> B, bool printMsgs);
	static helib::Ctxt mult_3by3_parallel(COED::Encryptor encryptor, std::vector<std::vector<long>> A, std::vector<std::vector<long>> B, bool printMsgs);
	static helib::Ctxt mult_3by3(COED::Encryptor encryptor, std::vector<std::vector<long>> A, std::vector<std::vector<long>> B, bool inParallel,bool printMsgs);

	static helib::Ctxt conv_filter_standard(COED::Encryptor encryptor, std::vector<std::vector<long>> x, std::vector<std::vector<long>> w, bool printMsgs);
	static helib::Ctxt conv_filter_parallel(COED::Encryptor encryptor, std::vector<std::vector<long>> x, std::vector<std::vector<long>> w, bool printMsgs);
	static helib::Ctxt conv_filter(COED::Encryptor encryptor, std::vector<std::vector<long>> x, std::vector<std::vector<long>> w, bool inParallel,bool printMsgs);
};

#endif //HELIBEXAMPLES_MATRIX_H