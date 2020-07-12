#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <vector>

#include "token.h"
#include "scanner.h"
#include "parser.h"
#include "dataLogProgram.h"

using namespace std;

int main (int argc, char* argv[]){

    string fileName = argv[1];

    Scanner scan;
    Parser p;

    scan.readScanner(fileName);

    p.passTokens(scan.tokens);

    p.dataProgram.toString();

    return 0;
};