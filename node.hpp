#ifndef NODE_H
#define NODE_H

#include <string>
#include <vector>
#include <sstream>
#include <iostream>

class Graph;

class Node{
public:
    Node();
    Node(std::string name, Graph* g);
    Node(std::string name, int deg, std::vector<std::string> pred, unsigned int nbPred, Graph* g);
    void buildPredecessors();
    void addSuccessor(Node* node);
    void addPredecessors(std::vector<std::string> predlist);
    std::string toString();
    std::string getName();
    int getNbPredecessors();
    int getNbSuccessors();
    void setNbPredecessors(int n);
    std::vector<Node*> getSuccessors();
    std::vector<Node*> getPredecessors();
    int higherLevel();
    void setLevel(int l);
    int getLevel();
    int getDegree();
    int getEarlyDate();
    int getLateDate();
    void setEarlyDate(int i);
    void setLateDate(int i);
    int getPredecessorsEarlyDate();
    int getSuccessorsLateDate();
    int getMargin();
    void setMargin(int i);
    bool isCritical();
    void setCritical(bool b);

    
private:
    std::string name;
    int degree;
    int level;
    int earlyDate;
    int lateDate;
    int margin;
    bool critical;
    std::vector<std::string> pred_names;
    std::vector<Node*> predecessors;
    std::vector<Node*> successors;
    unsigned int pred;
    unsigned int succ;
    Graph* graph;
};

#endif