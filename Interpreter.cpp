//
// Created by chase on 10/31/2022.
//

#include "Interpreter.h"
#include "Predicate.h"
#include "NTuple.h"
#include <iostream>

void Interpreter::InterpretSchemes() {
    // for each scheme ‘s’
        // create a relation using name and parameter values from ‘s’
    std::vector<Predicate> programSchemes = program.GetSchemes();
    for (auto & programScheme : programSchemes) {
        std::string emptyRelationName = programScheme.GetId();
        std::vector<std::string> emptyRelationHeader;
        for (unsigned int j = 0; j < programScheme.GetParameters().size(); j++) {
            emptyRelationHeader.push_back(programScheme.GetParameters().at(j).ToString());
        }
        Relation emptyRelation(emptyRelationName,emptyRelationHeader);
        database.AddRelation(emptyRelation);
    }
}

void Interpreter::InterpretFacts() {
    // for each fact ‘f’
        // make a tuple ‘t’ using the values from ‘f’
        // add ‘t’ to relation with the same name as ‘f’
    std::vector<Predicate> programFacts = program.GetFacts();
    for (auto & programFact : programFacts) {
        std::vector<std::string> tupleValues;
        for (unsigned int j = 0; j < programFact.GetParameters().size(); j++) {
            tupleValues.push_back(programFact.GetParameters().at(j).ToString());
        }
        nTuple tupleToAdd(tupleValues);
        database.EditRelations().find(programFact.GetId())->second.AddTuple(tupleToAdd);
    }
}

void Interpreter::InterpretRules() {
    bool tuplesAdded;
    unsigned int passesThroughRules = 0;
    do {
        tuplesAdded = false;
        std::vector<Rule> programRules = program.GetRules();
        for (auto &programRule: programRules) {
            std::vector<Predicate> bodyPredicates = programRule.GetBodyPredicates();
            std::vector<Relation> evaluatedPredicates;
            for (auto &bodyPredicate: bodyPredicates) {
                Relation evaluatedPredicate = EvaluatePredicate(bodyPredicate);
                // add the resulting relation to the vector
                evaluatedPredicates.push_back(evaluatedPredicate);
            }
            Relation evaluatedRule(evaluatedPredicates.at(0));
            if (evaluatedPredicates.size() > 1) {
                for (unsigned int j = 0; j < evaluatedPredicates.size() - 1; j++) {
                    evaluatedRule = evaluatedRule.join(evaluatedPredicates.at(j + 1));
                }
            }
            std::vector<std::string> headPredicateHeaderAttributes;
            for (unsigned int j = 0; j < programRule.GetHeadPredicate().GetParameters().size(); j++) {
                headPredicateHeaderAttributes.push_back(programRule.GetHeadPredicate().GetParameters().at(j).ToString());
            }
            // find the indices of the new relation of the attributes that match the attributes of the head predicate
            std::vector<std::string> evaluatedRuleAttributes = evaluatedRule.GetHeader().GetAttributes();
            std::vector<unsigned int> indicesToProject;
            for (auto &headPredicateHeaderAttribute: headPredicateHeaderAttributes) {
                for (unsigned int k = 0; k < evaluatedRuleAttributes.size(); k++) {
                    if (evaluatedRuleAttributes.at(k) == headPredicateHeaderAttribute) {
                        indicesToProject.push_back(k);
                        break;
                    }
                }
            }
            // project the relation on those indices
            evaluatedRule = evaluatedRule.project(indicesToProject);

            // find the name of the relation indicated by the head predicate of the rule
            std::vector<std::string> relationAttributes = database.GetRelations().at(
                    programRule.GetHeadPredicate().GetId()).GetHeader().GetAttributes();
            // rename the relation so we can union it with the relation by the same name
            evaluatedRule = evaluatedRule.rename(relationAttributes);
            // print the rule and the resulting tuples added
            std::cout << programRule.ToString() << std::endl;
            // union the resulting relation with the original relation in the database
            if (database.UnionWithRelation(programRule.GetHeadPredicate().GetId(), evaluatedRule)) {
                tuplesAdded = true;
            }
        }
        passesThroughRules++;
    } while (tuplesAdded);
    std::cout << "\nSchemes populated after " << passesThroughRules << " passes through the Rules." << std::endl;
}

void Interpreter::InterpretQueries() {
    // for each query ‘q’
    std::vector<Predicate> programQueries = program.GetQueries();
    for (auto & programQuery : programQueries) {
        Relation queryResult = EvaluatePredicate(programQuery);
        // print the resulting relation
        std::cout << programQuery.ToString() << "? ";
        if (queryResult.Empty()) std::cout << "No" << std::endl;
        else {
            std::cout << "Yes(" << queryResult.GetNumTuples() << ")" << std::endl;
            std::cout << queryResult.ToString();
        }
    }
}

Relation Interpreter::EvaluatePredicate(const Predicate& predicate) {
    // get the relation ‘r’ with the same name as the predicate
    Relation evaluatedPredicate(database.GetRelations().at(predicate.GetId()));

    // create data structures to keep track of the variables
    std::vector<unsigned int> variableIndices;
    std::vector<std::string> variables;

    for (unsigned int i = 0; i < predicate.GetParameters().size(); i++) {
        std::string parameter = predicate.GetParameters().at(i).ToString();

        // select for each constant in the query ‘q’
        if (parameter.at(0) == '\'') {
            evaluatedPredicate = evaluatedPredicate.select(i, parameter);
        }

        // select for each pair of matching variables in ‘q’
        else if (variables.empty()) {
            variableIndices.push_back(i);
            variables.push_back(parameter);
        } else {
            bool sameVariableFound = false;
            for (unsigned int j = 0; j < variables.size(); j++) {
                if (parameter == variables.at(j)) {
                    evaluatedPredicate = evaluatedPredicate.select(variableIndices.at(j), i);
                    sameVariableFound = true;
                    break;
                }
            }
            if (!sameVariableFound) {
                variableIndices.push_back(i);
                variables.push_back(parameter);
            }
        }
    }

    // project using the positions of the variables in ‘q’
    evaluatedPredicate = evaluatedPredicate.project(variableIndices);

    // rename to match the names of variables in ‘q’
    evaluatedPredicate = evaluatedPredicate.rename(variables);

    return evaluatedPredicate;
}