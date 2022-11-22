#ifndef CS236_PROJECT_1_PARAMETER_H
#define CS236_PROJECT_1_PARAMETER_H

#include <string>

class Parameter {
private:
    std::string value;
public:
    Parameter(std::string input) : value(input) {}
    ~Parameter() = default;
    Parameter(const Parameter& other) : value(other.value) {}
    bool operator==(const Parameter& other) { return value == other.value; }
    std::string ToString() const { return value; }
};

#endif //CS236_PROJECT_1_PARAMETER_H
