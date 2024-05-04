#pragma once

#include <iostream>
#include <vector>
#include <numeric>
#include <iomanip>
using namespace std; // 편의용

class UnionFind
{
public:
	vector<int> group;
	int num_groups;

	UnionFind(int N)
		: group(N), num_groups(N)
	{
		for (int i = 0; i < group.size(); i++)
			group[i] = i;
	}

	int NumGroups()
	{
		return num_groups;
	}

	bool Connected(int p, int q)
	{
		return Find(p) == Find(q);
	}

	/* Quick-Find 방식: Union()에서 미리 정리하기 때문에 Find()는 빠름 */
	int Find(int p)
	{
		return group[p];
	}

	void Union(int p, int q)
	{
		int pid = Find(p);
		int qid = Find(q);

		if (pid == qid) return;

		for (int i = 0; i < group.size(); i++)
		{
			// TODO:
		}

		num_groups--;
	}

	/* Quick-Union 방식: Union()은 빠르고 Find()할 때 정리 */
	/*
	int Find(int p)
	{
		while (p != group[p])
		{
			// TODO:
		}

		return p;
	}

	void Union(int p, int q)
	{
		int i = Find(p);
		int j = Find(q);
		if (i == j) return;

		group[i] = j;

		num_groups--;
	}
	*/

	void Print()
	{
		cout << "Num groups = " << NumGroups() << endl;

		cout << "Index:";
		for (int i = 0; i < group.size(); i++)
			cout << setw(3) << i;
		cout << endl;

		cout << "Group:";
		for (auto i : group)
			cout << setw(3) << i;
		cout << endl;
	}
};
