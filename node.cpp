#include "node.hpp"

Node::Node()
{
    
}

Node::Node(std::string name, int deg, std::vector<std::string> predlist, int nb_pred, Graph* graph)
{
    this->name = name;
    this->degree = deg;
    this->pred_names = predlist;
    this->pred = nb_pred;
    this->graph = graph;
    if(pred_names.size() != pred)
    {
        std::cout << "Erreur nombre de sommets precedents != liste des sommets precedents" << std::endl;
        exit(0);
    }
}

void Node::finish()
{
    
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
    
    for ( it=pred_names.begin() ; it < pred_names.end(); it++ )
    {
        s += ", ";
        s += *it;
    }
    s += ".";
    return s;
}


