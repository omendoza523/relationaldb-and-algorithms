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

    //PERFORM SELECT BASED ON A QUERY
    //ONLY KEEP ROWS WHERE THE RUPLE VALUES MATCHES THE QUERY VALUES
    //ASSUME THE SELECT OPEATION NEW QUERY IS SELECT Scheme1(X,X,X, '1'); FIRST TEST CASE SHOULD RETURN 0 TUPLES

    string relName2 = "alpha New";
    vector<string> Scheme2 = {"3", "X", "X", "X"};
    set<vector<int>> Scheme2Tuples;

    for (unsigned int i = 0; i < Scheme2.size(); i++){
        //FOR EVERY PARAMETER IN THE QUERY ANALIZE IF IT IS A STRING AND IF IT IS EQUAL TO THE ATTRIBUTE NAME OR IF IT IS A VALUE
        //IN PROJECT CHECK IF IT IS AN ID. IF IT IS AN ID CHECK TO SEE IF IT MATCHES ATTRIBUTE OF IT ID IS DUPLICATED. IF IT IS A STRING WE HAVE A CONSTANT
        if (Scheme2[i] == Scheme1[i]){ // QUERY PARAMETER MATCHES ATTRIBUTE
            // WE IGNORE THIS AS THIS CAN BE ANY VALUE, WE ARE LOOKING FOR THE CONSTANT
        }
        else {
            //cout << "1*" << endl;
            //IF IT IS A CONSTANT OR A VARIABLE 
            //IN PROJECT WE HAVE ID AND STRING. HERE WE WILL USE STRING AS ID AND DIGIT AS STRING OR CONSTANT VALUE
            //BREAK DOWN STRING
            for (unsigned int j = 0; j < Scheme2[i].size(); j++){
                if ( isalpha(Scheme2[i].at(j)) ){

                }
                else if ( isdigit(Scheme2[i].at(j)) ){
                    //cout << "2*" << endl;
                    //FOUND A CONSTANT! 
                    //RETURN ALL TUPLES WHERE POSITION IS i AND VALUE IS Scheme2[i].at(j)
                    int value = (int) Scheme2[i].at(j) - 48;
                    //cout << "value " << typeid(Scheme2[i].at(j)).name() << endl;

                    //cout << "value " << typeid(value).name() << "***" << value << endl;
                    int position = i;

                    //NOW CHECK TUPLES AND RETURN
                    for (unsigned int k = 0; k < Scheme1Tuples.size(); k++){
                        vector<int> tempT = Scheme1Tuples[k];
                        
                        // AVOID OUT OF RANGE LOOKUP
                        //CHECK POSITION
                        //CHECK VALUE
                        //cout << "3*" << endl;
                        if (tempT[position] == value){
                            //FOUND VALUE PUSH TUPLE
                            //cout << "4*" << endl;
                            vector<int> Scheme2Tuple = tempT;
                            Scheme2Tuples.insert(Scheme2Tuple);
                        }
                    }
                }
            }
        }
    }
    

    //PRINT AFTER PROJECT
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