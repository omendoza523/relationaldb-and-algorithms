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
                dbMap.insert({r.relName, r});
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
    //cout << "Select" << endl;
    Relation r;
    r.relName = rel.relName;
    r.relAtt = rel.relAtt;
    r.tuples.clear();
    //ITERATE OVER PARAMETERS OF THE QUERY
    vector<string> variables;
    map<string, int> indexFoundT2;
    bool hasDuplicate = false;

    for (unsigned int i = 0; i < query.parametersList.size(); i++){
        if (query.parametersList[i].isConstant == true){ //CHECK IF VARIABLE OR NOT
            //DO NOTHING
        }
        else {
            //THERE ARE VARIABLES START STORING THEM
            variables.push_back(query.parametersList[i].paramValue);
        }
    }
    
    //CHECK IF VARIABLE REPEATS 
    for (unsigned int i = 0; i < variables.size(); i++){
        string currentVar = variables[i];
        for (unsigned int j = 0; j < variables.size(); j++){
            if (currentVar == variables[j] && i != j){ //VARIABLE REPEATED. PASS VARIABLE AND INDEX OF FIRST TIME I ENCOUNTERED VARIABLE
                indexFoundT2.insert({currentVar, i});
                hasDuplicate = true;
            }
        }
    }

    if (hasDuplicate == true){ // IF IT HAS TWO OF THE SAME VARIABLE OR MORE!
        SelectType2(indexFoundT2, rel, r, query); //CALL TYPE 2
        Project(r, query, indexFoundT2);
    }
    else {
        //IF THERE ARE NO DUPLICATES WE STILL NEED TO PROJECT THE COLUMS BASED ON WHERE WE FOUND THE VARIABLES
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
        
        //CHECK THIS TUPLE
        for (map<string, int>::iterator mit = indexFound.begin(); mit != indexFound.end(); mit++){
        string currentValue = check[mit->second]; //VALUE FROM WHERE I FIRST FOUND THE VARIABLE

            for (unsigned int i = 0; i < check.size(); i++){
                
                if (query.parametersList[i].paramValue == mit->first){// QUERY HAS AN X!
                    if (check[i] == currentValue && check.flag == false){ // IF THE VALUE OF THE TUPLE MATCHES THE ORIGINAL VALUE WHERE THE QUERY HAS AN X DO NOT FLAG
                        //ANALYZE CHECK VS CURRENT VALUE TO MAKE SURE THAT THEY ARE THE SAME
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

void Interpreter::Project(Relation &r, Predicate &query){
    Relation temp;
    temp.relName = r.relName;
    for (unsigned int i = 0; i < query.parametersList.size(); i++){
        if (query.parametersList[i].isConstant != true){
            temp.relAtt.push_back(query.parametersList[i].paramValue);
        }   
    }
    //FOR EVERY ATT IN THE NEW SCHEME/QUERY, ONLY PROJECT VARIABLES 
    map<string, int> indexToPush;//MAP KEEPS TRACKS OF WHICH VARIABLES WERE FOUND IN WHICH COLUMN

    vector<int> colsUsed;//THIS WILL MAKE SURE THAT WE DO NOT GET DUPLICATED COLUMNS

    for (unsigned int i = 0; i < query.parametersList.size(); i++){
        Parameter qParam = query.parametersList[i];
        //FOR EVERY ATTRIBUTE KEEP IF THEY ARE VARIABLES
        if (qParam.isConstant != true){
            //WE HAVE A VARIABLE
            map<string, int>::iterator currentRow = indexToPush.find(qParam.paramValue);
            if (currentRow->first != qParam.paramValue){
                
                bool alreadyUsed = false;
                int signedJ = (int) i;
                if (colsUsed.size() < 1){ // IF THIS IS THE FIRST VARIABLE
                    indexToPush.insert({qParam.paramValue, i});
                    colsUsed.push_back(i);
                }
                else {
                    //CHECK TO SEE THAT THIS COLUMN NUMBER HASNT BEEN USED
                    for (unsigned int k = 0; k < colsUsed.size(); k++){
                        if (signedJ == colsUsed[k]){
                            //UPS COLUMN ALREADY USED DO NOT USE AGAIN
                            alreadyUsed = true;
                            break;
                        }
                    }
                }
                if (alreadyUsed == false){
                    //COLUMN NUMBER WASNT USED. WE CAN ADD TO THE MAP
                    indexToPush.insert({qParam.paramValue, i});
                }
            }
        }
    }

    //FOR EVERY TUPLE WE PROJECT THE COLUMNS PASSED USING THE MAP
    for (set<Tuple>::iterator tIt = r.tuples.begin(); tIt != r.tuples.end(); tIt++){
        Tuple tempTuple = *tIt;
        vector<string>newTempTuple(temp.relAtt.size(), ""); // INITIALIZE A VECTOR OF SIZE X BASED ON THE SIZE OF THE NEW COLUMNS
        
        for (map<string, int>::iterator pushM = indexToPush.begin(); pushM != indexToPush.end(); pushM++){
            //FOR EVERY VARIABLE IN THE MAP CHECK TO SEE IF WE FIND THAT IN THE RELATIONS ATTRIBUTES
            string att1 = pushM->first;
            StringToUp(att1);
            
            for (unsigned int i = 0; i < temp.relAtt.size(); i++){
                string att2 = temp.relAtt[i];
                StringToUp(att2);
                if (att1 == att2){
                    newTempTuple[i] = tempTuple[pushM->second];
                }
            }
        }
        //cout << "CLEANING TUPLE!" << endl;
        Tuple finalTuple;
        for (unsigned int i = 0; i < newTempTuple.size(); i++){
            if (newTempTuple[i] != ""){
                finalTuple.push_back(newTempTuple[i]);
            }
        }
        temp.tuples.insert(finalTuple);
        newTempTuple.clear();
    }

    r = temp;

};

void Interpreter::StringToUp(string &str){
    for (unsigned int i = 0; i < str.size(); i++){
        str[i] = tolower(str[i]);
    }
};

void Interpreter::Rename(Relation &r, Predicate &query){
    for (unsigned int i = 0; i < r.relAtt.size(); i++){
        r.relAtt[i] = query.parametersList[i].paramValue;
    }
};

void Interpreter::evRules(vector<RuleClass> &rules){  
    totalRuns++;
    //cout << "EV RULES!" << endl;
    map<string, Relation> tempMap;
    tempMap = dbMap;

    for (unsigned int i = 0; i < rules.size(); i++){
        //FOR EVERY RULE DO A RULE EVALUATION
        Predicate head = rules[i].headPredicate;
        vector<Predicate> body = rules[i].bodyPredicate;

        vector<Relation> resultingRelations;

        string newRelationName;
        
        Relation r;
        
        if (body.size() < 2){
            //IF I ONLY HAVE 1 PREDICATE FIND A RELATION AND DO A SELECT PROJECT AND RENAME BASED ON THE PREDICATE
            Relation newRa = dbMap.find(body[0].nameID)->second;
            Relation newRb = Select(body[0], newRa);
            Project(newRb, body[0]);
            Rename(newRb, body[0]);
            newRb.relName = body[0].nameID;
            
            r = newRb;
        }
        else if (body.size() > 1){
            //FOR EACH DO SELECT PROJECT RENAME
            //GET INMEDIATE RELATIONS RESULTS FROM THE PREDICATES ON THE RIGHT SIDE OF THE RULE
            for (unsigned int i = 0; i < body.size(); i++){
                Relation newRa = dbMap.find(body[i].nameID)->second;
                Relation newRb = Select(body[i], newRa);
                
                Project(newRb, body[i]);
                Rename(newRb, body[i]);
                newRb.relName = body[i].nameID;
                resultingRelations.push_back(newRb);
            }
            //NOW FOR EVERY RESULTING RELATION FROM THE PREDICATES DO A JOIN 
            //R TO JOIN WITH THE NEXT RELATION.
            for (unsigned int z = 0; z < resultingRelations.size(); z++){
                combineRelations(r, resultingRelations[z]);
                for (unsigned int j = 0; j < r.relAtt.size(); j++){
                    if (newRelationName.find(r.relAtt[j]) == string::npos){
                        newRelationName.append(r.relAtt[j]);
                    }
                }
            }
            //ADD RELATION TO THE DATABASE AFTER JOINING ALL RELATIONS
            dbMap.insert({newRelationName, r});
        }
        //AFTER THE JOIN PROJECT THE RULE BASED ON THE HEAD PREDICATE
        ProjectRule(r, head, body);
    }

    map<string, Relation>::iterator z, y;
    for (z = tempMap.begin(), y = dbMap.begin(); z != tempMap.end(); z++, y++){
        if (z->first == y->first){
            Relation rO = z->second;
            Relation rT = y->second;
            
            if (rO.tuples != rT.tuples){
                moreTuples = true;
            }
        }
        else {
            //THERE ARE NEW RELATIONS! SO WE RUN IT AGAIN!
            moreTuples = true;
        }
    }
    


    if (moreTuples == true){ // FIXED POINT ALGORITHM ?? FOR n TIMES THAT THERE ARE NEW TUPLES RUN n TIMES
        moreTuples = false;
        evRules(rules);
    }

};

void Interpreter::combineRelations(Relation &rA, Relation &rB){
    
    Relation temp;

    bool commonAtt = false;

    // CREATE NEW SCHEME
    for (unsigned int i = 0; i < rA.relAtt.size(); i++){ 
        string att = rA.relAtt[i];
        StringToUp(att);
        if (find(temp.relAtt.begin(), temp.relAtt.end(), att) != temp.relAtt.end()){
            //DUPLICATED SKIP
        }
        else {
            temp.relAtt.push_back(att);
        }
    }

    for (unsigned int i = 0; i < rB.relAtt.size(); i++){
        string att = rB.relAtt[i];
        StringToUp(att);
        if (find(temp.relAtt.begin(), temp.relAtt.end(), att) != temp.relAtt.end()){
            //DUPLICATED SKIP
            commonAtt = true;
        }
        else {
            temp.relAtt.push_back(att);
        }
    }
    
    if (rA.relAtt.size() < 1){
        //ONLY ONE ATTRIBUTE SO WE JUST PUSH IT.
        temp = rB;
    }
    else {
        //FOR EVERY TUPLE IN THE FIRST RELATION
        for (set<Tuple>::iterator it1 = rA.tuples.begin(); it1 != rA.tuples.end(); it1++){
            vector<string> t1 = *it1;
            //FOR EVERY TUPLE IN THE SECOND RELATION
            
            for (set<Tuple>::iterator it2 = rB.tuples.begin(); it2 != rB.tuples.end(); it2++){
                vector<string> t2 = *it2;
                Tuple newTuple;
                
                //ALWAYS PUSH FIRST TUPLE TO NEW TUPLE
                for (unsigned int i = 0; i < rA.relAtt.size(); i++){
                    newTuple.push_back(t1[i]);
                }

                bool canJoin = true;
                //NOW CHECK SECOND TUPLE AGAINST PREVIOUS TUPLE
                vector<int> doAddIndex;
                for (unsigned int i = 0; i < rB.relAtt.size(); i++){
                    string att1 = rB.relAtt[i];
                    StringToUp(att1);
                    bool canAdd = true;
                    for (unsigned int j = 0; j < rA.relAtt.size(); j++){
                        string att2 = rA.relAtt[j];
                        StringToUp(att2);
                
                        //JOIN TUPLES TOGETHER SKIP DUPLICATES
                        if (att1 == att2){
                            //FOUND DUPLICATED VARIABLE
                            if (t2[i] == t1[j]  && canJoin != false){
                                //The values are the same do not add
                                canJoin = true;
                            }
                            else if (t2[i] != t1[j]){
                                //THE VALUES ARE DIFFERENT CANNOT BE JOINED
                                canJoin = false;
                                break;
                            }
                            //THIS CANNOT BE ADDED AS THE ATTRIBUTE IS NOT UNIQUE
                            canAdd = false;
                            break;
                        }
                        else {
                            if (j == rA.relAtt.size() - 1 && canAdd == true){
                                //GOT THE END OF FIRST TUPLE AND CONCLUDED THAT THE VALUE CAN BE ADDED AS IT IS UNIQUE
                                //cout << t2[i] << endl;
                                doAddIndex.push_back(i);
                            }
                        }
                    }
                }
                //PUSH THE INDEXED THAT PASSED THE LOGIC
                for (unsigned int k = 0; k < doAddIndex.size(); k++){
                    //cout << t2[doAddIndex[k]] << endl;
                    newTuple.push_back(t2[doAddIndex[k]]);
                }
                
                if (canJoin == true && commonAtt == true){
                    //cout << "INSERTED TUPLE1" << endl;
                    temp.tuples.insert(newTuple);
                    newTuple.clear();
                }

                if (commonAtt == false){
                    //JOIN WITHOUT ANY COMMON ATTRIBUTES
                    //cout << "INSERTED TUPLE2" << endl;
                    temp.tuples.insert(newTuple);
                    newTuple.clear();
                }
            }   
        }
    }

    rA = temp;

    temp.relAtt.clear();
    temp.relName.clear();
    temp.tuples.clear();
};

void Interpreter::ProjectRule(Relation &r, Predicate &head, vector<Predicate> &body){
    //THIS WILL RETURN A RELATION WITH ONLY THE COLUMNS THAT WE WANT

    Relation headRelation = dbMap.find(head.nameID)->second;
    Relation oldRelation = dbMap.find(head.nameID)->second;
    
    for (unsigned int i = 0; i < head.parametersList.size(); i++){
        headRelation.relAtt[i] = head.parametersList[i].paramValue;
    }//EDITS HEAD RELATION TO MATCH THE HEAD SYNTAX

    //PRINT RULE
    cout << head.nameID << "(";
    for (unsigned int p = 0; p < head.parametersList.size(); p++){
        cout << head.parametersList[p].paramValue;
        if (p == head.parametersList.size() - 1){
            cout << ") :- ";
        }
        else {
            cout << ",";
        }
    }
    for (unsigned int q = 0; q < body.size(); q++){
        cout << body[q].nameID << "(";
        for (unsigned int p = 0; p < body[q].parametersList.size(); p++){
            cout << body[q].parametersList[p].paramValue;
            if (p == body[q].parametersList.size() - 1){
                if (q == body.size() - 1){
                    cout << ").";
                }
                else {
                    cout << "),";
                }
            }
            else {
                cout << ",";
            }
        }   
    }
    cout << endl;
    
    map<string, int> indexToPush;
    for (unsigned int i = 0; i < r.relAtt.size(); i++){
        string att1 = r.relAtt[i];
        StringToUp(att1);
        for (unsigned int j = 0; j < headRelation.relAtt.size(); j++){
            //FOR EVERY COLUM IN NEW RELATION CHECK EVERY COLUMN OF OLD RELATION
            string att2 = headRelation.relAtt[j];
            StringToUp(att2);
            if (att1 == att2){
                //cout << "Found where the two variables meet" << endl;
                //WE FOUND A MATCH BETWEEN SCHEME 2 and 1
                //NOW GET ALL THE TUPLES BUT ONLY FOR THE COLUMS THAT WE NEED. WE NEED COLUMS J WHERE SCHEME 1 AND 2 MATCH. 
                //NOW GET THE TUPLES AT THOSE COLUMS AND PUSH INTO A SINGLE TUPLE 
                //FOR EACH TUPLE IN SCHEME 1
                indexToPush.insert({r.relAtt[i], i});
            }
        }
    }

    for (set<Tuple>::iterator tIt = r.tuples.begin(); tIt != r.tuples.end(); tIt++){
        Tuple tempTuple = *tIt;
        vector<string>newTempTuple(headRelation.relAtt.size(), "");
        //cout << "STARTING TO PUSH TUPLES BASED ON HEAD RULE" << endl;
        for (map<string, int>::iterator pushM = indexToPush.begin(); pushM != indexToPush.end(); pushM++){
            string att2 = pushM->first;
            StringToUp(att2);
            for (unsigned int i = 0; i < headRelation.relAtt.size(); i++){
                string att1 = headRelation.relAtt[i];
                StringToUp(att1); 
                if (att1 == att2){
                    newTempTuple[i] = tempTuple[pushM->second];
                }
                else {

                }
            }
        }

        Tuple finalTuple;
        for (unsigned int i = 0; i < newTempTuple.size(); i++){
            if (newTempTuple[i] != ""){
                finalTuple.push_back(newTempTuple[i]);
            }
        }


        headRelation.tuples.insert(finalTuple);
        newTempTuple.clear();
    }

    
    //PRINT OUTPUT
    if (headRelation.tuples != oldRelation.tuples){
        //cout << "YES FOUND THAT WE INSERTED A TUPLE!" << endl;
        //moreTuples = true;
        headRelation.relAtt = oldRelation.relAtt;
        //NOW PRINT ONLY NEW TUPLES!
        for (set<Tuple>::iterator itr = headRelation.tuples.begin(); itr != headRelation.tuples.end(); itr++){
            bool inOldR = false;
           for (set<Tuple>::iterator it1 = oldRelation.tuples.begin(); it1 != oldRelation.tuples.end(); it1++){
               if (*itr == *it1){
                   //TUPLES ARE THE SAME!
                   inOldR = true;
               }
            }
           if (inOldR == false){
                headRelation.PrintRuleTuple(*itr, headRelation.relAtt);
           }
        }
    }
    
    //NOW WE NEED TO MAKE A UNION BETWEEN THE RELATION THAT ITS ALREADY THERE AND THE NEW RELATION THAT WE JUST CREATED
    //NEW RELATIONS IS HEAD RELATION
    Union(oldRelation, headRelation);
    
};

void Interpreter::Union(Relation &oldR, Relation &newR){
    set<Tuple> allTuples;
    for (set<Tuple>::iterator oldIt = oldR.tuples.begin(); oldIt != oldR.tuples.end(); oldIt++){
        allTuples.insert(*oldIt);
    }
    for (set<Tuple>::iterator newIt = newR.tuples.begin(); newIt != newR.tuples.end(); newIt++){
        allTuples.insert(*newIt);
    }

    map<string, Relation>::iterator mIt = dbMap.find(oldR.relName);
    mIt->second.tuples.clear();
    mIt->second.tuples = allTuples;
};

void Interpreter::PrintRelation(Relation &oldR){
    cout << oldR.relName << endl;
    for (unsigned int k = 0; k < oldR.relAtt.size(); k++){
        cout << " " << oldR.relAtt[k] << "   ";
    }
    cout << endl;
    for (set<Tuple>::iterator itr = oldR.tuples.begin(); itr != oldR.tuples.end(); itr++){
        oldR.PrintTuple(*itr);
    }
    cout << endl;
};