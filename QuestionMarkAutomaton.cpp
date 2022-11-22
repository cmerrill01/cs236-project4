//
// Created by chase on 9/16/2022.
//

#include "QuestionMarkAutomaton.h"

void QuestionMarkAutomaton::S0(const std::string& input) {
    if (input[index] == '?') {
        inputRead = 1;
    }
    else {
        Serr();
    }
}