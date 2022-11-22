cmake_minimum_required(VERSION 3.21)
project (cs236_project_1)

set(CMAKE_CXX_STANDARD 14)

add_executable(cs236_project_1 main.cpp Lexer.h Lexer.cpp Automaton.h ColonAutomaton.h ColonAutomaton.cpp ColonDashAutomaton.h ColonDashAutomaton.cpp inputFile1.txt CommaAutomaton.h CommaAutomaton.cpp Token.cpp PeriodAutomaton.h PeriodAutomaton.cpp QuestionMarkAutomaton.h QuestionMarkAutomaton.cpp LeftParenAutomaton.h LeftParenAutomaton.cpp RightParenAutomaton.h RightParenAutomaton.cpp MultiplyAutomaton.h MultiplyAutomaton.cpp AddAutomaton.h AddAutomaton.cpp SchemesAutomaton.h SchemesAutomaton.cpp FactsAutomaton.h FactsAutomaton.cpp RulesAutomaton.h RulesAutomaton.cpp QueriesAutomaton.h QueriesAutomaton.cpp StringAutomaton.h StringAutomaton.cpp LineCommentAutomaton.h LineCommentAutomaton.cpp BlockCommentAutomaton.h BlockCommentAutomaton.cpp IdAutomaton.h IdAutomaton.cpp UndefinedAutomaton.h UndefinedAutomaton.cpp Parser.h DatalogProgram.h Parser.cpp Predicate.h Parameter.h Rule.h DatalogProgram.cpp NTuple.h NTuple.cpp Header.h Header.cpp Relation.h Database.h Relation.cpp Interpreter.h Interpreter.cpp)
