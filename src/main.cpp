#include <iostream>
#include "dna/nucleicacid.h"
#include "util/stringutil.h"

int main() {
    std::string sequence = "tacatcgat";

    NucleicAcid dna(sequence);
    std::cout << "Binary Nucleotides " << StringUtil::toBinaryString(dna.getCompressed35()) << std::endl;
    std::cout << "Complement Binary Nucleotides " << StringUtil::toBinaryString(dna.getCompressed53()) << std::endl;
    std::cout << "Sequence " << dna.getDecompressed35() << std::endl;
    return 0;
}
