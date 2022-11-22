#include "Lexer.h"
#include "ColonAutomaton.h"
#include "ColonDashAutomaton.h"
#include "CommaAutomaton.h"
#include "PeriodAutomaton.h"
#include "QuestionMarkAutomaton.h"
#include "LeftParenAutomaton.h"
#include "RightParenAutomaton.h"
#include "MultiplyAutomaton.h"
#include "AddAutomaton.h"
#include "SchemesAutomaton.h"
#include "FactsAutomaton.h"
#include "RulesAutomaton.h"
#include "QueriesAutomaton.h"
#include "StringAutomaton.h"
#include "LineCommentAutomaton.h"
#include "BlockCommentAutomaton.h"
#include "IdAutomaton.h"
#include "UndefinedAutomaton.h"
#include <iostream>
#include <cctype>

Lexer::Lexer() {
    CreateAutomata();
}

Lexer::~Lexer() {
    for (unsigned int i = 0; i < automata.size(); i++) {
        delete automata.at(i);
    }
    for (unsigned int i = 0; i < tokens.size(); i++) {
        delete tokens.at(i);
    }
}

void Lexer::CreateAutomata() {
    automata.push_back(new ColonAutomaton());
    automata.push_back(new ColonDashAutomaton());
    automata.push_back(new CommaAutomaton());
    automata.push_back(new PeriodAutomaton());
    automata.push_back(new QuestionMarkAutomaton());
    automata.push_back(new LeftParenAutomaton());
    automata.push_back(new RightParenAutomaton());
    automata.push_back(new MultiplyAutomaton());
    automata.push_back(new AddAutomaton());
    automata.push_back(new IdAutomaton());
    automata.push_back(new SchemesAutomaton());
    automata.push_back(new FactsAutomaton());
    automata.push_back(new RulesAutomaton());
    automata.push_back(new QueriesAutomaton());
    automata.push_back(new StringAutomaton());
    automata.push_back(new LineCommentAutomaton());
    automata.push_back(new BlockCommentAutomaton());
    automata.push_back(new UndefinedAutomaton());
}

void Lexer::Run(std::string& input) {
    // std::cout << input << std::endl;

    /*
    set lineNumber to 1
     // While there are more characters to tokenize
        // Here is the "Parallel" part of the algorithm
        //   Each automaton runs with the same input
        foreach automaton in automata {
            inputRead = automaton.Start(input)
            if (inputRead > maxRead) {
                set maxRead to inputRead
                set maxAutomaton to automaton
            }
    }
     loop while input.size() > 0 {
        set maxRead to 0
        set maxAutomaton to the first automaton in automata

     */
    int lineNumber = 1;
    while (!input.empty()) {
        while (isspace(input.at(0))) {
            if (input.at(0) == '\n') lineNumber++;
            input = input.substr(1);
            if (input.size() == 0) break;
        }
        if (input.size() == 0) break;
        int maxRead = 0;
        Automaton* maxAutomaton = automata.at(0);
        for (unsigned int i = 0; i < automata.size(); i++) {
            int inputRead = automata.at(i)->Start(input);
            if (inputRead >= maxRead) {
                maxRead = inputRead;
                maxAutomaton = automata.at(i);
            }
        }
        if (maxRead > 0) {
            Token* newToken = maxAutomaton->CreateToken(input.substr(0,maxRead),lineNumber);
            lineNumber += maxAutomaton->NewLinesRead();
            tokens.push_back(newToken);
            input.erase(input.begin(),input.begin()+maxRead);
            while (!input.empty() && isspace(input.at(0))) {
                if (input.at(0) == '\n') lineNumber++;
                input = input.substr(1);
            }
        }
        else {
            maxRead = 1;
            Token* newToken = new Token(UNDEFINED,input.substr(0,1 ),lineNumber);
            tokens.push_back(newToken);
            input.erase(input.begin(),input.begin()+maxRead);
        }
    }
    Token* newToken = new Token(END_OF_FILE,"",lineNumber);
    tokens.push_back(newToken);
    /*
        // TODO: you need to handle whitespace in between tokens

        // Here is the "Max" part of the algorithm
        if maxRead > 0 {
            set newToken to maxAutomaton.CreateToken(...)
                increment lineNumber by maxAutomaton.NewLinesRead()
                add newToken to collection of all tokens
        }
        // No automaton accepted input
        // Create single character undefined token
        else {
            set maxRead to 1
                set newToken to a  new undefined Token
                (with first character of input)
                add newToken to collection of all tokens
        }
        // Update `input` by removing characters read to create Token
        remove maxRead characters from input
    }
    add end of file token to all tokens
    */
}

std::string Lexer::ToString() {
    std::stringstream ss;
    for (unsigned int i = 0; i < tokens.size(); i++) {
        ss << tokens.at(i)->ToString();
    }
    ss << "Total Tokens = " << tokens.size() << std::endl;
    return ss.str();
}