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
     * Computes the compressed 5' -> 3' strand and returns it.
     */
    std::string getCompressed53() const;

    /*
     * Returns the compressed 3' -> 5' sequence.
     */
    inline std::string getCompressed35() const { return compressedNucleotides; }

    std::string decompress(std::string compressed) const;

    /*
     * Returns the 5' -> 3' sequence of nucleotides in a human-readable format.
     */
    inline std::string getDecompressed53() const {
        return decompress(getCompressed53());
    }

    /*
     * Returns the 3' -> 5' sequence of nucleotides in a human-readable format.
     */
    inline std::string getDecompressed35() const {
        return decompress(compressedNucleotides);
    }

    /*
     * Returns the number of base pairs.
     * See NucleicAcid::getCompressed35 to getStored the actual bases.
     */
    inline int getBasePairs() const { return basePairs; }
};


#endif //DNA_NUCLEICACID_H
