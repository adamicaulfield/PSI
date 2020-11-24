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
#include "helib/timing.h"
#include <cmath>

int n_chose_k(int n, int k);
std::vector<std::vector<int>> getCombinations(int n, int k, int t);
void testGetCombinations();
std::vector<long> getSenderOptCoeffs(int n, std::vector<long> senderCoeff);

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

    // std::cout << "Program Finished" << std::endl;

    std::vector<long> childvector(encryptor.getEncryptedArray()->size()), parentvector(encryptor.getEncryptedArray()->size());
    long nslots = encryptor.getEncryptedArray()->size();

    // long one_num = 5;
    // helib::Ctxt one_num_ctxt(*encryptor.getPublicKey());
    // encryptor.getEncryptedArray()->encrypt(one_num_ctxt,*encryptor.getPublicKey(),one_num);

    //Parent vector only has even numbers 0-18
    //Child vector has all numbers 0-9
    int parentSize = 4;
    int childSize = 4;

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

    printf("Printing All Timers: \n");
    // helib::printAllTimers(std::cout);
    printf("\n");
    
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

    printf("--------------- Optimization 3: Windowed PSI -------------------\n");

    // std::vector<std::vector<int>> combinations = getCombinations(5,3);
    start = std::clock();
    std::vector<long> senderSet = {1,3};
    int n = senderSet.size();
    std::vector<long> senderOptCoeff = getSenderOptCoeffs(n, senderSet);
    printf("\t Sender Optimized Coeff: ");
    for(int i=0; i<=n; i++){
        printf("%ld ", senderOptCoeff[i]);
    }
    printf("\n");

    std::vector<long> optCoeff(nslots);
    for(int i=0; i<=n; i++){
        if(i<=n){
            optCoeff[i] = senderOptCoeff[i];
        }
        else{
            optCoeff[i] = 0;
        }
    }

    printf("Encrypting Sender Optimized Coeffs...");
    helib::Ctxt senderOptCoeff_Ctxt(*encryptor.getPublicKey());
    encryptor.getEncryptedArray()->encrypt(senderOptCoeff_Ctxt, *encryptor.getPublicKey(), optCoeff);
    printf("Done\n");

    std::vector<long> receiverSet = {1, 2, 3, 4};
    int x_n = receiverSet.size();
    printf("Setup ReceiverSet\n");
    std::vector<long> receiverDataExpanded(nslots);
    printf("Initialized vector for expanded receiver data\n");

    helib::Ctxt receiverDataExp_Ctxt(*encryptor.getPublicKey());
    for(int x = 0; x<x_n; x++){
        // printf("Expanded data for %d: ", x);
        for(int i=n; i>=0; i--){
            receiverDataExpanded[n-i] = (long) pow(receiverSet[x],i);
            // printf("Passed for i=%d\n", i);
        }
        for(int i=n+1; i<nslots; i++){
            receiverDataExpanded[i] = 0;
        }
        encryptor.getEncryptedArray()->encrypt(receiverDataExp_Ctxt, *encryptor.getPublicKey(), receiverDataExpanded);        
    
        helib::Ctxt result = PSI::windowedPSI(receiverDataExp_Ctxt, senderOptCoeff_Ctxt, n+1, encryptor);
        PSI::inspectResults(receiverSet[x], result, encryptor);
        // for(int i=0; i<n+1; i++){
        //     printf("%d ", receiverDataExpanded[i]);
        // }
        // printf("\n");    
    }
    stop = std::clock();
    double windowed_duration = (double) ((stop - start) / CLOCKS_PER_SEC);

    printf("--------------- Timing Comparison -------------------\n");
    printf("\tBaseline: %f\n", baseline_duration);
    printf("\tPacked: %f\n", packed_duration);
    printf("\tWindowed: %f\n", windowed_duration);

    printf("-------- Program End --------\n");
    return 0;
}

