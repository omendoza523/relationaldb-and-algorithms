#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <map>
#include "predicate.h"
#include "Database.h"

using namespace std;

class Interpreter {
    public:        
        Database dbMap;

        void AddRelations(vector<Predicate> allSchemes, vector<Predicate> allFacts);
        void AddTuples(vector<Predicate> allFacts);

        void evQuery(vector<Predicate> allQueries);
        Relation Select(Predicate singleQuery, Relation singleRelation);
        void SelectType1(Predicate sQuery, Relation sRelation, Relation &r);
        void SelectType2(map<string, int> index, Relation sRelation, Relation &r, Predicate query);
        void Project(Relation &r, Predicate query, map<string, int> indexFound);
        void Rename(Relation &r, Predicate query);
        void evRules();

};