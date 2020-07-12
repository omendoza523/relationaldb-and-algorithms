#include "parser.h"

void Parser::passTokens (vector<Token> tokens){
    for (unsigned i = 0; i < tokens.size(); i++){
        if (tokens[i].typeOfToken != "COMMENT"){
            lTokens.push_back(tokens[i]);
        }
    }
    parseDLP();
};

void Parser::matchToken(string strToken){

    string e = "";
      
    if (lTokens[0].typeOfToken == strToken){
        lTokens.erase(lTokens.begin());
    }
    else {
        e = "Failure!\n  (" + lTokens[0].typeOfToken + ",\"" + lTokens[0].value + "\"," + to_string(lTokens[0].lineAt) + ")";
        cout << e << endl;
        exit(0);
    } 
};

void Parser::parseDLP(){

    matchToken("SCHEMES");
    matchToken("COLON");
    parseScheme();
    matchToken("FACTS");
    matchToken("COLON");
    parseFacts();
    matchToken("RULES");
    matchToken("COLON");
    parseRule();
    matchToken("QUERIES");
    matchToken("COLON");
    parseQuerie();

    if (lTokens[0].typeOfToken == "EOF"){
        cout << "Success!" << endl;
    }
    else {
        string e = "Failure!\n  (" + lTokens[0].typeOfToken + ",\"" + lTokens[0].value + "\"," + to_string(lTokens[0].lineAt) + ")";
        cout << e << endl;
        exit(0);
    };

};

void Parser::parseScheme(){

    tempList.clear();
    string nameOfScheme = "";

    if (lTokens[0].typeOfToken == "ID"){ // FOUND THE NAME
    //BEFORE POPPING FROM STACK SAVE VALUE TO nameOfScheme
        nameOfScheme = lTokens[0].value;
        matchToken("ID");
    }
    
    matchToken("LEFT_PAREN");
    //INSIDE THE SCHEME! LOOK FOR PARAMS
    if (lTokens[0].typeOfToken == "ID"){// FOUND FIRST PARAM
        // IT IS THE ID OF THE SCHEME
        Parameter newParam = Parameter(lTokens[0].value, lTokens[0].typeOfToken);
        tempList.push_back(newParam);
        matchToken("ID"); // POP ID AFTER IT MATCHES
    }
    else {
        matchToken("ID"); // DID NOT FIND AN ID SO WE EXIT WITH LINE ISSUE
    }
    if (lTokens[0].typeOfToken == "COMMA"){
        //THERE IS A COMMA SO THERE ARE MORE ID'S
        matchToken("COMMA"); // COMMA MATCH POP THE COMA CALL SCHEME LIST
        parseIdList();
    }
    
    if (lTokens[0].typeOfToken == "RIGHT_PAREN"){
        matchToken("RIGHT_PAREN");
    }
    // HERE WE FINISH THE FIRST SCHEME WITH ALL ITS IDS
    // BEFORE GOING TO THE NEXT SCHEME WE PUSH AN ID VECTOR
    // WE INITIALIZE THE PREDICATE WITH THE FIRST ID OR NAME
    // AND THEN A LIST OF IDS STORED IN A TEMPORARY VARIABLE
    
    Predicate newScheme = Predicate(nameOfScheme, tempList);

    dataProgram.addScheme(newScheme);

    parseSchemeList();
};

void Parser::parseIdList(){
    if (lTokens[0].typeOfToken == "ID"){
        // IT IS ANOTHER PARAM! or ID
        Parameter newParam = Parameter(lTokens[0].value, lTokens[0].typeOfToken);
        tempList.push_back(newParam);
        matchToken("ID"); // POP ID AFTER IT MATCHES
    }

    if (lTokens[0].typeOfToken == "COMMA"){
        //THERE IS A COMMA SO THERE ARE MORE ID'S
        matchToken("COMMA"); // COMMA MATCH POP THE COMA CALL SCHEME LIST
        parseIdList();
    }


};

void Parser::parseSchemeList(){

    if (lTokens[0].typeOfToken == "ID"){
        //THERE IS ANOTHER SCHEME!
        parseScheme();
    }

};

