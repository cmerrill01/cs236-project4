//
// Created by chase on 9/16/2022.
//

#include "Token.h"
#include <sstream>

std::string Token::TypeToString() {
    switch (type) {
        case COMMA:
            return "COMMA";
        case PERIOD:
            return "PERIOD";
        case Q_MARK:
            return "Q_MARK";
        case LEFT_PAREN:
            return "LEFT_PAREN";
        case RIGHT_PAREN:
            return "RIGHT_PAREN";
        case COLON:
            return "COLON";
        case COLON_DASH:
            return "COLON_DASH";
        case MULTIPLY:
            return "MULTIPLY";
        case ADD:
            return "ADD";
        case SCHEMES:
            return "SCHEMES";
        case FACTS:
            return "FACTS";
        case RULES:
            return "RULES";
        case QUERIES:
            return "QUERIES";
        case STRING:
            return "STRING";
        case COMMENT:
            return "COMMENT";
        case ID:
            return "ID";
        case END_OF_FILE:
            return "EOF";
        default:
            return "UNDEFINED";
    }
}

std::string Token::ToString() {
    std::stringstream ss;
    ss << "(" << this->TypeToString() << ",";
    ss << "\"" << description << "\",";
    ss << line << ")" << std::endl;
    return ss.str();
}