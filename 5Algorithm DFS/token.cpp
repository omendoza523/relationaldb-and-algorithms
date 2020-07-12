#include "token.h"


//CREATE TOKEN CLASS
Token::Token (TokenType newToken, string& newValue, int& newLine){
    typeOfToken = getEnumName(newToken);
    value = newValue;
    lineAt = newLine;
};

string Token::getEnumName(TokenType& enumValue){

    switch (enumValue)
    {
        case 0:
            {
                return "COMMA";
            }
            break;
        case 1:
            {
                return "PERIOD";
            }
            break;
        case 2:
            {
                return "Q_MARK";
            }
            break;
        case 3:
            {
                return "LEFT_PAREN";
            }
            break;
        case 4:
            {
                return "RIGHT_PAREN";
            }
            break;
        case 5:
            {
                return "COLON";
            }
            break;
        case 6:
            {
                return "COLON_DASH";
            }
            break;
        case 7:
            {
                return "MULTIPLY";
            }
            break;
        case 8:
            {
                return "ADD";
            }
            break;
        case 9:
            {
                return "SCHEMES";
            }
            break;
        case 10:
            {
                return "FACTS";
            }
            break;
        case 11:
            {
                return "RULES";
            }
            break;
        case 12:
            {
                return "QUERIES";
            }
            break;
        case 13:
            {
                return "ID";
            }
            break;
        case 14:
            {
                return "STRING";
            }
            break;
        case 15:
            {
                return "COMMENT";
            }
            break;
        case 16:
            {
                return "EOF";
            }
            break;
        default: 
            {
                return "UNDEFINED";
            }
            break;
    }
};

