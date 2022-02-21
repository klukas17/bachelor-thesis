#include <stdlib.h>
#include <time.h>
#include <vector>
#include <iostream>
#include <string>
#include <map>
#include <iostream>
#include <fstream> 
#include <sstream>
#include <utility>

const int CODON_COUNT = 50;
const int POPULATION_SIZE = 20;
const std::string grammar_path = "grammars/gram02.bnf";

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
        
        std::string start_symbol;
        std::map<std::string, std::vector<std::vector<std::pair<std::string, int>>>> productions;
        
        Grammar()
        {
            std::string file_name(grammar_path);
            FILE *grammar_file = fopen(file_name.c_str(), "r");

            GrammarParsingState state = GrammarParsingState::start;
            char c;
            std::stringstream stream;
            std::string left_side_symbol;
            std::vector<std::vector<std::pair<std::string, int>>> right_sides;
            std::vector<std::pair<std::string, int>> right_side;
            std::string temp_string;

            while (true) {

                c = fgetc(grammar_file);
                if (c == EOF)
                {
                    state = GrammarParsingState::end;
                }

                switch(state) {

                    case GrammarParsingState::start:
                        if (c == '<')
                        {
                            stream << c;
                            state = GrammarParsingState::new_symbol;
                        }
                        else 
                            exit(1);
                        break;

                    case GrammarParsingState::new_symbol:
                        stream << c;
                        if (c == '>')
                        {
                            state = GrammarParsingState::is_one;
                            left_side_symbol = stream.str();
                            if (start_symbol == "")
                                start_symbol = left_side_symbol;
                            stream.str("");
                        }
                        break;

                    case GrammarParsingState::is_one:
                        if (c == ' ' || c == '\t')
                            continue;
                        if (c == ':')
                            state = GrammarParsingState::is_two;
                        else
                            exit(1);
                        break;

                    case GrammarParsingState::is_two:
                        if (c == ':')
                            state = GrammarParsingState::is_three;
                        else
                            exit(1);
                        break;

                    case GrammarParsingState::is_three:
                        if (c == '=')
                            state = GrammarParsingState::right_side;
                        else
                            exit(1);
                        break;

                    case GrammarParsingState::right_side:
                        if (c == ' ' || c == '\t')
                            continue;
                        if (c == '|')
                        {
                            right_sides.push_back(right_side);
                            right_side.clear();
                            state = GrammarParsingState::right_side;
                        }
                        else if (c == '\n')
                        {
                            state = GrammarParsingState::potential_break;
                        }
                        else if (c != '<') 
                        {
                            temp_string = std::string(1, c);
                            right_side.push_back(std::pair<std::string, int>{temp_string, 0});
                        }
                        else 
                        {
                            state = GrammarParsingState::right_side_state;
                            stream << c;
                        }
                        break;

                    case GrammarParsingState::right_side_state:
                        stream << c;
                        if (c == '>')
                        {
                            state = GrammarParsingState::right_side;
                            temp_string = stream.str();
                            stream.str("");
                            right_side.push_back(std::pair<std::string, int>{temp_string, 1});
                        }
                        break;

                    case GrammarParsingState::end:
                    case GrammarParsingState::potential_break:
                        if (c == '<' || c == EOF)
                        {
                            stream << c;
                            state = GrammarParsingState::new_symbol;
                            right_sides.push_back(right_side);
                            right_side.clear();
                            if (productions.count(left_side_symbol))
                            {
                                productions[left_side_symbol].insert(productions[left_side_symbol].end(), right_sides.begin(), right_sides.end());
                            }
                            else
                                productions[left_side_symbol] = right_sides;
                            right_sides.clear();
                        }
                        else
                        {
                            state = GrammarParsingState::right_side;
                        }
                        break;
                }

                if (c == EOF)
                    break;
            }

            fclose(grammar_file);
        }
        ~Grammar(){}

    enum GrammarParsingState 
    {
        start, new_symbol, is_one, is_two, is_three, right_side, right_side_state, potential_break, end
    };

    enum SymbolType
    {
        terminal, non_terminal
    };
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
        Grammar grammar;

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

    std::string file_name(grammar_path);
    FILE *grammar_file = fopen(file_name.c_str(), "r");

    char c;
    while ((c = fgetc(grammar_file)) != EOF)
        std::cout << c;

    fclose(grammar_file);
}

/* TODO:
    parametrize pairs in Grammar with SymbolType, not int
    set start_state in Grammar
*/