#include "Relation.h"

Relation::Relation (){
    relName = "";
    vector<string> relAtt;
    set<Tuple> tules;
}

Relation::Relation(string name, vector<string> attributes){
    relName = name;
    relAtt = attributes;
    set<Tuple> tuples;
}

void Relation::PrintTuple(Tuple t){
    for (unsigned int i = 0; i < t.size(); i++){
        cout << t[i] << "  ";
    }
    cout << endl;
}

void Relation::PrintRuleTuple(Tuple t, vector<string> p){
    for (unsigned int i = 0; i < t.size(); i++){
        if (i == 0){
            if (i == t.size() - 1){
                cout << "  " << p[i] << "=" << t[i];
            }
            else {
            cout << "  " << p[i] << "=" << t[i] << ", ";
            }
        }
        else if (i == t.size() - 1){
            cout << p[i] << "=" << t[i];
        }
        else {
            cout << p[i] << "=" << t[i] << ", ";
        }
    }
    cout << endl;
}
