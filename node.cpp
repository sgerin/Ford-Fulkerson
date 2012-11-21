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
    std::stringstream ss;
    ss << degree;
    s += ss.str();;
    s += " list of predecessors : ";
    std::vector<std::string>::iterator it;
    
    for ( it=predecessors.begin() ; it < predecessors.end(); it++ )
    {
        s += ", ";
        s += *it;
    }
    s += ".";
    return s;
}