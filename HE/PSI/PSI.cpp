#include <iostream>
#include "Util.h"
#include "PSI.h"

helib::Ctxt PSI::findIntersection(helib::Ctxt child_ctxt, helib::Ctxt parent_ctxt, int parentSize, COED::Encryptor encryptor){
	
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

    	// std::vector<long> results(encryptor.getEncryptedArray()->size());
    	// std::vector<long> pv(encryptor.getEncryptedArray()->size());
    	// encryptor.getEncryptedArray()->decrypt(intersection, *encryptor.getSecretKey(), results);
    	// encryptor.getEncryptedArray()->decrypt(search_ctxt, *encryptor.getSecretKey(), pv);
     //    printf("\t");
     //    for(int i = 0; i<parentSize*2; i++){
	    // 	printf("%ld ", pv[i]);
    	// }
    	// printf("\n");
    }

    return intersection;
}

void PSI::inspectResults(std::vector<long> childvector, std::vector<long> parentvector, helib::Ctxt intersection, int childSize, COED::Encryptor encryptor){
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