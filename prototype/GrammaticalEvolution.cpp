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

#include "GrammaticalEvolution.h"
#include "SymbolType.h"
#include "Unit.h"
#include "Symbol.h"
#include "Node.h"
#include "Grammar.h"

const int CODON_COUNT = 50;
const int POPULATION_SIZE = 20;
const int MAX_NUMBER_OF_WRAPPING = 5;
const std::string grammar_path = "grammars/gram04.bnf";

GrammaticalEvolution::GrammaticalEvolution() {
    grammar = new Grammar(grammar_path);
    for (int i = 0; i < POPULATION_SIZE; i++) {
        this->population.push_back(new Unit(CODON_COUNT));
    }
}

GrammaticalEvolution::~GrammaticalEvolution() {}

void GrammaticalEvolution::decode(Unit* unit) {
    Node* HEAD = new Node(Symbol(SymbolType::non_terminal, (*grammar).start_symbol));
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

        if (!(*grammar).productions.count(curr->symbol.value))
        {
            exit(1);
        }

        int count = (*grammar).productions[curr->symbol.value].size();
        int chosen_production_index = (*unit).genome[curr_codon] % count;
        std::vector<std::pair<std::string, SymbolType>> chosen_production = (*grammar).productions[curr->symbol.value][chosen_production_index];

        Node* first = NULL;
        Node* last = NULL;
                
        for (auto p : chosen_production)
        {
            if (!first)
            {
                first = new Node(Symbol(p.second, p.first));
                last = first;
            }
            else
            {
                Node* new_node = new Node(Symbol(p.second, p.first));
                last->next = new_node;
                last = new_node;
            }
        }

        if (!first) {
            if (prev)
                prev->next = curr->next;
            else
                        HEAD = curr->next;

            auto tmp = curr->next;
            (*curr).~Node();
            curr = tmp;   
        }

        else {
            if (prev)
                prev->next = first;
            else
                HEAD = first;

            last->next = curr->next;

            (*curr).~Node();
            curr = first;
        }

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

void GrammaticalEvolution::print_sequence(Node* curr) {
    if (curr) {
        std::cout << curr->symbol.value;
        print_sequence(curr->next);
    }
    else
        return;
}