void Parser::parseFacts(){

    if (lTokens[0].typeOfToken == "ID"){

        tempList.clear();
        string nameOfFact = "";

        nameOfFact = lTokens[0].value;
        matchToken("ID");

        matchToken("LEFT_PAREN");
        //INSIDE THE FACT!
        if (lTokens[0].typeOfToken == "STRING"){
            // IT IS THE STRING OF THE FACT
            Parameter newParam = Parameter(lTokens[0].value, lTokens[0].typeOfToken);
            tempList.push_back(newParam);
            dataProgram.addDomain(lTokens[0].value);
            matchToken("STRING"); // POP STRING AFTER IT MATCHES
        }
        else {
            matchToken("STRING");
        }

        if (lTokens[0].typeOfToken == "COMMA"){
            //THERE IS A COMMA SO THERE ARE MORE STRINGS
            matchToken("COMMA"); // COMMA MATCH POP THE COMA CALL STRING LIST
            parseStringList();
        }
        

        matchToken("RIGHT_PAREN");
        matchToken("PERIOD");


        Predicate newFact = Predicate(nameOfFact, tempList);

        dataProgram.addFact(newFact);

        parseFactList();
    }
    
};

void Parser::parseStringList(){

    if (lTokens[0].typeOfToken == "STRING"){
        // IT IS ANOTHER STRING
        Parameter newParam = Parameter(lTokens[0].value, lTokens[0].typeOfToken);
        tempList.push_back(newParam);
        dataProgram.addDomain(lTokens[0].value);
        matchToken("STRING"); // POP STRING AFTER IT MATCHES
    }

    if (lTokens[0].typeOfToken == "COMMA"){
        //THERE IS A COMMA SO THERE ARE MORE STRINGS
        matchToken("COMMA"); // COMMA MATCH POP THE COMA CALL STRING LIST
        parseStringList();
    }
};

void Parser::parseFactList(){
    if (lTokens[0].typeOfToken == "ID"){
        //THERE IS ANOTHER FACT!
        parseFacts();
    }
};

void Parser::parseRule(){

    tempListPredicate.clear();

    if (lTokens[0].typeOfToken == "ID"){
        Predicate head = parseHeadPredicate();
        matchToken("COLON_DASH");
        parsePredicate();

        if (lTokens[0].typeOfToken == "PERIOD"){
            matchToken("PERIOD"); // END OF MY PREDICATES
        }
        //FINISH WITH RULE 1 CHECK TO SEE IF THERE ARE OTHER RULES
        //FINISHED THE RULE CREATE RULE OBJECT AND PUSH TO VECTOR
        if (head.nameID != "empty"){
            RuleClass newRule = RuleClass(head, tempListPredicate);

            dataProgram.addRule(newRule);
        }

        parseRuleList();
    }
    else {
        // IT IS EMPTY COUT
        //cout << "empty RULES" << endl;
    }

};

void Parser::parseRuleList(){
    if (lTokens[0].typeOfToken == "ID"){
        //FOUND ANOTHER RULE!
        parseRule();
    }
}

Predicate Parser::parseHeadPredicate(){
    
    tempList.clear();
    string nameOfHeadPred = "";
    if (lTokens[0].typeOfToken == "ID"){
        //FOUND ID OF PREDICATE
        nameOfHeadPred = lTokens[0].value;
        matchToken("ID");
        // IF I CAN MATCH ID THEN
        matchToken("LEFT_PAREN");
        //FOUND FIRST PAREMETER
        Parameter newParam = Parameter(lTokens[0].value, lTokens[0].typeOfToken);
        tempList.push_back(newParam);
        matchToken("ID");

        parseIdList();
        matchToken("RIGHT_PAREN");

        Predicate newHeadPredicate = Predicate(nameOfHeadPred, tempList);

        return newHeadPredicate;
    }
    else {
        //THIS IS AN EMPTY RULE!
        //DONT DO ANYTHING
        Predicate newHeadPredicate = Predicate("empty", tempList);

        return newHeadPredicate;
    }
    //finish with head Predicate
};

void Parser::parsePredicate(){
    // cout << "Got INTO PREDICATE" << endl;
    tempList.clear();
    string nameOfBodyPred = "";
    if (lTokens[0].typeOfToken == "ID"){
        //FOUND ID OF PREDICATE
        nameOfBodyPred = lTokens[0].value;
        matchToken("ID");
    }
    matchToken("LEFT_PAREN");
    if (lTokens[0].typeOfToken == "RIGHT_PAREN"){   
        //THE PREDICATE IS EMPTY!
        matchToken("UNDEFINED"); // EXIT AND THROW ERROR
    }
    else {
        parseParameter(); // CHECK FOR PARAMETERS

    }
    matchToken("RIGHT_PAREN");

    Predicate newBodyPredicate = Predicate(nameOfBodyPred, tempList);

    tempListPredicate.push_back(newBodyPredicate);

    if (lTokens[0].typeOfToken == "COMMA"){
        matchToken("COMMA");
        parsePredicateList(); // THERE ARE MORE!
    }

};

