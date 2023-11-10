#include <iostream>
#include "dna/nucleicacid.h"
#include "util/stringutil.h"

using std::string;
using std::cout;
using std::endl;

void printDNAInfo(const NucleicAcid &dna) {
    cout << "Binary Nucleotides " << StringUtil::toBinaryString(dna.getCompressed35()) << endl;
    cout << "Complement Binary Nucleotides " << StringUtil::toBinaryString(dna.getCompressed53()) << endl;
    cout << "Sequence " << dna.getDecompressed35() << endl;
}

int main() {
    NucleicAcid dna("atcgaaaa");
    printDNAInfo(dna);
    return 0;
}
