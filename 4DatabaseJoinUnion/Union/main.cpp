#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <vector>
#include <set>
#include <map>

using namespace std;

int main (int argc, char* argv[]){

    //CREATE A RELATION
    string relName = "alpha";

    //CREATE A SCHEME
    vector<string> Scheme1 = {"one", "two", "three", "four"};

    //CREATE THE TUPLES
    vector<int> Scheme1Tuple1 = {1, 2, 3, 4};
    vector<int> Scheme1Tuple2 = {2, 3, 4, 5};
    vector<int> Scheme1Tuple3 = {3, 4, 5, 6};

    //GROUP ALL TUPLES
    vector<vector<int>> Scheme1Tuples;  
    Scheme1Tuples.push_back(Scheme1Tuple1);
    Scheme1Tuples.push_back(Scheme1Tuple2);
    Scheme1Tuples.push_back(Scheme1Tuple3);
    
    //CREATE SECOND RELATION
    string relName2 = "alpha New";
    vector<string> Scheme2 = {"one", "two", "three", "four"};
    vector<vector<int>> Scheme2Tuples;
    
    //CREATE TUPLES
    vector<int> Scheme2Tuple1 = {1, 2, 3, 4};
    vector<int> Scheme2Tuple2 = {5, 6, 7, 8};
    vector<int> Scheme2Tuple3 = {6, 7, 8, 9};
    
    //GROUP TUPLES
    Scheme2Tuples.push_back(Scheme2Tuple1);
    Scheme2Tuples.push_back(Scheme2Tuple2);
    Scheme2Tuples.push_back(Scheme2Tuple3);
    
    //THE TWO RELATIONS JOIN ON FISH AND VALUE 1 
    //EXPECTED OUTPUT ONLY TUPLES AT 0 CAN JOIN RESULTING IN 1, 2, 3, 4, 5.
    set<vector<int>> newTuples;
    vector<string> newScheme;
    

    //PRINT BEFORE JOIN
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

    cout << relName << endl;
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
    cout << endl;

    //PERFORM UNION
    for (unsigned int i = 0; i < Scheme1Tuples.size(); i++){
        newTuples.insert(Scheme1Tuples[i]);
    }
    

    for (unsigned int i = 0; i < Scheme2Tuples.size(); i++){
        newTuples.insert(Scheme2Tuples[i]);
    }


    //PRINT AFTER UNION
    cout << relName2 << endl;
    for (unsigned int i = 0; i < Scheme1.size(); i++){
        cout << Scheme1[i] << " ";
    }
    cout << endl;
    for (set<vector<int>>::iterator it = newTuples.begin(); it != newTuples.end(); it++){
        vector<int> temp = *it;
        for (unsigned int j = 0; j < temp.size(); j++){
            cout << temp[j] << "    ";
        }
        cout << endl;
    }

    return 0;
};
