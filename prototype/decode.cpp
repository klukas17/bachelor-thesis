#include <stdlib.h>
#include <string>

#include "GrammaticalEvolution.h"

int main(int argc, char* argv[]) {
    int population_count = std::stoi(argv[1]);
    int codon_count = std::stoi(argv[2]);

    std::string grammar1, grammar2;
    grammar1 = "grammars/grammar1.bnf";
    grammar2 = "grammars/grammar2.bnf";

    Grammar* gram1 = new Grammar(grammar1);
    Grammar* gram2 = new Grammar(grammar2);

    for (int i = 0; i < population_count; i++) {

        std::stringstream ss;
        ss << i + 1;
        
        std::string file_name; 
        file_name += "solutions/";
        file_name += ss.str();
        file_name += ".txt";

        Unit* unit1 = new Unit(codon_count);
        Unit* unit2 = new Unit(codon_count);

        
    }
}