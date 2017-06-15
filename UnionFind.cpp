#include "stdafx.h"
#include "UnionFind.h"


UnionFind::UnionFind(int n0) : n(n0)
{
	rank = new int[n];
	parent = new int[n];
	for (int i = 0; i <= n - 1; i++)
	{
		rank[i] = 0;
		parent[i] = i;
	}
};

UnionFind::~UnionFind()
{
	delete[] rank;
	delete[] parent;
}

int UnionFind::Find(int x) // return a representative of a set
{
	if (parent[x] != x)
		parent[x] = Find(parent[x]);
	return parent[x];
}

void UnionFind::Union(int x, int y) // take two different sets and merge them into one set
{
	int xRoot = Find(x);
	int yRoot = Find(y);
	if (xRoot == yRoot) // if x and y are already in the same set
		return;
	if (rank[xRoot] < rank[yRoot])
		parent[xRoot] = yRoot;
	else if (rank[xRoot] > rank[yRoot])
		parent[yRoot] = xRoot;
	else
	{
		parent[yRoot] = xRoot;
		rank[xRoot] = xRoot + 1;
	}
}