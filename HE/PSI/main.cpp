/*
Code by Adam Caulfield (ac7717@rit.edu) for CSCI759 Project 1    

Based on code from:
      Copyright SpiRITlab - Computations on Encrypted Data
      https://gitlab.com/SpiRITlab/coed

*/

#include <iostream>
#include "BasicExamples.h"
#include "PSI.h"
#include <cstdio>
#include <ctime>

/* 
    Main iterates through all of the Tasks once
    Task 1 requires two user integer inputs
*/
int main() {
    printf("-------- Program Start --------\n");

    unsigned long plaintext_prime_modulus = 53;
    unsigned long phiM = 26651;
    unsigned long lifting = 1;
    unsigned long numOfBitsOfModulusChain = 512;
    unsigned long numOfColOfKeySwitchingMatrix = 2;

    COED::Encryptor encryptor("/tmp/sk.txt", "/tmp/pk.txt",
                              plaintext_prime_modulus,
                              phiM,
                              lifting,
                              numOfBitsOfModulusChain,
                              numOfColOfKeySwitchingMatrix);
    printf("Finished creating encryptor.\n");

    std::cout << "Program Finished" << std::endl;

    std::vector<long> childvector(encryptor.getEncryptedArray()->size()), parentvector(encryptor.getEncryptedArray()->size());
    long nslots = encryptor.getEncryptedArray()->size();
    //Parent vector only has even numbers 0-18
    //Child vector has all numbers 0-9
    int parentSize = 10;
    int childSize = 10;
    printf("Filling Vectors...");
    for(int i=0; i<nslots; i++){
        if(i<parentSize){
            parentvector[i] = 2*i;
            childvector[i] = i;
        }
        else{
            parentvector[i] = 0;
            childvector[i] = 0;  
        }
    }
    printf("Done\n Encrypting vectors...");

    helib::Ctxt child_ctxt(*encryptor.getPublicKey()), parent_ctxt(*encryptor.getPublicKey());
    encryptor.getEncryptedArray()->encrypt(child_ctxt, *encryptor.getPublicKey(), childvector);
    encryptor.getEncryptedArray()->encrypt(parent_ctxt, *encryptor.getPublicKey(), parentvector);
    printf("Done\n Finding PSI...");
    helib::Ctxt intersection = PSI::findIntersection(child_ctxt, parent_ctxt, parentSize, encryptor);
    printf("Done\n");

    PSI::inspectResults(childvector,parentvector, intersection, childSize, encryptor);

    printf("-------- Program End --------\n");
    return 0;
}
