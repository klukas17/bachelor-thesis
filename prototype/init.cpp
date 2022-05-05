#include <stdlib.h>
#include <fstream>
#include <sstream>
#include <iostream>

#include "Unit.h"

int main(int argc, char* argv[]) {

    srand(time(NULL));

    int population_count = std::stoi(argv[1]);
    int codon_count = std::stoi(argv[2]);

    for (int i = 0; i < population_count; i++) {
        Unit* unit = new Unit(codon_count);

        std::stringstream ss;
        ss << i;
        
        std::string file_name; 
        file_name += "solutions/";
        file_name += ss.str();
        file_name += ".txt";
        
        std::ofstream f;
        f.open(file_name);

        for (int i = 0; i < codon_count; i++) f << (int) unit->genome[i] << " ";
        f << std::endl;
        f.close();
    }
}