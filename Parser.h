#ifndef CS236_PROJECT_1_PARSER_H
#define CS236_PROJECT_1_PARSER_H

#include "Token.h"
#include "DatalogProgram.h"
#include <vector>

class Parser
{
private:
    DatalogProgram program;

    std::vector<Token> tokens;
    bool Match(Token inputToken, TokenType matchType) {
        if (inputToken.GetType() == matchType) { return true; }
        else { return false; }
    }

    void parseDatalogProgram(unsigned int& index);
    Predicate parseScheme(unsigned int& index);
    std::vector<Predicate> parseSchemeList(unsigned int& index);
    Predicate parseFact(unsigned int& index);
    std::vector<Predicate> parseFactList(unsigned int& index);
    Rule parseRule(unsigned int& index);
    std::vector<Rule> parseRuleList(unsigned int& index);
    Predicate parseQuery(unsigned int& index);
    std::vector<Predicate> parseQueryList(unsigned int& index);
    Predicate parseHeadPredicate(unsigned int& index);
    Predicate parsePredicate(unsigned int& index);
    std::vector<Predicate> parsePredicateList(unsigned int& index);
    Parameter parseParameter(unsigned int& index);
    std::vector<Parameter> parseParameterList(unsigned int& index);
    std::vector<Parameter> parseStringList(unsigned int& index);
    std::vector<Parameter> parseIdList(unsigned int& index);

public:
    Parser(std::vector<Token*> input);
    ~Parser();
    DatalogProgram Parse();
    std::string ToString();
};

#endif //CS236_PROJECT_1_PARSER_H
