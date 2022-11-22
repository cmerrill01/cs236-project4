//
// Created by chase on 10/21/2022.
//

#include "Relation.h"
#include <iostream>

Relation Relation::select(unsigned int index, const std::string& value) {
    Relation newRelation(name + "\'",header);
    for (const auto & tuple : tuples) {
        if (tuple.GetValues().at(index) == value) {
            newRelation.AddTuple(tuple);
        }
    }
    return newRelation;
}

Relation Relation::select(unsigned int index1, unsigned int index2) {
    Relation newRelation(name + "\'",header);
    for (const auto & tuple : tuples) {
        if (tuple.GetValues().at(index1) == tuple.GetValues().at(index2)) {
            newRelation.AddTuple(tuple);
        }
    }
    return newRelation;
}

Relation Relation::project(const std::vector<unsigned int>& indices) {
    std::vector<std::string> newAttributes;
    newAttributes.reserve(indices.size());
for (const auto & index : indices) {
        newAttributes.push_back(header.GetAttributes().at(index));
    }
    Relation newRelation(name + "\'", newAttributes);
    for (const auto & tuple : tuples) {
        std::vector<std::string> newValues;
        newValues.reserve(indices.size());
        for (const auto & index : indices) {
            newValues.push_back(tuple.GetValues().at(index));
        }
        newRelation.AddTuple(nTuple(newValues));
    }
    return newRelation;
}

Relation Relation::rename(const std::vector<std::string>& attributes) {
    Relation newRelation(name + "\'",attributes);
    for (const auto & tuple : tuples) {
        newRelation.AddTuple(tuple);
    }
    return newRelation;
}

#if 1
Relation Relation::join(const Relation &other) {
    std::vector<std::pair<unsigned int, unsigned int>> indicesOfCommonAttributes;

    //make the header h for the result relation
    //(combine r1's header with r2's header)
    std::vector<std::string> newHeaderValues;
    newHeaderValues = header.GetAttributes();
    for (unsigned int i = 0; i < other.header.GetAttributes().size(); i++) {
        bool alreadyInHeader = false;
        for (unsigned int j = 0; j < newHeaderValues.size(); j++) {
            if (other.header.GetAttributes().at(i) == newHeaderValues.at(j)) {
                alreadyInHeader = true;
                std::pair<unsigned int, unsigned int> indices(j,i);
                indicesOfCommonAttributes.push_back(indices);
            }
        }
        if (!alreadyInHeader) newHeaderValues.push_back(other.header.GetAttributes().at(i));
    }

    //make a new empty relation r using header h
    Header newHeader(newHeaderValues);
    Relation newRelation(name + "Join" + other.name,newHeader);

    //for each tuple t1 in r1
    for (const auto & tuple : tuples) {
        //for each tuple t2 in r2
        for (const auto & iter2 : other.tuples) {
            std::vector<std::string> newTupleValues = tuple.GetValues();
            std::vector<std::string> otherTupleValues = iter2.GetValues();
            //if t1 and t2 can join
            if (!indicesOfCommonAttributes.empty()) {
                bool canJoin = true;
                for (auto & indicesOfCommonAttribute : indicesOfCommonAttributes) {
                    if (newTupleValues.at(indicesOfCommonAttribute.first)
                     != otherTupleValues.at(indicesOfCommonAttribute.second)) {
                        canJoin = false;
                        break;
                    }
                }
                if (canJoin) {
                    //join t1 and t2 to make tuple t
                    for (unsigned int i = 0; i < otherTupleValues.size(); i++) {
                        bool match = false;
                        for (auto & indicesOfCommonAttribute : indicesOfCommonAttributes) {
                            if (i == indicesOfCommonAttribute.second) match = true;
                        }
                        if (!match) newTupleValues.push_back(otherTupleValues.at(i));
                    }

                    nTuple newTuple(newTupleValues);
                    //add tuple t to relation r
                    newRelation.AddTuple(newTuple);
                }
            }
            else {
                //join t1 and t2 to make tuple t
                newTupleValues.insert(newTupleValues.end(), otherTupleValues.begin(), otherTupleValues.end());
                nTuple newTuple(newTupleValues);
                //add tuple t to relation r
                newRelation.AddTuple(newTuple);
            }
        }
    }

    return newRelation;
}
#endif

bool Relation::relationUnion(const Relation &other) {
    bool tuplesAdded = false;
    if (header != other.header) {
        throw std::invalid_argument("Cannot union relations: attributes do not match");
    }
    for (const auto & tuple : other.tuples) {
        if (this->AddTuple(tuple)) {
            tuplesAdded = true;
            if (!header.GetAttributes().empty()) {
                std::cout << "  ";
                if (header.GetAttributes().size() > 1) {
                    for (unsigned int i = 0; i < header.GetAttributes().size() - 1; i++) {
                        std::cout << header.GetAttributes().at(i) << "=" << tuple.GetValues().at(i) << ", ";
                    }
                }
                std::cout << header.GetAttributes().at(header.GetAttributes().size() - 1) << "="
                   << tuple.GetValues().at(header.GetAttributes().size() - 1) << std::endl;
            }
        }
    }
    return tuplesAdded;
}