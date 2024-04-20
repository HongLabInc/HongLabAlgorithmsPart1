#include <iostream>
#include <vector>
#include <list>
#include <queue>
#include <limits>
#include <iomanip>
#include <algorithm>
using namespace std;

template<typename T>
void Print(vector<T>& dist)
{
	for (int i = 0; i < dist.size(); i++)
		cout << setw(10) << dist[i];
	cout << endl;
}

struct Edge
{
	int v, w;
	double weight;
};

int main()
{
	constexpr double kInf = numeric_limits<double>::infinity();

	// Sedgewick p. 679
	vector<vector<double>> rates = {
		/*         USD    EUR    GBP    CHF    CAD */
		/*USD*/ {  1.0, 0.741, 0.657, 1.061, 1.005},
		/*EUR*/ {1.349,   1.0, 0.888, 1.433, 1.366},
		/*GBP*/ {1.521, 1.126,   1.0, 1.614, 1.538},
		/*CHF*/ {0.942, 0.698, 0.619,   1.0, 0.953},
		/*CAD*/ {0.995, 0.732, 0.650, 1.049,   1.0}
	};

	int V = 5;

	vector<Edge> edges;
	for (int i = 0; i < V; i++)
		for (int j = 0; j < V; j++)
		{
			if (i != j)
				edges.push_back({ i, j, rates[i][j] });
		}

	// reverse(edges.begin(), edges.end());

	int E = int(edges.size()); // number of edges

	vector<double> dist(V, -kInf);
	vector<int> prev(V, -1);

	int s = 0; // 시작 정점의 인덱스
	dist[s] = 1.0;

	Print(dist);

	for (int v = 1; v < V; v++)
	{
		for (auto e : edges)
		{
			// TODO:
		}

		Print(dist);
	}

	for (auto e : edges)
	{
		if (dist[e.w] < dist[e.v] * e.weight)
		{
			cout << "Arbitrage opportunity was found." << endl;
			prev[e.w] = e.v;

			// TODO:

			exit(0);
		}
	}

	cout << "Arbitrage opportunity was not found." << endl;

	return 0;
}
