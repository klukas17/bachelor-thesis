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

        std::vector<Unit> population;
        Grammar* grammar;

        GrammaticalEvolution();
        ~GrammaticalEvolution();

        void decode(Unit unit);

        void print_sequence(Node* curr);
};