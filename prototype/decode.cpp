#include <stdlib.h>
#include <string>
#include <fstream>

#include "GrammaticalEvolution.h"

int main(int argc, char* argv[]) {
    int population_count = std::stoi(argv[1]);
    int codon_count = std::stoi(argv[2]);
    int max_number_of_wrapping = std::stoi(argv[3]);

    std::string grammar1, grammar2;
    grammar1 = "grammars/grammar1.bnf";
    grammar2 = "grammars/grammar2.bnf";

    GrammaticalEvolution* ge1 = new GrammaticalEvolution(grammar1, max_number_of_wrapping);
    GrammaticalEvolution* ge2 = new GrammaticalEvolution(grammar2, max_number_of_wrapping);

    for (int i = 0; i < population_count; i++) {

        std::stringstream ss;
        ss << i + 1;
        
        std::string file_name; 
        file_name += "solutions/";
        file_name += ss.str();
        file_name += ".txt";

        Unit* unit1 = new Unit(codon_count);
        Unit* unit2 = new Unit(codon_count);

        std::ifstream input(file_name);
        std::string line;

        std::vector<unsigned char> v1, v2;

        std::istringstream iss;
        std::string s;

        getline(input, line);
        iss = std::istringstream(line);
        while (getline(iss, s, ' ')) v1.push_back(std::stoi(s));
        getline(input, line);
        iss = std::istringstream(line);
        while (getline(iss, s, ' ')) v2.push_back(std::stoi(s));

        unit1->genome = v1;
        unit2->genome = v2;

        std::cout << "int f" << i << "(GEStrategy* s) {" << std::endl;
        std::cout << "\t" << "int iterations = 0;" << std::endl;
        std::cout << "\t" << "int frame = 0;" << std::endl;
        std::cout << "\t" << ge1->decode(unit1) << std::endl;
        std::cout << "\t" << "return frame;" << std::endl;
        std::cout << "}" << std::endl;

        std::cout << "void g" << i << "(GEStrategy* s) {" << std::endl;
        std::cout << "\t" << "int iterations = 0;" << std::endl;
        std::cout << "\t" << ge2->decode(unit2) << std::endl;
        std::cout << "}" << std::endl;
    }
}