/*
Code by Adam Caulfield (ac7717@rit.edu) for CSCI759 Project 1    

Based on code from:
      Copyright SpiRITlab - Computations on Encrypted Data
      https://gitlab.com/SpiRITlab/coed

*/

#include "Vector.h"
#include <iostream>
#include "Util.h"

helib::Ctxt Vector::dot_product(COED::Encryptor encryptor, std::vector<long> vec1,std::vector<long> vec2,int size){
    //Computes the dot product of two vectors of the same size

    //Declare ctxt objects
    helib::Ctxt cvec1(*encryptor.getPublicKey());
    helib::Ctxt cvec2(*encryptor.getPublicKey());
    helib::Ctxt cdotprod(*encryptor.getPublicKey());

    //Declare ptxt object for dotproduct
    long nslots = encryptor.getEncryptedArray()->size();	
	std::vector<long> dotprod(nslots);

    for(int i = 0; i<=nslots; i++){
    	dotprod[i] = 0;
    }

    //Encrypt all plaintext into ctxt
    encryptor.getEncryptedArray()->encrypt(cvec1, *encryptor.getPublicKey(), vec1);
    encryptor.getEncryptedArray()->encrypt(cvec2, *encryptor.getPublicKey(), vec2);
    encryptor.getEncryptedArray()->encrypt(cdotprod, *encryptor.getPublicKey(), dotprod);

    //Take slotwise product
    helib::Ctxt prodctxt(cvec1);
    prodctxt.multiplyBy(cvec2);

    //Rotate and add for the size of the vectors, and the dot product will be at the slot of the size-1
    std::vector<long> tmp(encryptor.getEncryptedArray()->size());
    for(int i=0; i<size; i++){
    	cdotprod.addCtxt(prodctxt);
    	encryptor.getEncryptedArray()->rotate(prodctxt, 1);
    }
    
    return cdotprod;
}