#pragma once

#include "SymbolType.h"

class Grammar
    {
    public:
        
        std::string start_symbol;
        std::map<std::string, std::vector<std::vector<std::pair<std::string, SymbolType>>>> productions;
        
        Grammar(std::string grammar_path);
        ~Grammar();
};