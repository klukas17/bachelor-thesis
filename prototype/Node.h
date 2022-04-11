#pragma once

#include "Symbol.h"
#include <stdlib.h>

class Node
{
    public:
        Symbol symbol;
        Node* next;

        Node(Symbol s);
        ~Node();
};