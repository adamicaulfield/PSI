/*
Code by Adam Caulfield (ac7717@rit.edu) for CSCI759 Project 1    

Based on code from:
      Copyright SpiRITlab - Computations on Encrypted Data
      https://gitlab.com/SpiRITlab/coed

*/

#include <iostream>
#include "Calculator.h"
#include "Vector.h"
#include "Matrix.h"
#include <cstdio>
#include <ctime>

/* 
    Main iterates through all of the Tasks once
    Task 1 requires two user integer inputs
*/
int main() {
    std::cout << "Program Start!!!" << std::endl;

    // Create Encryptor
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

    bool inParallel = false;
    printf("--------------- TASK 1: Calculator ---------------\n");
    int again = 1;
    while(again != 0){
        helib::Ctxt cCalcResult = Calculator::run_calculator(encryptor,plaintext_prime_modulus);
        // Decrypt and Display result
        std::vector<long> calcResult(encryptor.getEncryptedArray()->size());
        encryptor.getEncryptedArray()->decrypt(cCalcResult, *encryptor.getSecretKey(), calcResult);
        printf("Result: %ld\n", calcResult[0]);
        printf("Press 0 to move on, Press any other number to continue: \n");
        std::cin >> again;
    }
    printf("Done Task 1\n");

    printf("--------------- TASK 2: Vector Dot Product ---------------\n");
    long nslots = encryptor.getEncryptedArray()->size();
    std::vector<long> vec1(nslots);
    std::vector<long> vec2(nslots);

    //Assign vector values
    int size = 5;
    for(int i = 0; i<=nslots; i++){
        if(i<size){
            vec1[i] = i;
            vec2[i] = size-1-i;
        } else{
            vec1[i] = 0;
            vec2[i] = 0;
        }
    }
    //Print Vectors
    printf("Vector 1: {");
    for(int i = 0; i<size; i++){
        printf("%ld ",vec1[i]);
    }
    printf("}\n");
    printf("Vector 2: {");
    for(int i = 0; i<size; i++){
        printf("%ld ",vec2[i]);
    }
    printf("}\n");
    helib::Ctxt cdotprod = Vector::dot_product(encryptor,vec1,vec2,size);
    //Encrypt and display result
    std::vector<long> dotprod(encryptor.getEncryptedArray()->size());
    encryptor.getEncryptedArray()->decrypt(cdotprod, *encryptor.getSecretKey(), dotprod);
    printf("Result: %ld\n", dotprod[size-1]);
    printf("Done Task 2\n");


    printf("--------------- TASK 3: 3x3 Matrix Multiplication ---------------\n");
    //Assigning matrices
    inParallel = false;
    std::vector<std::vector<long>> A = {{0,1,2}, {2,1,0}, {1,0,2}};
    std::vector<std::vector<long>> B = {{2,0,1}, {1,2,2}, {1,1,0}};
    std::clock_t start = std::clock();
    helib::Ctxt cMatProd = Matrix::mult_3by3(encryptor,A,B,inParallel,true);
    double matmult_standard_dur = (double)(std::clock() - start)/(CLOCKS_PER_SEC);

    //Decrypt and get result. 
    std::vector<long> matProd(encryptor.getEncryptedArray()->size());
    encryptor.getEncryptedArray()->decrypt(cMatProd, *encryptor.getSecretKey(), matProd);
    int count = 0;
    int printed_count = 0;
    const int all_printed = A.size()*A[0].size();
    int a_rows = A.size();
    int k = 0;
    while(printed_count < all_printed){
        if(k%(2*a_rows-1) == a_rows-1){
            printed_count++;
            printf("%ld ",matProd[k]);
            count = (count+1)%a_rows;
            if(count == 0){
                printf("\n");
            }
        }
        k++;
    }
    printf("Done Task 3\n");

    printf("--------------- TASK 4: Convolutional Filter ---------------\n");
    // // Test input and weights declared as all ones for easy testing.
    // // With input and weights of all ones, output is expected feature map containing all 9's
    std::vector<std::vector<long>> input = {{1,1,1,1,1,1},
                                            {1,1,1,1,1,1},
                                            {1,1,1,1,1,1},
                                            {1,1,1,1,1,1},
                                            {1,1,1,1,1,1},
                                            {1,1,1,1,1,1}};

    std::vector<std::vector<long>> filter = {{1,1,1},{1,1,1},{1,1,1}};
    inParallel = false;
    start = std::clock();
    helib::Ctxt cResult = Matrix::conv_filter(encryptor,input,filter,inParallel,true);
    //    double convfilter_standard_dur;
    double convfilter_standard_dur = (double)(std::clock() - start)/(CLOCKS_PER_SEC);

    //Decrpyt and display result
    std::vector<long> result(encryptor.getEncryptedArray()->size());
    encryptor.getEncryptedArray()->decrypt(cResult, *encryptor.getSecretKey(), result);
    
    int i = 0;
    int j = 0;

    count = 0;
    k = 0;
    int result_rows = 4;
    int result_cols = 4;

    //Print Result
    while(count<result_rows*result_cols){
        if(k%(2*(result_rows+result_cols)+1) == result_rows+result_cols){
            count++;
            printf("%ld ", result[k]);
            j = j+1;
                if(j==result_cols){
                    j = 0;
                    i = i+1;
                    printf("\n");
                }
        }
        k++;
    }

    printf("Done Task 4\n");


    printf("--------------- TASK 5: ACCELERATION ---------------\n");
    /* Acceleration using open MP. Unfortunately there is minimal speedup and speedup apears to depend on the machine
            For example, I have run it on two machines and the results were different. */
    inParallel = true;
    start = std::clock();
    cMatProd = Matrix::mult_3by3(encryptor,A,B,inParallel,false);
    double matmult_parallel_dur = (double)(std::clock() - start)/(CLOCKS_PER_SEC);
    printf("3x3 Matrix Multiplication:\n");
    printf("Standard: %0.4f\t",matmult_standard_dur);
    printf("Parallel: %0.4f\n",matmult_parallel_dur);

    start = std::clock();
    cResult = Matrix::conv_filter(encryptor,input,filter,inParallel,true);
    double convfilter_parallel_dur = (double)(std::clock() - start)/(CLOCKS_PER_SEC);
    printf("Convolutional Filtering: \n");
    printf("Standard: %0.4f\t",convfilter_standard_dur);
    printf("Parallel: %0.4f\n",convfilter_parallel_dur);
    printf("\n");
 

    std::cout << "Program Finished!!!" << std::endl;
    return 0;
}
