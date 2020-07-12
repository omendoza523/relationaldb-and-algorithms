#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <vector>
#include <set>

using namespace std;

int main (int argc, char* argv[]){

    //CREATE A RELATION
    string relName = "alpha";

    //CREATE A SCHEME
    vector<string> Scheme1 = {"cat", "fish", "dog", "bunny"};

    //CREATE THE TUPLES
    vector<int> Scheme1Tuple1 = {1, 2, 1, 2};
    vector<int> Scheme1Tuple2 = {3, 4, 3, 4};
    vector<int> Scheme1Tuple3 = {5, 6, 5, 6};

    //GROUP ALL TUPLES
    vector<vector<int>> Scheme1Tuples;
    Scheme1Tuples.push_back(Scheme1Tuple1);
    Scheme1Tuples.push_back(Scheme1Tuple2);
    Scheme1Tuples.push_back(Scheme1Tuple3);

    //PRINT BEFORE PROJECT
    cout << relName << endl;
    for (unsigned int i = 0; i < Scheme1.size(); i++){
        cout << Scheme1[i] << " ";
    }
    cout << endl;
    for (unsigned int i = 0; i < Scheme1Tuples.size(); i++){
        vector<int> temp = Scheme1Tuples[i];
        for (unsigned int j = 0; j < temp.size(); j++){
            cout << temp[j] << "    ";
        }
        cout << endl;
    }
    cout << endl;

    //PERFORM PROJECT BASED ON A QUERY
    //ONLY KEEP COLUMS THAT ARE ASKED IN THE PROJECT OPERATION
    //ASSUME THE PROJECT OPEATION NEW SCHEME IS Scheme1 = {"cat", "fish"};

    string relName2 = "alpha New";
    vector<string> Scheme2 = {"fish", "dog", "bunny"};
    vector<vector<int>> Scheme2Tuples;

    for (unsigned int m = 0; m < Scheme1Tuples.size(); m++){ // CREATE EMPTY TUPLES TO PUSH TUPLES FOR THE NEW RELATION
        vector<int> Scheme2Tuple; // KEEP ALL THE ROWS FOR PROJECT
        Scheme2Tuples.push_back(Scheme2Tuple);
    }

    //FOR EVERY ATTRIBUTE IN THE NEW SCHEME GET THE VALUES FROM THE PREVIOUS RELATION
    for (unsigned int i = 0; i < Scheme2.size(); i++){
        
        for (unsigned int j = 0; j < Scheme1.size(); j++){
            //FOR EVERY COLUM IN NEW RELATION CHECK EVERY COLUMN OF OLD RELATION
            if (Scheme2[i] == Scheme1[j]){
                //WE FOUND A MATCH BETWEEN SCHEME 2 and 1
                //NOW GET ALL THE TUPLES BUT ONLY FOR THE COLUMS THAT WE NEED. WE NEED COLUMS J WHERE SCHEME 1 AND 2 MATCH. 
                //NOW GET THE TUPLES AT THOSE COLUMS AND PUSH INTO A SINGLE TUPLE 
                //FOR EACH TUPLE IN SCHEME 1
                for (unsigned int k = 0; k < Scheme1Tuples.size(); k++){
                    //GET ONLY THE COLUMS AT J AND PUSH THEM TO THE CORRECT TUPLES IN SCHEME 2
                    vector<int> tupleTemp = Scheme1Tuples[k];// THIS IS THE FIRST TUPLE IN SCHEME 1

                    //GET THE TUPLE COLUMS

                    Scheme2Tuples[k].push_back(tupleTemp[j]);
                    
                    tupleTemp.clear();
                }
            }
        }
    }

    //PRINT BEFORE PROJECT
    cout << relName2 << endl;
    for (unsigned int i = 0; i < Scheme2.size(); i++){
        cout << Scheme2[i] << " ";
    }
    cout << endl;
    for (unsigned int i = 0; i < Scheme2Tuples.size(); i++){
        vector<int> temp = Scheme2Tuples[i];
        for (unsigned int j = 0; j < temp.size(); j++){
            cout << temp[j] << "    ";
        }
        cout << endl;
    }

    return 0;
};