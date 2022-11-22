#include "Parser.h"
#include "Parameter.h"
#include "Predicate.h"
#include "Rule.h"
#include <exception>

Parser::Parser(std::vector<Token *> input) {
    for (auto & i : input) {
        if (i->GetType() != COMMENT) { tokens.push_back(*i); }
    }
}

Parser::~Parser() = default;

void Parser::parseDatalogProgram(unsigned int& index) {
    // check if input is in FIRST set of SCHEMES
    if (Match(tokens.at(index), SCHEMES)) {
        index++;
    }
    else throw std::runtime_error("Syntax error");
    // check if input is in FIRST set of COLON
    if (Match(tokens.at(index),COLON)) {
        index++;
    }
    else throw std::runtime_error("Syntax error");
    // check if input is in FIRST set of scheme
    if (Match(tokens.at(index),ID)) {
        program.AddScheme(parseScheme(index));
    }
    else throw std::runtime_error("Syntax error");
    // check if input is in FIRST set of schemeList
    if (Match(tokens.at(index),ID)) {
        std::vector<Predicate> schemeList = parseSchemeList(index);
        for (auto & i : schemeList) {
            program.AddScheme(i);
        }
    }
    // check if input is in FOLLOW set of schemeList
    else if (Match(tokens.at(index),FACTS)) {
        // do nothing
    }
    else throw std::runtime_error("Syntax error");
    // check if input is in FIRST set of FACTS
    if (Match(tokens.at(index),FACTS)) {
        index++;
    }
    else throw std::runtime_error("Syntax error");
    // check if input is in FIRST set of COLON
    if (Match(tokens.at(index),COLON)) {
        index++;
    }
    else throw std::runtime_error("Syntax error");
    // check if input is in FIRST set of factList
    if (Match(tokens.at(index),ID)) {
        std::vector<Predicate> factList = parseFactList(index);
        for (auto & i : factList) {
            program.AddFact(i);
        }
    }
    // check if input is in FOLLOW set of factList
    else if (Match(tokens.at(index),RULES)) {
        // do nothing
    }
    else throw std::runtime_error("Syntax error");
    // check if input is in FIRST set of RULES
    if (Match(tokens.at(index),RULES)) {
        index++;
    }
    else throw std::runtime_error("Syntax error");
    // check if input is in FIRST set of COLON
    if (Match(tokens.at(index),COLON)) {
        index++;
    }
    else throw std::runtime_error("Syntax error");
    // check if input is in FIRST set of ruleList
    if (Match(tokens.at(index),ID)) {
        std::vector<Rule> ruleList = parseRuleList(index);
        for (auto & i : ruleList) {
            program.AddRule(i);
        }
    }
    // check if input is in FOLLOW set of ruleList
    else if (Match(tokens.at(index),QUERIES)) {
        // do nothing
    }
    else throw std::runtime_error("Syntax error");
    // check if input is in FIRST set of QUERIES
    if (Match(tokens.at(index),QUERIES)) {
        index++;
    }
    else throw std::runtime_error("Syntax error");
    // check if input is in FIRST set of COLON
    if (Match(tokens.at(index),COLON)) {
        index++;
    }
    else throw std::runtime_error("Syntax error");
    // check if input is in FIRST set of query
    if (Match(tokens.at(index),ID)) {
        program.AddQuery(parseQuery(index));
    }
    else throw std::runtime_error("Syntax error");
    // check if input is in FIRST set of queryList
    if (Match(tokens.at(index),ID)) {
        std::vector<Predicate> queryList = parseQueryList(index);
        for (auto & i : queryList) {
            program.AddQuery(i);
        }
    }
    // check if input is in FOLLOW set of queryList
    else if (Match(tokens.at(index),END_OF_FILE)) {
        // do nothing
    }
    else throw std::runtime_error("Syntax error");
    // check if input is in FIRST set of END_OF_FILE
    if (Match(tokens.at(index),END_OF_FILE)) {
        index++;
    }
    else throw std::runtime_error("Syntax error");
}

