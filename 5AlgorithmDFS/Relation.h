#pragma once

#include <iostream>
#include <vector>
#include <set>
#include <string>
#include "parameter.h"
#include "Tuple.h"

using namespace std;

class Relation {
    public:
        Relation();
        Relation(string relationName, vector<string> attributes);
        string relName;
        vector <string> relAtt;
        set<Tuple> tuples;

        void PrintTuple(Tuple t);
        void PrintRuleTuple(Tuple t, vector<string> p);
};