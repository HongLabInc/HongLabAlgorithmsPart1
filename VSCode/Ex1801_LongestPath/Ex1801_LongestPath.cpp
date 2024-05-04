#include <iostream>
#include <vector>
#include <stack>
using namespace std;

struct Vertex
{
	Vertex(int v) { value = v; }

	int value = -1;// 변수 이름은 value지만 실질적으로는 배열에 이 정점이 저장된 인덱스입니다.
	bool visited = false;

	vector<Vertex*> out_neighbors; // 나가는 방향의 이웃 vertex들에 대한 포인터
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

	void AddDiEdge(int v, int w) // 단방향 간선
	{
		vertices[v]->out_neighbors.push_back(vertices[w]);
	}

	void AddBiEdge(int v, int w) // 양방향 간선
	{
		vertices[v]->out_neighbors.push_back(vertices[w]);
		vertices[w]->out_neighbors.push_back(vertices[v]);
	}

	void DFS(int source)
	{
		cout << "Depth-first Search: ";
		for (auto* v : this->vertices)
			v->visited = false;
		DFS(vertices[source]);
		cout << endl;
	}

	void DFS(Vertex* source)
	{
		cout << source->value << " ";
		source->visited = true;
		for (auto* w : source->out_neighbors)
			if (!w->visited)
				DFS(w);
	}

	void DepthFirstPath(int source, int sink)
	{
		cout << "Paths from " << vertices[source]->value << " to " << vertices[sink]->value << endl;

		longest_path.clear();

		for (auto* v : this->vertices)
			v->visited = false;

		DepthFirstPathHelper(vertices[source], vertices[sink], vector<Vertex*>());

		cout << "Longest length : " << int(longest_path.size() - 1) << endl;
		cout << "Longest path : ";
		PrintPath(longest_path);
	}

private:
	vector<Vertex*> vertices;
	vector<Vertex*> longest_path;

	void DepthFirstPathHelper(Vertex* source, Vertex* sink, vector<Vertex*> path)
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
	Graph g(6);

	// 주의: 양방향 간선 (undirected graph)
	g.AddBiEdge(0, 2);
	g.AddBiEdge(2, 1);
	g.AddBiEdge(2, 3);
	g.AddBiEdge(3, 4);
	g.AddBiEdge(1, 5);
	g.AddBiEdge(2, 4);
	g.AddBiEdge(3, 5);

	g.DepthFirstPath(0, 4);

	return 0;
}

