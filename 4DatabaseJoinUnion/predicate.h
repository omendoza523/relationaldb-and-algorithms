#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "parameter.h"

using namespace std;

class Predicate {
    public:
        string nameID;
        vector<Parameter> parametersList;

        Predicate();
        
        Predicate(string name, vector<Parameter> paramList);
};