#include "resource.hpp"
#include "node.hpp"

Resource::Resource(int i)
{
    this->number = i;
    this->owner = NULL; 
}

Resource::Resource(int i, Node* node)
{
    this->number = i;
    this->owner = node;
}


int Resource::getNumber()
{
    return number;
}


Node* Resource::getOwner()
{
    return owner;
}

vois Resource:setOwner(Node* node)
{
    this->owner = node;
