#pragma once

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Parameter {
    public:
        string paramValue;
        string paramType;
        bool isConstant;
        // THIS NEEDS TO HOLD STRING ID AND EXPRESSION
        Parameter();
        Parameter(string value, string type);
};