#include "parameter.h"

Parameter::Parameter(){

    paramValue = "";
    paramType = "";

};


Parameter::Parameter(string value, string type){
    paramValue = value;
    paramType = type; 
};