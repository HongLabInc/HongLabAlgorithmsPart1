#include <iostream>
#include <vector>
#include <stack>
using namespace std;

// Vertex에는 용도에 따라서 int 외에 string 같은 다른 정보들도 저장할 수 있습니다.
// 삽입/삭제가 많으면 list, 접근(읽기/쓰기)이 많으면 vector 권장

struct Vertex
{
	Vertex(int v) { value = v; }

	int value = -1;
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

	// source에서 sink로 가는 경로(path) 찾기
	void DepthFirstPath(int source, int sink)
	{
		cout << "Paths from " << vertices[source]->value << " to " << vertices[sink]->value << endl;

		for (auto* v : this->vertices)
			v->visited = false;

		// DepthFirstPathHelper(... , ... , vector<Vertex*>());
	}

private:
	vector<Vertex*> vertices;

	// 주의: 인수 path는 호출될때마다 매번 복사가 됩니다.
	void DepthFirstPathHelper(Vertex* source, Vertex* sink, vector<Vertex*> path)
	{
		path.push_back(source);

		if (source == sink)
		{
			// 경로 출력
			PrintPath(path);
			return; // 더 찾아갈 필요없음

			// 주의: source->visited = true로 설정하면 다른 경로가 못 들어옴
		}

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
	// Digraph: 간선에서 한쪽으로만 갈 수 있는 단방향 그래프

	// 간단한 경우
	//{
	//	// 0: 애피타이저
	//	// 1: 메인요리
	//	// 2: 디저트

	//	Graph g(3);
	//	g.AddDiEdge(0, 1); // 애피타이저 -> 메인요리
	//	g.AddDiEdge(1, 2); // 메인요리 -> 디저트
	//	g.AddDiEdge(0, 2); // 애피타이저 -> 디저트

	//	// 디저트->애피타이저 X, 싸이클이 생기기 때문

	//	g.DepthFirstPath(0, 2);
	//}

	// Sedgewick Algorithm 4.1 p.536 (조금 달라요)
	{
		Graph g(6);

		g.AddDiEdge(0, 2);
		g.AddDiEdge(2, 1);
		g.AddDiEdge(2, 3);
		g.AddDiEdge(3, 4);
		g.AddDiEdge(3, 5);

		g.AddDiEdge(1, 5);

		for (int i = 0; i < 5; i++)
			for (int j = i + 1; j < 6; j++)
			{
				g.DepthFirstPath(i, j);
				g.DepthFirstPath(j, i);
			}
	}

	return 0;
}

// 참고 자료
// - https://www.geeksforgeeks.org/find-paths-given-source-destination/