void Parser::parsePredicateList(){
    if (lTokens[0].typeOfToken == "ID"){
        parsePredicate();
    }
};

void Parser::parseParameter(){

    // cout << "Got INTO PARAMETER TOKEN TYPE --> " << lTokens[0].typeOfToken << endl;
    if (lTokens[0].typeOfToken == "STRING"){
        Parameter newParam = Parameter(lTokens[0].value, lTokens[0].typeOfToken);
        tempList.push_back(newParam);
        matchToken("STRING"); // POP TERMINAL
    }

    if (lTokens[0].typeOfToken == "ID"){
        Parameter newParam = Parameter(lTokens[0].value, lTokens[0].typeOfToken);
        tempList.push_back(newParam);
        matchToken("ID"); // POP TERMINAL
    }

    if (lTokens[0].typeOfToken == "LEFT_PAREN"){
    //   cout << "GOT INTO EXPRESSION!" << endl;
        expression = "";
        tempList.push_back(parseExpression());
        expression = "";
    }

    if (lTokens[0].typeOfToken == "COMMA"){
        matchToken("COMMA");
        parseParameterList();
    }
};

void Parser::parseParameterList(){
    parseParameter();
};

Parameter Parser::parseExpression(){

    expression += lTokens[0].value;
    matchToken("LEFT_PAREN");

    expression += lTokens[0].value;
    parseParameterFromExpression();
    
    expression += lTokens[0].value;
    parseOperator();
    
    expression += lTokens[0].value;
    parseParameterFromExpression();

    expression += lTokens[0].value;
    matchToken("RIGHT_PAREN");
    
    Parameter newParam = Parameter(expression, "expression");
    
    return newParam;
};

void Parser::parseParameterFromExpression(){
    // cout << "Got INTO PARAMETER FROM EXPRESSION TOKEN TYPE --> " << lTokens[0].typeOfToken << endl;
    if (lTokens[0].typeOfToken == "STRING"){
        matchToken("STRING"); // POP TERMINAL
    }

    if (lTokens[0].typeOfToken == "ID"){
        matchToken("ID"); // POP TERMINAL
    }

    if (lTokens[0].typeOfToken == "LEFT_PAREN"){
    //   cout << "GOT INTO EXPRESSION!" << endl;
        parseExpressionFromExpression();
    }

    if (lTokens[0].typeOfToken == "COMMA"){
        matchToken("COMMA");
        parseParameterFromExpressionList();
    }
};

void Parser::parseParameterFromExpressionList(){
    parseParameterFromExpression();
};

void Parser::parseExpressionFromExpression(){

    matchToken("LEFT_PAREN");

    expression += lTokens[0].value;
    parseParameterFromExpression();
    
    expression += lTokens[0].value;
    parseOperator();
    
    expression += lTokens[0].value;
    parseParameterFromExpression();

    expression += lTokens[0].value;
    matchToken("RIGHT_PAREN");

};

void Parser::parseOperator(){
    if (lTokens[0].typeOfToken == "ADD"){
        matchToken("ADD");  
    }
    else if (lTokens[0].typeOfToken == "MULTIPLY"){
        matchToken("MULTIPLY");  
    }
    else {
        if (lTokens[0].typeOfToken != "EOF"){
            string e = "Failure!\n  (" + lTokens[0].typeOfToken + ",\"" + lTokens[0].value + "\"," + to_string(lTokens[0].lineAt) + ")";
            cout << e << endl;
            exit(0);
        }
    }
};

void Parser::parseQuerie(){
    string nameOfQuery = "";
    //cout << "Got INTO QUERIE" << endl;

    if (lTokens[0].typeOfToken == "ID"){
        nameOfQuery = lTokens[0].value;
    }
    parsePredicate();
    matchToken("Q_MARK");

    Predicate newQuery = Predicate(nameOfQuery, tempList); 

    dataProgram.addQuery(newQuery);

    parseQuerieList();
};

void Parser::parseQuerieList(){
    if (lTokens[0].typeOfToken == "ID"){
        //FOUND ANOTHER QUERIE!
        parseQuerie();
    }
};

