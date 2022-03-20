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
#include "SymbolType.h"
#include "GrammarParsingState.h"

Grammar::Grammar(std::string grammar_path)
{
    std::string file_name(grammar_path);
    FILE *grammar_file = fopen(file_name.c_str(), "r");

    GrammarParsingState state = GrammarParsingState::start;
    char c;
    std::stringstream stream;
    std::string left_side_symbol;
    std::vector<std::vector<std::pair<std::string, SymbolType>>> right_sides;
    std::vector<std::pair<std::string, SymbolType>> right_side;
    std::string temp_string;

    while (true) {

        c = fgetc(grammar_file);
        if (c == EOF)
        {
            state = GrammarParsingState::end;
        }

        switch(state) {

            case GrammarParsingState::start:
                if (c == '<')
                {
                    stream << c;
                    state = GrammarParsingState::new_symbol;
                }
                else 
                    exit(1);
                break;

            case GrammarParsingState::new_symbol:
                stream << c;
                if (c == '>')
                {
                    state = GrammarParsingState::is_one;
                    left_side_symbol = stream.str();
                    if (start_symbol == "")
                        start_symbol = left_side_symbol;
                    stream.str("");
                }
                break;

            case GrammarParsingState::is_one:
                if (c == ' ' || c == '\t')
                    continue;
                if (c == ':')
                    state = GrammarParsingState::is_two;
                else
                    exit(1);
                break;

            case GrammarParsingState::is_two:
                if (c == ':')
                    state = GrammarParsingState::is_three;
                else
                    exit(1);
                break;

            case GrammarParsingState::is_three:
                if (c == '=')
                    state = GrammarParsingState::right_side;
                else
                    exit(1);
                break;

            case GrammarParsingState::right_side:
                if (c == ' ' || c == '\t')
                    continue;
                else if (c == '|')
                {
                    right_sides.push_back(right_side);
                    right_side.clear();
                    state = GrammarParsingState::right_side;
                }
                else if (c == '\n')
                {
                    state = GrammarParsingState::potential_break;
                }
                else if (c == '\'')
                {
                    state = GrammarParsingState::single_quotes;
                }
                else if (c == '"')
                {
                    state = GrammarParsingState::double_quotes;
                }
                else if (c != '<') 
                {
                    temp_string = std::string(1, c);
                    right_side.push_back({temp_string, SymbolType::terminal});
                }
                else 
                {
                    state = GrammarParsingState::right_side_state;
                    stream << c;
                }
                break;

            case GrammarParsingState::right_side_state:
                stream << c;
                if (c == '>')
                {
                    state = GrammarParsingState::right_side;
                    temp_string = stream.str();
                    stream.str("");
                    right_side.push_back({temp_string, SymbolType::non_terminal});
                }
                break;

            case GrammarParsingState::end:
            case GrammarParsingState::potential_break:
                if (c == '<' || c == EOF)
                {
                    stream << c;
                    state = GrammarParsingState::new_symbol;
                    right_sides.push_back(right_side);
                    right_side.clear();
                    if (productions.count(left_side_symbol))
                    {
                        productions[left_side_symbol].insert(productions[left_side_symbol].end(), right_sides.begin(), right_sides.end());
                    }
                    else
                        productions[left_side_symbol] = right_sides;
                    right_sides.clear();
                }
                else
                {
                    state = GrammarParsingState::right_side;
                }
                break;

            case GrammarParsingState::single_quotes:
                if (c == '\'')
                {
                    temp_string = stream.str();
                    stream.str("");
                    right_side.push_back({temp_string, SymbolType::terminal});
                    state = GrammarParsingState::right_side;
                }
                else
                    stream << c;
                break;

            case GrammarParsingState::double_quotes:
                if (c == '"')
                {
                    temp_string = stream.str();
                    stream.str("");
                    right_side.push_back({temp_string, SymbolType::terminal});
                    state = GrammarParsingState::right_side;
                }
                else
                    stream << c;
                break;
        }

        if (c == EOF)
            break;
    }

    fclose(grammar_file);
}

Grammar::~Grammar(){}