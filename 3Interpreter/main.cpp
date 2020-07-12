#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <vector>
#include <set>

#include "token.h"
#include "scanner.h"
#include "parser.h"
#include "dataLogProgram.h"
#include "Interpreter.h"

using namespace std;

int main (int argc, char* argv[]){

    string fileName = argv[1];

    Scanner scan;
    Parser p;
    Interpreter dbInt;

    scan.readScanner(fileName);

    p.passTokens(scan.tokens);
    
    dbInt.AddRelations(p.dataProgram.schemes, p.dataProgram.facts); // CREATES A NEW TABLE ON THE DB PUSHES THE RELATION WITH THE SCHEME NAME AND ATTRIBUTES
    // PUSH THE TUPLES TO THE RIGHT RELATION

    //EVALUATES QUERIES!!
    //cout << "Query Evaluation" << endl;
    
    dbInt.evQuery(p.dataProgram.queries);

    /*for (map<string, Relation>::iterator it = dbInt.dbMap.begin(); it != dbInt.dbMap.end(); it++){
        cout << it->first << endl;
        for (unsigned int k = 0; k < it->second.relAtt.size(); k++){
            cout << " " << it->second.relAtt[k] << "   ";
        }
        cout << endl;
        for (set<Tuple>::iterator itr = it->second.tuples.begin(); itr != it->second.tuples.end(); itr++){
            it->second.PrintTuple(*itr);
        }
        cout << endl;
    }*/
    
    return 0;
};