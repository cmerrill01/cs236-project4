//
// Created by chase on 9/19/2022.
//

#include "IdAutomaton.h"

void IdAutomaton::S0(const std::string& input) {
    if (isalpha(input[index])) {
        inputRead++;
        index++;
        S1(input);
    }
    else {
        Serr();
    }
}

void IdAutomaton::S1(const std::string& input) {
    if (isalpha(input[index])) {
        inputRead++;
        index++;
        S1(input);
    }
    else if (std::isdigit(input[index])) {
        inputRead++;
        index++;
        S1(input);
    }
    else {
        // Do nothing
    }
}

void IdAutomaton::S2(const std::string& input) {
    if (input[index] == 'e') {
        inputRead++;
        index++;
        S3(input);
    }
    else {
        Serr();
    }
}

void IdAutomaton::S3(const std::string& input) {
    if (input[index] == 'r') {
        inputRead++;
        index++;
        S4(input);
    }
    else {
        Serr();
    }
}

void IdAutomaton::S4(const std::string& input) {
    if (input[index] == 'i') {
        inputRead++;
        index++;
        S5(input);
    }
    else {
        Serr();
    }
}

void IdAutomaton::S5(const std::string& input) {
    if (input[index] == 'e') {
        inputRead++;
        index++;
        S6(input);
    }
    else {
        Serr();
    }
}

void IdAutomaton::S6(const std::string& input) {
    if (input[index] == 's') {
        inputRead++;
    }
    else {
        Serr();
    }
}