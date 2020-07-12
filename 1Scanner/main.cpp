#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <vector>

#include "token.h"
#include "scanner.h"

using namespace std;

int main (int argc, char* argv[]){

    string fileName = argv[1];

    Scanner scan;

    scan.readScanner(fileName);

    for (unsigned int i = 0; i < scan.tokens.size(); i++){
        cout << "(" << scan.tokens[i].typeOfToken << ",\"" << scan.tokens[i].value << "\"," << scan.tokens[i].lineAt << ")" << endl; 
    }

    cout << "Total Tokens = " << scan.tokens.size();

    return 0;
};