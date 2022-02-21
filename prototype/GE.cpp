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
const int MAX_NUMBER_OF_WRAPPING = 5;
const std::string grammar_path = "grammars/gram04.bnf";

class Unit
{
    public:

        unsigned char genome[CODON_COUNT];

        Unit()
        {
            for (int i = 0; i < CODON_COUNT; i++)
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
                        else if (c == '|')
                        {
                            right_sides.push_back(right_side);
                            right_side.clear();
                            state = GrammarParsingState::right_side;
                        }
                        else if (c == '\n')
                        {
                            state = GrammarParsingState::potential_break;
                        }
                        else if (c == '\'')
                        {
                            state = GrammarParsingState::single_quotes;
                        }
                        else if (c == '"')
                        {
                            state = GrammarParsingState::double_quotes;
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

                    case GrammarParsingState::single_quotes:
                        if (c == '\'')
                        {
                            temp_string = stream.str();
                            stream.str("");
                            right_side.push_back(std::pair<std::string, int>{temp_string, 0});
                            state = GrammarParsingState::right_side;
                        }
                        else
                            stream << c;
                        break;

                    case GrammarParsingState::double_quotes:
                        if (c == '"')
                        {
                            temp_string = stream.str();
                            stream.str("");
                            right_side.push_back(std::pair<std::string, int>{temp_string, 0});
                            state = GrammarParsingState::right_side;
                        }
                        else
                            stream << c;
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
        start, 
        new_symbol, 
        is_one, 
        is_two, 
        is_three, 
        right_side, 
        right_side_state, 
        potential_break, 
        end, 
        single_quotes, 
        double_quotes
    };

};

enum SymbolType
{
    terminal, 
    non_terminal
};

class Symbol
{
    public:

        SymbolType type;
        std::string value;

        Symbol(SymbolType type, std::string value){
            this->type = type;
            this->value = value;
        }
        Symbol(){}
        ~Symbol(){}
};

class Node
{
    public:
        Symbol symbol;
        Node* next;

        Node(Symbol symbol)
        {
            this->symbol = symbol;
            this->next = NULL;
        }
        ~Node(){}
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
                this->population.push_back(Unit());
            }
        }
        ~GrammaticalEvolution(){}

        void decode(Unit unit)
        {
            Node* HEAD = new Node(Symbol(SymbolType::non_terminal, grammar.start_symbol));
            Node* curr = HEAD;
            Node* prev = NULL;

            int wrap_count = 0;
            int curr_codon = 0;

            print_sequence(curr);
            std::cout << std::endl;

            while (curr)
            {
                if (curr->symbol.type == SymbolType::terminal)
                {
                    prev = curr;
                    curr = curr->next;
                    continue;
                }

                if (!grammar.productions.count(curr->symbol.value))
                {
                    exit(1);
                }

                int count = grammar.productions[curr->symbol.value].size();
                int chosen_production_index = unit.genome[curr_codon] % count;
                std::vector<std::pair<std::string, int>>* chosen_production = &grammar.productions[curr->symbol.value][chosen_production_index];

                Node* first = NULL;
                Node* last = NULL;
                
                for (std::pair<std::string, int> p : *chosen_production)
                {
                    if (!first)
                    {
                        // TODO : merge if-else into one command
                        if (p.second == 1)
                        {
                            first = new Node(Symbol(SymbolType::non_terminal, p.first));
                        }
                        else
                        {
                            first = new Node(Symbol(SymbolType::terminal, p.first));
                        }

                        last = first;
                    }
                    else
                    {
                        Node* new_node = NULL;
                        // TODO : merge if-else into one command
                        if (p.second == 1)
                        {
                            new_node = new Node(Symbol(SymbolType::non_terminal, p.first));
                        }
                        else
                        {
                            new_node = new Node(Symbol(SymbolType::terminal, p.first));
                        }

                        last->next = new_node;
                        last = new_node;
                    }

                }

                if (prev)
                    prev->next = first;
                else
                    HEAD = first;

                last->next = curr->next;

                (*curr).~Node();
                curr = first;

                print_sequence(HEAD);
                std::cout << std::endl;

                curr_codon++;
                if (curr_codon == CODON_COUNT)
                {
                    curr_codon = 0;
                    wrap_count++;
                    if (wrap_count > MAX_NUMBER_OF_WRAPPING)
                        exit(1);
                }
            }
        }

        void print_sequence(Node* curr) {
            std::cout << curr->symbol.value;
            if (curr->next)
                print_sequence(curr->next);
        }
};


int main() 
{
    srand(time(0));
    GrammaticalEvolution GE = GrammaticalEvolution();
    GE.population[0].genome[0] = 2;
    GE.population[0].genome[1] = 1;
    GE.population[0].genome[2] = 1;
    GE.population[0].genome[3] = 0;
    GE.population[0].genome[4] = 0;
    GE.population[0].genome[5] = 0;
    GE.population[0].genome[6] = 1;
    GE.population[0].genome[7] = 1;
    GE.population[0].genome[8] = 1;
    GE.population[0].genome[9] = 2;
    GE.population[0].genome[10] = 0;
    GE.population[0].genome[11] = 0;
    GE.population[0].genome[12] = 0;
    GE.population[0].genome[13] = 0;
    GE.population[0].genome[14] = 0;
    GE.population[0].genome[15] = 1;
    GE.population[0].genome[16] = 1;
    GE.population[0].genome[17] = 0;
    GE.population[0].genome[18] = 0;
    GE.decode(GE.population[0]);
}

/* TODO:
    parametrize pairs in Grammar with SymbolType, not int
*/