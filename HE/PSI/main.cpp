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
#include <vector>

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

    // long one_num = 5;
    // helib::Ctxt one_num_ctxt(*encryptor.getPublicKey());
    // encryptor.getEncryptedArray()->encrypt(one_num_ctxt,*encryptor.getPublicKey(),one_num);

    //Parent vector only has even numbers 0-18
    //Child vector has all numbers 0-9
    int parentSize = 10;
    int childSize = 10;

    printf("Filling Vectors...");
    for(int i=0; i<nslots; i++){
        if(i<parentSize){
            parentvector[i] = 2*(i+1);
            childvector[i] = i+1;
        }
        else{
            parentvector[i] = 0;
            childvector[i] = 0;  
        }
    }
    printf("Done\n");   
    
    printf("\tParent Vector: ");
    for(int i=0; i<parentSize; i++){
        printf("%ld ", parentvector[i]);
    }
    printf("\n");

    printf("\tChild Vector: ");
    for(int i=0; i<childSize; i++){
        printf("%ld ", childvector[i]);
    }
    printf("\n");

    printf("--------------- Baseline Version (no packing) -------------------\n");
    helib::Ctxt parent_ctxt(*encryptor.getPublicKey());
    clock_t start = std::clock();
    encryptor.getEncryptedArray()->encrypt(parent_ctxt, *encryptor.getPublicKey(), parentvector);
    // std::vector<helib::Ctxt> child_ctxt_vector();
    for(int i=0; i<childSize; i++){
        std::vector<long> childvector_i(nslots);
        childvector_i[0] = childvector[i];
        // for(int j=0; j<nslots; j++){
        //     printf("%ld ", childvector_i[j]);
        // }
        // printf("\n");
        helib::Ctxt child_ctxt_i(*encryptor.getPublicKey());
        // child_ctxt_vector.push_back(child_ctxt_i);
        encryptor.getEncryptedArray()->encrypt(child_ctxt_i, *encryptor.getPublicKey(), childvector_i);
        helib::Ctxt intersection = PSI::findIntersection(child_ctxt_i, parent_ctxt, parentSize, encryptor);
        
        PSI::inspectResults(childvector[i], intersection, encryptor);
    }
    clock_t stop = std::clock();
    double baseline_duration = (double) ((stop - start) / CLOCKS_PER_SEC);

    printf("--------------- Optimization 1: Packed -------------------\n");
    start = std::clock();
    printf("Encrypting vectors into Packed CTXT...");
    helib::Ctxt child_ctxt(*encryptor.getPublicKey());
    encryptor.getEncryptedArray()->encrypt(child_ctxt, *encryptor.getPublicKey(), childvector);
    encryptor.getEncryptedArray()->encrypt(parent_ctxt, *encryptor.getPublicKey(), parentvector);

    printf("Done\n Finding PSI...");
    helib::Ctxt intersection = PSI::findIntersectionPacked(child_ctxt, parent_ctxt, parentSize, encryptor);
    printf("Done\n");

    PSI::inspectResultsPacked(childvector, intersection, childSize, encryptor);
    stop = std::clock();
    double packed_duration = (double) ((stop - start) / CLOCKS_PER_SEC);

    printf("--------------- Timing Comparison -------------------\n");
    printf("\tBaseline: %f\n", baseline_duration);
    printf("\tPacked: %f\n", packed_duration);


    printf("-------- Program End --------\n");
    return 0;
}
