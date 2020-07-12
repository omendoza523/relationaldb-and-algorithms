#pragma once

#include <vector>
#include <string>
#include <set>

using namespace std;

class Node{
public:
	Node(){}
	~Node(){}

	int nodeName;
	vector<int> adjacentNodes;
	bool isVisited = false;
	int postOrderNumber = -1;

	string toString(){
		//cout << "NODE TO STRING" << endl;
		string out;
		out += "R" + to_string(nodeName) + ":";
		for(unsigned int i = 0; i < adjacentNodes.size(); i++)
		{
			if(i > 0){
                out += ",";
            }
            out += "R" + to_string(adjacentNodes[i]);
		}
		return out;
	};

	bool hasCircDep(){
        for(unsigned int i = 0; i < adjacentNodes.size(); i++){
			if(adjacentNodes[i] == nodeName){
				return true;
			}
		}
		return false;
	};

	bool operator<(const Node& currentNode) const{ //OPERATOR TO FIND IF NODE NAME IS BIGGER OR SMALLER THAT NODE PARAMETER
        
		if(nodeName < currentNode.nodeName){
            return true;
        }
		else{
            return false;
        }
	};

	bool operator==(const Node& currentNode){ // FFIND NODE NAME IF EQUAL TO CURRENT NODE NADE

		if(nodeName == currentNode.nodeName){
            return true;
        }
		else{
            return false;
        }
	};
};