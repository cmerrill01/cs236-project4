#ifndef TOKEN_H
#define TOKEN_H
#include <string>
#include <iostream>
#include <sstream>

enum TokenType {
    COMMA,
    PERIOD,
    Q_MARK,
    LEFT_PAREN,
    RIGHT_PAREN,
    COLON,
    COLON_DASH,
    MULTIPLY,
    ADD,
    SCHEMES,
    FACTS,
    RULES,
    QUERIES,
    STRING,
    COMMENT,
    ID,
    END_OF_FILE,
    UNDEFINED
};

class Token
{
private:
    TokenType type;
    std::string description;
    int line;
    std::string TypeToString();

public:
    Token(TokenType type, std::string description, int line) : type(type), description(description), line(line) {}
    TokenType GetType() { return type; }
    std::string ToString();
    std::string GetDescription() { return description; }
};

#endif // TOKEN_H

