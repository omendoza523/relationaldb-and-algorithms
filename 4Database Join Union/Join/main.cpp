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
    vector<int> Scheme1Tuple2 = {8, 2, 3, 4};
    vector<int> Scheme1Tuple3 = {6, 7, 8, 9};

    //GROUP ALL TUPLES
    vector<vector<int>> Scheme1Tuples;  
    Scheme1Tuples.push_back(Scheme1Tuple1);
    Scheme1Tuples.push_back(Scheme1Tuple2);
    Scheme1Tuples.push_back(Scheme1Tuple3);
    
    //CREATE SECOND RELATION
    string relName2 = "alpha New";
    vector<string> Scheme2 = {"one", "two", "five"};
    vector<vector<int>> Scheme2Tuples;
    
    //CREATE TUPLES
    vector<int> Scheme2Tuple1 = {1, 2, 5};
    vector<int> Scheme2Tuple2 = {2, 2, 6};
    vector<int> Scheme2Tuple3 = {6, 7, 10};
    
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


    for (unsigned int m = 0; m < Scheme1Tuples.size(); m++){ // CREATE EMPTY TUPLES TO PUSH TUPLES FOR THE NEW RELATION
        vector<int> Scheme2Tuple; 
        Scheme2Tuples.push_back(Scheme2Tuple);
    }

    //PERFORM JOIN OPERATION HERE! FOR ATTRIBUTES
    //FOR EVERY ATTRIBUTE ON THE FIRST VECTOR CHECK THE SECOND FOR DUPLICATES AND CREATE A MAP TO CHECK DUPLICATE VALUE AND LOCATION
    for (unsigned int j = 0; j < Scheme1.size(); j++){
        newScheme.push_back(Scheme1[j]);
    }
    
    for (unsigned int i = 0; i < Scheme2.size(); i++){
        bool duplicate = false;
        for (unsigned int j = 0; j < Scheme1.size(); j++){
            if (Scheme2[i] == Scheme1[j]){
                //ATTRIBUTE IS ALREADY THERE DO NOT HAD
                duplicate = true;
            }
        }
        if (duplicate != true){
            newScheme.push_back(Scheme2[i]);
        }
    }
    
    //NOW THAT WE HAVE THE ATTRIBUTES WE NEED TO KNOW IF THE TWO TUPLES CAN BE JOINED
    //THEN JOIN THE TUPLES
    bool canJoin = true;
    for (unsigned int i = 0; i < Scheme1Tuples.size(); i++){
        vector<int> t1 = Scheme1Tuples[i];
        
        for (unsigned int j = 0; j < Scheme2Tuples.size(); j++){
            vector<int> t2 = Scheme2Tuples[j];
            //cout << t2.size() << "  &&&&&&&&&&&&&" << endl;
            vector<int> newTupleVector;

            for (unsigned int z = 0; z < Scheme1.size(); z++){
                newTupleVector.push_back(t1[z]);
            }
            
            set<int> doAddIndex;

            canJoin = true;
            if (t2.size() > 0){
                for (unsigned int mA = 0; mA < Scheme2.size(); mA++){
                    bool canAdd = true;
                    //cout << Scheme2.size() << "~~~~~~~~~~~~" << endl;
                    //cout << Scheme2[mA] << "````````" << endl;

                    for (unsigned int nB = 0; nB < Scheme1.size(); nB++){
                        //cout << Scheme2[mA] << " //////////////// " << Scheme1[nB] << endl;

                        if (canJoin != true){
                            break;
                        }
                        
                        if (Scheme2[mA] == Scheme1[nB]){
                            //cout << t2[mA] << " ********** " << t1[nB] << endl;
                            if (t2[mA] == t1[nB] && canJoin == true){
                                //cout << t1[n] << " ********** " << t2[m] << endl;
                                canJoin = true;
                            }
                            else if (t2[mA] != t1[nB]){
                                //cout << t1[n] << " ********** " << t2[m] << endl;
                                canJoin = false;
                                break;
                            }
                            canAdd = false;
                            break;
                        }
                        else {
                            if (nB == Scheme1.size() - 1 && canAdd == true){

                                doAddIndex.insert(mA);
                            }
                        }
                    }
                }
                //cout << canJoin << endl;
                for (set<int>::iterator it = doAddIndex.begin(); it != doAddIndex.end(); it++){
                    newTupleVector.push_back(t2[*it]);
                }
                if (canJoin == true){
                    newTuples.insert(newTupleVector);
                    newTupleVector.clear();
                }
                else {
                    newTupleVector.clear();
                }
            }            
        }
    }
    

    //PRINT AFTER JOIN
    cout << relName2 << endl;
    for (unsigned int i = 0; i < newScheme.size(); i++){
        cout << newScheme[i] << " ";
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
