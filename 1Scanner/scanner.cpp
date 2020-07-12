#include "scanner.h"
#include "token.h"

void Scanner::readScanner(string fileName){

    readFile.open(fileName);

    for(;;){ // READ FILES AND GET TOKENS

        currentCharacter = readFile.get();

        if (currentCharacter != -1){
            //NOT END OF FILE DO SOMETHNG AND SCANN TOKEN RETURN TOKEN WITH VALUE AND TYPE
            //SCANN CURRENT CHAR FOR SPECIFIC TOKEN
            if (currentCharacter == '\n'){ // NEW LINE COUNTER
                line++;
            }
            else if (isspace(currentCharacter)) {
                //IT IS SPACE SKIP DONT DO ANYTHING AND RUN LOOP AGAIN
            }
            else {
                //NOT NEW LINE AND NOT SPACE THEN IT IS A VALID CHARACTER
                //CALL SCANNER AND PASS THE CURRENT CHARACTER TO SCAN THE TYPE OF THE TOKEN
                scanToken(currentCharacter, line);
            }
        }
        else {
            //END OF FILE SCANN TOKEN AS END OF FILE AND RETURN TOKEN WITH VALUE AND TYPE
            string str = "";
            Token newToken(EOFILE, str, line);
            tokens.push_back(newToken);
            break;
        }
    };
};

void Scanner::scanIdentifier(string& str, regex& identifier){

    if (regex_match(str, identifier)){ // Any letters as part of the character A-Z and a-z

        string myIdent = str;

        for (;;){

            string myChar;
            
            int cChar = readFile.peek();
            myChar = (char) cChar;

            regex followedBY("([A-Za-z]|[0-9])");

            if (regex_match(myChar, followedBY)){
                myIdent += (char) readFile.get();
            }
            else {
                
                if (myIdent.length()){
                    
                    if (myIdent == "Schemes" && (!isalpha(readFile.peek()) || !isdigit(readFile.peek()))){
                        Token newToken = Token(SCHEMES, myIdent, line);
                        tokens.push_back(newToken);
                    }
                    else if (myIdent == "Facts" && (!isalpha(readFile.peek()) || !isdigit(readFile.peek()))){
                        Token newToken = Token(FACTS, myIdent, line);
                        tokens.push_back(newToken);
                    }
                    else if (myIdent == "Rules" && (!isalpha(readFile.peek()) || !isdigit(readFile.peek()))){
                        Token newToken = Token(RULES, myIdent, line);
                        tokens.push_back(newToken);
                    }
                    else if (myIdent == "Queries" && (!isalpha(readFile.peek()) || !isdigit(readFile.peek()))){
                        Token newToken = Token(QUERIES, myIdent, line);
                        tokens.push_back(newToken);
                    }
                    else {
                        Token newToken = Token(ID, myIdent, line);
                        tokens.push_back(newToken);
                    }
                }
                break;
            }
        }
    }
    else {
        Token newToken = Token(UNDEFINED, str, line);
        tokens.push_back(newToken);
    }

};

void Scanner::scanString(int& currentCharacter){

    string buildString;
    buildString = (char) currentCharacter;

    string myChar;

    int stringStartLine = line;

    for (;;){

        if (readFile.peek() != '\''){ //IF FOLLOW BY ANY TYPE OF CHARACTERS EXCEPT NEW LINE
            
            if (readFile.peek() != -1){
                myChar = (char) readFile.get();
                buildString += myChar;
                
                if (myChar == "\n"){
                    line++;
                }
            }
            else if (readFile.peek() != '\'' && readFile.peek() == -1){
                Token newToken = Token(UNDEFINED, buildString, stringStartLine);
                tokens.push_back(newToken);
                break;
            }
        }
        if (readFile.peek() == '\''){ // WHEN FOLLOWED BY A CLOSING QUOTE 
            myChar = (char) readFile.get();
            buildString += myChar;
            if (readFile.peek() == '\''){ // IF THERE IS DOUBLE QUOTE KEEP GOING
                buildString += (char) readFile.get();
            }
            else { // IF THERE ISNT A DOUBLE QUOTE STOP
                Token newToken = Token(STRING, buildString, stringStartLine);
                tokens.push_back(newToken);
                break;
            }
        }
    }
};

