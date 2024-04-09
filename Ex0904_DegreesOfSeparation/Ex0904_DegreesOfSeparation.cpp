#include <iostream>
#include <vector>
#include <stack>
#include <unordered_map>
#include <map>
#include <queue>
#include <fstream>
#include <string>
using namespace std;

struct Vertex
{
	Vertex(int v)
	{
		value = v; // ID (디버깅용)
	}

	int value = -1;

	bool visited = false;

	vector<Vertex*> out_neighbors;
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

	deque<Vertex*> BreadthFirstPaths(int source, int sink)
	{
		for (auto* v : vertices)
			v->visited = false;

		vector<Vertex*> prev(vertices.size(), nullptr);

		vertices[source]->visited = true;
		queue<Vertex*> q;
		q.push(vertices[source]);

		while (!q.empty())
		{
			Vertex* v = q.front();
			q.pop();

			if (v == vertices[sink])
				break;

			for (Vertex* w : v->out_neighbors)
			{
				if (!w->visited)
				{
					w->visited = true;
					q.push(w);

					// prev[TODO] = TODO
				}
			}
		}

		deque<Vertex*> path;

		// TODO: prev를 이용해서 path 만들기
		//       deque의 push_front() 사용


		// 결과 출력 (숫자만)
		for (auto* v : path) {
			cout << v->value;
			if (v != path.back())
				cout << " -> ";
		}
		cout << endl;

		return path;
	}

private:
	vector<Vertex*> vertices;
};

vector<string> split(const std::string& str, char delim)
{
	vector<string> strings;
	size_t start;
	size_t end = 0;
	while ((start = str.find_first_not_of(delim, end)) != string::npos) {
		end = str.find(delim, start);
		strings.push_back(str.substr(start, end - start));
	}
	return strings;
}

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

		g.BreadthFirstPaths(0, 2);
	}

	// 조금 더 복잡한 경우
	{
		Graph g(6);

		g.AddDiEdge(5, 2);
		g.AddDiEdge(5, 0);
		g.AddDiEdge(4, 0);
		g.AddDiEdge(4, 1);
		g.AddDiEdge(2, 3);
		g.AddDiEdge(3, 1);

		g.BreadthFirstPaths(5, 4);
		g.BreadthFirstPaths(5, 0);
	}

	{
		// Sedgewick Ch4.2 p.582 jobs.txt 예제
		vector<vector<string>> jobs =
		{
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
		map<string, int> map;  // string -> int
		for (auto& l : jobs)
			for (auto& s : l)
				if (map.count(s) == 0) {
					map[s] = int(values.size());
					values.push_back(s);
				}

		Graph g(int(map.size()));

		for (auto& l : jobs)
		{
			int v = map[l[0]];
			for (int i = 1; i < l.size(); i++)
				g.AddDiEdge(v, map[l[i]]);
		}

		deque<Vertex*> result = g.BreadthFirstPaths(map["Algorithms"], map["Neural Networks"]);

		for (auto* v : result)
			cout << values[v->value] << " " << v->value << endl;
	}

	{
		// movies.txt 파일 출처
		// http://algs4.cs.princeton.edu
		// http://algs4.cs.princeton.edu/code/algs4-data.zip

		vector<vector<string>> jobs;

		cout << "Read file" << endl;
		string line;
		ifstream f("movies.txt");
		if (f.is_open())
		{
			while (std::getline(f, line))
			{
				vector<string> words = split(line, '/');
				jobs.push_back(words);
			}
		}
		else {
			cout << "File not opened" << endl;
		}

		vector<string> values; // int -> string
		map<string, int> map;  // string -> int
		for (auto& l : jobs)
			for (auto& s : l)
				if (map.count(s) == 0) {
					map[s] = int(values.size());
					values.push_back(s);
					// cout << map[s] << " " << s << endl;
				}

		Graph g(int(map.size()));

		for (auto& l : jobs)
		{
			int v = map[l[0]];
			for (int i = 1; i < l.size(); i++)
			{
				g.AddBiEdge(v, map[l[i]]); // Bi-directional edge

				//cout << map[l[i]] << ", ";
			}
		}

		deque<Vertex*> result = g.BreadthFirstPaths(map["Bacon, Kevin"], map["Kidman, Nicole"]);
		//deque<Vertex*> result = g.BreadthFirstPaths(map["Bacon, Kevin"], map["Grant, Cary"]);

		for (auto* v : result)
			cout << values[v->value] << " " << v->value << endl;
	}

	return 0;
}
