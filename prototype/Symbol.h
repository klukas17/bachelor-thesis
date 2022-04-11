#pragma once

#include <string>
#include "SymbolType.h"

class Symbol
{
    public:

        SymbolType type;
        std::string value;

        Symbol(SymbolType t, std::string v);
        Symbol();
        ~Symbol();
};