std::vector<std::vector<int>> getCombinations(int n, int k, int t){
    printf("Start getting Combinations\n");

    std::vector<int> elt(k);
    std::vector<int> max_val(k);
    std::vector<std::vector<int>> all_combo;
    all_combo.resize(t, std::vector<int>(k, 0));

    for(int i=0; i<k; i++){
        elt[i] = i;
        max_val[i] = k-1+i;
    }

    int count = 0;
    bool checking;
    int check_ind;
    while(count<t){
        check_ind = k-1;
        checking = true;
        // for(int i=0; i<k; i++){
        //     printf("%d ", elt[i]);
        // }
        // printf("\n");

        for(int i=0; i<k; i++){
            all_combo[count][i] = elt[i];
        }


        elt[k-1]++;
        // printf("\telt[k-1]++ --> elt[k-1]=%d\n", elt[k-1]);
        while(checking){
            // printf("\tchecking %d>%d\n", elt[check_ind], max_val[check_ind]);
            if(check_ind < 0){
                checking = false;
            }
            else{
                if(elt[check_ind]>max_val[check_ind]){
                    // printf("\tTRUE decrementing check_ind from %d to %d\n", check_ind, check_ind-1);
                    check_ind--;
                    if(check_ind>=0){
                        elt[check_ind]++;
                        // printf("\tIncrementing elt[%d]to %d\n", check_ind, elt[check_ind]);
                    }
                }
                else{
                    // printf("\tFALSE\n");
                    checking = false;
                }
            }
        }

        int c = check_ind+1;
        // printf("\tEntering final while loop with c=%d and check_ind = %d\n", c, check_ind);
        while(0<c && c<k){
            // printf("\tChanging elt[%d] from %d to %d\n",c, elt[c], elt[c-1]+1);
            elt[c] = elt[c-1]+1;
            c++;
        }

        count++;
        
    }
    printf("Done getting Combinations\n");
    return all_combo;
}

int n_chose_k(int n, int k){
    int factorial_n = 1;
    int factorial_k = 1;
    int factorial_n_minus_k = 1;
    for(int i=1; i<=n; i++){
        factorial_n = factorial_n*i;
    }
    // printf("Factorial of %d = %d\n", n, factorial_n);

    for(int i=1; i<=k; i++){
        factorial_k = factorial_k*i;
    }
    // printf("Factorial of %d = %d\n", k, factorial_k);

    for(int i=1; i<=(n-k) ; i++){
        factorial_n_minus_k = factorial_n_minus_k*i;
    }

    // printf("Factorial of (%d-%d) = factorial of %d = %d\n", n, k, n-k, factorial_n_minus_k);

    int result = (int)(factorial_n/(factorial_k * (factorial_n_minus_k)));
    // printf("Result  of %d chose %d = %d\n", n, k, result);
    return result;
}

void testGetCombinations(){
    int n = 5;
    int k = 3;
    int t = n_chose_k(n, k);
    std::vector<std::vector<int>> all_combo = getCombinations(n,k,t);

    printf("Result of get Combos:\n");

    for(int i=0; i<t; i++){
        for(int j=0; j<k; j++){
            printf("%d ", all_combo[i][j]);
        }
        printf("\n");
    }
}

std::vector<long> getSenderOptCoeffs(int n, std::vector<long> senderCoeff){
    printf("Starting setup sender optimized coefficients:\n");
    std::vector<long> optimizedCoeff(n+1,0);
    long sum, prod;
    std::vector<std::vector<int>> all_combo;

    for(int k=n; k>=0; k--){
        if(k==0){
            sum = 1;
        }
        else{
            sum = 0;
            int t = n_chose_k(n,k);
            // printf("\tk=%d, n=%d, t=%d, ", k, n, t);
            all_combo = getCombinations(n,k,t);
            // printf("\tgot all combinaitons\n");
            for(int i=0; i<t; i++){
                prod = 1;
                for(int j=0; j<k; j++){
                    prod = prod*(-1)*senderCoeff[all_combo[i][j]]; //negative because subtracting
                }
                sum = sum+prod;
            }
        }
        // printf("\tCompleted sum: optCoef[%d] = %d\n",k, sum);
        optimizedCoeff[k] = sum;
    }

    printf("Done getting sender optimized coefficients\n");
    
    return optimizedCoeff;
}