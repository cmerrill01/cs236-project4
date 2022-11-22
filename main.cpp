#include "Lexer.h"
#include "Parser.h"
#include "Interpreter.h"
#include <iostream>
#include <fstream>

#include "Parameter.h"

#include "NTuple.h"
#include "Header.h"
#include "Relation.h"
#include "Database.h"

int main(int argc, char** argv) {

    if (argc < 2) {
        std::cerr << "Please provide input file";
        return 1;
    }
    // std::cout << "Input file: " << argv[1] << std::endl;
    std::ifstream in(argv[1]);
    if (!in)
    {
        std::cerr << "Unable to open " << argv[1] << " for input" << std::endl;
        return 2;
    }

    std::string input = std::string((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());
#if 1
    Lexer* lexer = new Lexer();
    lexer->Run(input);
    Parser* parser = new Parser(lexer->GetTokens());
    Interpreter* interpreter = new Interpreter(parser->Parse());
    interpreter->InterpretSchemes();
    interpreter->InterpretFacts();
    std::cout << "Rule Evaluation\n";
    interpreter->InterpretRules();
    std::cout << "\nQuery Evaluation\n";
    interpreter->InterpretQueries();

    delete lexer;
    delete parser;
    delete interpreter;
#endif

#if 0
    std::vector<std::string> h1values;
    std::vector<std::string> h2values;
    h1values.push_back("A");
    h1values.push_back("B");
    h2values.push_back("A");
    h2values.push_back("B");

    Header header1(h1values);
    Header header2(h2values);

    Relation relation1("Ben",header1);
    Relation relation2("Jerry",header2);

    std::vector<std::string> values1;
    values1.push_back("\'5\'");
    values1.push_back("\'1\'");
    std::vector<std::string> values2;
    values2.push_back("\'6\'");
    values2.push_back("\'1\'");
    std::vector<std::string> values3;
    values3.push_back("\'4\'");
    values3.push_back("\'2\'");
    std::vector<std::string> values4;
    values4.push_back("\'3\'");
    values4.push_back("\'4\'");

    std::vector<std::string> values5;
    values5.push_back("\'1\'");
    values5.push_back("\'4\'");
    std::vector<std::string> values6;
    values6.push_back("\'2\'");
    values6.push_back("\'4\'");
    std::vector<std::string> values7;
    values7.push_back("\'2\'");
    values7.push_back("\'5\'");
    std::vector<std::string> values8;
    values8.push_back("\'3\'");
    values8.push_back("\'6\'");
    std::vector<std::string> values9;
    values9.push_back("\'3\'");
    values9.push_back("\'9\'");

    nTuple tuple1(values1);
    nTuple tuple2(values2);
    nTuple tuple3(values3);
    nTuple tuple4(values4);
    relation1.AddTuple(tuple1);
    relation1.AddTuple(tuple2);
    relation1.AddTuple(tuple3);
    relation1.AddTuple(tuple4);

    nTuple tuple5(values5);
    nTuple tuple6(values6);
    nTuple tuple7(values7);
    nTuple tuple8(values8);
    nTuple tuple9(values9);
    relation2.AddTuple(tuple5);
    relation2.AddTuple(tuple6);
    relation2.AddTuple(tuple7);
    relation2.AddTuple(tuple8);
    relation2.AddTuple(tuple9);

    std::cout << relation1.ToString() << std::endl;
    std::cout << relation2.ToString() << std::endl;

    Relation relation3 = relation1.join(relation2);
    std::cout << relation3.ToString() << std::endl;

    try {
        relation3 = relation1.relationUnion(relation2);
        std::cout << relation3.ToString() << std::endl;
    }
    catch(std::exception& e) {
        std::cerr << e.what() << std::endl;
    }


#endif

    return 0;
}