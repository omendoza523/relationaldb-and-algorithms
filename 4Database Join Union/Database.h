#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <map>
#include "predicate.h"
#include "Relation.h"

using namespace std;

class Database : public map<string, Relation> {
};