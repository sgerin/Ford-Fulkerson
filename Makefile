all: graph

graph: graph.o main.o node.o
	g++ graph.o main.o node.o -o graph

main.o: main.cpp
	g++ -c main.cpp

graph.o: graph.cpp
	g++ -c graph.cpp

node.o: node.cpp
	g++ -c node.cpp

clean:
	rm -rf *.o graph
	
