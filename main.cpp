#include "graph.hpp"

int main(int argc, char **argv)
{
    if(argc == 2)
    {
        graph g = new Graph(argv[1]);
        //Ouvrir ou creer argv2 si graph est ok
        //Ecrire dedans
    }
    
    cout << "Erreur manque des fichiers" << endl;
    return 1;
    
    
}