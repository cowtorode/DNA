//
// Name: nucleicacid.cpp
// Author: Cory Torode
// Date: 11/8/23
// Description: Stores DNA nucleotides compactly
//

#include <stdexcept>
#include "nucleicacid.h"
#include "../util/stringutil.h"

NucleicAcid::NucleicAcid(const std::string& sequence) : compressedNucleotides(compressSequence(sequence)),
                                                        basePairs(sequence.length()) {
}

std::string NucleicAcid::compressSequence(std::string sequence) {
    StringUtil::toUpperReference(sequence);
    std::string compressed;
    compressed.reserve(sequence.length() / 4 + 1);

    // chars are 16 bits so with 2 bits per nucleotide we can store 8 compressedNucleotides per char
    char append = 0; // buffer of 8 compressedNucleotides before added to resulting building
    char offset = 6; // amount to bitshift to find position of current nucleotide in iteration
    bool y;          // 3rd bit of current char, (5th and 2nd bits are also calculated)

    // 'A' == 0b01000001
    // 'C' == 0b01000011
    // 'G' == 0b01000111
    // 'T' == 0b01010100
    // How to calculate value instead of switch case
    //             x yzw
    // Diff   0b   _ ___ <- only bits that change between
    // 'A' == 0b   0 001
    // 'C' == 0b   0 011
    // 'G' == 0b   0 111
    // 'T' == 0b   1 100 (Lowercase has the same differences between)
    // Preferentially, we want to calculate the following mapping with as little input
    // bits as possible, out of the above input bits that change between values.
    // Two bit output, first bit, and second bit.
    // A   | C   | G   | T
    // 0 0 | 0 1 | 1 0 | 1 1
    // First bit = x0 | y0
    // Second bit = y ^ z
    // 0b00 == A
    // 0b01 == C
    // 0b10 == G
    // 0b11 == T
    for (char c : sequence) {
        // validation
        if (c == 'A' || c == 'T' || c == 'U' || c == 'C' || c == 'G') {
            // getStored 2nd 3rd and 5th bits for calculating bit corresponding to nucleotide
            y = (c & 0b100) != 0; // calculate 3rd bit
            append |= (y | ((c & 0b10000) != 0) /* 5th bit */) << (offset + 1);
            append |= (y ^ ((c & 0b00010) != 0) /* 2nd bit */) << offset;
            // handle 8 bit char running out of bits
            if (offset == 0) {
                offset = 6;
                compressed += append;
                append = 0;
            } else {
                offset -= 2;
            }
        } else {
            throw std::invalid_argument("Cannot construct a nucleic strand out of non ACG(T OR U) nitrogenous bases.");
        }
    }
    // add last character... (some of this may be cut off depending on base pairs)
    compressed += append;
    return compressed;
}

std::string NucleicAcid::getCompressed53() const {
    std::string complement = compressedNucleotides;

    for (int i = 0; i < compressedNucleotides.size(); i++) {
        // A (00) complements T (11), C (01) complements G (10)
        complement[i] = ~compressedNucleotides[i];
    }
    return complement;
}

std::string NucleicAcid::decompress(std::string compressed) const {
    // instantiate sequence with final size
    std::string sequence(compressed.size() * 4, '\0');
    char curr;
    int offset;
    bool odd;

    // for each char
    for (int i = 0; i < compressed.size(); i++) {
        curr = compressed[i];

        for (int j = 0; j < 4 /* 4 compressed per char */; j++) {
            // curr = 0b00110110 ATCG
            // j == 0, look at 0 and 1 bit. curr & 0b10000000, curr & 0b01000000
            // j == 1, look at 2 and 3 bit. curr & 0b00100000, curr & 0b00010000
            // j == 2, look at 4 and 5 bit. curr & 0b00001000, curr & 0b00000100
            // j == 3, look at 6 and 7 bit. curr & 0b00000010, curr & 0b00000001
            // to calculate the even bit value that we & with curr, you do (0b10 << (2 * (4 - j) - 2))
            // to calculate the odd bit value that we & with curr, you do (0b01 << (2 * (4 - j) - 2))

            offset = (2 * (4 - j) - 2);
            // bool even = (curr & (0b10 << offset)) != 0;
            odd    = (curr & (0b01 << offset)) != 0;

            // 4 * i + j is the char that this nucleotide needs to go.
            sequence[4 * i + j] = (((curr & (0b10 << offset)) != 0) ? (odd ? 'T' : 'G') : (odd ? 'C' : 'A'));
        }
    }

    return sequence.substr(0, basePairs);
}
