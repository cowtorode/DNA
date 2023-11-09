//
// Name: nucleicacid.cpp
// Author: Cory Torode
// Date: 11/8/23
// Description: Stores DNA nucleotides compactly
//

#include "nucleicacid.h"
#include "../util/stringutil.h"

NucleicAcid::NucleicAcid(const std::string& sequence) : nucleotides(compressSequence(sequence)),
                                                        basePairs(sequence.length()) {
}

std::string NucleicAcid::compressSequence(std::string sequence) {
    StringUtil::toUpperReference(sequence);
    std::string genome;

    // chars are 16 bits so with 2 bits per nucleotide we can store 8 nucleotides per char
    char append = 0;  // buffer of 8 nucleotides before added to resulting string
    char offset = 6; // amount to bitshift to find position of current nucleotide in iteration

    for (char c : sequence) {
        switch (c) {
            case 'A': // 0b00
                // because it's 0b00, we don't need to change the already 0 append char
                break;
            case 'C': // 0b01
                append |= 0b01 << offset;
                break;
            case 'G': // 0b10
                append |= 0b10 << offset;
                break;
            case 'T': // 0b11
                append |= 0b11 << offset;
                break;
            default:
                // throw new IllegalArgumentException("Cannot build nucleic acid out of non ATCGU nucleotides.");
                break;
        }
        // handle 8 bit char running out of bits
        if (offset == 0) {
            offset = 6;
            genome += append;
            append = 0;
        } else {
            offset -= 2;
        }
    }
    // add last character... (some of this may be cut off depending on base pairs)
    genome += append;
    return genome;
}

std::string NucleicAcid::getComplementingNucleotides() {
    std::string complement = nucleotides;

    for (int i = 0; i < nucleotides.size(); i++) {
        // A (00) complements T (11), C (01) complements G (10)
        complement[i] = ~nucleotides[i];
    }
    return complement;
}

std::string NucleicAcid::getSequence() {
    // instantiate sequence with final size
    std::string sequence(nucleotides.size() * 4, '\0');

    // for each char
    for (int i = 0; i < nucleotides.size(); i++) {
        char curr = nucleotides[i];

        for (int j = 0; j < 4 /* 4 nucleotides per char */; j++) {
            // curr = 0b00110110 ATCG
            // j == 0, look at 0 and 1 bit. curr & 0b10000000, curr & 0b01000000
            // j == 1, look at 2 and 3 bit. curr & 0b00100000, curr & 0b00010000
            // j == 2, look at 4 and 5 bit. curr & 0b00001000, curr & 0b00000100
            // j == 3, look at 6 and 7 bit. curr & 0b00000010, curr & 0b00000001
            // to calculate the even bit value that we & with curr, you do (0b10 << (2 * (4 - j) - 2))
            // to calculate the odd bit value that we & with curr, you do (0b01 << (2 * (4 - j) - 2))

            int offset = (2 * (4 - j) - 2);
            bool even = (curr & (0b10 << offset)) != 0;
            bool odd  = (curr & (0b01 << offset)) != 0;

            // 4 * i + j is the char that this nucleotide needs to go.
            sequence[4 * i + j] = (even ? (odd ? 'T' : 'G') : (odd ? 'C' : 'A'));
        }
    }

    return sequence.substr(0, basePairs);
}
