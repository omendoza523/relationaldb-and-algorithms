#pragma once
#include <string>
#include <iostream>

using namespace std;

enum TokenType { //token types that are allowed
    COMMA, 
    PERIOD, 
    Q_MARK, 
    LEFT_PAREN, 
    RIGHT_PAREN, 
    COLON, 
    COLON_DASH, 
    MULTIPLY, 
    ADD, 
    SCHEMES, 
    FACTS, 
    RULES, 
    QUERIES,
    ID,
    STRING,
    COMMENT,
    EOFILE,
    UNDEFINED
};

class Token {  //CONSTRUCTOR
    public:
        string value;
        int lineAt;
        string typeOfToken;

        string getEnumName(TokenType& enumValue);
        
        Token(TokenType newToken, string& newValue, int& newLine);
};




//string printToken (string value, int line, TokenType typeOfToken);
