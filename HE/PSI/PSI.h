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
	static helib::Ctxt findIntersectionPacked(helib::Ctxt child_ctxt, helib::Ctxt parent_ctxt, int parentSize, COED::Encryptor encryptor);
	static void inspectResults(long childvector_i, helib::Ctxt intersection, COED::Encryptor encryptor);
	static void inspectResultsPacked(std::vector<long> childvector, helib::Ctxt intersection, int childSize, COED::Encryptor encryptor);
	static helib::Ctxt findIntersectionHashingPacked(const helib::Ctxt& child,
                                                     const helib::Ctxt& parent,
                                                     const COED::Encryptor& encryptor,
                                                     unsigned int childLength,
                                                     unsigned int parentLength);

    static void inspectResultsHashingPacked(const helib::Ctxt& ctxt,
                                            std::vector<long> values,
                                            const COED::Encryptor& encryptor,
                                            unsigned long childSlotSize);
};


#endif //HELIBEXAMPLES_PSI_H
