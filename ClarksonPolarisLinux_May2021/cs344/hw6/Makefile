sorting: main.o graph.o
	g++ main.o graph.o -o sorting
main.o: main.cpp
	g++ -c main.cpp
graph.o: graph.h graph.cpp
	g++ -c graph.cpp
clean:
	rm *.o sorting
