#include <iostream>
#include <fstream>// this is the c++ version of buffer reader
#include "DisjointSets.h"
#include "Maze.h"

int main(int argc, char* argv[])
{
	int size = 0;
	std::ifstream a;
	Maze *m;
	if (argc > 1)
	{	
		a.open(argv[1]);	
		m = new Maze(&a);
		m->toString();
		m->solve();
		a.close();
	}
	else
	{
		std::cout << "Enter the size: ";
		std::cin >> size;
		m = new Maze(size);
		m->randomMaze();
		m->toString();
		m->solve();
	}
	delete m;
}