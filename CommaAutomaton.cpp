//
// Created by chase on 9/16/2022.
//

#include "CommaAutomaton.h"

void CommaAutomaton::S0(const std::string& input) {
    if (input[index] == ',') {
        inputRead = 1;
    }
    else {
        Serr();
    }
}