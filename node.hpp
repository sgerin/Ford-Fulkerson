#ifndef NODE_H
#define NODE_H

#include <string>
#include <vector>
#include <sstream>
#include <iostream>
//#include "graph.hpp"

class Graph;

class Node{
public:
    Node();
    Node(std::string name, Graph* g);
    Node(std::string name, int deg, std::vector<std::string> pred, int nbPred, Graph* g);
    //~Node();
    void buildPredecessors();
    void addSuccessor(Node* node);
    //void addSuccessors(std::vector<std::string> succlist);
    void addPredecessors(std::vector<std::string> predlist);
    //void buildSuccessors();
    std::string toString();
    std::string getName();
    int getNbPredecessors();
    int getNbSuccessors();
    //Node* alpha();
    //Node* omega();
    
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