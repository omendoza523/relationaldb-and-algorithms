#pragma once

#include <iostream>
#include <vector>
#include <string>
#include "predicate.h"

using namespace std;

class RuleClass {
    public:
        Predicate headPredicate;
        vector<Predicate> bodyPredicate;

        RuleClass(Predicate head, vector<Predicate> body);
};