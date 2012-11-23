#include "graph.hpp"

//#define DEBUG

Graph::Graph()
{
    std::cout << "No file provided" << std::endl;
}

Graph::Graph(char* file)
{
    Node* node = NULL;
    std::ifstream text;
    text.open(file);
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
                
                //std::cout << "Values :";
                for (it = x.begin() ; it < x.end(); it++)
                {
                    if(it - x.begin() == 0)//it == 1)
                    {
                        name = *it;
                        //nodes.push_back(*it);
                    }
                    else if(it - x.begin() == 1)//it == 2)
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
        
        finish();
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

void Graph::display()
{
    std::map<std::string, Node*>::iterator it;
    
    for (it = graph.begin(); it != graph.end(); it++)
    {
        //std::cout << it->first << "  " << it->second->toString() << std::endl;
    }

}

void Graph::finish()
{
    std::map<std::string, Node*>::iterator it;
    
    for (it = graph.begin(); it != graph.end(); it++)
    {
        it->second->buildPredecessors();
    }
    
    //for (it = graph.begin(); it != graph.end(); it++)
    //{
    //    it->second->buildSuccessors();
    //}
    
    buildAlphaOmega();
    //buildOmega();
    //new Node(nom, cout, listpredstring, nbpred, this);
    
    /*std::map<std::string, Node*>::iterator it;
    
    for (it = graph.begin(); it != graph.end(); it++)
    {
        if(it->second->getNbPred == 0)
        {
            addAlpha(it->second);
        }
        if(it->second->getNbSucc == 0)
        {
            addOmega(it->second);
        }
    }*/
    //
}

void Graph::addAlpha(Node* node)
{
    
}

void Graph::addOmega(Node* node)
{
    
}


void Graph::buildAlphaOmega()
{
    std::vector<Node*> nopred;
    std::vector<Node*> nosucc;
    std::map<std::string, Node*>::iterator it;
    for (it = graph.begin(); it != graph.end(); it++)
    {
        if(it->second->getNbPredecessors() == 0)
        {
            nopred.push_back(it->second);
        }
        if(it->second->getNbSuccessors() == 0)
        {
            nosucc.push_back(it->second);
        }
    }
    
    std::vector<Node*>::iterator imperator;
    std:: cout << std::endl << std::endl;
    for (imperator = nopred.begin(); imperator < nopred.end(); imperator++)
    {
        std::cout << (*imperator)->getName() << "  ";
    }
    
    std:: cout << std::endl << std::endl;
    
    
    for (imperator = nosucc.begin(); imperator < nosucc.end(); imperator++)
    {
        std::cout << (*imperator)->getName() << "  ";
    }
    
    std:: cout << std::endl << std::endl;
    //Node* alpha = new Node("alpha", 0, NULL, 0, this);
    //graph.insert(std::pair<std::string, Node*>("alpha", alpha));
    // then create alpha & omega nodes
    // alpha node will have a cost of 0 and be the common predecessor of all node that didn't have any
    // omega node will have a cost of 0 and be the common successor of all node that didn't have any
}


/*void Graph::buildOmega()
{
    std::vector<std::string> x;
    for (it = graph.begin(); it != graph.end(); it++)
    {
        if(it->getNbPred() == 0)
            x.push_back(it->getName());
    }
    Node* omega = new Node("omega", 0, NULL, 0, this);
    // then create alpha & omega nodes
    // alpha node will have a cost of 0 and be the common predecessor of all node that didn't have any
    // omega node will have a cost of 0 and be the common successor of all node that didn't have any
    graph.insert(std::pair<std::string, Node*>("omega", omega));
}*/
