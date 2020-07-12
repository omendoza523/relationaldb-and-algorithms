#pragma once

#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include "node.h"

using namespace std;

class Graph{
public:
	Graph(){}
	~Graph(){}

	map<int, Node> allNodes;

	string toString();
	vector<Node> getPostOrder();
	vector<Node> DFS(Node &currentNode);
};