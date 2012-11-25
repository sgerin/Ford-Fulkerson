CXX=g++
CLANG=clang
LLVM=llvm
LDFLAGS=-Wall -ggdb -Iinc/ 

all: graph

graph: graph.o main.o node.o
	$(CXX) graph.o main.o node.o -o graph $(LDFLAGS)

main.o: main.cpp
	$(CXX) -c main.cpp $(LDFLAGS)

graph.o: graph.cpp
	$(CXX) -c graph.cpp $(LDFLAGS)

node.o: node.cpp
	$(CXX) -c node.cpp $(LDFLAGS)

clean:
	rm -rf *.o *.png *.dot graph 	
