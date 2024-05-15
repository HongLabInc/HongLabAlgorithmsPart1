#include <iostream>
#include <vector>
#include <stack>
using namespace std;

struct Edge
{
	int u = 0;
	int v = 0;
	int weight = 0;
};

struct Vertex
{
	Vertex(int v) { value = v; }

	int value = -1;// 변수 이름은 value지만 실질적으로는 배열에 이 정점이 저장된 인덱스입니다.
	bool visited = false;

	vector<Edge> out_neighbors; // 나가는 방향의 이웃 vertex들에 대한 포인터
};

class Graph
{
public:
	Graph(int num_vertices)
	{
		vertices.resize(num_vertices);
		for (int i = 0; i < num_vertices; i++)
			vertices[i] = new Vertex(i);
	}

	~Graph()
	{
		for (auto* v : vertices)
			delete v;
	}

	void AddDiEdge(int u, int v, int weight) // 단방향 간선
	{
		vertices[u]->out_neighbors.push_back(Edge{ u, v, weight });
	}

	void AddBiEdge(int u, int v, int weight) // 양방향 간선
	{
		vertices[u]->out_neighbors.push_back(Edge{ u, v, weight });
		vertices[v]->out_neighbors.push_back(Edge{ v, u, weight });
	}

	void TravellingSalesman(int source)
	{
		cout << "Start : " << vertices[source]->value << endl;

		minimum_path.clear();

		for (auto* v : this->vertices)
			v->visited = false;

		TravellingSalesmanHelper(vertices[source], vertices[source], vector<Vertex*>(), 0);

		cout << "Minimum cost : " << min_wsum << endl;
		cout << "Minimum path : ";
		PrintPath(minimum_path);
	}

private:
	vector<Vertex*> vertices;
	vector<Vertex*> minimum_path;
	int min_wsum = 1000000; // large number

	void TravellingSalesmanHelper(Vertex* source, Vertex* sink, vector<Vertex*> path, int wsum)
	{
		// TODO:
	}

	void PrintPath(vector<Vertex*> path)
	{
		for (auto& v : path) {
			cout << v->value;
			if (&v != &path.back())
				cout << " -> ";
		}
		cout << endl;
	}
};

int main()
{
	Graph g(4);

	// 주의: 양방향 간선 (undirected graph)
	g.AddBiEdge(0, 1, 20);
	g.AddBiEdge(0, 2, 25);
	g.AddBiEdge(0, 3, 30);
	g.AddBiEdge(1, 2, 10);
	g.AddBiEdge(2, 3, 35);
	g.AddBiEdge(3, 1, 15);

	g.TravellingSalesman(0);

	return 0;
}

