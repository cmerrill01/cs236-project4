//
// Created by chase on 9/16/2022.
//

#ifndef CS236_PROJECT_1_QUESTIONMARKAUTOMATON_H
#define CS236_PROJECT_1_QUESTIONMARKAUTOMATON_H

#include "Automaton.h"

class QuestionMarkAutomaton : public Automaton
{
public:
    QuestionMarkAutomaton() : Automaton(TokenType::Q_MARK) {}  // Call the base constructor

    void S0(const std::string& input);
};


#endif //CS236_PROJECT_1_QUESTIONMARKAUTOMATON_H
