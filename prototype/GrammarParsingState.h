#pragma once

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