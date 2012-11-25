#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include "node.hpp"


class Graph{
public:
    Graph();
    Graph(char* file);
    Node* getAlpha();
    Node* getOmega();
    Node* getNode(std::string node);
    void finish();
    std::string display();
    void displayGraph();
    
private:
    std::map<std::string, Node*> graph;
    std::vector<std::string> split(std::string &s, char delim);
    std::vector<std::string>& split(std::string &s, char delim, std::vector<std::string> &elems);
    void buildAlphaOmega();
    int globalHigherLevel();
    void leveling();
    void earlyDate();
    void lateDate();
    void margin();
};


#endif