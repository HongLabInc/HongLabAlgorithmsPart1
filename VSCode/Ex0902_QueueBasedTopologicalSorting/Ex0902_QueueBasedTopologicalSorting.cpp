#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <unordered_map>
#include <map>
#include <assert.h>
using namespace std;

struct Vertex
{
	Vertex(int v)
	{
		value = v;
	}

	// 여기서는 value가 그래프에 저장된 인덱스와 동일합니다.
	// 디버깅하기에 편합니다.
	// 실무에서는 인덱스 외에 다른 정보도 저장될 수 있습니다.

	int value = -1;

	bool visited = false;

	vector<Vertex*> out_neighbors;
	vector<Vertex*> in_neighbors; // 선행 정점 방문 확인용

	// int indegree = 0; // indegree를 Vertex에 저장하는 방식으로 구현할 수도 있습니다.
	// 특정 기능을 수행하기 위한 임시 메모리는 Vertex에 넣어두기 보다는
	// 별도로 필요한 때만 할당해서 사용하는 것이 더 효율적일 수도 있습니다.
	// 여기서는 아래에 별도의 vector<int> indegree(vertices.size());를 사용합니다.
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
		vertices[w]->in_neighbors.push_back(vertices[v]); // 선행 정점 방문 확인용
	}

	void PrecedenceCheck(stack<Vertex*> my_stack) // my_stack의 사본
	{
		for (auto* v : this->vertices)
			v->visited = false;

		while (!my_stack.empty())
		{
			Vertex* v = my_stack.top();
			cout << "Precedence check " << v->value << " : ";
			for (auto* w : v->in_neighbors)
			{
				// 선수조건을 만족했는지 확인
				if (!w->visited)
				{
					cout << "Wrong" << endl;
					exit(-1);
				}
				else {
					cout << w->value << ", ";
				}
			}
			cout << endl;
			v->visited = true;
			my_stack.pop();
		}
		cout << "OK" << endl;
	}

	stack<Vertex*> QueueBasedTopologicalSort()
	{
		vector<int> indegree(vertices.size()); // indegree를 Vertex에 저장할 수도 있습니다.
		// TODO:

		queue<Vertex*> q;

		// indegree가 0인 vertex들을 q에 넣기
		// TODO:

		vector<Vertex*> result;

		// TODO:

		// 뒤에서 DFS 방식 예제와의 호환성을 위해 역순으로 stack에 저장
		stack<Vertex*> s;
		for (auto i = result.rbegin(); i != result.rend(); i++)
			s.push(*i);

		return s;
	}
private:
	vector<Vertex*> vertices;
};

int main()
{
	// 간단한 경우
	{
		// 0: 애피타이저
		// 1: 메인요리
		// 2: 디저트

		Graph g(3);
		g.AddDiEdge(0, 1); // 애피타이저 -> 메인요리
		g.AddDiEdge(1, 2); // 메인요리 -> 디저트
		g.AddDiEdge(0, 2); // 애피타이저 -> 디저트

		// 디저트->애피타이저 X, 싸이클이 생기기 때문

		auto my_stack = g.QueueBasedTopologicalSort();

		g.PrecedenceCheck(my_stack);

		// 결과 출력
		while (!my_stack.empty())
		{
			cout << my_stack.top()->value;
			my_stack.pop();
			if (!my_stack.empty())
				cout << " -> ";
		}
		cout << endl;
	}

	// 조금 더 복잡한 경우
	{
		Graph g(6);

		g.AddDiEdge(5, 2);
		g.AddDiEdge(5, 0);
		g.AddDiEdge(0, 2);
		g.AddDiEdge(4, 0);
		g.AddDiEdge(4, 1);
		g.AddDiEdge(2, 3);
		g.AddDiEdge(3, 1);

		auto my_stack = g.QueueBasedTopologicalSort();
		g.PrecedenceCheck(my_stack);

		while (!my_stack.empty())
		{
			cout << my_stack.top()->value;
			my_stack.pop();
			if (!my_stack.empty())
				cout << " -> ";
		}
		cout << endl;
	}

	{
		// Sedgewick Ch4.2 p.582 jobs.txt 예제
		// 가장 왼쪽의 과목이 나머지의 선수과목인 예제입니다.
		// 예: "Algorithms"가 "Theoretical CS", "Databases", "Scientific Computing" 세 과목의 선수과목
		vector<vector<string>> jobs = {
			{"Algorithms", "Theoretical CS", "Databases", "Scientific Computing"},
			{"Introduction to CS", "Advanced Programming", "Algorithms"},
			{"Advanced Programming", "Scientific Computing"},
			{"Scientific Computing", "Computational Biology"},
			{"Theoretical CS", "Computational Biology", "Artificial Intelligence"},
			{"Linear Algebra", "Theoretical CS"},
			{"Calculus", "Linear Algebra"},
			{"Artificial Intelligence", "Neural Networks", "Robotics", "Machine Learning"},
			{"Machine Learning", "Neural Networks"}
		};

		vector<string> values; // int -> string
		map<string, int> keys;  // string -> int
		for (auto& l : jobs)
			for (auto& s : l)
				if (keys.count(s) == 0) {
					keys[s] = int(values.size());
					values.push_back(s);
					cout << keys[s] << " " << s << endl;
				}

		Graph g(int(keys.size()));

		for (auto& l : jobs)
		{
			int v = keys[l[0]];
			cout << v << " : ";
			for (int i = 1; i < l.size(); i++)
			{
				g.AddDiEdge(v, keys[l[i]]);

				cout << keys[l[i]] << ", ";
			}
			cout << endl;
		}

		auto my_stack = g.QueueBasedTopologicalSort();
		g.PrecedenceCheck(my_stack);

		while (!my_stack.empty())
		{
			cout << values[my_stack.top()->value] << " " << my_stack.top()->value << endl;
			my_stack.pop();
		}
	}

	return 0;
}
