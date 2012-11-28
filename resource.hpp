#ifndef RESOURCE_H
#define RESOURCE_H

#include <string>

class Node;

class Resource{
public:
    Resource(std::string);
    Resource(std::string, Node* owner);
    std::string getName();
    Node* getOwner();
    
private:
    std::string name;
    Node* owner;
};

#endif