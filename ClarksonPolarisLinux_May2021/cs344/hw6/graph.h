#include <list>

using namespace std;

class Graph 
{
private:
	int num_of_vertices;		//number of vertices in the graph 
	list <int> *Adj;			//adjancency list    
public: 
	Graph(int n);   		//Construct a graph with n vertices
	void addEdge(int u, int v);		//Add (u, v) to the graph

	void printAdjacencyList();	
	//Print the adjacency lists of all the vertices.

	void sort();
	//If the graph has a topological ordering, output it.
	//Otherwise, output "The graph no topological ordering."
};
