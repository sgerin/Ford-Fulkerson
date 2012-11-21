#ifndef NODE
#define NODE

#import <string>
#import <vector>
#include <sstream>
#import <iostream>
#import "graph.hpp"

class Node{
public:
    Node();
    Node(std::string name, int deg, std::vector<std::string> pred, int nbPred, Graph* g);
    //~Node();
    void buildPredecessors();
    void addSuccessor(Node* node);
    //void buildSuccessors();
    std::string toString();
    
private:
    std::string name;
    int degree;
    std::vector<std::string> pred_names;
    std::vector<Node*> predecessors;
    std::vector<Node*> successors;
    int pred;
    int succ;
    Graph* graph;
};

#endif