/*
Code by Adam Caulfield (ac7717@rit.edu) for CSCI759 Project 1    

Based on code from:
      Copyright SpiRITlab - Computations on Encrypted Data
      https://gitlab.com/SpiRITlab/coed

*/

#include "Calculator.h"
#include "BasicExamples.h"
#include <iostream>
#include "Util.h"

helib::Ctxt Calculator::run_calculator(COED::Encryptor encryptor, unsigned long plaintext_prime_modulus){
    //Runs an iteration of a calculator

    //Get two inputs for calulator that are less than ptxt prime modulus
    int p1 = plaintext_prime_modulus+1;
    int p2 = plaintext_prime_modulus+1;
    while(p1 > plaintext_prime_modulus){
    	printf("Enter first number (must be less than %ld): ", plaintext_prime_modulus);
    	std::cin >> p1;
    }
    printf("\n");
    while(p2 > plaintext_prime_modulus){
    	printf("Enter second number (must be less than %ld): ", plaintext_prime_modulus);
    	std::cin >> p2;
    }
    printf("\n");

    //Initialize plaintext vectors and fill in the value
    helib::Ptxt<helib::BGV> ptxt1(*(encryptor.getContext()));
    helib::Ptxt<helib::BGV> ptxt2(*(encryptor.getContext()));
    ptxt1[0] = p1;
    ptxt2[0] = p2;

    //Get operation from user through console
    int operation = -1;
    printf("Enter the operation to perform: (0) for addition, (1) for subtraction, (2) for multiplication, (3) for division: ");
    std::cin >> operation;

    //Initialize ciphertext objects and encrypt the values into cipherte
    helib::Ctxt ctxt1(*(encryptor.getPublicKey()));
    helib::Ctxt ctxt2(*(encryptor.getPublicKey()));
    encryptor.getPublicKey()->Encrypt(ctxt1, ptxt1);
    encryptor.getPublicKey()->Encrypt(ctxt2, ptxt2);

    //Based on operation selected, complete arithmetic operation
    switch(operation){
    	case 0:
    			//Addition
    			ctxt1 += ctxt2;
    			break;
		case 1:
				//Subtraction
				// Double it (using additions)
    			ctxt1 -= ctxt2;
				break;
		case 2:
				//Multiplication
				ctxt1.multiplyBy(ctxt2);
				break;
		case 3:
				//Division
				// First make a copy of the ctxt using copy constructor
			    helib::Ctxt ctxt2_divisor(ctxt2);
			    // Raise the copy to the exponenet p-2
			    ctxt2_divisor.power(plaintext_prime_modulus - 2);
			    // a^{p-2}*a = a^{-1}*a = a / a = 1;
				ctxt1.multiplyBy(ctxt2_divisor);
				break;
    }
    printf("Done\n");

    return ctxt1;
}