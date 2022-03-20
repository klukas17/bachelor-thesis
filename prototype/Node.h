#pragma once

#include "Symbol.h"

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