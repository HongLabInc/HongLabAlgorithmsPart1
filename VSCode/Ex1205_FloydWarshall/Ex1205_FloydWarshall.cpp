#include <iostream>
#include <vector>
#include <limits>
#include <iomanip>
#include <deque>
using namespace std;

constexpr double kInf = numeric_limits<double>::infinity();

template<typename T>
void Print(const vector<vector<T>>& dist)
{
	int V = dist.size();

	for (int i = 0; i < V; i++)
	{
		for (int j = 0; j < V; j++)
			cout << setw(5) << dist[i][j];
		cout << endl;
	}
	cout << endl;
}

void Print(int i, int j, double w)
{
	cout << "(" << i << "," << j << "," << w << ")";
}

void PrintPaths(vector<int> prev)
{
	for (int i = 0; i < prev.size(); i++)
	{
		deque<int> path;
		path.push_front(i);
		int v = prev[i];
		while (v != -1)
		{
			path.push_front(v);
			v = prev[v];
		}

		for (auto v : path) {
			cout << v;
			if (v != path.back())
				cout << " -> ";
		}
		cout << endl;
	}
}

void RepeatingBellmanFord(const vector<vector<double>>& graph)
{
	// 힌트: 벨먼-포드를 여러 번 반복하는 방식
	cout << "Repeating Bellman-Ford" << endl;

	vector<vector<double>> dist = graph; // 복사 후 업데이트 하는 방식

	int V = graph.size();

	vector<vector<int>> prev(V, vector<int>(V));
	for (int i = 0; i < V; i++)
		for (int j = 0; j < V; j++)
		{
			if (i == j || graph[i][j] == kInf)
				prev[i][j] = -1;
			else
				prev[i][j] = i;
		}

	cout << "dist 0" << endl;
	Print(dist);
	cout << "prev 0" << endl;
	Print(prev);

	for (int s = 0; s < V; s++) // s는 시작 정점
	{
		for (int v = 1; v < V; v++)
		{
			// CLRS 교재에서는 Floyd-Warshall을 구현할 때 사본을 만들어서 업데이트 방식이라서
			// 여기서는 이해를 돕기 위해 Bellman-Ford도 비슷하게 구조를 바꿔봤습니다.
			// 참고로, 위키피디아에서는 사본 없이 바로 덮어쓰는 in-place 방식입니다.
			auto dist_k = dist;
			auto prev_k = prev;

			// Bellman-Ford에 인접 리스트 대신에 인접 행렬 사용
			for (int i = 0; i < V; i++)
			{
				for (int j = 0; j < V; j++)
				{
					// TODO: grpah[][]와 dist[][]를 사용해서 dist_k와 prev_k 업데이트
				}
			}

			swap(dist_k, dist);
			swap(prev_k, prev);

			cout << "dist " << s + 1 << endl;
			Print(dist);
			cout << "prev " << s + 1 << endl;
			Print(prev);

			cout << "Paths " << s + 1 << endl;
			for (int i = 0; i < prev.size(); i++) {
				cout << "From " << i << " to others:" << endl;
				PrintPaths(prev[i]);
			}
		}
	}
}

void FloydWarshall(const vector<vector<double>>& graph)
{
	cout << "FloydWarshall" << endl;

	vector<vector<double>> dist = graph; // 복사 후 업데이트 하는 방식

	int V = graph.size();

	vector<vector<int>> prev(V, vector<int>(V));
	for (int i = 0; i < V; i++)
		for (int j = 0; j < V; j++)
		{
			if (i == j || graph[i][j] == kInf)
				prev[i][j] = -1;
			else
				prev[i][j] = i;
		}

	cout << "dist 0" << endl;
	Print(dist);
	cout << "prev 0" << endl;
	Print(prev);

	for (int k = 0; k < V; k++)
	{
		auto dist_k = dist;
		auto prev_k = prev;

		for (int i = 0; i < V; i++)
		{
			for (int j = 0; j < V; j++)
			{
				// TODO: i -> j 와 i -> k -> j 비교해서 필요하면 업데이트
			}
		}

		swap(dist_k, dist);
		swap(prev_k, prev);

		cout << "dist " << k + 1 << endl;
		Print(dist);
		cout << "prev " << k + 1 << endl;
		Print(prev);

		cout << "Paths " << k + 1 << endl;
		for (int i = 0; i < prev.size(); i++) {
			cout << "From " << i << " to others:" << endl;
			PrintPaths(prev[i]);
		}
	}
}

int main()
{
	vector<vector<double>> graph =
	{
		{0.0, 3.0, 8.0, kInf, -4.0},
		{kInf, 0.0, kInf, 1.0, 7.0},
		{kInf, 4.0, 0.0, kInf, kInf},
		{2.0, kInf, -5.0, 0.0, kInf},
		{kInf, kInf, kInf, 6.0, 0.0}
	};

	// RepeatingBellmanFord(graph);

	FloydWarshall(graph);
}
