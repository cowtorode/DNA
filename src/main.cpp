#include <iostream>
#include "dna/nucleicacid.h"
#include "util/stringutil.h"

int main() {
    std::string sequence = "tacatcgat";

    NucleicAcid dna(sequence);
    std::cout << "Binary Nucleotides " << StringUtil::toBinaryString(dna.getNucleotides()) << std::endl;
    std::cout << "Complement Binary Nucleotides " << StringUtil::toBinaryString(dna.getComplementingNucleotides()) << std::endl;
    std::cout << "Sequence " << dna.getSequence() << std::endl;
    return 0;
}
