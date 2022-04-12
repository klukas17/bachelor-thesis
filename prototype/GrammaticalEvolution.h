#pragma once

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

#include "Grammar.h"
#include "Unit.h"
#include "Node.h"

class GrammaticalEvolution
{
    public:

        std::vector<Unit*> population;
        Grammar* grammar;
        std::string grammar_path;
        int max_number_of_wrapping;

        GrammaticalEvolution(std::string grammar_path, int m_n_o_w);
        ~GrammaticalEvolution();

        std::string decode(Unit* unit);

        void print_sequence(Node* curr);
};