void Scanner::scanSingleComment(int& currentCharacter){

    string buildString;
    buildString = (char) currentCharacter;

    string myChar;

    for (;;){

        if (readFile.peek() != '\n' && readFile.peek() != -1){
            myChar = (char) readFile.get();
            buildString += myChar;
        }
        else {
            Token newToken = Token(COMMENT, buildString, line);
            tokens.push_back(newToken);
            break;
        }
    }
};

void Scanner::scanMultyComment(int& currentCharacter){

    string buildString;
    buildString = (char) currentCharacter;

    string myChar;

    buildString += (char) readFile.get();

    int commentStartLine = line;

    for (;;){

        if (readFile.peek() != '|' && readFile.peek() != -1){

            myChar = (char) readFile.get();
            buildString += myChar;
            if (myChar == "\n"){
                line++;
            }
        }
        else if (readFile.peek() != '|' && readFile.peek() == -1){
            line++;
            Token newToken = Token(UNDEFINED, buildString, commentStartLine);
            tokens.push_back(newToken);
            break;
        }
        else if (readFile.peek() == '|'){

            myChar = (char) readFile.get();
            buildString += myChar;
            
            if (readFile.peek() == '#'){

                myChar = (char) readFile.get();
                buildString += myChar;

                Token newToken = Token(COMMENT, buildString, commentStartLine);
                tokens.push_back(newToken);
                break;
            }
            else {
                myChar = (char) readFile.get();
                buildString += myChar;
            }
        }
    }
};

void Scanner::scanToken(int& currentCharacter, int& currentLine){ // EVALUATE THE TOKENS PASSED FROM MAIN

    int c = currentCharacter;
    int line = currentLine;
    string str ;
    str = (char) c;
    
    regex identifier("([A-Za-z]+)");
    
    switch (c)
    {
        case ',':
            {
                Token newToken = Token(COMMA, str, line);
                tokens.push_back(newToken);
            }
            break;
        case '.':
            {
                Token newToken = Token(PERIOD, str, line);
                tokens.push_back(newToken);
            }
            break;
        case '?':
            {
                Token newToken = Token(Q_MARK, str, line);
                tokens.push_back(newToken);
            }
            break;
        case '(':
            {
                Token newToken = Token(LEFT_PAREN, str, line);
                tokens.push_back(newToken);
            }
            break;
        case ')':
            {
                Token newToken = Token(RIGHT_PAREN, str, line);
                tokens.push_back(newToken);
            }
            break;
        case ':':
            {
                if (readFile.peek() == '-'){
                    str += (char) readFile.get();
                    Token newToken = Token(COLON_DASH, str, line);
                    tokens.push_back(newToken);
                }
                else{
                    Token newToken = Token(COLON, str, line);
                    tokens.push_back(newToken);
                }
            }
            break;
        case '*':
            {
                Token newToken = Token(MULTIPLY, str, line);
                tokens.push_back(newToken);
            }
            break;
        case '+':
            {
                Token newToken = Token(ADD, str, line);
                tokens.push_back(newToken);
            }
            break;
        case '\'':
            {
                scanString(c);
            }
            break;
        case '#':
            {
                if (readFile.peek() == '|'){
                    scanMultyComment(c);
                }
                else {
                    scanSingleComment(c);
                }
                
            }
            break;
        default: 
            {
                scanIdentifier(str, identifier);
            }
            break;
    }
};

