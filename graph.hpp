#ifndef GRAPH
#define GRAPH

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
//#include "node.hpp"

class Node;

class Graph{
public:
    Graph();
    Graph(char* file);
    //~Graph();
    Node* getAlpha();
    Node* getOmega();
    Node* getNode(std::string node);
    void display();
    //std::vector<Node> getNodes();
    
private:
    //std::vector<Node> graph;
    std::map<std::string, Node*> graph;
    std::vector<std::string> split(std::string &s, char delim);
    std::vector<std::string>& split(std::string &s, char delim, std::vector<std::string> &elems);
};


#endif