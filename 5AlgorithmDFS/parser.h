#pragma once

#include <string>
#include <cctype>
#include <iostream>
#include <fstream>
#include <vector>
#include "token.h"
#include "dataLogProgram.h"

using namespace std;

class Parser {
    public: 
        DataLogClass dataProgram;
        vector<Token> lTokens;
        string expression = "";


        void passTokens (vector<Token> tokens);

        vector<Parameter> tempList;
        vector<Predicate> tempListPredicate;

        void matchToken(string strToken);

        void parseDLP();
        void parseScheme();
        void parseIdList();
        void parseSchemeList();
        void parseFacts();
        void parseStringList();
        void parseFactList();
        void parseRule();
        Predicate parseHeadPredicate();
        void parsePredicate();
        void parsePredicateList();
        void parseParameter();
        void parseParameterList();
        Parameter parseExpression();
        void parseOperator();
        void parseRuleList();
        void parseQuerie();
        void parseQuerieList();
        void parseParameterFromExpression();
        void parseParameterFromExpressionList();
        void parseExpressionFromExpression();
};