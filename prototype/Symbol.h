#pragma once

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