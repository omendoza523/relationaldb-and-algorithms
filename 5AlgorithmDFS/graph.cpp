#include "graph.h"

string Graph::toString(){
	string output;
	for(std::map<int,Node>::iterator it = allNodes.begin(); it != allNodes.end(); ++it)
	{
		output += it->second.toString() + "\n";
	}

	return output;
};

vector<Node> Graph::getPostOrder(){
	//cout << "GETTING POST ORDER" << endl;
	vector<Node> newNodes;

	for(map<int,Node>::iterator it = allNodes.begin(); it != allNodes.end(); ++it){
		//cout << "CHECK EVERY NODE IN THE MAP" << endl;
		if(!it->second.isVisited){
			//IF THIS NODE HAS NOT BEEN VISITED THEN WE GET THE DFS FROM THIS NODE.
			vector<Node> temp = DFS(it->second);
			//DFS RETURNS THE NODES THAT WERE NOT VISITED BASED ON THE CURRENT NODE THAT STARTED THE DFS
			//WHEN THE DFS FINISHES WE SAY THAT WE POP THE NODE FROM THE STACK AND ADDED TO THE POST ORDER LIST
			newNodes.insert(newNodes.end(), temp.begin(), temp.end());
		}
	}
	//RETURN THE POST ORDER 
	return newNodes;
};

vector<Node> Graph::DFS(Node &currentNode){
	//cout << "DOING DFS" << endl;
	vector<Node> newNodes;

	currentNode.isVisited = true;
	//VISIT THIS NODE
	for(unsigned int i = 0; i < currentNode.adjacentNodes.size(); i++){
		//FOR EVERY NODE THAT IS ADJACENT TO THIS ONE THEN GO TO THAT NODE
		if(allNodes[currentNode.adjacentNodes[i]].isVisited != true){
			vector<Node> temp = DFS(allNodes[currentNode.adjacentNodes[i]]);
			//RETURN RESULTING NODES FROM THE DFS
			newNodes.insert(newNodes.end(), temp.begin(), temp.end());
		}

	}
	newNodes.push_back(currentNode);

	return newNodes;
};