Predicate Parser::parseScheme(unsigned int& index) {
    std::string schemeId = "void";
    // check if input is in FIRST set of ID
    if (Match(tokens.at(index),ID)) {
        schemeId = tokens.at(index).GetDescription();
        index++;
    }
    else throw std::runtime_error("Syntax error");
    Predicate scheme(schemeId);
    // check if input is in FIRST set of LEFT_PAREN
    if (Match(tokens.at(index),LEFT_PAREN)) {
        index++;
    }
    else throw std::runtime_error("Syntax error");
    // check if input is in FIRST set of ID
    if (Match(tokens.at(index),ID)) {
        scheme.AddParameter(Parameter(tokens.at(index).GetDescription()));
        index++;
    }
    else throw std::runtime_error("Syntax error");
    // check if input is in FIRST set of parseIdList
    if (Match(tokens.at(index),COMMA)) {
        std::vector<Parameter> moreIds = parseIdList(index);
        for (auto & moreId : moreIds) {
            scheme.AddParameter(moreId);
        }
    }
    // check if input is in FOLLOW set of parseIdList
    else if (Match(tokens.at(index),RIGHT_PAREN)) {
        // do nothing
    }
    else throw std::runtime_error("Syntax error");
    // check if input is in FIRST set of RIGHT_PAREN
    if (Match(tokens.at(index),RIGHT_PAREN)) {
        index++;
    }
    else throw std::runtime_error("Syntax error");
    return scheme;
}

std::vector<Predicate> Parser::parseSchemeList(unsigned int& index) {
    std::vector<Predicate> schemeList;
    // check if input is in FIRST set of scheme
    if (Match(tokens.at(index),ID)) {
        schemeList.push_back(parseScheme(index));
    }
    else throw std::runtime_error("Syntax error");
    // check if input is in FIRST set of schemeList
    if (Match(tokens.at(index),ID)) {
        std::vector<Predicate> recurseSchemes = parseSchemeList(index);
        for (auto & recurseScheme : recurseSchemes) {
            schemeList.push_back(recurseScheme);
        }
    }
    // check if input is in FOLLOW set of schemeList
    else if (Match(tokens.at(index),FACTS)) {
        return schemeList;
    }
    else throw std::runtime_error("Syntax error");
    return schemeList;
}

Predicate Parser::parseFact(unsigned int& index) {
    std::string factId = "void";
    // check if input is in FIRST set of ID
    if (Match(tokens.at(index),ID)) {
        factId = tokens.at(index).GetDescription();
        index++;
    }
    else throw std::runtime_error("Syntax error");
    Predicate fact(factId);
    // check if input is in FIRST set of LEFT_PAREN
    if (Match(tokens.at(index),LEFT_PAREN)) {
        index++;
    }
    else throw std::runtime_error("Syntax error");
    // check if input is in FIRST set of STRING
    if (Match(tokens.at(index),STRING)) {
        fact.AddParameter(Parameter(tokens.at(index).GetDescription()));
        index++;
    }
    else throw std::runtime_error("Syntax error");
    // check if input is in FIRST set of stringList
    if (Match(tokens.at(index),COMMA)) {
        std::vector<Parameter> moreStrings = parseStringList(index);
        for (auto & moreString : moreStrings) {
            fact.AddParameter(moreString);
        }
    }
    // check if input is in FOLLOW set of stringList
    else if (Match(tokens.at(index),RIGHT_PAREN)) {
        // do nothing
    }
    else throw std::runtime_error("Syntax error");
    // check if input is in FIRST set of RIGHT_PAREN
    if (Match(tokens.at(index),RIGHT_PAREN)) {
        index++;
    }
    else throw std::runtime_error("Syntax error");
    // check if input is in FIRST set of PERIOD
    if (Match(tokens.at(index),PERIOD)) {
        index++;
    }
    else throw std::runtime_error("Syntax error");
    return fact;
}

