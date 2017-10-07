#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <list>
#include <deque>

#define STR_LEN 256
#define WHITE 0
#define GREY 1
#define BLACK 2

using namespace std;

class Vertex
{
public:
	Vertex()
	{
		setPuzzle("");
		setColor(WHITE);
		setFather(NULL);
		setDistance(0);
	}
	Vertex(string str)
	{
		setPuzzle(str);
		setColor(WHITE);
		setFather(NULL);
		setDistance(0);
	}

	void setPuzzle(string str)
	{
		puzzle = str;
	}

	void setColor(short col)
	{
		color = col;
	}

	short getColor()
	{
		return color;
	}

	void setDistance(int dist)
	{
		distance = dist;
	}

	int getDistance()
	{
		return distance;
	}

	void setFather(Vertex* v)
	{
		father = v;
	}

	Vertex* getFather()
	{
		return father;
	}
	
	string getPuzzle()
	{
		return puzzle;
	}

	// calculates the total number of inversions a given puzzle has
	// if even, ok. If odd, puzzle is not solvable.
	int inversions()
	{
		int inversions = 0;
		int val;

		for (int i = 0; i < puzzle.length(); i++)
		{
			val = (int)(puzzle[i] - '0');
			for (int j = i + 1; j < puzzle.length(); j++)
			{
				if ((int)(puzzle[j] - '0') < val)
					inversions++;
			}
		}

		return inversions;
	}

	// checks if current puzzle is solved or not
	bool isSolved(string str)
	{
		bool solution = false;
		string correct = "123456780";

		if (str.compare(correct) == 0)
			solution = true;

		return solution;
	}
	
	// returns the position of element 0 in current puzzle
	int getZeroPosition()
	{
		int position;
		
		for(int i = 0; i < puzzle.length(); i++)
			if(puzzle.at(i) == '0')
				position = i;
				
		return position;
	}

	string movePuzzle(int from, int to)
	{
		string origin, destination;
		string swapped;

		origin = puzzle[from];
		destination = puzzle[to];

		swapped = puzzle;

		swapped.replace(from,1,destination);
		swapped.replace(to,1,origin);

		return swapped;
	}

	void printMatrix()
	{
		for(int i = 0; i < puzzle.length(); i++)
		{
			printf("%c", puzzle.at(i));
			if(i > 0 && i%3 == 0)
				printf("\n");
		}
	}

private:
	string puzzle;
	short color; // 0-white 1-gray 2-black
	int distance;
	Vertex* father;
};

class Graph
{
public:
	Graph(list<list<Vertex> >* adjList)
	{
		adjacencyList = adjList;
	}

