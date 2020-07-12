#include <iostream>
#include <fstream>
#include <typeinfo>
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

    //PRINT BEFORE RENAME
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

    //PERFORM RENAME BASED ON A QUERY

    string relName2 = "alpha New";
    vector<string> Scheme2 = {"dog", "horse", "kitten", "shark"};
    set<vector<int>> Scheme2Tuples;

    for (unsigned int i = 0; i < Scheme1Tuples.size(); i++){
        Scheme2Tuples.insert(Scheme1Tuples[i]);
    }

    for (unsigned int i = 0; i < Scheme2.size(); i++){
        Scheme1[i] == Scheme2[i];
    }
    
    //PRINT AFTER RENAME
    cout << relName2 << endl;
    cout << "Query: Scheme1( ";
    for (unsigned int i = 0; i < Scheme2.size(); i++){
        cout << Scheme2[i] << " ";
    }
    cout << ")" << endl;
    if (Scheme2Tuples.size() == 0){
        //EMPTY!
        cout << "EMPTY: NO MATCHING TUPLES" << endl; 
    }
    else {
        set<vector<int>>::iterator sIt;
        for (sIt = Scheme2Tuples.begin(); sIt != Scheme2Tuples.end(); sIt++){
            vector<int> temp = *sIt;
            
            for (unsigned int j = 0; j < temp.size(); j++){
                cout << temp[j] << "    ";
            }
            cout << endl;
        }
    }

    return 0;
};