std::vector<Predicate> Parser::parseFactList(unsigned int& index) {
    std::vector<Predicate> factList;
    // check if input is in FIRST set of fact
    if (Match(tokens.at(index),ID)) {
        factList.push_back(parseFact(index));
    }
    else throw std::runtime_error("Syntax error");
    // check if input is in FIRST set of factList
    if (Match(tokens.at(index),ID)) {
        std::vector<Predicate> recurseFacts = parseFactList(index);
        for (auto & recurseFact : recurseFacts) {
            factList.push_back(recurseFact);
        }
    }
    // check if input is in FOLLOW set of schemeList
    else if (Match(tokens.at(index),RULES)) {
        return factList;
    }
    else throw std::runtime_error("Syntax error");
    return factList;
}

Rule Parser::parseRule(unsigned int& index) {
    std::vector<Predicate> headPredicate;
    // check if input is in FIRST set of headPredicate
    if (Match(tokens.at(index),ID)) {
        headPredicate.push_back(parseHeadPredicate(index));
    }
    else throw std::runtime_error("Syntax error");
    Rule rule(headPredicate.at(0));
    // check if input is in FIRST set of COLON_DASH
    if (Match(tokens.at(index),COLON_DASH)) {
        index++;
    }
    else throw std::runtime_error("Syntax error");
    // check if input is in FIRST set of predicate
    if (Match(tokens.at(index),ID)) {
        rule.AddPredicate(parsePredicate(index));
    }
    else throw std::runtime_error("Syntax error");
    // check if input is in FIRST set of predicateList
    if (Match(tokens.at(index),COMMA)) {
        std::vector<Predicate> morePredicates = parsePredicateList(index);
        for (auto & morePredicate : morePredicates) {
            rule.AddPredicate(morePredicate);
        }
    }
    // check if input is in FOLLOW set of predicateList
    else if (Match(tokens.at(index),PERIOD)) {
        // do nothing
    }
    else throw std::runtime_error("Syntax error");
    // check if input is in FIRST set of PERIOD
    if (Match(tokens.at(index),PERIOD)) {
        index++;
    }
    else throw std::runtime_error("Syntax error");
    return rule;
}

std::vector<Rule> Parser::parseRuleList(unsigned int& index) {
    std::vector<Rule> ruleList;
    // check if input is in FIRST set of rule
    if (Match(tokens.at(index),ID)) {
        ruleList.push_back(parseRule(index));
    }
    else throw std::runtime_error("Syntax error");
    // check if input is in FIRST set of ruleList
    if (Match(tokens.at(index),ID)) {
        std::vector<Rule> recurseRules = parseRuleList(index);
        for (auto & recurseRule : recurseRules) {
            ruleList.push_back(recurseRule);
        }
    }
    // check if input is in FOLLOW set of ruleList
    else if (Match(tokens.at(index),QUERIES)) {
        return ruleList;
    }
    else throw std::runtime_error("Syntax error");
    return ruleList;
}

Predicate Parser::parseQuery(unsigned int& index) {
    std::vector<Predicate> query;
    // check if input is in FIRST set of predicate
    if (Match(tokens.at(index),ID)) {
        query.push_back(parsePredicate(index));
    }
    else throw std::runtime_error("Syntax error");
    // check if input is in FIRST set of Q_MARK
    if (Match(tokens.at(index),Q_MARK)) {
        index++;
    }
    else throw std::runtime_error("Syntax error");
    return query.at(0);
}

std::vector<Predicate> Parser::parseQueryList(unsigned int& index) {
    std::vector<Predicate> queryList;
    // check if input is in FIRST set of query
    if (Match(tokens.at(index),ID)) {
        queryList.push_back(parseQuery(index));
    }
    else throw std::runtime_error("Syntax error");
    // check if input is in FIRST set of queryList
    if (Match(tokens.at(index),ID)) {
        std::vector<Predicate> recurseQueries = parseQueryList(index);
        for (auto & recurseQuery : recurseQueries) {
            queryList.push_back(recurseQuery);
        }
    }
    // check if input is in FOLLOW set of queryList
    else if (Match(tokens.at(index),END_OF_FILE)) {
        return queryList;
    }
    else throw std::runtime_error("Syntax error");
    return queryList;
}

