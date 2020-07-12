#pragma once

#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include "predicate.h"
#include "rule.h"

using namespace std;

class DataLogClass {
    public:
        DataLogClass();

        vector<Predicate> schemes;
        vector<Predicate> facts;
        vector<RuleClass> rules;
        vector<Predicate> queries;
        vector<string> domain;

        void addScheme(Predicate newScheme);
        void addFact(Predicate newFact);
        void addRule(RuleClass newRule);
        void addQuery(Predicate newQuery);
        void addDomain(string value);

        void toStringSchemes();
        void toStringFacts();
        void toStringRules();
        void toStringQueries();
        void toStringDomain();
        void toString();
};