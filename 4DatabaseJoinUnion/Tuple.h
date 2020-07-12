#pragma once

#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Tuple : public vector<string> {
    public:
        Tuple(){};
        bool flag = false;
};