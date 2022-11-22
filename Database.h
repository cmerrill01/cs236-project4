#ifndef CS236_PROJECT_1_DATABASE_H
#define CS236_PROJECT_1_DATABASE_H

#include <map>
#include "Relation.h"
#include <sstream>

class Database {
private:
    std::map<std::string, Relation> relations;
public:
    Database() = default;
    ~Database() = default;
    std::string ToString() {
        std::stringstream ss;
        for (auto & relation : relations) {
            ss << relation.second.ToString() << std::endl;
        }
        return ss.str();
    }
    void AddRelation(const Relation& relationToAdd) {
        std::pair<std::string, Relation> newRelation(relationToAdd.GetName(),relationToAdd);
        relations.insert(newRelation);
    }
    std::map<std::string, Relation> GetRelations() { return relations; }
    std::map<std::string, Relation>& EditRelations() { return relations; }
    bool UnionWithRelation(const std::string& relationName, const Relation& relationToUnion) {
        return relations.at(relationName).relationUnion(relationToUnion);
    }
};

#endif //CS236_PROJECT_1_DATABASE_H
