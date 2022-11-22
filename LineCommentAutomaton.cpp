//
// Created by chase on 9/19/2022.
//

#include "LineCommentAutomaton.h"

void LineCommentAutomaton::S0(const std::string& input) {
    if (input[index] == '#') {
        inputRead++;
        index++;
        S1(input);
    }
    else {
        Serr();
    }
}

void LineCommentAutomaton::S1(const std::string& input) {
    if (index >= input.size()) {
        // Do nothing
    }
    else if (input[index] == '\n') {
        // Do nothing
    }
    else {
        inputRead++;
        index++;
        S1(input);
    }
}