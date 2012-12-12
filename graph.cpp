#include "graph.hpp"

//#define DEBUG

Graph::Graph()
{
    std::cout << "No file provided" << std::endl;
}

Graph::Graph(char* nodes, char* res)
{
    Node* node = NULL;
    Resource resource = NULL;
    std::ifstream text;
    text.open(nodes);
    if(text.is_open())
    {
        while(text.good())
        {
            std::string line = "";
            getline(text, line);
            if(line.length() != 0)
            {
                std::string name;
                int cost;
                int nb_pred;
                std::vector<std::string> pred;
                
                std::vector<std::string> x = split(line, ' ');
                std::vector<std::string>::iterator it;
                

                #ifdef DEBUG
                for (it = x.begin(); it < x.end(); it++)
                {
                    std::cout << *it << "  ";
                }
                
                std::cout << std::endl << std::endl << std::endl << std::endl;
                #endif
                
                for (it = x.begin() ; it < x.end(); it++)
                {
                    if(it - x.begin() == 0)
                    {
                        name = *it;
                    }
                    else if(it - x.begin() == 1)
                    {
                        std::stringstream ss;
                        ss << *it;
                        ss >> cost;
                    }
                    else if(it - x.begin() == 2)
                    {
                        std::stringstream ss;
                        ss << *it;
                        ss >> nb_pred;
                    }
                    else
                    {
                        pred.push_back(*it);
                    }
                }
                node = new Node(name, cost, pred, nb_pred, this);
                graph.insert(std::pair<std::string, Node*>(name, node));
                name.clear();
                cost = 0;
                pred.clear();                
            }
        }        
        text.close();
        text.clear();
        text.open(res);
        if(text.is_open())
        {
            int i = 0;
            int nb_res = 0;
            while(text.good())
            {
                std::string line = "";
                getline(text, line);
                if(line.length() != 0)
                {
                    std::string name;
                    std::vector<std::string> x = split(line, ' ');
                    std::vector<std::string>::iterator it;
                    /*for (it = x.begin(); it < x.end(); it++)
                    {
                        std::cout << *it << "  ";
                    }
                    std::cout << std::endl;*/
                    if(i == 0)
                    {
                        for (it = x.begin() ; it < x.end(); it++)
                        {
                            if(it - x.begin() == 0)
                            {
                                std::stringstream ss;
                                ss << *it;
                                ss >> nb_res;
                            }
                            else
                            {
                                std::cout << "It shouldn't happen : 1st line of file is just a nbr" << std::endl;
                            }
                        }
                    }
                    else
                    {
                        for (it = x.begin() ; it < x.end(); it++)
                        {
                            if(it - x.begin() == 0)
                            {
                                name = *it;
                            }
                            else
                            {
                                int res;
                                std::stringstream ss;
                                ss << *it;
                                ss >> res;
                                
                                resource = new Resource(res);
                                resources.insert(std::pair<int, Resource*>(res, resource));
                                (this->getNode(name))->setResource(res);
                                
                                //pred.push_back(*it);
                            }
                        }

                    }
                    
                }
                i++;
            }
        }
        else
        {
            std::cout << "Resources file couldn't be opened" << std::endl;
            exit(0);
        }

    }
    else
    {
        std::cout << "File coudn't be opened" << std::endl;
        exit(0);
    }
}




std::vector<std::string>& Graph::split(std::string &s, char delim, std::vector<std::string> &elems)
{
    std::stringstream ss(s);
    std::string item;
    while(std::getline(ss, item, delim))
    {
        elems.push_back(item);
    }
    return elems;
}


std::vector<std::string> Graph::split(std::string &s, char delim)
{
    std::vector<std::string> elems;
    return split(s, delim, elems);
}


Node* Graph::getAlpha()
{
    std::map<std::string, Node*>::iterator it;
    it = graph.find("alpha");
    return it->second;
}


Node* Graph::getOmega()
{
    std::map<std::string, Node*>::iterator it;
    it = graph.find("omega");
    return it->second;
}


Node* Graph::getNode(std::string node)
{
    std::map<std::string, Node*>::iterator it;
    it = graph.find(node);
    if(it != graph.end())
        return it->second;
    return NULL;
}

std::string Graph::display()
{
    std::map<std::string, Node*>::iterator it;
    std::string s;
    
    for (it = graph.begin(); it != graph.end(); it++)
    {
        s += it->second->toString();
        s += "\n";
    }
    
    s += "Chemin critique ";
    
    int current = 0;
    
    while(current <= getOmega()->getLevel()){
        for (it = graph.begin(); it != graph.end(); it++)
        {
            if(it->second->getLevel() == current && it->second->isCritical())
            {
                s += it->second->getName();
                s += "  ";
            }
        }
        current += 1;
    }
    return s;
}

void Graph::finish()
{
    std::map<std::string, Node*>::iterator it;
    
    for (it = graph.begin(); it != graph.end(); it++)
    {
        it->second->buildPredecessors();
    }
    
    buildAlphaOmega();
    leveling();
    earlyDate();
    lateDate();
    margin();
}

