#include <stdlib.h>
#include <time.h>
#include <vector>
#include <iostream>
#include <string>
#include <map>
#include <iostream>
#include <fstream> 

const int CODON_COUNT = 50;
const int POPULATION_SIZE = 20;

class Unit
{
    public:

        char genome[CODON_COUNT];
        int size;

        Unit(int size)
        {
            this->size = size;
            for (int i = 0; i < this->size; i++)
            {
                this->genome[i] = rand();
            }
        }
        ~Unit(){}
};

class Grammar
    {
    public:
        
        std::string start_state;
        std::map<std::string, std::vector<std::vector<std::string>>> productions;
        
        Grammar(){}
        ~Grammar(){}
};

class Symbol
{
    public:

        int type;
        std::string value;

        Symbol(){}
        ~Symbol(){}
};

class GrammaticalEvolution
{
    public:

        std::vector<Unit> population;

        GrammaticalEvolution()
        {
            for (int i = 0; i < POPULATION_SIZE; i++)
            {
                this->population.push_back(Unit(CODON_COUNT));
            }
        }
        ~GrammaticalEvolution(){}
};

int main() 
{
    srand(time(0));
    GrammaticalEvolution GE = GrammaticalEvolution();
    char* arr = GE.population[0].genome;

    std::string file_name("grammars/gram01.bnf");
    FILE *grammar_file = fopen(file_name.c_str(), "r");

    char c;
    while ((c = fgetc(grammar_file)) != EOF)
        std::cout << c;

    fclose(grammar_file);
}