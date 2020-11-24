#include <iostream>
#include "Util.h"
#include "PSI.h"

helib::Ctxt PSI::findIntersection(helib::Ctxt child_ctxt, helib::Ctxt parent_ctxt, int parentSize, COED::Encryptor encryptor){
    
    // helib::Ctxt search_ctxt(parent_ctxt);
    // encryptor.getEncryptedArray()->rotate(search_ctxt,parentSize);
    // search_ctxt.addCtxt(parent_ctxt);

    helib::Ctxt diff(child_ctxt);
    helib::Ctxt intersection(child_ctxt);
    intersection = parent_ctxt;
    intersection -= child_ctxt;

    for(int i=0; i<parentSize; i++){
        // std::vector<long> results(encryptor.getEncryptedArray()->size());
        // std::vector<long> pv(encryptor.getEncryptedArray()->size());
        // encryptor.getEncryptedArray()->decrypt(intersection, *encryptor.getSecretKey(), results);
        // encryptor.getEncryptedArray()->decrypt(parent_ctxt, *encryptor.getSecretKey(), pv);
        // printf("\t");
        // for(int j = 0; j<parentSize; j++){
        //     printf("%ld ", pv[j]);
        // }
        // printf("\n\t");
        // for(int j = 0; j<parentSize; j++){
        //     printf("%ld ", results[j]);
        // }
        // printf("\n");

        encryptor.getEncryptedArray()->rotate(parent_ctxt,-1);
        diff = parent_ctxt;
        diff -= child_ctxt;
        intersection.multiplyBy(diff);
    }

    return intersection;
}

helib::Ctxt PSI::findIntersectionPacked(helib::Ctxt child_ctxt, helib::Ctxt parent_ctxt, int parentSize, COED::Encryptor encryptor){
	
	helib::Ctxt search_ctxt(parent_ctxt);
	encryptor.getEncryptedArray()->rotate(search_ctxt,parentSize);
    search_ctxt.addCtxt(parent_ctxt);

    helib::Ctxt diff(child_ctxt);
    helib::Ctxt intersection(child_ctxt);
    intersection = search_ctxt;
    intersection -= child_ctxt;

    for(int i=0; i<parentSize+1; i++){
    	encryptor.getEncryptedArray()->rotate(search_ctxt,-1);
    	diff = search_ctxt;
    	diff -= child_ctxt;
    	intersection.multiplyBy(diff);
    }

    return intersection;
}

void PSI::inspectResults(long childvector_i, helib::Ctxt intersection, COED::Encryptor encryptor){
	std::vector<long> results(encryptor.getEncryptedArray()->size());
    encryptor.getEncryptedArray()->decrypt(intersection, *encryptor.getSecretKey(), results);
    if(results[0]==0){
    	printf("Value: %ld\t Found: True\n", childvector_i);
    }
    else{
    	printf("Value: %ld\t Found: False\n", childvector_i);
    }
}

void PSI::inspectResultsPacked(std::vector<long> childvector, helib::Ctxt intersection, int childSize, COED::Encryptor encryptor){
    std::vector<long> results(encryptor.getEncryptedArray()->size());
    encryptor.getEncryptedArray()->decrypt(intersection, *encryptor.getSecretKey(), results);
    for(int i = 0; i<childSize; i++){
        if(results[i]==0){
            printf("Value: %ld\t Found: True\n", childvector[i]);
        }
        else{
            printf("Value: %ld\t Found: False\n", childvector[i]);
        }
    }
}

helib::Ctxt PSI::findIntersectionHashingPacked(helib::Ctxt child,
                                               helib::Ctxt parent,
                                               COED::Encryptor encryptor,
                                               unsigned int childLength,
                                               unsigned int parentLength) {
    auto finalAnswer = child;

    encryptor.getEncryptedArray()->rotate(parent, childLength);

    auto rotationAmount = fmax(childLength, parentLength);

    for (int i = 0; i < rotationAmount; i++) {
        auto answer = child;

//        std::vector<long> results(encryptor.getEncryptedArray()->size());
//        encryptor.getEncryptedArray()->decrypt(child, *encryptor.getSecretKey(), results);
//        std::cout << "encrypted child:\n ";
//        for (int j = 0; j < encryptor.getEncryptedArray()->size(); j++) {
//            std::cout << results[j];
//        }
//        std::cout << std::endl;
//
//        std::cout << "minus" << std::endl;

        encryptor.getEncryptedArray()->rotate(parent, -1);

//        std::vector<long> results3(encryptor.getEncryptedArray()->size());
//        encryptor.getEncryptedArray()->decrypt(parent, *encryptor.getSecretKey(), results3);
//        for (int j = 0; j < encryptor.getEncryptedArray()->size(); j++) {
//            std::cout << results3[j];
//        }
//        std::cout << std::endl;

        answer -= parent;

//        std::cout << "equals" << std::endl;
//
//        std::vector<long> results2(encryptor.getEncryptedArray()->size());
//        encryptor.getEncryptedArray()->decrypt(answer, *encryptor.getSecretKey(), results2);
//        for (int j = 0; j < encryptor.getEncryptedArray()->size(); j++) {
//            std::cout << results2[j];
//        }
//        std::cout << std::endl;

        finalAnswer.multiplyBy(answer);
    }
    return finalAnswer;
}

void PSI::inspectResultsHashingPacked(helib::Ctxt ctxt, std::vector<long> values, COED::Encryptor encryptor, unsigned long childSlotSize) {
    std::vector<long> results(encryptor.getEncryptedArray()->size());
    encryptor.getEncryptedArray()->decrypt(ctxt, *encryptor.getSecretKey(), results);
    for (int i = 0; i < childSlotSize; i++) {
        if (results[i] == 0){
            printf("Value: %ld\t Found: True\n", values[i]);
        }
        else{
            printf("Value: %ld\t Found: False\n", values[i]);
        }
    }
}