#include "rule.h"

RuleClass::RuleClass(Predicate head, vector<Predicate> body){
    headPredicate = head;
    bodyPredicate = body;
};