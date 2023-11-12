//
// Name: main.cpp
// Author: Cory Torode
// Date: 11/8/23
// Description: Start point for digital DNA compression testing
//

#include <iostream>
#include "dna/nucleicacid.h"
#include "util/stringutil.h"

using std::string;
using std::cout;
using std::endl;

void printDNAInfo(const NucleicAcid &dna) {
    cout << "3' -> 5' Binary " << StringUtil::toBinaryString(dna.getCompressed35()) << endl;
    cout << "5' -> 3' Binary " << StringUtil::toBinaryString(dna.getCompressed53()) << endl;
    cout << "3' -> 5' Sequence     " << dna.getDecompressed35() << endl;
    string decompressed53 = dna.getDecompressed53();
    cout << "5' -> 3' Sequence     " << decompressed53 << endl;
    cout << "5' -> 3' Sequence RNA " << StringUtil::replace(decompressed53, 'T', 'U');
}

int main() {
    NucleicAcid dna("tactcggcatattttactgaactcatgcacatgcaccatctgactgacgagcagcgactacgcgaagcgacagtcc");
    printDNAInfo(dna);
    return 0;
}
