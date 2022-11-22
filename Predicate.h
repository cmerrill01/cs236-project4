#ifndef CS236_PROJECT_1_PREDICATE_H
#define CS236_PROJECT_1_PREDICATE_H

#include <string>
#include <vector>
#include <sstream>
#include "Parameter.h"

class Predicate {
private:
    std::string predicateId;
    std::vector<Parameter> parameters;
public:
    Predicate(std::string id) : predicateId(id) {}
    ~Predicate() = default;
    void AddParameter(const Parameter param) { parameters.push_back(param); }
    std::string ToString() const {
        std::stringstream ss;
        ss << predicateId << "(";
        if (!parameters.empty()) {
            for (unsigned int i = 0; i < parameters.size() - 1; i++) { ss << parameters.at(i).ToString() << ","; }
            ss << parameters.at(parameters.size() - 1).ToString();
        }
        ss << ")";
        return ss.str();
    }
    std::string GetId() const { return predicateId; }
    std::vector<Parameter> GetParameters() const { return parameters; }
};

#endif //CS236_PROJECT_1_PREDICATE_H
