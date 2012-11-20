#include "graph.hpp"

Graph::Graph()
{
    std::cout << "No file provided" << std::endl;
}

Graph::Graph(char* file)
{
    //std::vector<std::string> nodes;
    //std::vector<int> costs;
    //std::vector<int> nb_pred;
    //std::vector<std::vector<std::string>> predecessors;
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
                
                std::cout << "Values :";
                for (it = x.begin() ; it < x.end(); it++)
                {
                    if(it - x.begin() == 1)//it == 1)
                    {
                        name = *it;
                        //nodes.push_back(*it);
                    }
                    else if(it - x.begin() == 2)//it == 2)
                    {
                        std::stringstream ss;
                        //int cost;
                        ss << *it;
                        ss >> cost;
                        //costs.push_back(cost)
                    }
                    else if(it - x.begin() == 3)//it == 3)
                    {
                        std::stringstream ss;
                        //int nb;
                        ss << *it;
                        ss >> nb_pred;
                        //nb_pred.push_back(nb);
                    }
                    else
                    {
                        pred.push_back(*it);
                    }
                }
                if(pred.size() != nb_pred)
                {
                    std::cout << "Erreur nombre de sommets precedents != liste des sommets precedents" << std::endl;
                    exit(0);
                }
                node = new Node(name, cost, pred, this);
                graph.insert(pair<std::string, Node*>(name, node));
                //std::map<std::string, Node*>::iterator ;
                name.clear();
                cost = 0;
                pred.clear();
                // std::cout << " " << *it << std::endl;
                // std::cout << std::endl;
                
                // iterator on x
                // 1rst value -> name
                // 2nd -> cost
                // 3rd -> nb of predecessors
                // until end -> name of predecessors
            }
        //iss >> ;
        // break down line into differents strings
        // you should create a vector of string for node name
        // + a vector of int for node cost
        // + a vector of vector of string to know each node predecessors
        // build all the node with their cost then add their predecessors -> successors and degree will be deduced
        
        // then create alpha & omega nodes
        // alpha node will have a cost of 0 and be the common predecessor of all node that didn't have any
        // omega node will have a cost of 0 and be the common successor of all node that didn't have any

        }
        text.close();
    }
    else
    {
        std::cout << "File coudn't be opened" << std::endl;
        //return 1;
    }
    //return 0;
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
    for (it = x.begin() ; it < x.end(); it++)
    {
        std::cout << it->first << "  " << it->second->toString() << std::endl;
    }

}
