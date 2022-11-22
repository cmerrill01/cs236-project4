//
// Created by chase on 9/16/2022.
//

#ifndef CS236_PROJECT_1_LEFTPARENAUTOMATON_H
#define CS236_PROJECT_1_LEFTPARENAUTOMATON_H

#include "Automaton.h"

class LeftParenAutomaton : public Automaton
{
public:
    LeftParenAutomaton() : Automaton(TokenType::LEFT_PAREN) {}  // Call the base constructor

    void S0(const std::string& input);
};

#endif //CS236_PROJECT_1_LEFTPARENAUTOMATON_H
