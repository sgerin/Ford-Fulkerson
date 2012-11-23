#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include "node.hpp"

//class Node;

class Graph{
public:
    Graph();
    Graph(char* file);
    //~Graph();
    Node* getAlpha();
    Node* getOmega();
    Node* getNode(std::string node);
    void finish();
    void display();
    
private:
    std::map<std::string, Node*> graph;
    std::vector<std::vector<Node*>> lists;
    std::vector<std::string> split(std::string &s, char delim);
    std::vector<std::string>& split(std::string &s, char delim, std::vector<std::string> &elems);
    void buildAlphaOmega();
    //void buildOmega();
    void addAlpha(Node* node);
    void addOmega(Node* node);
    void leveling();
};


#endif