	// geracao de vertice aqui. Faz switch-case com as possibilidades
	void buscaEmLargura()
	{
		int pos;
		deque<Vertex> deq;
		string puz;
		string swapped;
		Vertex start = Vertex();
		Vertex u = new Vertex();
		Vertex v = new Vertex();

		list<list<Vertex> >::iterator it;

		// will iterate n times, where n is the number of puzzles
		for(it = adjacencyList->begin(); it != adjacencyList->end(); it++)
		{
			list<Vertex>vertexList=*it;
			list<Vertex>::iterator it2;
			it2 = puzzle.begin();

			// got initial state
			start = *it2;
			start.setColor(GREY);
			start.setDistance(0);
			start.setFather(NULL);

			deq.push_back(start);

			// BFS algorithm
			while(deq.size() != 0)
			{
				u = deq.front(); deq.pop_front();
				switch(u.getZeroPosition())
				{
					case 0:
						if(u.getPuzzle() != u.movePuzzle(0,1))
						{
							v = Vertex(u.movePuzzle(0,1));
							if(v.getColor() == WHITE)
							{
								v.setColor(GREY);
								v.setDistance(u.getDistance()+1);
								v.setFather(&u);
								deq.push_back(v);
							}
						}
						else if(u.getPuzzle() != u.movePuzzle(0,3))
						{
							v = Vertex(u.movePuzzle(0,3));
							if(v.getColor() == WHITE)
							{
								v.setColor(GREY);
								v.setDistance(u.getDistance()+1);
								v.setFather(&u);
								deq.push_back(v);
							}
						}
						puzzle.push_back(v);
					break;
					case 1:
						if(u.getPuzzle() != u.movePuzzle(1,0))
						{
							v = Vertex(u.movePuzzle(1,0));
							if(v.getColor() == WHITE)
							{
								v.setColor(GREY);
								v.setDistance(u.getDistance()+1);
								v.setFather(&u);
								deq.push_back(v);
							}
						}
						else if(u.getPuzzle() != u.movePuzzle(1,2))
						{
							v = Vertex(u.movePuzzle(1,2));
							if(v.getColor() == WHITE)
							{
								v.setColor(GREY);
								v.setDistance(u.getDistance()+1);
								v.setFather(&u);
								deq.push_back(v);
							}
						}
						else if(u.getPuzzle() != u.movePuzzle(1,4))
						{
							v = Vertex(u.movePuzzle(1,4));
							if(v.getColor() == WHITE)
							{
								v.setColor(GREY);
								v.setDistance(u.getDistance()+1);
								v.setFather(&u);
								deq.push_back(v);
							}
						}
						puzzle.push_back(v);
					break;
					case 2:
						if(u.getPuzzle() != u.movePuzzle(2,1))
						{
							v = Vertex(u.movePuzzle(2,1));
							if(v.getColor() == WHITE)
							{
								v.setColor(GREY);
								v.setDistance(u.getDistance()+1);
								v.setFather(&u);
								deq.push_back(v);
							}
						}
						else if(u.getPuzzle() != u.movePuzzle(2,5))
						{
							v = Vertex(u.movePuzzle(2,5));
							if(v.getColor() == WHITE)
							{
								v.setColor(GREY);
								v.setDistance(u.getDistance()+1);
								v.setFather(&u);
								deq.push_back(v);
							}
						}
						puzzle.push_back(v);
					break;
					case 3:
						if(u.getPuzzle() != u.movePuzzle(3,0))
						{
							v = Vertex(u.movePuzzle(3,0));
							if(v.getColor() == WHITE)
							{
								v.setColor(GREY);
								v.setDistance(u.getDistance()+1);
								v.setFather(&u);
								deq.push_back(v);
							}
						}
						else if(u.getPuzzle() != u.movePuzzle(3,4))
						{
							v = Vertex(u.movePuzzle(3,4));
							if(v.getColor() == WHITE)
							{
								v.setColor(GREY);
								v.setDistance(u.getDistance()+1);
								v.setFather(&u);
								deq.push_back(v);
							}
						}
						else if(u.getPuzzle() != u.movePuzzle(3,6))
						{
							v = Vertex(u.movePuzzle(3,6));
							if(v.getColor() == WHITE)
							{
								v.setColor(GREY);
								v.setDistance(u.getDistance()+1);
								v.setFather(&u);
								deq.push_back(v);
							}
						}
						puzzle.push_back(v);
					break;
					case 4:
						if(u.getPuzzle() != u.movePuzzle(4,1))
						{
							v = Vertex(u.movePuzzle(4,1));
							if(v.getColor() == WHITE)
							{
								v.setColor(GREY);
								v.setDistance(u.getDistance()+1);
								v.setFather(&u);
								deq.push_back(v);
							}
						}
						else if(u.getPuzzle() != u.movePuzzle(4,3))
						{
							v = Vertex(u.movePuzzle(4,3));
							if(v.getColor() == WHITE)
							{
								v.setColor(GREY);
								v.setDistance(u.getDistance()+1);
								v.setFather(&u);
								deq.push_back(v);
							}
						}
						else if(u.getPuzzle() != u.movePuzzle(4,5))
						{
							v = Vertex(u.movePuzzle(4,5));
							if(v.getColor() == WHITE)
							{
								v.setColor(GREY);
								v.setDistance(u.getDistance()+1);
								v.setFather(&u);
								deq.push_back(v);
							}
						}
						else if(u.getPuzzle() != u.movePuzzle(4,7))
						{
							v = Vertex(u.movePuzzle(4,7));
							if(v.getColor() == WHITE)
							{
								v.setColor(GREY);
								v.setDistance(u.getDistance()+1);
								v.setFather(&u);
								deq.push_back(v);
							}
						}
						puzzle.push_back(v);
					break;
					case 5:
						if(u.getPuzzle() != u.movePuzzle(5,2))
						{
							v = Vertex(u.movePuzzle(5,2));
							if(v.getColor() == WHITE)
							{
								v.setColor(GREY);
								v.setDistance(u.getDistance()+1);
								v.setFather(&u);
								deq.push_back(v);
							}			
						}
						else if(u.getPuzzle() != u.movePuzzle(5,4))
						{
							v = Vertex(u.movePuzzle(5,4));
							if(v.getColor() == WHITE)
							{
								v.setColor(GREY);
								v.setDistance(u.getDistance()+1);
								v.setFather(&u);
								deq.push_back(v);
							}
						}
						else if(u.getPuzzle() != u.movePuzzle(5,8))
						{
							v = Vertex(u.movePuzzle(5,8));
							if(v.getColor() == WHITE)
							{
								v.setColor(GREY);
								v.setDistance(u.getDistance()+1);
								v.setFather(&u);
								deq.push_back(v);
							}
						}
						puzzle.push_back(v);
					break;
					case 6:
						if(u.getPuzzle() != u.movePuzzle(6,3))
						{
							v = Vertex(u.movePuzzle(6,3));
							if(v.getColor() == WHITE)
							{
								v.setColor(GREY);
								v.setDistance(u.getDistance()+1);
								v.setFather(&u);
								deq.push_back(v);
							}
						}
						else if(u.getPuzzle() != u.movePuzzle(6,7))
						{
							v = Vertex(u.movePuzzle(6,7));
							if(v.getColor() == WHITE)
							{
								v.setColor(GREY);
								v.setDistance(u.getDistance()+1);
								v.setFather(&u);
								deq.push_back(v);
							}
						}
						puzzle.push_back(v);
					break;
					case 7:
						if(u.getPuzzle() != u.movePuzzle(7,4))
						{
							v = Vertex(u.movePuzzle(7,4));
							if(v.getColor() == WHITE)
							{
								v.setColor(GREY);
								v.setDistance(u.getDistance()+1);
								v.setFather(&u);
								deq.push_back(v);
							}
						}
						else if(u.getPuzzle() != u.movePuzzle(7,6))
						{
							v = Vertex(u.movePuzzle(7,6));
							if(v.getColor() == WHITE)
							{
								v.setColor(GREY);
								v.setDistance(u.getDistance()+1);
								v.setFather(&u);
								deq.push_back(v);
							}
						}
						else if(u.getPuzzle() != u.movePuzzle(7,8))
						{
							v = Vertex(u.movePuzzle(7,8));
							if(v.getColor() == WHITE)
							{
								v.setColor(GREY);
								v.setDistance(u.getDistance()+1);
								v.setFather(&u);
								deq.push_back(v);
							}
						}
						puzzle.push_back(v);
					break;
					case 8:
						if(u.getPuzzle() != u.movePuzzle(8,5))
						{
							v = Vertex(u.movePuzzle(8,5));
							if(v.getColor() == WHITE)
							{
								v.setColor(GREY);
								v.setDistance(u.getDistance()+1);
								v.setFather(&u);
								deq.push_back(v);
							}
						}
						else if(u.getPuzzle() != u.movePuzzle(8,7))
						{
							v = Vertex(u.movePuzzle(8,7));
							if(v.getColor() == WHITE)
							{
								v.setColor(GREY);
								v.setDistance(u.getDistance()+1);
								v.setFather(&u);
								deq.push_back(v);
							}
						}
						puzzle.push_back(v);
					break;
				}
				u.setColor(BLACK);
			}
		}
	}

