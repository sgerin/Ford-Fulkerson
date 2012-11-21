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
    if(predlist.size() != nb_pred)
    {
        std::cout << "Erreur nombre de sommets precedents != liste des sommets precedents" << std::endl;
        exit(0);
    }
}

void Node::buildPredecessors()
{
    std::vector<std::string>::iterator it;
    for ( it=pred_names.begin() ; it < pred_names.end(); it++ )
    {
        predecessors.push_back(graph->getNode(*it));
        ++pred;
        graph->getNode(*it)->addSuccessor(this);
    }

    

}


void Node::addSuccessor(Node* node)
{
    successors.push_back(node);
    ++succ;
    
    //if(successors.size() != succ)
    //{
    //    std::cout << "Erreur nombre de sommets precedents != liste des sommets precedents" << std::endl;
    //    exit(0);
    //}
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


