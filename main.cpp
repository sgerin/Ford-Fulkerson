#include <iostream>
#include "graph.hpp"

int main(int argc, char **argv)
{
    if(argc == 2)
    {
        Graph* g = new Graph(argv[1]);
        g->finish();
        g->displayGraph();
        std::cout << g->display() << std::endl;
    }
    else if(argc == 3)
    {
        Graph* g = new Graph(argv[1]);
        g->finish();
        std::ofstream output(argv[2]);
        if(output)
        {
            output << g->display() << std::endl;
            output.close();
        }
        else
        {
            std::cerr << "Failure opening " << argv[1] << '\n';
            return -1;
        }
    }
    else
    {
        std::cout << "Erreur manque des fichiers" << std::endl;
        return 1;
    }
    return 0;
    
}