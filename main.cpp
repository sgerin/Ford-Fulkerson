#include <iostream>
#include "graph.hpp"

int main(int argc, char **argv)
{
    if(argc == 2)
    {
        Graph* g = new Graph(argv[1]);
        //Ouvrir ou creer argv2 si graph est ok
        //Ecrire dedans
    }
    
    std::cout << "Erreur manque des fichiers" << std::endl;
    return 1;
    
    
}