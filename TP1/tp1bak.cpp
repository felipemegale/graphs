// TP1 - Felipe Marques Megale - 476280
// Adjacency Matrix
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>
#include <sstream>

#define STR_SIZE 1024

using namespace std;

// Declares and initializes a matrix OK
int** adj_matrix(int vertices)
{
	int** matrix = new int*[vertices];

	for(int i = 0; i < vertices; i++)
	{
		matrix[i] = new int[vertices];
		for(int j = 0; j < vertices; j++)
			matrix[i][j] = 0;
	}
	return matrix;
}

// Creates the graph OK
int** create_graph(int vertices, int graph_digraph)
{
	string input;
	int from, to, weight;
	char delim;

	int** matrix = adj_matrix(vertices);

	getline(cin, input);
	
	// Read the information regarding graph assembly
	do
	{
		stringstream ss(input);
		
		ss >> from >> delim >> to >> delim >> weight;
		
		matrix[from][to] = weight;
		matrix[to][from] = weight;

		getline(cin, input);

	} while(input.compare("FIM") != 0);

	return matrix;
}

// This determines the degree of a given vertex of a given graph OK
int vertex_degree(int** graph, int vertex, int vertices)
{
	int degree = 0;

	for(int j = 0; j < vertices; j++)
		if(graph[j][vertex] != 0)
			degree++;
	
	return degree;
}

// Determines the number of edges in a given graph
int graph_edges(int** graph, int vertices)
{
	int edges = 0;

	for(int i = 0; i <= (vertices-1); i++)
		for(int j = (i+1); j < vertices; j++)
			if(graph[i][j] != 0)
				edges++;

	return edges;
}

// Prints a given graph in a grid pattern OK
void print_graph(int** graph, int vertices)
{

	for(int i = 0; i < vertices; i++)
	{
		for(int j = 0; j < vertices; j++)
			printf("%d ", graph[i][j]);
		cout << endl;
	}
}

// Checks whether there is an edge
bool is_edge(int** graph, int row, int col)
{
	bool isedge = true;
	
	if(graph[row][col] == 0)
		isedge = false;

	return isedge;
}

// Checks if a graph is complete
bool is_complete(int** graph, int vertices)
{
	bool iscomplete = true;

	for(int i = 0; i < vertices; i++)
		for(int j = i+1; j < vertices; j++)
			if(graph[i][j] == 0)
				iscomplete = false;

	return iscomplete;
}

// Determines the complement of a given graph
int** complement_graph(int** graph, int vertices)
{
	int** complement = adj_matrix(vertices);

	for(int i = 0; i <= vertices-1; i++)
	{
		for(int j = i+1; j < vertices; j++)
		{
			if(graph[i][j] == 0)
				complement[i][j] = 1;
		}
	}

	return complement;
}

// Prints a graph as a list
void print_list(int** graph, int vertices)
{
	for(int i = 0; i <= vertices-1; i++)
	{
		for(int j = i+1; j < vertices; j++)
		{
			if(graph[i][j] != 0)
			{
				printf("%d,%d,%d\n", i,j,graph[i][j]);
			}
		}
	}
}

int main()
{
	string input;
	int digraph;
	int vertices, from, to, weight, vertex, degree, edges, row, col;
	int** myGraph;
	int** complement;
	char delim;
	char line[STR_SIZE];
	bool isedge, iscomplete;

	// get graph or digraph
	// fgets(line, STR_SIZE, stdin);
	// digraph = atoi(line);
	getline(cin, input);
	digraph = stoi(input);

	// get number of vertices
	// fgets(line, STR_SIZE, stdin);
	// vertices = atoi(line);
	getline(cin, input);
	vertices = stoi(input);

	myGraph = create_graph(vertices, digraph);

	// Gets the vertex one wishes to analyze
	// fgets(line, STR_SIZE, stdin);
	// vertex = atoi(line);
	getline(cin, input);
	vertex = stoi(input);

	getline(cin,input);
	stringstream ss(input);
	ss >> row >> delim >> col;

	degree = vertex_degree(myGraph, vertex, vertices);
	isedge = is_edge(myGraph, row, col); // returns an integer, needs treatment
	edges = graph_edges(myGraph, vertices);
	iscomplete = is_complete(myGraph, vertices); // returns an integer, need treatment
	complement = complement_graph(myGraph, vertices);

	// print_graph(graph, vertices);

	// print_list(myGraph, vertices);
	
	printf("%d\n",degree);
	
	if(isedge)
	{
		printf("SIM\n");
	} else
	{
		printf("NAO\n");
	}

	printf("%d\n", edges);

	if(iscomplete)
	{
		printf("SIM\n");
	} else
	{
		printf("NAO\n");
	}

	print_list(complement, vertices);

	return 0;
}

// NNDNNSNTDG
//KE CE
