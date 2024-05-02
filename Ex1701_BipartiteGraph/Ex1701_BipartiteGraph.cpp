#include <iostream>
#include <queue>
#include <vector>
#include <cassert>
#include <iomanip>
using namespace std;

void Print(vector<int>& colors)
{
	for (auto c : colors)
		cout << std::setw(3) << c;
	cout << endl;
}

bool IsBipartite(vector<vector<int>>& graph)
{
	int V = int(graph.size());
	vector<int> colors(V, -1);

	colors[0] = 0;

	queue <int> q;
	q.push(0);

	while (!q.empty())
	{
		int u = q.front();
		q.pop();

		assert(graph[u][u] == 0);

		for (int v = 0; v < V; ++v)
		{
			Print(colors);

			if (graph[u][v] && colors[v] == -1)
			{
				colors[v] = 1 - colors[u]; // color는 0 또는 1, 이웃은 다른 색으로 설정
				q.push(v);
			}
			//else if ( TODO )
			//{
			//	cout << u << " " << v << endl;
			//	return false;
			//}
		}

		Print(colors);
	}

	return true;
}

int main()
{
	{
		vector<vector<int>> graph =
		{
			{0, 1, 1},
			{1, 0, 1},
			{1, 1, 0}
		};

		cout << std::boolalpha << IsBipartite(graph) << endl;
	}

	{
		vector<vector<int>> graph =
		{
			{0, 0, 1, 1},
			{0, 0, 1, 0},
			{1, 1, 0, 0},
			{1, 0, 0, 0}
		};

		cout << std::boolalpha << IsBipartite(graph) << endl;
	}

	{
		vector<vector<int>> graph =
		{
			{0, 1, 1, 1}, // <- 0-1 추가
			{1, 0, 1, 0},
			{1, 1, 0, 0},
			{1, 0, 0, 0}
		};

		cout << std::boolalpha << IsBipartite(graph) << endl;
	}

	return 0;
}

// 참고자료
// https://www.geeksforgeeks.org/bipartite-graph/