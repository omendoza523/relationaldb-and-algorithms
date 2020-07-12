#pragma once

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Parameter {
    public:
        string paramValue;
        string paramType;
        // THIS NEEDS TO HOLD STRING ID AND EXPRESSION
        Parameter();
        Parameter(string value, string type);
};