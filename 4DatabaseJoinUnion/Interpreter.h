#pragma once

#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <set>
#include <cctype>
#include <map>
#include "rule.h"
#include "predicate.h"
#include "Database.h"

using namespace std;

class Interpreter {
    public:        
        Database dbMap;
        
        bool moreTuples = false;
        int totalRuns = 0;

        void AddRelations(vector<Predicate> allSchemes, vector<Predicate> allFacts);
        void AddTuples(vector<Predicate> allFacts);

        void evQuery(vector<Predicate> allQueries);
        Relation Select(Predicate singleQuery, Relation singleRelation);
        void SelectType1(Predicate sQuery, Relation sRelation, Relation &r);
        void SelectType2(map<string, int> index, Relation sRelation, Relation &r, Predicate query);
        void Project(Relation &r, Predicate query, map<string, int> indexFound);
        void Project(Relation &r, Predicate &query);
        void Rename(Relation &r, Predicate &query);
        void evRules(vector<RuleClass> &rules);
        void combineRelations(Relation &a, Relation &b);
        void ProjectRule(Relation &finalRelation, Predicate &head, vector<Predicate> &body);
        void Union(Relation &a, Relation &b);
        void StringToUp(string &str);

        void PrintRelation(Relation &r);
};