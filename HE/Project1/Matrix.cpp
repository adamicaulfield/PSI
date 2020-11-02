/*
Code by Adam Caulfield (ac7717@rit.edu) for CSCI759 Project 1    

Based on code from:
      Copyright SpiRITlab - Computations on Encrypted Data
      https://gitlab.com/SpiRITlab/coed
*/

#include "Matrix.h"
#include <iostream>
#include "Util.h"
#include "omp.h"


/*	Matrix 3x3 multiplication Selector. Based on whether OpenMP is to be used or not to be used.*/
helib::Ctxt Matrix::mult_3by3(COED::Encryptor encryptor, std::vector<std::vector<long>> A, std::vector<std::vector<long>> B, bool inParallel,bool printMsgs){
	if(inParallel){
		return Matrix::mult_3by3_parallel(encryptor, A, B, printMsgs);
	}
	else{
		return Matrix::mult_3by3_standard(encryptor, A, B, printMsgs);
	}
}

/*	Matrix 3x3 multiplication without OpenMP*/
helib::Ctxt Matrix::mult_3by3_standard(COED::Encryptor encryptor, std::vector<std::vector<long>> A, std::vector<std::vector<long>> B,bool printMsgs){
	int a_rows = A.size();
	int a_cols = A[0].size();
	int b_rows = B.size();
	int b_cols = B[0].size();

	std::vector<std::vector<long>> A_expanded( a_rows , std::vector<long> (2*a_cols-1, 0)); 
	std::vector<std::vector<long>> B_expanded( 2*b_rows-1 , std::vector<long> (b_cols, 0));
	
	//Matrices expanded to add zeros
	//Easier to unroll into vector for dot-product and rotation
	for(int i = 0; i<a_rows; i++){
		for(int j = 0; j<2*a_cols-1; j++){
			if(j<3){
				A_expanded[i][j] = A[i][j];
			}
			else{
				A_expanded[i][j] = 0;
			}
		}
	}
	for(int i = 0; i<2*b_rows-1; i++){
		for(int j = 0; j<b_cols; j++){
			if(i<3){
				B_expanded[i][j] = B[i][j];
			}
			else{
				B_expanded[i][j] = 0;
			}
		}
	}

	//Declare ciphertexts for the two inputs and the result
    helib::Ctxt cvecA(*encryptor.getPublicKey());
    helib::Ctxt cvecB(*encryptor.getPublicKey());
    helib::Ctxt cdotprod(*encryptor.getPublicKey());

    //Declare plaintext for the two inputs and the result
    long nslots = encryptor.getEncryptedArray()->size();
	std::vector<long> vecA(nslots);
	std::vector<long> vecB(nslots); 
	std::vector<long> dotprod(nslots);

	//Unroll A and B into Vectors for encryption
	// A unrolled each row 3 times before the next row
	// B unrolled entire matrix three times
	// This is so the rows that multiply by the columns of A are in order and aligned
	int index = 0;
	for(int i = 0; i<a_rows; i++){
		for(int count = 0; count < a_rows; count++){
			for(int j = 0; j<2*b_cols-1; j++){
				vecA[index] = A_expanded[i][j];
				index++;
			}
		}
	}
	index = 0;
	for(int count = 0; count < b_rows; count++){
		for(int j = 0; j<b_cols; j++){
			for(int i = 0; i<2*b_rows-1; i++){
				vecB[index] = B_expanded[i][j];
				index++;
			}
		}
	}

	//Encrypt the vectors
    encryptor.getEncryptedArray()->encrypt(cvecA, *encryptor.getPublicKey(), vecA);
    encryptor.getEncryptedArray()->encrypt(cvecB, *encryptor.getPublicKey(), vecB);
    encryptor.getEncryptedArray()->encrypt(cdotprod, *encryptor.getPublicKey(), dotprod);

    //Take slotwise product
	helib::Ctxt prodctxt(cvecA);
    prodctxt.multiplyBy(cvecB);

    //Rotate and Add until for values
    for(int i=0; i<a_rows; i++){
    	cdotprod.addCtxt(prodctxt);
    	encryptor.getEncryptedArray()->rotate(prodctxt, 1);
    }

    return cdotprod;
}

