//
// Created by chase on 9/19/2022.
//

#ifndef CS236_PROJECT_1_LINECOMMENTAUTOMATON_H
#define CS236_PROJECT_1_LINECOMMENTAUTOMATON_H

#include "Automaton.h"

class LineCommentAutomaton : public Automaton
{
private:
    void S1(const std::string& input);

public:
    LineCommentAutomaton() : Automaton(TokenType::COMMENT) {}  // Call the base constructor

    void S0(const std::string& input);
};

#endif //CS236_PROJECT_1_LINECOMMENTAUTOMATON_H
