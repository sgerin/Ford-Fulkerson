//std::ifstream text;
//text.open(argv[1]);
//iss >> ;
//text.close();


#include "graph.hpp"

Graph::Graph()
{
    std::cout << "No file provided" << std::endl;
}

Graph::Graph(char* file)
{
    std::ifstream text;
    text.open(file);
    if(text.isOpen())
    {
        iss >> ;
        text.close();
    }
    else
    {
        std::cout << "File coudn't be opened" << endl;
        return 1;
    }
    return 0;
}