#include "dataLogProgram.h"

DataLogClass::DataLogClass(){
    //
};

void DataLogClass::addScheme(Predicate newScheme){
    schemes.push_back(newScheme);
};

void DataLogClass::addFact(Predicate newFact){
    facts.push_back(newFact);
};

void DataLogClass::addRule(RuleClass newRule){
    rules.push_back(newRule);
};

void DataLogClass::addQuery(Predicate newQuery){
    queries.push_back(newQuery);
};

void DataLogClass::addDomain(string value){
    bool isThere = false;
    for (unsigned i = 0; i < domain.size(); i++){
        if (domain[i] != value){
            isThere = false;
        }
        else {
            isThere = true;
            break;
        }
    }
    if (isThere == false){
        domain.push_back(value);
    }
    sort(domain.begin(), domain.end());
};

void DataLogClass::toStringSchemes(){
    cout << "Schemes("<< schemes.size() << "):" << endl;
    for (unsigned i = 0; i < schemes.size(); i++){
        cout << "  " << schemes[i].nameID << "(";
        for (unsigned j = 0; j < schemes[i].parametersList.size(); j++){
            cout << schemes[i].parametersList[j].paramValue;
            if (j == schemes[i].parametersList.size() - 1){
                cout << ")" << endl;
            }
            else {
                cout << ",";
            }
        };
    };
};

void DataLogClass::toStringFacts(){
    cout << "Facts("<< facts.size() << "):" << endl;
    for (unsigned i = 0; i < facts.size(); i++){
        cout << "  " << facts[i].nameID << "(";
        for (unsigned j = 0; j < facts[i].parametersList.size(); j++){
            cout << facts[i].parametersList[j].paramValue;
            if (j == facts[i].parametersList.size() - 1){
                cout << ")." << endl;
            }
            else {
                cout << ",";
            }
        };
    };

};

void DataLogClass::toStringRules(){
    cout << "Rules("<< rules.size() << "):" << endl;
    for (unsigned i = 0; i < rules.size(); i++){
        cout << "  " << rules[i].headPredicate.nameID << "(";
        for (unsigned j = 0; j < rules[i].headPredicate.parametersList.size(); j++){
            cout << rules[i].headPredicate.parametersList[j].paramValue;
            if (j == rules[i].headPredicate.parametersList.size() - 1){
                cout << ")";
            }
            else {
                cout << ",";
            }
        };
        cout << " :- ";
        for (unsigned k = 0; k < rules[i].bodyPredicate.size(); k++){
            cout << rules[i].bodyPredicate[k].nameID << "(";

            for (unsigned l = 0; l < rules[i].bodyPredicate[k].parametersList.size(); l++){
                cout << rules[i].bodyPredicate[k].parametersList[l].paramValue;

                if (l == rules[i].bodyPredicate[k].parametersList.size() - 1){
                cout << ")";
                }
                else {
                    cout << ",";
                }
            }
            if (k != rules[i].bodyPredicate.size() - 1){
                cout << ",";
            }
        }
        cout << "." << endl; 
    };
};

void DataLogClass::toStringQueries(){
    cout << "Queries("<< queries.size() << "):" << endl;
    for (unsigned i = 0; i < queries.size(); i++){
        cout << "  " << queries[i].nameID << "(";
        for (unsigned j = 0; j < queries[i].parametersList.size(); j++){
            cout << queries[i].parametersList[j].paramValue;
            if (j == queries[i].parametersList.size() - 1){
                cout << ")?" << endl;
            }
            else {
                cout << ",";
            }
        };
    };

};

void DataLogClass::toStringDomain(){   
    cout << "Domain("<< domain.size() << "):" << endl;
    for (unsigned i = 0; i < domain.size(); i++){
        cout << "  " << domain[i] << endl;
    };

};

void DataLogClass::toString(){
    toStringSchemes();
    toStringFacts();
    toStringRules();
    toStringQueries();
    toStringDomain();
};