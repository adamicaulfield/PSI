//
// Copyright SpiRITlab - Computations on Encrypted Data
// https://gitlab.com/SpiRITlab/coed
//

#ifndef HELIBEXAMPLES_PSI_H
#define HELIBEXAMPLES_PSI_H

#include "Encryptor.h"


class PSI {
public:
	static helib::Ctxt findIntersection(helib::Ctxt child_ctxt, helib::Ctxt parent_ctxt, int parentSize, COED::Encryptor encryptor);
	static void inspectResults(std::vector<long> childvector, std::vector<long> parentvector, helib::Ctxt intersection, int childSize, COED::Encryptor encryptor);
};


#endif //HELIBEXAMPLES_PSI_H
