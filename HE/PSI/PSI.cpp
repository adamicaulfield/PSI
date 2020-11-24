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

helib::Ctxt PSI::windowedPSI(helib::Ctxt receiver_ctxt, helib::Ctxt sender_ctxt, int senderSetSize, COED::Encryptor encryptor){
	helib::Ctxt result(receiver_ctxt);
	result.multiplyBy(sender_ctxt);

	// std::vector<long> inspect(encryptor.getEncryptedArray()->size());
	// encryptor.getEncryptedArray()->decrypt(result, *encryptor.getSecretKey(), inspect);
	// printf("in windowedPSI(): Product of ciphertexts: ");
	// for(int i=0; i<inspect.size(); i++){
	// 	printf("%ld ", inspect[i]);
	// }
	// printf("\n");

	helib::Ctxt tmp(result);
	encryptor.getEncryptedArray()->rotate(tmp, -1);
	result += tmp;
	
	for(int i=0; i<senderSetSize-1; i++){
		
		// encryptor.getEncryptedArray()->decrypt(result, *encryptor.getSecretKey(), inspect);
		// printf("in windowedPSI(): After %d rotations/sums: ", i+1);
		// for(int i=0; i<inspect.size(); i++){
		// 	printf("%ld ", inspect[i]);
		// }
		// printf("\n");

		encryptor.getEncryptedArray()->rotate(tmp, -1);
		result += tmp;
	}

	return result;
}