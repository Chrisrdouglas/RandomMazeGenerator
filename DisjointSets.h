#ifndef DISJOINTSETS_H
#define DISJOINTSETS_H
#pragma once
#include <iostream>
//#include "dsNode.h"

template<typename T>
class DisjointSets {
private:
	int * ds;
	int size;
public:
	DisjointSets()
	{
		ds = NULL;
	}

	DisjointSets(int n)
	{
		ds = new int[n+1];
		size = n;
		for (int i = 0; i < n; i++)
		{
			ds[i] = -1;
		}
	}
	
	~DisjointSets()
	{
		delete[] ds;
	}

	bool findAll()
	{
		for (int i = 0; i < size; i++)
		{
			if (find(0) != find(i))
			{
				return false;
			}
		}
		return true;
	}

	void Union(int i, int j) //will ruin the disjoint set if i == j. i and j must be roots of sets
	{
		if (find(i) != find(j))
		{
			if (ds[j] < ds[i])
			{
				ds[i] = j;
			}
			else
			{
				if (ds[i] == ds[j])
				{
					ds[i]--;
				}
				ds[j] = i;
			}
		}
	}

	int find(int i)
	{

		if (ds[i] < 0)
			{	return i;	}
		else 
		{
			ds[i] = find(ds[i]);//path compression
			return ds[i];
		}
	}

	/*void printer(int i)
	{
		while (i != 0)
		{
			std::cout << i << ' ';
			i = ds[i];
		}
		std::cout << i << ' ' << '\n';
	}*/
};


#endif
