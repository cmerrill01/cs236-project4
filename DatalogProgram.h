#ifndef CS236_PROJECT_1_DATALOGPROGRAM_H
#define CS236_PROJECT_1_DATALOGPROGRAM_H

#include <set>
#include <vector>
#include <string>
#include <sstream>
#include "Rule.h"
#include "Predicate.h"

class DatalogProgram
{
private:
    std::vector<Predicate> schemes;
    std::vector<Predicate> facts;
    std::vector<Rule> rules;
    std::vector<Predicate> queries;
    std::set<std::string> domain;
public:
    DatalogProgram() {}
    ~DatalogProgram() = default;
    std::vector<Predicate> GetSchemes() { return schemes; }
    std::vector<Predicate> GetFacts() { return facts; }
    std::vector<Rule> GetRules() { return rules; }
    std::vector<Predicate> GetQueries() { return queries; }
    void AddScheme(Predicate scheme) { schemes.push_back(scheme); }
    void AddFact(Predicate fact) {
        facts.push_back(fact);
        for (unsigned int i = 0; i < fact.GetParameters().size(); i++) {
            domain.insert(fact.GetParameters().at(i).ToString());
        }
    }
    void AddRule(Rule rule) { rules.push_back(rule); }
    void AddQuery(Predicate query) { queries.push_back(query); }
    std::string ToString();
};

#endif //CS236_PROJECT_1_DATALOGPROGRAM_H
