#include "Symbol.h"

Symbol::Symbol(SymbolType t, std::string v){
    this->type = t;
    this->value = v;
}
Symbol::Symbol() {}
Symbol::~Symbol() {}