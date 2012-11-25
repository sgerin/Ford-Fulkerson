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
                std::cout << name << nb_pred << std::endl;
                node = new Node(name, cost, pred, nb_pred, this);
                graph.insert(std::pair<std::string, Node*>(name, node));
                name.clear();
                cost = 0;
                pred.clear();                
            }
            

        }
        text.close();
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
        std::cout << it->first << "  " << it->second->toString() << std::endl;
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
    leveling();
    
    //CLASSER LES NOEUDS PAR NIVEAU
    
    
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

void Graph::leveling()
{
    std::vector<Node*> done;
    std::map<std::string, Node*>::iterator it;
    std::vector<Node*>::iterator love;
    // mettre alpha dans la liste de vectors !
    //decrementer le nb_pred de tout les successeurs d'alpha
    done.push_back(getAlpha());
    for (love = getAlpha()->getSuccessors().begin(); love < getAlpha()->getSuccessors().end(); love++)
    {
        //love->setLevel(love->getLevel()-1);
        (*love)->setNbPredecessors((*love)->getNbPredecessors()-1);
    }
    // change de vector
    done.push_back(getOmega());
    std::vector<Node*>::iterator imp;

    
    /*for (it = graph.begin(); it != graph.end(); it++)
    {
        for(imp = it->second->getSuccessors().begin(); imp < it->second->getSuccessors().end(); imp++)
        {
            std::cout << "meditation transcendantale " << (*imp)->getName() << std::endl;
            std::cout << "MAIS OUIII" << (*imp)->getName() << std::endl;
            if((*imp)->getName() != "omega" && (*imp)->getName() != "alpha")
            {
                std::cout << "GENTLE" << (*imp)->getName() << std::endl;
            }
            if((*imp)->getName() != "omega" && (*imp)->getName() != "alpha")
            {
                if((*imp)->getNbPredecessors() == 0 && std::find(done.begin(), done.end(), *imp)==done.end())
                {
                std::cout << "JUGULAIRE" << std::endl;
                (*imp)->setLevel((*imp)->higherLevel()+1);
                std::cout << "BLLAA " << (*imp)->getName() <<std::endl;
                std::cout << getNode((*imp)->getName())->getName() << std::endl;
                //done.push_back(getNode("a"));
                //std::cout << "BLAAAh" << std::endl;
                done.push_back(*imp);
                //done.push_back(getNode("a"));
                //LA LIGNE CI DESSUS PLANTE
                for (love = (*imp)->getSuccessors().begin(); love < (*imp)->getSuccessors().end(); love++)
                {
                    (*love)->setNbPredecessors((*love)->getNbPredecessors()-1);
                }
                std::cout << "FEOIHE" << std::endl;
                //mettre *imp dans un vector
                //mettre *imp dans done pour ne pas le repasser
                //decrementer le nb_pred de tout les noeuds successeurs
                }
            }
            std::cout << "crayon titi " << (*imp)->getName() << std::endl;
        }
    }*/
    
    
    for (it = graph.begin(); it != graph.end(); it++)
    {
        std::cout << "MC Salo  :  " << it->second->getNbPredecessors() << "  " << it->second->getName() << std::endl;
        std::cout << "PREDECESSEURS DE " << it->second->getName() << "  : ";
        for (love = it->second->getPredecessors().begin(); love < it->second->getPredecessors().end(); love++)
        {
            std::cout << (*love)->getName() << ", ";
        }
        
        std::cout << std::endl;
    }
    
    
    /*while (done.size() != graph.size())
    {
        for (it = graph.begin(); it != graph.end(); it++)
        {
        //if(it->second->getName() != "omega" && it->second->getName() != "alpha")
        //{
            std::cout << "MC Salo  :  " << it->second->getNbPredecessors() << "  " << it->second->getName() << std::endl;
            if(it->second->getNbPredecessors() == 0)
            {
                std::cout << "Cadillac  :  " << it->second->getNbPredecessors() << "  " << it->second->getName() << std::endl;
            }
            if(std::find(done.begin(), done.end(), it->second)==done.end())
            {
                std::cout << "Pop Hip !!" << std::endl;
            }
            if(it->second->getNbPredecessors() == 0 && std::find(done.begin(), done.end(), it->second)==done.end())
            {
                it->second->setLevel(it->second->higherLevel()+1);
                std::cout << getNode(it->second->getName())->getName() << std::endl;
                //done.push_back(getNode("a"));
                //std::cout << "BLAAAh" << std::endl;
                done.push_back(it->second);
                //done.push_back(getNode("a"));
                //LA LIGNE CI DESSUS PLANTE
                for (love = it->second->getSuccessors().begin(); love < it->second->getSuccessors().end(); love++)
                {
                    (*love)->setNbPredecessors((*love)->getNbPredecessors()-1);
                }
                std::cout << "FEOIHE" << std::endl;
                //mettre *imp dans un vector
                //mettre *imp dans done pour ne pas le repasser
                //decrementer le nb_pred de tout les noeuds successeurs
            }
        //}
        }
    }*/
    
    getOmega()->setLevel(this->globalHigherLevel() + 1);
}


