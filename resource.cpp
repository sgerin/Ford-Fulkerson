#include "resource.hpp"
#include "node.hpp"

Resource::Resource(std::string s)
{
    this->name = s;
    this->owner = NULL; 
}

Resource::Resource(std::string s, Node* node)
{
    this->name = s;
    this->owner = node;
}


std::string Resource::getName()
{
    return name;
}


Node* Resource::getOwner()
{
    return owner;
}
