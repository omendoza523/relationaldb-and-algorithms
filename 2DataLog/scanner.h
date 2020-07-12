#pragma once
#include <string>
#include <cctype>
#include <iostream>
#include <fstream>
#include <vector>
#include "token.h"
#include <regex>

using namespace std;

//CONSTRUCTOR

class Scanner {
    public:
        ifstream readFile;
        int line = 1;
        int currentCharacter;

        void scanToken(int& currentCharacter, int& currentLine);
        //VECTOR 
        vector<Token> tokens;
        void readScanner(string fileName);
        void scanIdentifier(string& str, regex& identifier);
        void scanString(int& currentCharacter);
        void scanSingleComment(int& currentCharacter);
        void scanMultyComment(int& currentCharacter);

};