/*	Matrix 3x3 multiplication with OpenMP.*/
helib::Ctxt Matrix::mult_3by3_parallel(COED::Encryptor encryptor, std::vector<std::vector<long>> A, std::vector<std::vector<long>> B,bool printMsgs){
	int a_rows = A.size();
	int a_cols = A[0].size();
	int b_rows = B.size();
	int b_cols = B[0].size();

	std::vector<std::vector<long>> A_expanded( a_rows , std::vector<long> (2*a_cols-1, 0)); 
	std::vector<std::vector<long>> B_expanded( 2*b_rows-1 , std::vector<long> (b_cols, 0));

	#pragma omp parallel for collapse(2)
	for(int i = 0; i<a_rows; i++){
		for(int j = 0; j<2*a_cols-1; j++){
			if(j<3){
				A_expanded[i][j] = A[i][j];
			}
			else{
				A_expanded[i][j] = 0;
			}
		}
	}
	#pragma omp parallel for collapse(2)
	for(int i = 0; i<2*b_rows-1; i++){
		for(int j = 0; j<b_cols; j++){
			if(i<3){
				B_expanded[i][j] = B[i][j];
			}
			else{
				B_expanded[i][j] = 0;
			}
		}
	}

	//Declare ciphertexts for the two inputs and the result
    helib::Ctxt cvecA(*encryptor.getPublicKey());
    helib::Ctxt cvecB(*encryptor.getPublicKey());
    helib::Ctxt cdotprod(*encryptor.getPublicKey());

    //Declare plaintext for the two inputs and the result
    long nslots = encryptor.getEncryptedArray()->size();
	std::vector<long> vecA(nslots);
	std::vector<long> vecB(nslots); 
	std::vector<long> dotprod(nslots);

	//Unroll A and B into Vectors for encryption
	// A unrolled each row 3 times before the next row
	// B unrolled entire matrix three times
	// This is so the rows that multiply by the columns of A are in order and aligned
	int index = 0;
	for(int i = 0; i<3; i++){
		for(int count = 0; count < 3; count++){
			for(int j = 0; j<5; j++){
				vecA[index] = A_expanded[i][j];
				index++;
			}
		}
	}
	index = 0;
	for(int count = 0; count < 3; count++){
		for(int j = 0; j<3; j++){
			for(int i = 0; i<5; i++){
				vecB[index] = B_expanded[i][j];
				index++;
			}
		}
	}

    encryptor.getEncryptedArray()->encrypt(cvecA, *encryptor.getPublicKey(), vecA);
    encryptor.getEncryptedArray()->encrypt(cvecB, *encryptor.getPublicKey(), vecB);
    encryptor.getEncryptedArray()->encrypt(cdotprod, *encryptor.getPublicKey(), dotprod);

	helib::Ctxt prodctxt(cvecA);
    prodctxt.multiplyBy(cvecB);

    for(int i=0; i<3; i++){
    	cdotprod.addCtxt(prodctxt);
    	encryptor.getEncryptedArray()->rotate(prodctxt, 1);
    }

    std::vector<long> result(encryptor.getEncryptedArray()->size());
    encryptor.getEncryptedArray()->decrypt(cdotprod, *encryptor.getSecretKey(), result);

    return cdotprod;
}

/*	Convolution Filter function Selector. Based on whether OpenMP is to be used or not to be used.*/
helib::Ctxt Matrix::conv_filter(COED::Encryptor encryptor, std::vector<std::vector<long>> x, std::vector<std::vector<long>> w, bool inParallel,bool printMsgs){
	if(inParallel){
		return Matrix::conv_filter_parallel(encryptor, x, w, printMsgs);
	}
	else{
		return Matrix::conv_filter_standard(encryptor, x, w, printMsgs);
	}
}

/*	Convolution filter without OpenMP*/
helib::Ctxt Matrix::conv_filter_standard(COED::Encryptor encryptor, std::vector<std::vector<long>> x, std::vector<std::vector<long>> w, bool printMsgs){
	//Convolutional filter
	//3x3 filter w applied on a 6x6 matrix x of input dat
	//Produces 4x4 feature map

	int x_rows = x.size();
	int x_cols = x[0].size();
	int w_rows = w.size();
	int w_cols = w[0].size();

	int result_rows = x_rows-w_rows+1;
	int result_cols = x_cols-w_cols+1;


    helib::Ctxt xCtxt(*encryptor.getPublicKey());
    helib::Ctxt wCtxt(*encryptor.getPublicKey());
    helib::Ctxt cdotprod(*encryptor.getPublicKey());

    long nslots = encryptor.getEncryptedArray()->size();

    std::vector<long> vecX(nslots);
	std::vector<long> vecW(nslots);
	std::vector<long> dotprod(nslots);
	if(printMsgs)
		printf("Creating Plaintext Vectors....");
	
	//initialize vecX to zeros before loading the matrix into it
	//initialize vecW to zeros before loading the matrix into it
	for(int c=0; c<nslots; c++){
		vecX[c] = 0;
		vecW[c] = 0;
	}

	//Unroll matrix into vector
	//Unrolling one 3x3 grid at a time with 8 empty spaces
	//All 3x3 grids that the filter will be applied to separeted by 8 epmty spaces which are needed for rotation dot product algorithm
	int ind = 0;
	for(int i_k=0; i_k<result_rows; i_k++){ 
		for(int j_k=0; j_k<result_cols; j_k++){
			for(int i=0; i<w_rows; i++){
				for(int j=0; j<w_cols; j++){
					vecX[ind] = x[i+i_k][j+j_k];
					ind = ind + 1;
					}
			}
			ind = ind+result_rows+result_cols;
		}
	}

	ind = 0;
	//Unroll the filter into the vector. Repeat for all 16 sub-matrices of X which the filter will apply to.
	for(int k=0; k<result_rows*result_cols; k++){ 
		for(int i=0; i<w_rows; i++){
			for(int j=0; j<w_cols; j++){
				vecW[ind] = w[i][j];
				ind = ind + 1;
				}
		}
		ind = ind+result_rows+result_cols;
	}
	if(printMsgs){
		printf("Done\n");
		printf("Encrypting...");
	}
	//Encrypt and compute dot products of all 16 combinations
	encryptor.getEncryptedArray()->encrypt(xCtxt, *encryptor.getPublicKey(), vecX);
    encryptor.getEncryptedArray()->encrypt(wCtxt, *encryptor.getPublicKey(), vecW);
    encryptor.getEncryptedArray()->encrypt(cdotprod, *encryptor.getPublicKey(), dotprod);
	
	if(printMsgs){
		printf("Done\n");
		printf("Computing Homomorphic Convolutions....");
	}

	//Slotwise multiplication
	helib::Ctxt prodctxt(xCtxt);
    prodctxt.multiplyBy(wCtxt);

    //Rotate and add all elements
    for(int i=0; i<=result_rows+result_cols; i++){
    	cdotprod.addCtxt(prodctxt);
    	encryptor.getEncryptedArray()->rotate(prodctxt, 1);
    }

   	if(printMsgs)
		printf("Done\n");

    return cdotprod;
}

