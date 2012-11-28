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
    this->earlyDate = 0;
    this->lateDate = 0;
    this->margin = 0;
    this->critical = false;
}


Node::Node(std::string name, int deg, std::vector<std::string> predlist, unsigned int nb_pred, Graph* graph)
{
    this->name = name;
    this->degree = deg;
    this->pred_names = predlist;
    this->pred = nb_pred;
    this->succ = 0;
    this->level = 0;
    this->earlyDate = 0;
    this->lateDate = 0;
    this->margin = 0;
    this->critical = false;
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
        graph->getNode(*it)->addSuccessor(this);
    }
}


void Node::addPredecessors(std::vector<std::string> predlist)
{
    pred_names = predlist;
    buildPredecessors();
    ++pred;
}


void Node::addSuccessor(Node* node)
{
    successors.push_back(node);
    ++succ;
}



std::string Node::toString()
{
    std::string s = "Node : ";
    s += name;
    s += " cost : ";
    std::stringstream ss;
    ss << degree;
    s += ss.str();;
    ss.str("");
    ss.clear();
    
    s += " List of predecessors : ";
    std::vector<Node*>::iterator it;
    
    for ( it=predecessors.begin() ; it < predecessors.end(); it++ )
    {
        s += (*it)->getName();
        s += " ";
    }
    
    s += ". List of successors : " ;
    
    for ( it=successors.begin() ; it < successors.end(); it++ )
    {
        s += (*it)->getName();
        s += " ";
    }

    s += ". Level ";
    ss << level;
    s += ss.str();
    ss.str("");
    ss.clear();

    s+= ". Early Date ";
    ss << earlyDate;
    s += ss.str();
    ss.str("");
    ss.clear();

    
    s+= ". Late Date ";
    ss << lateDate;
    s += ss.str();
    ss.str("");
    ss.clear();

    
    s+= ". Margin ";
    ss << margin;
    s += ss.str();
    ss.str("");
    ss.clear();

    
    s += ". Critical ";
    ss << std::boolalpha << critical;
    s += ss.str();
    ss.str("");
    ss.clear();


    return s;
}


int Node::higherLevel()
{
    std::vector<Node*>::iterator it;
    int love = 0;
    for ( it=predecessors.begin() ; it < predecessors.end(); it++ )
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

int Node::getDegree()
{
    return degree;
}

int Node::getEarlyDate()
{
    return earlyDate; 
}

int Node::getLateDate()
{
    return lateDate;
}

void Node::setEarlyDate(int i)
{
    if(i>=0)
        earlyDate = i;
    else
        std::cout << "ERRREUR SET EARLY DATE" << std::endl;
}

void Node::setLateDate(int i)
{
    if(i>=0)
        lateDate = i;
    else
        std::cout << "ERRREUR SET LATE DATE" << std::endl;
}


int Node::getMargin()
{
    return margin;
}

void Node::setMargin(int i)
{
    if(i >= 0)
        margin = i;
    else
        std::cout << "ERRREUR SET CRITICAL" << std::endl;
}

bool Node::isCritical()
{
    return critical;
}

void Node::setCritical(bool b)
{
    critical = b;
}


int Node::getPredecessorsEarlyDate()
{
    std::vector<Node*>::iterator it;
    int early = 0;
    for ( it=predecessors.begin() ; it < predecessors.end(); it++)
    {
        if((*it)->getEarlyDate() + (*it)->getDegree() > early)
            early = (*it)->getEarlyDate() + (*it)->getDegree();
    }
    return early;

}

int Node::getSuccessorsLateDate()
{
    std::vector<Node*>::iterator it;
    int late = graph->getOmega()->getLateDate();
    for ( it=successors.begin() ; it < successors.end(); it++)
    {
        if((*it)->getLateDate() - this->getDegree() < late)
            late = (*it)->getLateDate() - this->getDegree();
    }
    return late;

}
