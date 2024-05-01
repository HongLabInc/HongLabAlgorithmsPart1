#include <limits.h>
#include <string.h>
#include <vector>
#include <iostream>
#include <queue>
#include <algorithm>
#include <assert.h>
#include <list>

using namespace std;

class FlowEdge
{
public:
	int v = -1;
	int w = -1;
	double capacity = 0.0; // 최대 용량
	double flow = 0.0;     // 현재 유량

	FlowEdge()
		:v(-1), w(-1), capacity(0.0), flow(0.0)
	{}

	FlowEdge(int v, int w, double capacity)
		: v(v), w(w), capacity(capacity), flow(0.0)
	{}

	FlowEdge(int v, int w, double capacity, double flow)
		: v(v), w(w), capacity(capacity), flow(flow)
	{}

	int From() { return v; }
	int To() { return w; }
	double Capacity() { return capacity; }
	double Flow() { return flow; }
	int Other(int vertex)
	{
		if (vertex == v) return w;
		else if (vertex == w) return v;
		else {
			assert(false);
			return -1;
		}
	}

	double ResidualCapacityTo(int vertex)
	{
		if (vertex == v) return flow;
		else if (vertex == w) return capacity - flow;

		assert(false);

		return 0.0;
	}

	void AddResidualFlowTo(int vertex, double delta)
	{
		if (vertex == v) flow -= delta;
		else if (vertex == w) flow += delta;
		else assert(false);
	}

	void Print()
	{
		cout << v << "->" << w << " " << flow << "/" << capacity << endl;
	}

	int Either() { return v; }
};

class FlowNetwork
{
public:
	int V;
	int E;
	vector<list<FlowEdge*>> adj;

	FlowNetwork(int V)
		: V(V), E(0), adj(V)
	{}

	void AddEdge(FlowEdge e)
	{
		FlowEdge* newEdge = new FlowEdge(e);
		int v = e.Either();
		int w = e.Other(v);
		adj[v].push_back(newEdge); // v의 out_neighbor
		adj[w].push_back(newEdge); // w의 in_neighbor
	}

	list<FlowEdge*>& Adj(int v)
	{
		return adj[v];
	}

	vector<FlowEdge*> AllEdges() {
		vector<FlowEdge*> b;
		for (int v = 0; v < V; v++)
			for (auto& e : this->Adj(v))
				if (e->Other(v) > v)
					b.push_back(e);
		return b;
	}
};

class FordFulkerson
{
public:
	vector<bool> marked;
	vector<FlowEdge*> prev;
	double value;

	FordFulkerson(FlowNetwork& g, int s, int t)
		: marked(g.V), prev(g.V), value(0.0)
	{
		while (HasAugmentingPath(g, s, t))
		{
			// 힌트: Other(), ResidualCapacityTo(), AddResidualFlowTo() 사용
			// TODO:

			Print(g);

			break; // TODO: 삭제
		}
	}

	bool HasAugmentingPath(FlowNetwork& g, int s, int t)
	{
		fill(marked.begin(), marked.end(), false);

		queue<int> q; // BFS

		marked[s] = true;
		q.push(s);

		while (!q.empty())
		{
			int v = q.front();
			q.pop();

			for (FlowEdge* e : g.Adj(v))
			{
				int w = e->Other(v);
				if (!marked[w] && e->ResidualCapacityTo(w) > 0) // <- TODO: BFS와의 차이 확인
				{
					prev[w] = e;
					marked[w] = true;
					q.push(w);
				}
			}
		}

		return marked[t];
	}

	void Print(FlowNetwork& g)
	{
		cout << "Result:" << endl;
		for (int v = 0; v < g.V; v++)
			for (FlowEdge* e : g.Adj(v))
				if (v == e->From())
					e->Print();
		cout << value << endl;
	}
};

int main()
{
	// 강의 영상에 나오는 예시
	FlowNetwork g(4);
	for (const auto& e : vector<FlowEdge>{ {0, 1, 4.0}, {0, 2, 8.0}, {1, 2, 6.0}, {1, 3, 2.0}, {2, 3, 3.0} })
	{
		g.AddEdge(e);
	}

	//FlowNetwork g(6); // CLRS 예제
	//g.AddEdge({ 0, 1, 16.0 });
	//g.AddEdge({ 0, 2, 13.0 });
	//g.AddEdge({ 1, 3, 12.0 });
	//g.AddEdge({ 2, 1, 4.0 });
	//g.AddEdge({ 2, 4, 14.0 });
	//g.AddEdge({ 3, 2, 9.0 });
	//g.AddEdge({ 3, 5, 20.0 });
	//g.AddEdge({ 4, 3, 7.0 });
	//g.AddEdge({ 4, 5, 4.0 });

	FordFulkerson f(g, 0, g.V - 1);

	return 0;
}
