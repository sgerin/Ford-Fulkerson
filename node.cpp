#include "node.hpp"

Node::Node()
{
    
}

Node::Node(std::string name, int deg, std::vector<std::string> pred, Graph* graph)
{
    this->name = name;
    this->degree = deg;
    this->predecessors = pred;
    this->graph = graph; 
}

std::string Node::toString()
{
    std::string s = "Node : ";
    s += name;
    s += " degree : ";
    s += degree;
    s += "list of predecessors : ";
    std::vector<std::string>::iterator it;
    
    for ( it=predecessors.begin() ; it < predecessors.end(); it++ )
    {
        s += *it;
        s += ", ";
    }
    s += ".";
    return s;
}