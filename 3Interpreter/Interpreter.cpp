#include "Interpreter.h"

void Interpreter::AddRelations(vector<Predicate> schemes, vector<Predicate> facts){
    
    for (unsigned int i = 0; i < schemes.size(); i++){ // FOR EACH SCHEME!
        //ADD ONE RELATION FOR EACH SCHEME!
        vector<string> attributeList;
        string name = schemes[i].nameID; 
        //THIS LOOP TRANSFORMS PARAMETER VECTOR TO STRING VECTOR
        for (unsigned int m = 0; m < schemes[i].parametersList.size(); m++){ 
            
            attributeList.push_back(schemes[i].parametersList[m].paramValue);
            //ATTRIBUTE VECTOR IS READY!
        } 
        
        //CREATE RELATION OBJECT
        Relation newRelation(schemes[i].nameID, attributeList);
        
        dbMap.insert(pair<string, Relation>(name, newRelation));
    }

    AddTuples(facts);
};

void Interpreter::AddTuples(vector<Predicate> factList){
    
    for (unsigned int i = 0; i < factList.size(); i++){ // FOR EACH FACT!
        //ADD ONE TUPLE FOR EACH FACT
        vector<Parameter> paramVector = factList[i].parametersList; // FOUND FIRST PARAMETER VECTOR
        Tuple newTuple; // CREATE A TUPLE OBJECT
        for (unsigned int m = 0; m < paramVector.size(); m++){
            newTuple.push_back(paramVector[m].paramValue);
        }

        map<string, Relation>::iterator itr;
        
        for (itr = dbMap.begin(); itr != dbMap.end(); itr++){
            //CHECK RELATION TO FIND THE NAME OF THE RELATION THE FACT BELONGS TO
            if (factList[i].nameID == itr->first){
                itr->second.tuples.insert(newTuple);
            }
        }
    }
};

void Interpreter::evQuery(vector<Predicate> queries){
    //FOR EACH QUERY FIND THE RELATION THAT IT BELONGS TOO
    for (unsigned int  i = 0; i < queries.size(); i++){
        for (map<string, Relation>::iterator it = dbMap.begin(); it != dbMap.end(); it++){
            
            if (queries[i].nameID == it->first){//FOUND THE RELATION THAT THE QUERY BELONGS TO 
                //CALL A FUNCTION TO DO ALL THE SELECTS PASS THE QUERY 
                //AND THE RELATION
                Relation r = Select(queries[i], it->second);
                Rename(r, queries[i]);
                cout << r.relName << "(";
                for (unsigned int p = 0; p < queries[i].parametersList.size(); p++){
                    cout << r.relAtt[p];
                    if (p == queries[i].parametersList.size() - 1){
                        cout << ")?";
                    }
                    else {
                        cout << ",";
                    }
                }
                if (r.tuples.size() > 0){
                    cout << " Yes(" << r.tuples.size() << ")" << endl;
                    set<Tuple>::iterator itr;
                    for (itr = r.tuples.begin(); itr != r.tuples.end(); itr++){
                        vector<string> temp = *itr;
                        bool hasVars = false;
                        for (unsigned int p = 0; p < temp.size(); p++){
                            if (queries[i].parametersList[p].isConstant == false){
                                hasVars = true;
                                break;
                            }
                        }
                        if (hasVars == true){
                            cout << " ";
                            int first = 0;
                            for (unsigned int p = 0; p < temp.size(); p++){
                                if (queries[i].parametersList[p].isConstant == false && temp[p] != ""){
                                    
                                    if (p == 0 && queries[i].parametersList[p].isConstant == false){
                                        first++;
                                        cout << " " << queries[i].parametersList[p].paramValue;
                                        cout << "=" << temp[p];
                                    }
                                    else {
                                        if (first > 0){
                                            cout << ", " << queries[i].parametersList[p].paramValue;
                                            cout << "=" << temp[p];
                                        }
                                        else {
                                            first++;
                                            cout << " " << queries[i].parametersList[p].paramValue;
                                            cout << "=" << temp[p];
                                        }
                                    }
                                }
                            }
                            cout << endl;
                        }
                    }
                }
                else {
                    cout << " No" << endl;
                }

            }
        }

    }
    //FOR EVERY QUERY DO A SELECT
};

Relation Interpreter::Select(Predicate query, Relation rel){

    Relation r;
    r.relName = rel.relName;
    r.relAtt = rel.relAtt;
    r.tuples.clear();
    //ITERATE OVER PARAMETERS OF THE QUERY
    vector<string> variables;
    map<string, int> indexFound;
    bool hasDuplicate = false;

    for (unsigned int i = 0; i < query.parametersList.size(); i++){
        if (query.parametersList[i].isConstant == true){
            //DO NOTHING
        }
        else {
            //THERE ARE VARIABLES START STORING THEM
            variables.push_back(query.parametersList[i].paramValue);
        }
    }
    
    for (unsigned int i = 0; i < variables.size(); i++){
        string currentVar = variables[i];
        for (unsigned int j = 0; j < variables.size(); j++){
            if (currentVar == variables[j] && i != j){
                indexFound.insert({currentVar, i});
                hasDuplicate = true;
            }
        }
    }

    if (hasDuplicate == true){
        SelectType2(indexFound, rel, r, query);
        Project(r, query, indexFound);
    }
    else {
        SelectType1(query, rel, r);
    }
    
    //CHECK DUPLICATED VARIABLES
        
    
    return r;
};