Predicate Parser::parseHeadPredicate(unsigned int& index) {
    std::string predicateId = "void";
    // check if input is in FIRST set of ID
    if (Match(tokens.at(index),ID)) {
        predicateId = tokens.at(index).GetDescription();
        index++;
    }
    else throw std::runtime_error("Syntax error");
    Predicate headPredicate(predicateId);
    // check if input is in FIRST set of LEFT_PAREN
    if (Match(tokens.at(index),LEFT_PAREN)) {
        index++;
    }
    else throw std::runtime_error("Syntax error");
    // check if input is in FIRST set of ID
    if (Match(tokens.at(index),ID)) {
        headPredicate.AddParameter(Parameter(tokens.at(index).GetDescription()));
        index++;
    }
    else throw std::runtime_error("Syntax error");
    // check if input is in FIRST set of parseIdList
    if (Match(tokens.at(index),COMMA)) {
        std::vector<Parameter> moreIds = parseIdList(index);
        for (auto & moreId : moreIds) {
            headPredicate.AddParameter(moreId);
        }
    }
    // check if input is in FOLLOW set of parseIdList
    else if (Match(tokens.at(index),RIGHT_PAREN)) {
        // do nothing
    }
    else throw std::runtime_error("Syntax error");
    // check if input is in FIRST set of RIGHT_PAREN
    if (Match(tokens.at(index),RIGHT_PAREN)) {
        index++;
    }
    else throw std::runtime_error("Syntax error");
    return headPredicate;
}

Predicate Parser::parsePredicate(unsigned int& index) {
    std::string predicateId = "void";
    // check if input is in FIRST set of ID
    if (Match(tokens.at(index),ID)) {
        predicateId = tokens.at(index).GetDescription();
        index++;
    }
    else throw std::runtime_error("Syntax error");
    Predicate pred(predicateId);
    // check if input is in FIRST set of LEFT_PAREN
    if (Match(tokens.at(index),LEFT_PAREN)) {
        index++;
    }
    else throw std::runtime_error("Syntax error");
    // check if input is in FIRST set of parameter
    if (Match(tokens.at(index),ID) || Match(tokens.at(index),STRING)) {
        pred.AddParameter(parseParameter(index));
    }
    else throw std::runtime_error("Syntax error");
    // check if input is in FIRST set of parameterList
    if (Match(tokens.at(index),COMMA)) {
        std::vector<Parameter> moreParameters = parseParameterList(index);
        for (auto & moreParameter : moreParameters) {
            pred.AddParameter(moreParameter);
        }
    }
    // check if input is in FOLLOW set of parameterList
    else if (Match(tokens.at(index),RIGHT_PAREN)) {
        // do nothing
    }
    else throw std::runtime_error("Syntax error");
    // check if input is in FIRST set of RIGHT_PAREN
    if (Match(tokens.at(index),RIGHT_PAREN)) {
        index++;
    }
    else throw std::runtime_error("Syntax error");
    return pred;
}

std::vector<Predicate> Parser::parsePredicateList(unsigned int& index) {
    std::vector<Predicate> predicates;
    // check if input is in FIRST set of COMMA
    if (Match(tokens.at(index),COMMA)) {
        index++;
    }
    else throw std::runtime_error("Syntax error");
    // check if input is in FIRST set of predicate
    if (Match(tokens.at(index),ID)) {
        predicates.push_back(parsePredicate(index));
    }
    else throw std::runtime_error("Syntax error");
    // check if input is in FIRST set of predicateList
    if (Match(tokens.at(index),COMMA)) {
        std::vector<Predicate> recursePredicates = parsePredicateList(index);
        for (auto & recursePredicate : recursePredicates) {
            predicates.push_back(recursePredicate);
        }
    }
        // check if input is in FOLLOW set of predicateList
    else if (Match(tokens.at(index),PERIOD)) {
        return predicates;
    }
    else throw std::runtime_error("Syntax error");
    return predicates;
}

