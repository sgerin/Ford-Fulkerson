#ifndef NODE
#define NODE

#import <string>
#import <vector>
#include <sstream>
#import <iostream>

class Graph;

class Node{
public:
    Node();
    Node(std::string name, int deg, std::vector<std::string> pred, Graph* g);
    //~Node();
    std::string toString();
    
private:
    std::string name;
    int degree;
    std::vector<std::string> predecessors;
    Graph* graph;
};

#endif