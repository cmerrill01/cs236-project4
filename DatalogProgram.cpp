#include "DatalogProgram.h"

std::string DatalogProgram::ToString() {
    std::stringstream ss;
    ss << "Schemes(" << schemes.size() << "):" << std::endl;
    if (!schemes.empty()) {
        for (unsigned int i = 0; i < schemes.size(); i++) {
            ss << "  " << schemes.at(i).ToString() << "\n";
        }
    }
    ss << "Facts(" << facts.size() << "):" << std::endl;
    if (!facts.empty()) {
        for (unsigned int i = 0; i < facts.size(); i++) {
            ss << "  " << facts.at(i).ToString() << ".\n";
        }
    }
    ss << "Rules(" << rules.size() << "):" << std::endl;
    if (!rules.empty()) {
        for (unsigned int i = 0; i < rules.size(); i++) {
            ss << "  " << rules.at(i).ToString() << "\n";
        }
    }
    ss << "Queries(" << queries.size() << "):" << std::endl;
    if (!queries.empty()) {
        for (unsigned int i = 0; i < queries.size(); i++) {
            ss << "  " << queries.at(i).ToString() << "?\n";
        }
    }
    ss << "Domain(" << domain.size() << "):" << std::endl;
    if (!domain.empty()) {
        for (auto iter = domain.begin(); iter != domain.end(); iter++) {
            ss << "  " << *iter << "\n";
        }
    }
    return ss.str();
}