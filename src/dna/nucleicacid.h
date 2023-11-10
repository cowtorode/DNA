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
    std::string compressedNucleotides;

    int basePairs; // number of base pairs, size of input sequence...

    std::string compressSequence(std::string sequence);
public:
    /*
     * Converts an std::string input of 3' to 5' nucleotides, each character being either
     * 'A', 'C', 'T', 'G', into a more compressed format stored as a string.
     */
    explicit NucleicAcid(const std::string& sequence);

    /*
     * Computes the compressed complement of 35 and returns it.
     */
    std::string getCompressed53() const;

    /*
     * Returns the compressed 35 sequence.
     */
    inline std::string getCompressed35() const { return compressedNucleotides; }

    std::string getDecompressed35() const;

    /*
     * Returns the number of base pairs.
     * See NucleicAcid::getCompressed35 to get the actual bases.
     */
    inline int getBasePairs() const { return basePairs; }
};


#endif //DNA_NUCLEICACID_H