/*void Graph::leveling()
{
    std::map<std::string, Node*>::iterator titi;
    std::vector<Node*> done;
    for (titi = graph.begin(); titi != graph.end(); titi++)
    {
        done.push_back(titi->second);
        std::cout << titi->second->getName() << " : ";
        std::vector<Node*>::iterator imp;
        for(imp = titi->second->getSuccessors().begin(); imp < titi->second->getSuccessors().end(); imp++)
        {
            std::cout << (*imp)->getName() << " ";
        }
        std::cout << std::endl;
    }
    std::cout << graph.size() << std::endl;

    std::map<std::string, Node*>::iterator it;
    std::vector<Node*>::iterator imp;
    std::vector<std::string> done;
    done.push_back(getAlpha()->getName());
    done.push_back(getOmega()->getName());
    for (it = graph.begin(); it != graph.end(); it++)
    {
        std::cout << "Number of successors for node " << it->second->getName() << "  :  " << it->second->getSuccessors().size() << std::endl;
        done.push_back(it->second->getName());
        for(imp = it->second->getSuccessors().begin(); imp <= it->second->getSuccessors().end(); imp++)
        {
            std::cout << "Des nouuuu" << std::endl;
            if(*imp != NULL)
            {
                std::cout << "Gargamel :  " << *imp << std::endl;
                if(std::find(done.begin(), done.end(), (*imp)->getName())==done.end())
                {
                    std::cout << "ah bah oui  " << (*imp)->getName() << std::endl;
                    done.push_back((*imp)->getName());
                    std::cout << "biiites" << std::endl;
                }
            }
        }
    }
    
    std::vector<std::string>::iterator imp2;

    for (imp2 = done.begin(); imp2 < done.end(); ++imp2)
    {
        //std::cout << "OK " << std::endl;
        std::cout << *imp2 << std::endl;
    }
    
    std::cout << std::endl << std::endl;
    
    std::map<std::string, Node*>::iterator fada;
    for (fada = graph.begin(); fada != graph.end(); fada++)
    {
        if(std::find(done.begin(), done.end(), fada->second->getName())!=done.end())
           std::cout << "teeeest" << std::endl;
    }

    
}*/



// tu prend un noeud dans ta map
// tu parcours tout ses successeurs
// si un de ses successeurs a tout ses precedents rangés dans les vectors et s'il n'a pas déjà été rangé dans un vector
// range dans un vector
// le mettre dans done pour ne pas le reranger une deuxieme fois
// decrementer le nb_pred de tout les noeuds successeurs

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


void Graph::addAlpha(Node* node)
{
    
}

void Graph::addOmega(Node* node)
{
    
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
            //nopred.push_back(it->second->getName());
            it->second->addPredecessors(only_alpha);
        }
        if(it->second->getNbSuccessors() == 0 && it->second->getName().compare("alpha") != 0 && it->second->getName().compare("omega") != 0)
        {
            nosucc.push_back(it->second->getName());
        }
    }
    
    omega->addPredecessors(nosucc);
    //alpha->addSuccessors(nopred);
    // alpha -> lister les successeurs
    // omega -> 
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