/*	Convolution filter with OpenMP*/
helib::Ctxt Matrix::conv_filter_parallel(COED::Encryptor encryptor, std::vector<std::vector<long>> x, std::vector<std::vector<long>> w, bool printMsgs){
	//Convolutional filter
	//3x3 filter w applied on a 6x6 matrix x of input dat
	//Produces 4x4 feature map

	int x_rows = x.size();
	int x_cols = x[0].size();
	int w_rows = w.size();
	int w_cols = w[0].size();

	int result_rows = x_rows-w_rows+1;
	int result_cols = x_cols-w_cols+1;


    helib::Ctxt xCtxt(*encryptor.getPublicKey());
    helib::Ctxt wCtxt(*encryptor.getPublicKey());
    helib::Ctxt cdotprod(*encryptor.getPublicKey());

    long nslots = encryptor.getEncryptedArray()->size();

    std::vector<long> vecX(nslots);
	std::vector<long> vecW(nslots);
	std::vector<long> dotprod(nslots);
	if(printMsgs)
		printf("Creating Plaintext Vectors....");
	
	//initialize vecX to zeros before loading the matrix into it
	//initialize vecW to zeros before loading the matrix into it
	#pragma omp parallel for
	for(int c=0; c<nslots; c++){
		vecX[c] = 0;
		vecW[c] = 0;
	}

	//Unroll matrix into vector
	//Unrolling one 3x3 grid at a time with 8 empty spaces
	//All 3x3 grids that the filter will be applied to separeted by 8 epmty spaces which are needed for rotation dot product algorithm
	int ind = 0;
	for(int i_k=0; i_k<result_rows; i_k++){ 
		for(int j_k=0; j_k<result_cols; j_k++){
			for(int i=0; i<w_rows; i++){
				for(int j=0; j<w_cols; j++){
					vecX[ind] = x[i+i_k][j+j_k];
					ind = ind + 1;
					}
			}
			ind = ind+result_rows+result_cols;
		}
	}

	ind = 0;
	//Unroll the filter into the vector. Repeat for all 16 sub-matrices of X which the filter will apply to.
	for(int k=0; k<result_rows*result_cols; k++){ 
		for(int i=0; i<w_rows; i++){
			for(int j=0; j<w_cols; j++){
				vecW[ind] = w[i][j];
				ind = ind + 1;
				}
		}
		ind = ind+result_rows+result_cols;
	}
	if(printMsgs){
		printf("Done\n");
		printf("Encrypting...");
	}
	//Encrypt and compute dot products of all 16 combinations
	encryptor.getEncryptedArray()->encrypt(xCtxt, *encryptor.getPublicKey(), vecX);
    encryptor.getEncryptedArray()->encrypt(wCtxt, *encryptor.getPublicKey(), vecW);
    encryptor.getEncryptedArray()->encrypt(cdotprod, *encryptor.getPublicKey(), dotprod);
	
	if(printMsgs){
		printf("Done\n");
		printf("Computing Homomorphic Convolutions....");
	}

	//Slotwise multiplication
	helib::Ctxt prodctxt(xCtxt);
    prodctxt.multiplyBy(wCtxt);

    //Rotate and add all elements
    for(int i=0; i<=result_rows+result_cols; i++){
    	cdotprod.addCtxt(prodctxt);
    	encryptor.getEncryptedArray()->rotate(prodctxt, 1);
    }

   	if(printMsgs)
		printf("Done\n");

    return cdotprod;
}