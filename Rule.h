#ifndef CS236_PROJECT_1_RULE_H
#define CS236_PROJECT_1_RULE_H

#include <string>
#include <vector>
#include "Predicate.h"

class Rule {
private:
    Predicate headPredicate;
    std::vector<Predicate> bodyPredicates;
public:
    Rule(Predicate head) : headPredicate(head) {}
    ~Rule() = default;
    void AddPredicate(Predicate pred) { bodyPredicates.push_back(pred); }
    std::vector<Predicate> GetBodyPredicates() const { return bodyPredicates; }
    Predicate GetHeadPredicate() const { return headPredicate; }
    std::string ToString() {
        std::stringstream ss;
        ss << headPredicate.ToString() << " :- ";
        if (!bodyPredicates.empty()) {
            for (unsigned int i = 0; i < bodyPredicates.size() - 1; i++) { ss << bodyPredicates.at(i).ToString() << ","; }
            ss << bodyPredicates.at(bodyPredicates.size() - 1).ToString();
        }
        ss << ".";
        return ss.str();
    }
};

#endif //CS236_PROJECT_1_RULE_H