void Interpreter::SelectType1(Predicate query, Relation rel, Relation &r){
    for (set<Tuple>::iterator itr = rel.tuples.begin(); itr != rel.tuples.end(); itr++){
        Tuple check = *itr;
        for (unsigned int i = 0; i < check.size(); i++){
            if (query.parametersList[i].paramValue == check[i] && check.flag == false){
                check.flag = false;
            }
            else if (query.parametersList[i].paramValue != check[i] && query.parametersList[i].isConstant == false){
               check.flag = false;
                
            }
            else if (query.parametersList[i].paramValue != check[i] && query.parametersList[i].isConstant != false){
                check.flag = true;
                break;
            }
            else {
                check.flag = true;
            }
        }
        
        if (check.flag == false){
            r.tuples.insert(check);
        }

        check.flag = false;
    }
}

void Interpreter::SelectType2(map<string, int> indexFound, Relation rel, Relation &r, Predicate query){
    
    for (set<Tuple>::iterator itr = rel.tuples.begin(); itr != rel.tuples.end(); itr++){
        Tuple check = *itr;
        //INITIALIZE STRING TO MATCH THIS VALUE EVERY TIME THE QUERY HAS AN "X"
        
        for (map<string, int>::iterator mit = indexFound.begin(); mit != indexFound.end(); mit++){
        string currentValue = check[mit->second];

            for (unsigned int i = 0; i < check.size(); i++){
                
                if (query.parametersList[i].paramValue == mit->first){// QUERY HAS AN X!
                    if (check[i] == currentValue && check.flag == false){ // IF THE VALUE OF THE TUPLE MATCHES THE ORIGINAL VALUE WHERE THE QUERY HAS AN X DO NOT FLAG
                        check.flag = false; // 
                    }
                    else {
                        check.flag = true;
                        break;
                    }
                }

                if (query.parametersList[i].isConstant == true){
                    for (unsigned int i = 0; i < check.size(); i++){
                        if (query.parametersList[i].paramValue == check[i] && check.flag == false){
                            check.flag = false;
                        }
                        else if (query.parametersList[i].paramValue != check[i] && query.parametersList[i].isConstant == false){
                        check.flag = false;
                            
                        }
                        else if (query.parametersList[i].paramValue != check[i] && query.parametersList[i].isConstant != false){
                            check.flag = true;
                            break;
                        }
                        else {
                            check.flag = true;
                        }
                    }
                    //____
                }
            }
            
        }
        if (check.flag == false){
            r.tuples.insert(check);
        }
        check.flag = false;
    }
};

void Interpreter::Project(Relation &r, Predicate query, map<string, int> indexFound){
    //project operation to keep only the columns from the Relation that correspond to the positions of the variables in the query
    //GET RID OF THE COLUMS THAT HAVE CONSTANTS MATCHING THE QUERY;
    set<Tuple>::iterator itr;
    for (itr = r.tuples.begin(); itr != r.tuples.end(); itr++){
        Tuple temp = *itr;
        for (unsigned int p = 0; p < temp.size(); p++){
            
            if (query.parametersList[p].isConstant == true){
                temp[p] = "";
            }
        }
        
        // NOW GET RID OF COLUMNS THAT ARE FROM DUPLICATED QUERIES
        for (map<string, int>::iterator mit = indexFound.begin(); mit != indexFound.end(); mit++){

            string currentValue = temp[mit->second];
            for (unsigned int i = temp.size(); i > 0; i--){
                if (query.parametersList[i].paramValue == mit->first){// QUERY HAS AN X!
                    if (temp[i] == currentValue){ // IF THE VALUE OF THE TUPLE MATCHES THE ORIGINAL VALUE 
                    //WHERE THE QUERY HAS AN X
                        for (unsigned int z = 0; z < temp.size(); z++){
                            if (temp[z] == temp[i] && query.parametersList[i].paramValue == query.parametersList[z].paramValue && i != z){
                                //FOUND THAT IT IS ALREADY THERE!
                                temp[i] = "";
                            }
                        }
                    }
                }
            }
        }

        r.tuples.erase(*itr);
        r.tuples.insert(temp);
    }

};

void Interpreter::Rename(Relation &r, Predicate query){
    for (unsigned int i = 0; i < r.relAtt.size(); i++){
        r.relAtt[i] = query.parametersList[i].paramValue;
    }
};

