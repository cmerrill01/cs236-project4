#ifndef CS236_PROJECT_1_INTERPRETER_H
#define CS236_PROJECT_1_INTERPRETER_H

#include "DatalogProgram.h"
#include "Database.h"

class Interpreter {
private:
    DatalogProgram program;
    Database database;
    Relation EvaluatePredicate(const Predicate& predicate);
public:
    Interpreter(const DatalogProgram& programToInterpret) : program(programToInterpret) {}
    ~Interpreter() = default;
    void InterpretSchemes();
    void InterpretFacts();
    void InterpretRules();
    void InterpretQueries();
    std::string ToString() { return "Database: \n" + database.ToString(); }
};

#endif //CS236_PROJECT_1_INTERPRETER_H
