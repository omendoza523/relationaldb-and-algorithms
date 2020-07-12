#include "parameter.h"

Parameter::Parameter(){

    paramValue = "";
    paramType = "";
    isConstant = false;

};


Parameter::Parameter(string value, string type){
    paramValue = value;
    paramType = type; 
    if (type == "ID"){
        isConstant = false;
    }
    else if (type == "STRING"){
        isConstant = true;
    }
};