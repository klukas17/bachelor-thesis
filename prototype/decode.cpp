#include <stdlib.h>
#include <string>
#include <fstream>

#include "GrammaticalEvolution.h"
#include "DecodeException.h"

int main(int argc, char* argv[]) {
    int population_count = std::stoi(argv[1]);
    int codon_count = std::stoi(argv[2]);
    int max_number_of_wrapping = std::stoi(argv[3]);

    std::string grammar;
    grammar = "grammars/grammar.bnf";

    GrammaticalEvolution* ge = new GrammaticalEvolution(grammar, max_number_of_wrapping);

    std::vector<int> blacklisted;

    //std::cerr << "READ GEN:" << std::endl;

    for (int i = 0; i < population_count; i++) {

        std::stringstream ss;
        ss << i;
        
        std::string file_name; 
        file_name += "solutions/";
        file_name += ss.str();
        file_name += ".txt";

        Unit* unit = new Unit(codon_count);

        std::ifstream input(file_name);
        std::string l;

        std::vector<unsigned char> v;

        std::istringstream iss;
        std::string s;

        getline(input, l);
        iss = std::istringstream(l);
        while (getline(iss, s, ' ')) v.push_back(std::stoi(s));

        //std::cerr << i + 1 << ":\t\t";
        //for (int j = 0; j < v.size(); j++) {
        //    std::cerr << (unsigned int) v[j] << " ";
        //}
        //std::cerr << std::endl;

        unit->genome = v;
        std::string decoded;
        try {
            decoded = ge->decode(unit);
        }
        catch (const DecodeException& d) {
            decoded = "";
            blacklisted.push_back(i);
        }
        if (decoded.find("frame=") == std::string::npos || 
            decoded.find("frame=s->time;") != std::string::npos ||
            decoded.find("frame=s->page_request;") != std::string::npos)
            blacklisted.push_back(i);
        std::cout << "int f" << i << "(GEStrategy* s) {" << std::endl;
        std::cout << "\t" << "int iterations = 0;" << std::endl;
        std::cout << "\t" << "int frame = 0;" << std::endl;
        std::cout << "\t" << decoded << std::endl;
        std::cout << "\t" << "if (frame < 0 || frame >= s->frame_count) frame = 0;" << std::endl;
        std::cout << "\t" << "return frame;" << std::endl;
        std::cout << "}" << std::endl;
    }

    std::ofstream blacklisted_file("solutions/blacklisted.txt");
    for (int i : blacklisted) blacklisted_file << i << " ";
    blacklisted_file << std::endl;
    blacklisted_file.close();
}