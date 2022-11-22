#ifndef CS236_PROJECT_1_RELATION_H
#define CS236_PROJECT_1_RELATION_H

#include <string>
#include <set>
#include "Header.h"
#include "NTuple.h"
#include <sstream>
#include <list>

class Relation {
private:
    std::string name;
    Header header;
    std::set<nTuple> tuples;
public:
    Relation(const std::string& relationName, const Header& relationHeader) : name(relationName), header(relationHeader) {}
    ~Relation() = default;
    Relation(const Relation& other) : name(other.name), header(other.header), tuples(other.tuples) {}
    Relation& operator=(const Relation& other) = default;
    std::string GetName() const { return name; }
    Header GetHeader() const { return header; }
    bool Empty() { return tuples.empty(); }
    unsigned int GetNumTuples() { return tuples.size(); }

    std::string ToString() {
        std::stringstream ss;
        if (!header.GetAttributes().empty()) {
            for (const auto & tuple : tuples) {
                ss << "  ";
                if (header.GetAttributes().size() > 1) {
                    for (unsigned int i = 0; i < header.GetAttributes().size() - 1; i++) {
                        ss << header.GetAttributes().at(i) << "=" << tuple.GetValues().at(i) << ", ";
                    }
                }
                ss << header.GetAttributes().at(header.GetAttributes().size() - 1) << "="
                   << tuple.GetValues().at(header.GetAttributes().size() - 1) << std::endl;
            }
        }
        return ss.str();
    }

    bool AddTuple(const nTuple& tupleToAdd) {
        return tuples.insert(tupleToAdd).second;
    }
    Relation select(unsigned int index, const std::string& value);
    Relation select(unsigned int index1, unsigned int index2);
    Relation project(const std::vector<unsigned int>& indices);
    Relation rename(const std::vector<std::string>& attributes);
    Relation join(const Relation& other);
    bool relationUnion(const Relation& other);
};

#endif //CS236_PROJECT_1_RELATION_H