Parameter Parser::parseParameter(unsigned int& index) {
    std::string value = "void";
    // check if input is in FIRST set of ID
    if (Match(tokens.at(index),ID)) {
        value = tokens.at(index).GetDescription();
        index++;
    }
    // check if input is in FIRST set of STRING
    else if (Match(tokens.at(index),STRING)) {
        value = tokens.at(index).GetDescription();
        index++;
    }
    else throw std::runtime_error("Syntax error");
    Parameter param(value);
    return param;
}

std::vector<Parameter> Parser::parseParameterList(unsigned int& index) {
    std::vector<Parameter> parameters;
    // check if input is in FIRST set of COMMA
    if (Match(tokens.at(index),COMMA)) {
        index++;
    }
    else throw std::runtime_error("Syntax error");
    // check if input is in FIRST set of parameter
    if (Match(tokens.at(index),ID) || Match(tokens.at(index),STRING)) {
        parameters.push_back(parseParameter(index));
    }
    else throw std::runtime_error("Syntax error");
    // check if input is in FIRST set of parameterList
    if (Match(tokens.at(index),COMMA)) {
        std::vector<Parameter> recurseParameters = parseParameterList(index);
        for (auto & recurseParameter : recurseParameters) {
            parameters.push_back(recurseParameter);
        }
    }
    // check if input is in FOLLOW set of parameterList
    else if (Match(tokens.at(index),RIGHT_PAREN)) {
        return parameters;
    }
    else throw std::runtime_error("Syntax error");
    return parameters;
}

std::vector<Parameter> Parser::parseStringList(unsigned int& index) {
    // check if input is in FIRST set of COMMA
    if (Match(tokens.at(index),COMMA)) {
        index++;
    }
    else throw std::runtime_error("Syntax error");
    std::vector<Parameter> stringList;
    // check if input is in FIRST set of STRING
    if (Match(tokens.at(index),STRING)) {
        stringList.push_back(Parameter(tokens.at(index).GetDescription()));
        index++;
    }
    else throw std::runtime_error("Syntax error");
    // check if input is in FIRST set of stringList
    if (Match(tokens.at(index),COMMA)) {
        std::vector<Parameter> recurseStrings = parseStringList(index);
        for (auto & recurseString : recurseStrings) {
            stringList.push_back(recurseString);
        }
    }
    // check if input is in FOLLOW set of parseIdList
    else if (Match(tokens.at(index),RIGHT_PAREN)) {
        return stringList;
    }
    else throw std::runtime_error("Syntax error");
    return stringList;
}

std::vector<Parameter> Parser::parseIdList(unsigned int& index) {
    // check if input is in FIRST set of COMMA
    if (Match(tokens.at(index),COMMA)) {
        index++;
    }
    else throw std::runtime_error("Syntax error");
    std::vector<Parameter> idList;
// check if input is in FIRST set of ID
    if (Match(tokens.at(index),ID)) {
        idList.push_back(Parameter(tokens.at(index).GetDescription()));
        index++;
    }
    else throw std::runtime_error("Syntax error");
    // check if input is in FIRST set of parseIdList
    if (Match(tokens.at(index),COMMA)) {
        std::vector<Parameter> recurseIds = parseIdList(index);
        for (auto & recurseId : recurseIds) {
            idList.push_back(recurseId);
        }
    }
    // check if input is in FOLLOW set of parseIdList
    else if (Match(tokens.at(index),RIGHT_PAREN)) {
        return idList;
    }
    else throw std::runtime_error("Syntax error");
    return idList;
}

DatalogProgram Parser::Parse() {
    unsigned int index = 0;
    try {
        parseDatalogProgram(index);
        // std::cout << "Success!\n";
    }
    catch(std::exception& e) {
        std::cout << "Failure!\n  " << tokens.at(index).ToString();
    }
    return program;
}

std::string Parser::ToString() { return program.ToString(); }