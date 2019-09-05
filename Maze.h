#ifndef MAZE_H
#define MAZE_H
#pragma once
#include <iostream>
#include <fstream>
#include <random>
#include <string>
#include "DisjointSets.h"
#include "Graph.h"

class Maze{
private:
	int n;
	int nSquared;
	int** mazeArray;
	DisjointSets<int> * ds;

public:
	Maze() {
		n = 0;
		nSquared = 0;
		mazeArray = NULL;
		ds = NULL;

	}
	
	Maze(int a)
	{
		n = a;
		nSquared = n*n;
		mazeArray = new int*[nSquared];
		for (int i = 0; i < nSquared; i++)
		{
			mazeArray[i] = new int[4];
			for (int j = 0; j < 4; j++)
			{
				mazeArray[i][j] = 1; // close off the entire maze
			}
		}
		ds = new DisjointSets<int>(nSquared);
	}

	Maze(std::ifstream *f)
	{
		*f >> n;
		nSquared = n*n;
		mazeArray = new int*[nSquared];
		ds = new DisjointSets<int>(n);
		for (int i = 0; i < nSquared; i++)
		{
			mazeArray[i] = new int[4];
			*f >> mazeArray[i][0];
			*f >> mazeArray[i][1];
			*f >> mazeArray[i][2];
			*f >> mazeArray[i][3];
		}
		//std::cout << toString();
	}

	~Maze() {
		for (int i = 0; i < n; i++)
		{
			delete[] mazeArray[i];
		}
		delete[] mazeArray;
		delete ds;
	}

	std::string toString()
	{
		//print top
		std::string maze = "";
		std::string mazeT = "";
		std::string mazeR = "";
		
		for (int j = 0; j < nSquared; j += n)
		{
			mazeT = "";
			mazeR = "";
			for (int i = j; i < n+j; i++)
			{
				if (mazeArray[i][0] == 1) // checks the top
				{
					mazeT += " --";
				}//prints this if the top is present
				else
				{
					mazeT += "   ";
				}

				if (mazeArray[i][3] == 1)
				{
					mazeR += "|  ";
				}
				else
				{
					mazeR += "   ";
				}
			}
			maze = maze + mazeT + "\n" + mazeR + "|\n";
		}
		
		mazeT = "";
		for (int i = 0; i < n-1; i++)
		{
			mazeT += " --";
		}
		maze = maze + mazeT + "\n";
		std::cout << maze;
		return maze;
	}