/* case 'S':
            {
                if (readFile.peek() == 'c'){
                    str += (char) readFile.get();
                    if (readFile.peek() == 'h'){
                        str += (char) readFile.get();
                        if (readFile.peek() == 'e'){
                            str += (char) readFile.get();
                            if (readFile.peek() == 'm'){
                                str += (char) readFile.get();
                                if (readFile.peek() == 'e'){
                                    str += (char) readFile.get();
                                    if (readFile.peek() == 's'){
                                        str += (char) readFile.get();
                                        if (str == "Schemes"){
                                            if (){
                                                scanIdentifier(str, identifier);
                                            }
                                            else {
                                                Token newToken = Token(SCHEMES, str, line);
                                                tokens.push_back(newToken);
                                            }
                                        }
                                    }
                                    else {
                                        scanIdentifier(str, identifier);
                                    }
                                }
                                else {
                                    scanIdentifier(str, identifier);
                                }
                            }
                            else {
                                scanIdentifier(str, identifier);
                            }
                        }
                        else {
                            scanIdentifier(str, identifier);
                        }
                    }
                    else {
                        scanIdentifier(str, identifier);
                    }
                }
                else {
                    scanIdentifier(str, identifier);
                }
            }
            break;
        case 'F':
            {
                if (readFile.peek() == 'a'){
                    str += (char) readFile.get();
                    if (readFile.peek() == 'c'){
                        str += (char) readFile.get();
                        if (readFile.peek() == 't'){
                            str += (char) readFile.get();
                            if (readFile.peek() == 's'){
                                str += (char) readFile.get();
                                if (str == "Facts"){
                                    if (isalpha(readFile.peek()) || isdigit(readFile.peek())){
                                        scanIdentifier(str, identifier);
                                    }
                                    else {
                                        Token newToken = Token(FACTS, str, line);
                                        tokens.push_back(newToken);
                                    }
                                }
                            }
                            else {
                                scanIdentifier(str, identifier);
                            }
                        }
                        else {
                            scanIdentifier(str, identifier);
                        }
                    }
                    else {
                        scanIdentifier(str, identifier);
                    }
                }
                else {
                    scanIdentifier(str, identifier);
                }
            }
            break;
        case 'R':
            {
                if (readFile.peek() == 'u'){
                    str += (char) readFile.get();
                    if (readFile.peek() == 'l'){
                        str += (char) readFile.get();
                        if (readFile.peek() == 'e'){
                            str += (char) readFile.get();
                            if (readFile.peek() == 's'){
                                str += (char) readFile.get();
                                if (str == "Rules"){
                                    if (isalpha(readFile.peek()) || isdigit(readFile.peek())){
                                        scanIdentifier(str, identifier);
                                    }
                                    else {
                                        Token newToken = Token(RULES, str, line);
                                        tokens.push_back(newToken);
                                    }
                                }
                            }
                            else {
                                scanIdentifier(str, identifier);
                            }
                        }
                        else {
                            scanIdentifier(str, identifier);
                        }
                    }
                    else {
                        scanIdentifier(str, identifier);
                    }
                }
                else {
                    scanIdentifier(str, identifier);
                }
            }
            break;
        case 'Q':
            {
                if (readFile.peek() == 'u'){
                    str += (char) readFile.get();
                    if (readFile.peek() == 'e'){
                        str += (char) readFile.get();
                        if (readFile.peek() == 'r'){
                            str += (char) readFile.get();
                            if (readFile.peek() == 'i'){
                                str += (char) readFile.get();
                                if (readFile.peek() == 'e'){
                                    str += (char) readFile.get();
                                    if (readFile.peek() == 's'){
                                        str += (char) readFile.get();
                                        if (str == "Queries"){
                                            if (isalpha(readFile.peek()) || isdigit(readFile.peek())){
                                                scanIdentifier(str, identifier);
                                            }
                                            else {
                                                Token newToken = Token(QUERIES, str, line);
                                                tokens.push_back(newToken);
                                            }
                                        }
                                    }
                                    else {
                                        scanIdentifier(str, identifier);
                                    } 
                                }
                                else {
                                    scanIdentifier(str, identifier);
                                } 
                            }
                            else {
                                scanIdentifier(str, identifier);
                            }                             
                        }
                        else {
                            scanIdentifier(str, identifier);
                        }                        
                    }
                    else {
                        scanIdentifier(str, identifier);
                    }               
                } 
                else {
                    scanIdentifier(str, identifier);
                } 
            }
            break;
            */