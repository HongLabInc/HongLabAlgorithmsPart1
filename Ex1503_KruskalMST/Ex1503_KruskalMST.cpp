#include "../Ex1502_UnionFind/UnionFind.h"
#include <queue>
#include <assert.h>
#include <vector>
#include <list>

struct Edge
{
	int u; // 한쪽 끝
	int v; // 다른쪽 끝
	double weight;

	// 정렬할 때 사용
	bool operator < (const Edge& other) const
	{
		return weight < other.weight;
	}
};

void PrintEdges(vector<Edge>& edges)
{
	for (auto e : edges)
		cout << "(" << e.u << ", " << e.v << ", " << e.weight << ")" << endl;
}

int main()
{
	// Kruskal 알고리듬에서는 간선만 사용하기 때문에 edges만 가지고 진행
	vector<Edge> edges =
	{
		{ 0, 1, 4.0 },
		{ 0, 7, 9.0 },
		{ 1, 2, 8.0 },
		{ 1, 7, 11.0 },
		{ 2, 3, 7.0 },
		{ 2, 5, 4.0 },
		{ 2, 8, 2.0 },
		{ 3, 4, 9.0 },
		{ 3, 5, 14.0 },
		{ 4, 5, 10.0 },
		{ 5, 6, 2.0 },
		{ 6, 7, 1.0 },
		{ 6, 8, 6.0 },
		{ 7, 8, 7.0 },
	};

	// 여기서는 간선의 weight가 정점 사이의 이동 비용을 의미합니다.
	sort(edges.begin(), edges.end()); // 간선의 weight 오름차순

	PrintEdges(edges); // 정렬 결과 확인

	double mst_wt = 0.0;

	UnionFind uf(9);

	for (auto& e : edges)
	{
		// TODO:

		mst_wt += e.weight;

		cout << e.u << " - " << e.v << " : " << e.weight << endl;
	}

	cout << mst_wt << endl;

	return 0;
}