void Graph::leveling()
{
    std::vector<Node*> done;
    std::map<std::string, Node*>::iterator it;
    std::vector<Node*>::iterator love;
    done.push_back(getAlpha());
    for (love = getAlpha()->getSuccessors().begin(); love < getAlpha()->getSuccessors().end(); love++)
    {
        (*love)->setNbPredecessors((*love)->getNbPredecessors()-1);
    }
    done.push_back(getOmega());
    std::vector<Node*>::iterator imp;

    
    while (done.size() != graph.size())
    {
        for (it = graph.begin(); it != graph.end(); it++)
        {
            if(it->second->getNbPredecessors() == 0 && std::find(done.begin(), done.end(), it->second)==done.end())
            {
                it->second->setLevel(it->second->higherLevel()+1);
                done.push_back(it->second);
                for (love = it->second->getSuccessors().begin(); love < it->second->getSuccessors().end(); love++)
                {
                    (*love)->setNbPredecessors((*love)->getNbPredecessors()-1);
                }
            }
        }
    }
    
    getOmega()->setLevel(this->globalHigherLevel() + 1);
}


void Graph::earlyDate()
{
    std::vector<Node*> done;
    std::map<std::string, Node*>::iterator it;
    int current = 0;
    
    getAlpha()->setEarlyDate(0);
    done.push_back(getAlpha());
    current += 1;
    
    while(done.size() != graph.size())
    {
        for (it = graph.begin(); it != graph.end(); it++)
        {
            if(it->second->getLevel() == current)
            {
                it->second->setEarlyDate(it->second->getPredecessorsEarlyDate());
                done.push_back(it->second);
            }
        }
        current += 1;
    }
    
}

void Graph::lateDate()
{
    std::vector<Node*> done;
    std::map<std::string, Node*>::iterator it;
    int current = getOmega()->getLevel();

    getOmega()->setLateDate(getOmega()->getEarlyDate());
    done.push_back(getOmega());
    current -= 1;
    
    while(done.size() != graph.size())
    {
        for (it = graph.begin(); it != graph.end(); it++)
        {
            if(it->second->getLevel() == current)
            {
                it->second->setLateDate(it->second->getSuccessorsLateDate());
                done.push_back(it->second);
            }
        }
        current -= 1;
    }
}

void Graph::margin()
{
    std::map<std::string, Node*>::iterator it;
    for (it = graph.begin(); it != graph.end(); it++)
    {
        int early = it->second->getEarlyDate();
        int late = it->second->getLateDate();
        it->second->setMargin(late - early);
        if(late - early == 0)
            it->second->setCritical(true);
    }
}

int Graph::globalHigherLevel()
{
    std::map<std::string, Node*>::iterator it;
    int love = 0;
    for (it = graph.begin(); it != graph.end(); it++)
    {
        if(love < it->second->getLevel())
            love = it->second->getLevel();
    }
    return love;
}


void Graph::buildAlphaOmega()
{
    
    std:: cout << std::endl << std::endl;
    Node* alpha = new Node("alpha", this);
    Node* omega = new Node("omega", this);
    
    graph.insert(std::pair<std::string, Node*>("alpha", alpha));
    graph.insert(std::pair<std::string, Node*>("omega", omega));
    
    std::vector<std::string> only_alpha;
    only_alpha.push_back("alpha");
    std::vector<std::string> nosucc;
    std::map<std::string, Node*>::iterator it;
    for (it = graph.begin(); it != graph.end(); it++)
    {
        if(it->second->getNbPredecessors() == 0 && it->second->getName().compare("alpha") != 0 && it->second->getName().compare("omega") != 0)
        {
            it->second->addPredecessors(only_alpha);
        }
        if(it->second->getNbSuccessors() == 0 && it->second->getName().compare("alpha") != 0 && it->second->getName().compare("omega") != 0)
        {
            nosucc.push_back(it->second->getName());
        }
    }
    
    omega->addPredecessors(nosucc);
}

void Graph::displayGraph()
{
    std::map<std::string, Node*>::iterator it;
    std::vector<Node*>::iterator it2;
    std::ofstream output("graph.dot", std::ios::out|std::ios::trunc);
    if(output)
    {
        output << "digraph G{" << std::endl;
        output << "rankdir=\"LR\"" << std::endl;
        output << "make_string [label=\"Node(date au plus tôt, date au plus tard, marge)\",color=\"1.2 0.3 1.0\"];" << std::endl;
        for(it = graph.begin(); it != graph.end(); ++it)
        {
            for(it2 = it->second->getSuccessors().begin(); it2 < it->second->getSuccessors().end(); ++it2)
            {
                output << it->second->getName() << " -> " << (*it2)->getName() << ";" << std::endl;
            }
        }
        for(it = graph.begin(); it != graph.end(); ++it)
        {
            output << it->second->getName() << "[label = \"" << it->second->getName() << "(" << it->second->getEarlyDate() << ", " << it->second->getLateDate() << ", " << it->second->getMargin() << ")\"]" << std::endl;
            if(it->second->isCritical())
                output << it->second->getName() << " [color=red];" << std::endl;
        }
        output << "}";
        output.close();
        system("dot -Tpng graph.dot > graph.png");
    }
    else
        std::cout << "ERROR WRITING DOT FILE" << std::endl;
}