	void printStates()
	{
		Vertex v;

		list<list<Vertex> >::iterator it;
		for(it = adjacencyList->begin(); it != adjacencyList->end(); it++)
		{
			list<Vertex>vertexList=*it;
			list<Vertex>::iterator it2;
			for(it2 = puzzle.begin(); it2 != puzzle.end(); it2++)
			{
				v = *it2;
				v.printMatrix();
			}
		}
	}

	list<list<Vertex> >* adjacencyList;
	list<Vertex> puzzle;
};

int main()
{
	string line;
	int numberOfPuzzles, strPos;
	string puzzle;
	list<list<Vertex> >* adjList;
	list<Vertex> initialPuzzle;

	strPos = 0;
	adjList = new list<list<Vertex> >;
	Graph graph = Graph(adjList);

	// gets number of puzzles to solve;
	getline(cin, line); // ok
	numberOfPuzzles = atoi(line.c_str()); // ok
	
	// read input, creates vertexes and places them as initial states of the puzzle
	for(int i = 0; i < numberOfPuzzles; i++)
	{
		// read puzzle
		getline(cin, line);
		cout << "Puzzle: " << line << "\n";

		Vertex vertex = Vertex(line); // vertice de origem
		cout << "Instanciou um vertice\n";

		initialPuzzle.push_back(vertex);
		cout << "Jogou o vertice pra lista\n";

		graph.adjacencyList->push_back(initialPuzzle);
		cout << "Adicionou a primeira lista à lista\n";
	}
	graph.buscaEmLargura();
	graph.printStates();
}
