#include "NTuple.h"

#include <sstream>

std::string nTuple::ToString() const {
    std::stringstream ss;
    if (values.size() > 1) {
        for (unsigned int i = 0; i < values.size() - 1; i++) {
            ss << values.at(i) << ",";
        }
    }
    ss << values.at(values.size() - 1) << std::endl;
    return ss.str();
}

bool nTuple::operator<(const nTuple& otherTuple) const {
    return values < otherTuple.values;
}