
#include "graph.h"
#include <iostream>

using namespace std;

Graph::Graph(int n){
	num_of_vertices = n;
	Adj = new list<int>[n];
}

void Graph::addEdge(int u, int v){
	Adj[u].push_front(v);
}

void Graph::printAdjacencyList(){
	list<int>::iterator v;
	for(int u = 0; u < num_of_vertices; u++){
		cout << u << ": ";
		for (v = Adj[u].begin(); v != Adj[u].end(); v++){
			cout << *v << " ";
		}
		cout << endl;
	}
}

void Graph::sort()
{
	list<int>::iterator v;
	int n = num_of_vertices;
	int out[n];
	bool test = true;

	for(int i = 0; i < n; i++)
	{
		int temp = 0;
		int count = 0;
		bool done = false;
				
		for(int j = 0; j < n; j++)
		{
			for(int k = 0; k < n; k++)
			{
				for (v = Adj[k].begin(); v != Adj[k].end(); v++)
				{
					if(temp == *v)
					{
						for(int z = 0; z < i; z++)
						{
							if(out[z] == k)
							{
								done = true;
							}
							if(out[z] != k && done == true && temp == z)
							{
								done = false;
							}
						}
						if(done == true)
						{
							break;
						}
						temp = k;
						count++;
					}
				}
			}
		}
		out[i] = temp;
	}
	
	if(out[n-1] == 0 && out[n-2] == 0)
	{
		test = false;
	}	

	if(test == true)
	{
		cout <<"Order: ";
		for(int i = 0; i < n; i++)
		{
			cout <<out[i] <<" ";
		}
		cout <<endl;
	}
	if(test == false)
	{
		cout <<"The graph has no topological ordering!\n";
	}
	return;
}
