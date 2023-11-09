//
// Name: nucleicacid.h
// Author: Cory Torode
// Date: 11/8/23
// Description: Declare methods for DNA compression, etc
//

#ifndef DNA_NUCLEICACID_H
#define DNA_NUCLEICACID_H

#include <string>

class NucleicAcid {
private:
    /*
     * 0b00 == A
     * 0b01 == C
     * 0b10 == G
     * 0b11 == T or U, (depending on if RNA or DNA)
     * Notice, A == ~T, C == ~G. This allows for easy computation of strand complements.
     */
    std::string nucleotides;

    int basePairs; // number of base pairs, size of input sequence...

    std::string compressSequence(std::string sequence);
public:
    /*
     * Expects the 5' to 3' sequence of DNA nucleotides
     */
    explicit NucleicAcid(const std::string& sequence);

    std::string getComplementingNucleotides();

    inline std::string getNucleotides() const { return nucleotides; }

    std::string getSequence();

    /*
     * Returns the number of base pairs.
     * See NucleicAcid::getNucleotides to get the actual bases.
     */
    inline int getBasePairs() const { return basePairs; }
};


#endif //DNA_NUCLEICACID_H
