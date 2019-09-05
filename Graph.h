#ifndef GRAPH_H
#define GRAPH_H
#pragma once
#include <list>
#include <vector>
#include <algorithm>
#include <queue>
#include <cmath>
#include "Stack.h"

template<typename T>
class Graph {
private:
	int verticies;
	int edges;
	std::vector< std::list<T> > adjacencyList;
public:
	Graph()
	{
		verticies = 0;
		edges = 0;
		adjacencyList = NULL;
	}

	Graph(int n) {
		verticies = n;
		adjacencyList.resize(n);
	}

	/*Graph(int n, int nSquared, T * arr[])
	{
		verticies = nSquared;
		adjacencyList.resize(nSquared);
		for (int i = 0; i < nSquared; i++)
		{
			std::list<T> & whichList = adjacencyList[i];

			if (i == 0)
			{
				if (arr[i][1] == 0)
				{
					edge(i, i+n);
				}
				if (arr[i][2] == 0)
				{
					edge(i, i + 1);
				}
			}
			else if (i == (n) - 1)
			{
				if (arr[i][0] == 0)
				{
					edge(i, i - n);
				}
				if (arr[i][3] == 0)
				{
					edge(i, i - 1);
				}
			}
			else 
			{
				if (arr[i][0] == 0)
				{
					edge(i, i - n);
				}
				if (arr[i][1] == 0)
				{
					edge(i, i + n);
				}
				if (arr[i][2] == 0)
				{
					edge(i, i + 1);
				}
				if (arr[i][3] == 0)
				{
					edge(i, i - 1);
				}
			}
		}
	}*/

	void edge(int i, int j)
	{
		std::list<T> & whichList = adjacencyList[i];
		whichList.push_back(j);
		edges++;
	}

	bool areAdj(int i, int j)
	{
		std::list<T> & whichList1 = adjacencyList[i];
		std::list<T> & whichList2 = adjacencyList[j];
		if (std::find(whichList1.begin(), whichList1.end(), j) && std::find(whichList2.begin(), whichList2.end(), i))
		{
			return true;
		}
		return false;
	}

	std::list<T> listOfEdges(int i)
	{
		return adjacencyList[i];
	}

	int * bfs(int start, int end)
	{
		int * solution = new int[verticies];
		std::queue<int> myqueue;
		std::list<int> edg;
		bool * visited = new bool[verticies];
		int i = start;
		int j;

		visited[i] = true;
		solution[0] = -1;
		for (int a = 1; a < verticies; a++)
		{
			solution[a] = -1;
			visited[a] = false;
		}
		myqueue.push(start);
		std::cout << "Rooms visited by BFS: ";
		while (myqueue.size() != 0)
		{
			i = myqueue.front();
			myqueue.pop();
			std::cout << i << ' ';
			if (i == end)
			{
				//ds->Union_NOCOMPRESS(j, i);
				break;
			}
			edg = listOfEdges(i);
			for (int a = 0; a < edg.size(); a++)
			{
				j = edg.front();
				edg.pop_front();
				a--;
				if (!visited[j])
				{
					myqueue.push(j);
					solution[j] = i;
					visited[j] = true;
					//ds->Union_NOCOMPRESS(j, i);
				}
				
			}
			//ds.Union(j, i);
		}
		delete[] visited;
		return solution;
	}


	int * dfs(int start, int end)
	{
		Stack<int> f(verticies);
		int * solution = new int[verticies];
		bool * visited = new bool[verticies];
		std::list<int> edg;

		int i = start;
		int j;

		solution[i] = -1;
		visited[0] = true;

		for (i = 1; i < verticies; i++)
		{
			solution[i] = -1;
			visited[i] = false;
		}

		
		f.push(start);

		std::cout << "Rooms visited by DFS: ";
		while (!f.isEmpty())
		{
			f.pop(i);
			std::cout << i << ' ';
			if (i == end)
			{
				break;
			}
			
			edg = listOfEdges(i);
			for (int a = 0; a < edg.size(); a++)
			{
				j = edg.front();
				edg.pop_front();
				a--;
				
				if (!visited[j])
				{
					f.push(j);
					solution[j] = i;
					visited[j] = true;
				}
			}
		}
		delete[] visited;
		return solution;
	
	}
};

#endif
