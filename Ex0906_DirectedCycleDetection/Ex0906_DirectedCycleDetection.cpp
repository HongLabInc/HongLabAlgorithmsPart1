#include <iostream>
#include <vector>
#include <stack>
using namespace std;

struct Vertex
{
	Vertex(int v) { index = v; }

	int index = -1; // 덜 헷갈리기 위해 value를 index로 변경
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

	void AddDiEdge(int v, int w)
	{
		vertices[v]->out_neighbors.push_back(vertices[w]);
	}

	void AddBiEdge(int v, int w)
	{
		vertices[v]->out_neighbors.push_back(vertices[w]);
		vertices[w]->out_neighbors.push_back(vertices[v]);
	}

	void DFS(int source)
	{
		cout << "Depth-first Search: ";
		for (auto* v : vertices)
			v->visited = false;
		DFS(vertices[source]);
		cout << endl;
	}

	void DFS(Vertex* source)
	{
		cout << source->index << " ";
		source->visited = true;
		for (auto* w : source->out_neighbors)
			if (!w->visited)
				DFS(w);
	}

	void DetectCycle()
	{
		prev.resize(vertices.size(), nullptr);
		on_stack.resize(vertices.size(), false);
		cycle.clear();

		for (auto* v : vertices)
			v->visited = false;

		for (auto* v : vertices)
		{
			DetectCycle(v);

			if (!cycle.empty()) {
				cout << "Cycle detected" << endl;
				PrintCycle(cycle); // 출력할 때 역순으로 출력합니다.
				return; // 싸이클을 하나라도 발견시 종료
			}
		}

		if (cycle.empty())
			cout << "No cycle detected" << endl;
	}

	void DetectCycle(Vertex* v)
	{
		v->visited = true;
		on_stack[v->index] = true; // 재귀호출 스택에 쌓인 상태 (재귀호출이 끝나지 않은 상태)

		// 디버깅용 출력 (재귀호출 스택에 쌓여있는 상황)
		cout << "On stack: ";
		for (int i = 0; i < on_stack.size(); i++)
			if (on_stack[i])
				cout << i << " ";
		cout << endl;

		for (auto* w : v->out_neighbors)
		{
			if (!cycle.empty())
				return;
			else if (!w->visited)
			{
				// TODO: prev[TODO] = TODO; // Kevin Bacon 예제 복습

				DetectCycle(w);
			}
			//else if ( TODO ) // 싸이클 발견!
			//{
			//	cout << "Cycle detected: " << w->index << endl;

			//	// TODO: 싸이클 저장, 이것도 Kevin Bacon 예제 복습
			//}
		}

		on_stack[v->index] = false; // 재귀호출이 곧 끝난다는 것을 표기
	}

private:
	vector<Vertex*> vertices;
	vector<Vertex*> cycle; // 싸이클이 발견되면 여기에 저장
	vector<Vertex*> prev;  // 이전에 방문한 정점 기록용
	vector<bool> on_stack; // 현재 재귀호출 스택에 들어가 있는 상태인지

	void PrintCycle(vector<Vertex*> cycle)
	{
		std::reverse(cycle.begin(), cycle.end());
		for (auto& v : cycle) {
			cout << v->index;
			if (&v != &cycle.back())
				cout << " -> ";
		}
		cout << endl;
	}
};

int main()
{
	// 한 경로 안에서 한 번 방문한 정점은 다시 방문하지 않는다.

	// 간단한 경우
	{
		// 0: 애피타이저
		// 1: 메인요리
		// 2: 디저트

		Graph g(3);
		g.AddDiEdge(0, 1); // 애피타이저 -> 메인요리
		g.AddDiEdge(1, 2); // 메인요리 -> 디저트
		//g.AddDiEdge(0, 2); // 애피타이저 -> 디저트
		g.AddDiEdge(2, 0); // 디저트 -> 애피타이저 싸이클 생성

		//g.DFS(0);
		g.DetectCycle();
	}

	// Sedgewick Algorithm 4.1 p.536 (조금 달라요)
	{
		Graph g(6);

		g.AddDiEdge(0, 2);
		g.AddDiEdge(2, 1);
		g.AddDiEdge(2, 3);
		g.AddDiEdge(3, 4);
		g.AddDiEdge(1, 5);
		g.AddDiEdge(2, 4);
		g.AddBiEdge(0, 5); // 싸이클 생성

		//g.DFS(2);
		g.DetectCycle();
	}

	return 0;
}

