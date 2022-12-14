//
// Created by chase on 9/16/2022.
//

#ifndef CS236_PROJECT_1_QUERIESAUTOMATON_H
#define CS236_PROJECT_1_QUERIESAUTOMATON_H

#include "Automaton.h"

class QueriesAutomaton : public Automaton
{
private:
    void S1(const std::string& input);
    void S2(const std::string& input);
    void S3(const std::string& input);
    void S4(const std::string& input);
    void S5(const std::string& input);
    void S6(const std::string& input);
public:
    QueriesAutomaton() : Automaton(TokenType::QUERIES) {}  // Call the base constructor

    void S0(const std::string& input);
};

#endif //CS236_PROJECT_1_QUERIESAUTOMATON_H
