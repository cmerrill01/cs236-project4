#include "Header.h"

#include <sstream>

std::string Header::ToString() const {
    std::stringstream ss;
    if (attributes.size() > 1) {
        for (unsigned int i = 0; i < attributes.size() - 1; i++) {
            ss << attributes.at(i) << ",";
        }
    }
    ss << attributes.at(attributes.size() - 1) << std::endl;
    return ss.str();
}