#include "node.hpp"

class Graph{
public:
    Graph();
    Graph(char* file);
    ~Graph();
    Node* getAlpha();
    Node* getOmega();
    std::vector<Node> getNodes();
    
private:
    std::vector<Node> graph;
    
}