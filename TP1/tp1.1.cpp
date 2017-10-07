// TP1 - Felipe Marques Megale - 476280
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

class AdjacencyMatrix
{
public:
	// Class constructor
	AdjacencyMatrix(int digraph, int vertices)
	{
		setVertices(vertices);
		setDigraph(digraph);
		setEdges(0);
		createAdjacencyMatrix();
	}

	// Sets the number of vertices
	void setVertices(int vertices)
	{
		this->vertices = vertices;
	}

	// Gets the number of vertices
	int getVertices()
	{
		return this->vertices;
	}

	// Sets the number of edges in a graph. USED ONLY IN CONSTRUCTOR
	void setEdges(int edges)
	{
		this->edges = 0;
	}

	// Gets the number of edges in a graph
	int getEdges()
	{
		return this->edges;
	}

    // Sets digrah condition
    void setDigraph(int digraph)
    {
        this->digraph = digraph;
    }

    // Gets digraph condition
    int getDigraph()
    {
        return this->digraph;
    }

	// Creates the adjacency matrix and the skeleton for the complement graph
	void createAdjacencyMatrix()
	{
		this->adjMatrix = new int*[this->vertices];
		for (int i = 0; i < this->vertices; i++)
		{
			this->adjMatrix[i] = new int[this->vertices];
			for (int j = 0; j < this->vertices; j++)
				this->adjMatrix[i][j] = 0;
		}
	}

    // Reads stdin and assembles graph
	void createGraph()
	{
        string input;
        int from, to, weight;
        char delim;

        getline(cin, input);

        do
        {
            stringstream ss(input);
            ss >> from >> delim >> to >> delim >> weight;

            adjMatrix[from][to] = weight;
            adjMatrix[to][from] = weight;
			this->edges += 1;

            getline(cin, input);
        } while(input.compare("FIM") != 0);
	}

    // Determines the degree of a given vertex
    int getDegree(int vertex)
    {
        int degree = 0;

        for(int i = 0; i < this->vertices; i++)
            if(adjMatrix[i][vertex] != 0)
                degree++;

        return degree;
    }

    // Prints a graph in a grid pattern
	void printGraphGrid()
	{
		for(int i = 0; i < this->vertices; i++)
		{
			for(int j = 0; j < this->vertices; j++)
				printf("%d ", this->adjMatrix[i][j]);
			cout << endl;
		}
	}

	// Checks whether there is an edge
	bool isEdge(int from, int to)
	{
		bool isEdge = true;

		if(this->adjMatrix[from][to] == 0)
			isEdge = false;

		return isEdge;
	}

	// Checks if a graph is complete
	bool isComplete()
	{
		bool isComplete = true;

		for(int i = 0; i < this->vertices; i++)
			for(int j = 0; j < this->vertices; j++)
				if(this->adjMatrix[i][j] == 0)
					isComplete = false;

		return isComplete;
	}

	// Determines the complement of a graph
	void complementGraph(AdjacencyMatrix original)
	{
		for(int i = 0; i <= this->vertices-1; i++)
			for(int j = i+1; j < this->vertices; j++)
				if(original.adjMatrix[i][j] == 0)
					this->adjMatrix[i][j] = 1;
	}

	// Prints a graph as a list
	void printList()
	{
		for(int i = 0; i <= this->vertices-1; i++)
			for(int j = i+1; j < this->vertices; j++)
				if(this->adjMatrix[i][j] != 0)
					printf("%d,%d,%d\n", i, j, this->adjMatrix[i][j]);
	}

private:
	int vertices;
    int digraph;
	int edges;
	int** adjMatrix;
};

int main()
{
	string input;
	int digraph;
	int vertices, vertex, degree, from, to, edges;
	char delim;
	bool isEdge, isComplete;

	// gets digraph
	getline(cin, input);
	digraph = atoi(input.c_str());

	//gets number of vertices
	getline(cin, input);
	vertices = atoi(input.c_str());

	AdjacencyMatrix graph(digraph, vertices);
	AdjacencyMatrix complement(digraph, vertices);

	graph.createGraph();

	// gets vertex to know degree
	getline(cin, input);
	vertex = atoi(input.c_str());
	degree = graph.getDegree(vertex);

	// gets and edge value to check its existence
	getline(cin, input);
	stringstream ss(input);
	ss >> from >> delim >> to;
	isEdge = graph.isEdge(from, to);

	edges = graph.getEdges();

	isComplete = graph.isComplete();

	complement.complementGraph(graph);

	printf("%d\n", degree);

	if(isEdge)
		printf("SIM\n");
	else
		printf("NAO\n");
	
	printf("%d\n", edges);

	if(isComplete)
		printf("SIM\n");
	else
		printf("NAO\n");

	complement.printList();

	return 0;
}

// NNDNNSNTDG
// KE CE