	void readMaze(std::ifstream &f)
	{
		for (int i = 0; i < nSquared; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				f >> mazeArray[i][j];
			}
		}
	}

	void randomMaze()
	{
		int r = 0;
		int dice = 0;

		std::random_device rd;//get seed
		std::mt19937 eng(rd());//seed the generator
		
		while (!findAll()) //ds->find(0) != ds->find(nSquared - 1)
		{
			
			std::uniform_int_distribution<int> distrobution(0, nSquared-1); // set the limits
			r = distrobution(eng);

			if (r == 0)
			{
				std::uniform_int_distribution<int> distrobution(0, 1);// picks the adjacent room
				dice = distrobution(eng);
				

				switch (dice) 
				{
				case 0:
					if (ds->find(r) == ds->find(r + 1))
					{
						continue;
					}
					mazeArray[r][2]	= 0; //opens both doors
					mazeArray[r + 1][3] = 0;
					ds->Union(ds->find(r), ds->find(r + 1));
					//ds->Union(r, r + 1);//unions the two rooms
					break;
				case 1:
					if (ds->find(r) == ds->find(r + n))
					{
						continue;
					}
					mazeArray[r][1] = 0;
					mazeArray[r + n][0] = 0;
					ds->Union(ds->find(r), ds->find(r +n ));
					//ds->Union(r, r+n);
					break;
				}

			}
			else if (r == nSquared - 1)
			{
				std::uniform_int_distribution<int> distrobution(0, 1);// picks the adjacent room
				dice = distrobution(eng);

				switch (dice)
				{
				case 0:
					if (ds->find(r) == ds->find(r - n))
					{
						continue;
					}
					mazeArray[r][0] = 0; //opens both doors
					mazeArray[r - n][1] = 0;
					ds->Union(ds->find(r), ds->find(r - n));
					//ds->Union(r, r-n);//unions the two rooms
					break;
				case 1:
					if (ds->find(r) == ds->find(r - 1))
					{
						continue;
					}
					mazeArray[r][3] = 0;
					mazeArray[r -1][2] = 0;
					ds->Union(ds->find(r), ds->find(r -1));
					//ds->Union(r, r -1);
					break;
				}
			}
			else if (r == n - 1)
			{
				std::uniform_int_distribution<int> distrobution(0, 1);// picks the adjacent room
				dice = distrobution(eng);

				switch (dice)
				{
				case 0:
					if (ds->find(r) == ds->find(r + n))
					{
						continue;
					}
					mazeArray[r][1] = 0; //opens both doors
					mazeArray[r + n][0] = 0;
					ds->Union(ds->find(r), ds->find(r +n));
					//ds->Union(r, r+n);//unions the two rooms
					break;
				case 1:
					if (ds->find(r) == ds->find(r - 1))
					{
						continue;
					}
					mazeArray[r][3] = 0;
					mazeArray[r -1][2] = 0;
					ds->Union(ds->find(r), ds->find(r - 1));
					//ds->Union(r, r -1);
					break;
				}
			}
			else if (r == nSquared - n)
			{
				std::uniform_int_distribution<int> distrobution(0, 1);// picks the adjacent room
				dice = distrobution(eng);

				switch (dice)
				{
				case 0:
					if (ds->find(r) == ds->find(r - n))
					{
						continue;
					}
					mazeArray[r][0] = 0; //opens both doors
					mazeArray[r - n][1] = 0;
					ds->Union(ds->find(r), ds->find(r - n));
					//ds->Union(r, r - n);//unions the two rooms
					break;
				case 1:
					if (ds->find(r) == ds->find(r + 1))
					{
						continue;
					}
					mazeArray[r][2] = 0;
					mazeArray[r + 1][3] = 0;
					ds->Union(ds->find(r), ds->find(r + 1));
					//ds->Union(r, r + 1);
					break;
				}
			}
			else if (r > 0 && r < n - 1)
			{
				std::uniform_int_distribution<int> distrobution(0, 2);// picks the adjacent room
				dice = distrobution(eng);

				switch (dice)
				{
				case 0:
					if (ds->find(r) == ds->find(r + 1))
					{
						continue;
					}
					mazeArray[r][2] = 0; //opens both doors
					mazeArray[r + 1][3] = 0;
					ds->Union(ds->find(r), ds->find(r + 1));
					//ds->Union(r, r + 1);//unions the two rooms
					break;
				case 1:
					if (ds->find(r) == ds->find(r + n))
					{
						continue;
					}
					mazeArray[r][1] = 0;
					mazeArray[r + n][0] = 0;
					ds->Union(ds->find(r), ds->find(r + n));
					//ds->Union(r, r + n);
					break;
				case 2:
					if (ds->find(r) == ds->find(r - 1))
					{
						continue;
					}
					mazeArray[r][3] = 0;
					mazeArray[r - 1][2] = 0;
					ds->Union(ds->find(r), ds->find(r - 1));
					//ds->Union(r, r - 1);
					break;
				}
			}
			else if (((r + 1) % n) == 0)
			{

				std::uniform_int_distribution<int> distrobution(0, 2);// picks the adjacent room
				dice = distrobution(eng);

				switch (dice)
				{
				case 0:
					if (ds->find(r) == ds->find(r - n))
					{
						continue;
					}
					mazeArray[r][0] = 0; //opens both doors
					mazeArray[r - n][1] = 0;
					ds->Union(ds->find(r), ds->find(r - n));
					//ds->Union(r, r - n);//unions the two rooms
					break;
				case 1:
					if (ds->find(r) == ds->find(r - 1))
					{
						continue;
					}
					mazeArray[r][3] = 0;
					mazeArray[r -1][2] = 0;
					ds->Union(ds->find(r), ds->find(r - 1));
					//ds->Union(r, r - 1);
					break;
				case 2:
					if (ds->find(r) == ds->find(r + n))
					{
						continue;
					}
					mazeArray[r][1] = 0;
					mazeArray[r + n][0] = 0;
					ds->Union(ds->find(r), ds->find(r + n));
					//ds->Union(r, r + n);
					break;
				}
			}
			else if (r%n == 0)
			{
				std::uniform_int_distribution<int> distrobution(0, 2);// picks the adjacent room
				dice = distrobution(eng);

				switch (dice)
				{
				case 0:
					if (ds->find(r) == ds->find(r - n))
					{
						continue;
					}
					mazeArray[r][0] = 0; //opens both doors
					mazeArray[r - n][1] = 0;
					ds->Union(ds->find(r), ds->find(r - n));
					//ds->Union(r, r - n);//unions the two rooms
					break;
				case 1:
					if (ds->find(r) == ds->find(r + 1))
					{
						continue;
					}
					mazeArray[r][2] = 0;
					mazeArray[r + 1][3] = 0;
					ds->Union(ds->find(r), ds->find(r + 1));
					//ds->Union(r, r + 1);
					break;
				case 2:
					if (ds->find(r) == ds->find(r + n))
					{
						continue;
					}
					mazeArray[r][1] = 0;
					mazeArray[r + n][0] = 0;
					ds->Union(ds->find(r), ds->find(r + n));
					//ds->Union(r, r + n);
					break;
				}
			}
			else if (r<(nSquared - 1) && r>(nSquared - n))
			{
				std::uniform_int_distribution<int> distrobution(0, 2);// picks the adjacent room
				dice = distrobution(eng);

				switch (dice)
				{
				case 0:
					if (ds->find(r) == ds->find(r - n))
					{
						continue;
					}
					mazeArray[r][0] = 0; //opens both doors
					mazeArray[r - n][1] = 0;
					ds->Union(ds->find(r), ds->find(r - n));
					//ds->Union(r, r - n);//unions the two rooms
					break;
				case 1:
					if (ds->find(r) == ds->find(r + 1))
					{
						continue;
					}
					mazeArray[r][2] = 0;
					mazeArray[r + 1][3] = 0;
					ds->Union(ds->find(r), ds->find(r + 1));
					//ds->Union(r, r + 1);
					break;
				case 2:
					if (ds->find(r) == ds->find(r - 1))
					{
						continue;
					}
					mazeArray[r][3] = 0;
					mazeArray[r -1][2] = 0;
					ds->Union(ds->find(r), ds->find(r - 1));
					//ds->Union(r, r - 1);
					break;
				}
			}
			else
			{
				std::uniform_int_distribution<int> distrobution(0, 3);// picks the adjacent room
				dice = distrobution(eng);

				switch (dice)
				{
				case 0:
					if (ds->find(r) == ds->find(r - n))
					{
						continue;
					}
					mazeArray[r][0] = 0; //opens both doors
					mazeArray[r - n][1] = 0;
					ds->Union(ds->find(r), ds->find(r - n));
					//ds->Union(r, r - n);//unions the two rooms
					break;
				case 1:
					if (ds->find(r) == ds->find(r + 1))
					{
						continue;
					}
					mazeArray[r][2] = 0;
					mazeArray[r + 1][3] = 0;
					ds->Union(ds->find(r), ds->find(r + 1));
					//ds->Union(r, r + 1);
					break;
				case 2:
					if (ds->find(r) == ds->find(r - 1))
					{
						continue;
					}
					mazeArray[r][3] = 0;
					mazeArray[r - 1][2] = 0;
					ds->Union(ds->find(r), ds->find(r - 1));
					//ds->Union(r, r - 1);
					break;
				case 3:
					if (ds->find(r) == ds->find(r + n))
					{
						continue;
					}
					mazeArray[r][1] = 0;
					mazeArray[r + n][0] = 0;
					ds->Union(ds->find(r), ds->find(r + n));
					break;
				}
			}
		}
		mazeArray[0][0] = 0;
		mazeArray[nSquared - 1][1] = 0;
		//std::cout << "\n\n" << ds->find(24) << "\n\n";
		//ds->printer(24);
	}

	void solve()
	{
		int * solution;
		//Graph<int>* graph = new Graph<int>(n, nSquared, mazeArray);;
		
		Graph<int> * graph = new Graph<int>(nSquared);
		for (int i = 0; i < nSquared; i++)
		{
			//std::list<T> & whichList = adjacencyList[i];

			if (i == 0)
			{
				if (mazeArray[i][1] == 0)
				{
					graph->edge(i, i + n);
				}
				if (mazeArray[i][2] == 0)
				{
					graph->edge(i, i + 1);
				}
			}
			else if (i == (nSquared)-1)
			{
				if (mazeArray[i][0] == 0)
				{
					graph->edge(i, i - n);
				}
				if (mazeArray[i][3] == 0)
				{
					graph->edge(i, i - 1);
				}
			}
			else
			{
				if (mazeArray[i][0] == 0)
				{
					graph->edge(i, i - n);
				}
				if (mazeArray[i][1] == 0)
				{
					graph->edge(i, i + n);
				}
				if (mazeArray[i][2] == 0)
				{
					graph->edge(i, i + 1);
				}
				if (mazeArray[i][3] == 0)
				{
					graph->edge(i, i - 1);
				}
			}
		}

		solution = graph->bfs(0 , nSquared-1);
		printSolution(solution);
		solution = graph->dfs(0, nSquared-1);
		printSolution(solution);
		delete graph;
	
	}


	void printSolution(int * solution)
	{
		char* sol = new char[nSquared];
		int a;
		for (int i = 0; i < nSquared; i++)
		{
			sol[i] = ' ';
		}

		std::cout << "\nThis is the path (in reverse): ";
		a = nSquared - 1;
		std::cout << nSquared - 1 << ' ';
		sol[nSquared - 1] = 'X';
		sol[0] = 'X';
		while (solution[a] != -1)
		{
			sol[solution[a]] = 'X';
			std::cout << solution[a] << ' ';
			a = solution[a];
		}
		
		for (int i = 0; i < nSquared; i++)
		{
			if (i%n == 0)
			{
				std::cout << '\n' << sol[i];
			}
			else
			{
				std::cout << sol[i];
			}
			
		}
		std::cout << '\n';
		delete[] sol;
		delete[] solution;
	}


	bool findAll()
	{
		for (int i = 0; i < nSquared; i++)
		{
			if (ds->find(0) != ds->find(i))
			{
				return false;
			}
		}
		return true;
	}
};

#endif