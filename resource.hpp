#ifndef RESOURCE_H
#define RESOURCE_H

#include <string>

class Node;

class Resource{
public:
    Resource(int);
    Resource(int, Node*);
    int getNumber();
    Node* getOwner();
    void setOwner(Node*);
    
private:
    int number;
    Node* owner;
};

#endif