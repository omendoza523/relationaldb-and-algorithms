#include "predicate.h"

Predicate::Predicate(){
    nameID = "";
    parametersList = vector<Parameter>();
};

//CONSTRUCTOR FOR A NEW PREDICATE
Predicate::Predicate(string name, vector<Parameter> paramList){
    nameID = name;
    parametersList = paramList; 
    // PARAM LIST WILL BE SEND AS A PARAMETER WHEN
    // ALL THE PARAMETERS FOR THAT SPECEFIC PREDICATE ARE DONE
};