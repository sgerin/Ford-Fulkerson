#include "node.hpp"
#include "graph.hpp"

Node::Node()
{
    
}

Node::Node(std::string name, Graph* g)
{
    this->name = name;
    this->degree = 0;
    this->pred = 0;
    this->succ = 0;
    this->graph = g;
    this->level = 0;
}


Node::Node(std::string name, int deg, std::vector<std::string> predlist, int nb_pred, Graph* graph)
{
    this->name = name;
    this->degree = deg;
    this->pred_names = predlist;
    this->pred = nb_pred;
    this->succ = 0;
    this->level = 0;
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


void Node::addPredecessors(std::vector<std::string> predlist)
{
    pred_names = predlist;
    buildPredecessors();
}

/*void Node::addSuccessors(std::vector<std::string> succlist)
{
    succ
}*/

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
    std::vector<Node*>::iterator it;
    
    /*for ( it=pred_names.begin() ; it < pred_names.end(); it++ )
    {
        s += ", ";
        s += *it;
    }
    s += ".";*/
    
    for ( it=predecessors.begin() ; it < predecessors.end(); it++ )
    {
        s += (*it)->getName();
        s += ", ";
        //s += it->toString();
    }
    s += ".";
    
    s += "list of successors : " ;
    
    for ( it=successors.begin() ; it < successors.end(); it++ )
    {
        s += (*it)->getName();
        s += ", ";
        //s += it->toString;
    }

    s += " LEVEL ";
    std::stringstream st;
    st << level;
    s += st.str();
    return s;
}


int Node::higherLevel()
{
    std::vector<Node*>::iterator it;
    int love = 0;
    for ( it=successors.begin() ; it < successors.end(); it++ )
    {
        if(love < (*it)->getLevel())
            love = (*it)->getLevel();
    }
    return love;
}


std::string Node::getName()
{
    return name;
}


int Node::getNbPredecessors()
{
    return pred;
}

int Node::getNbSuccessors()
{
    return succ;
}

int Node::getLevel()
{
    return level;
}

void Node::setLevel(int l)
{
    level = l;
}

void Node::setNbPredecessors(int n)
{
    pred = n;
}


std::vector<Node*> Node::getSuccessors()
{
    return this->successors;
}


std::vector<Node*> Node::getPredecessors()
{
    return this->predecessors;
}

/*Node* Node::alpha(std::vector<Node*> nopred)
{
    
    //graph->getAlpha()->
}

Node* Node::omega(std::vector<Node*> nosucc)
{
    
}*/