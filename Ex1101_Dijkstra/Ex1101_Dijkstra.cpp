#include <iostream>
#include <list>
#include <vector>
#include <limits>
#include <queue>
#include <iomanip>

using namespace std;

// 간선을 저장하는 구조 사용 (문제에 따라 적절한 자료구조 사용)
// Sedgewick p. 642
class DirectedEdge
{
public:
	int v;         // 간선 시작(edge tail, 화살표 꼬리) 정점의 인덱스
	int w;         // 간선 끝(edge head, 화살촉) 정점의 인덱스
	double weight; // edge weight

	DirectedEdge(int v, int w, double weight)
	{
		this->v = v;
		this->w = w;
		this->weight = weight;
	}

	double Weight() { return weight; }
	int From() { return v; }
	int To() { return w; }
};

// 간선에 가중치가 있는 방향성 그래프
class EdgeWeightedDiagraph
{
public:
	int num_vertices;
	int num_edges;
	vector<vector<DirectedEdge>> adj; // 여기서는 Edge를 기록하는 자료구조

	EdgeWeightedDiagraph(int num_vertices)
	{
		this->num_vertices = num_vertices;
		this->num_edges = 0;
		adj.resize(this->num_vertices);
	}

	void AddEdge(DirectedEdge e)
	{
		adj[e.From()].push_back(e);
		num_edges += 1;
	}

	vector<DirectedEdge>& Adj(int v) { return adj[v]; }
};

// 최단거리 찾기만을 수행하는 클래스
// 그래프 자체는 다른 클래스 사용
class DijkstraShortestPaths
{
public:
	DijkstraShortestPaths(EdgeWeightedDiagraph& g, int s)
		:
		prev(g.num_vertices, -1),
		dist(g.num_vertices, numeric_limits<double>::infinity()),
		visited(g.num_vertices, false)
	{
		dist[s] = 0.0; // 자기자신과의 거리는 0

		pq.push(pair<double, int>{ 0.0, s }); // {dist, vertex index} 우선순위 큐라서 dist가 필요

		PrintIndex(dist);
		PrintDist(dist);

		while (!pq.empty())
		{
			Relax(g);
		}

		PrintPaths(g.adj); // 최단 경로 출력
	}

	// 여기서 Relax는 점점 긴장을 풀어간다는 의미입니다.
	// 정답을 한 번에 찾는 방식이 아니라 반복(iteration)하면서 
	// 제약 조건을 조금씩 완화시켜간다는 표현입니다.

	void Relax(EdgeWeightedDiagraph& g)
	{
		int v = pq.top().second; // pair<double, int> 중에서 int 부분
		pq.pop();

		if (visited[v]) return;
		visited[v] = true;
		// 우선순위큐에 change_key()가 없기 때문에 중복 방문을 방지하고 싶은 경우에는
		// visited에 기록하는 방식으로 보완할 수 있습니다. 
		// visited 관련 코드를 모두 삭제해도 최단거리 결과는 동일합니다.
		// 아래 pq.push() 밑의 설명도 참고하세요.

		// 인접 edge들 중에서 가장 가까운 것을 이용해서 업데이트
		for (DirectedEdge& e : g.Adj(v))
		{
			// dist[v]: s에서 v까지 오기 위해 현재까지 발견된 최소거리 경로
			// v에서 다시 w로 이동할 경우 dist 업데이트

			//int w = TODO

			// 현재까지 알려진 v까지의 최단거리에 v의 아웃 간선의 거리를 더해서 w 까지의 새로운 거리 계산
			//double new_dist = TODO
			//if (TODO) // w까지 오는 새로운 최단 경로 발견
			//{
			//	dist[w] = TODO;

			//	prev[w] = TODO; // 최단 경로 기록

			//	pq.push({ dist[w], w });
			//	// vertex w까지 오는 더 빠른 경로가 나타났으니 w 이후의 경로를 다시 업데이트 하라는 의미
			//	// 이론적으로는 이미 큐에 들어있는 w에 대해서 dist[w]를 줄여주는 것이 깔끔합니다.
			//	// 현실적으로는 이미 들어 있던 dist[w]는 건드릴 필요 없이
			//	// 더 작은 dist[w]를 추가로 넣어주면 visited에 의해 더 큰 것은 무시됩니다.
			//	// https://stackoverflow.com/questions/9209323/easiest-way-of-using-min-priority-queue-with-key-update-in-c

			//	// pq에 update() 기능이 있을 때의 가상 구현
			//	// if(pq.contains(w) pq.update({dist[w], w});
			//	// else pr.push({dist[w], w});
			//	// visited 관련 코드는 모두 제거 가능
			//}
		}

		PrintDist(dist);
	}

	void PrintIndex(vector<double>& dist)
	{
		cout << "Vertex: ";
		for (int i = 0; i < dist.size(); i++)
			cout << setw(6) << i;
		cout << endl;
	}

	void PrintDist(vector<double>& dist)
	{
		cout << "Dist  : ";
		for (int i = 0; i < dist.size(); i++)
			cout << setw(6) << dist[i];
		cout << endl;
	}

	void PrintPaths(vector<vector<DirectedEdge>>& adj)
	{
		for (int i = 0; i < adj.size(); i++)
		{
			// TODO: 앞에 비슷한 패턴이 몇 번 나왔습니다.
		}
	}

private:
	vector<int> prev;
	vector<double> dist;
	vector<bool> visited;

	priority_queue<pair<double, int>, vector<pair<double, int>>, greater<pair<double, int>>> pq;
};

int main()
{
	// CLRS p.621
	{
		vector<DirectedEdge> edges = {
		{0, 1, 10.0},
		{0, 3, 5.0},
		{1, 2, 1.0},
		{1, 3, 2.0},
		{2, 4, 4.0},
		{3, 1, 3.0},
		{3, 2, 9.0},
		{3, 4, 2.0},
		{4, 0, 7.0},
		{4, 2, 6.0},
		};

		EdgeWeightedDiagraph g(5);

		for (auto e : edges)
			g.AddEdge(e);

		DijkstraShortestPaths d(g, 0);
	}

	// 우선순위 큐 
	//{
	//	// 큰 값의 우선순위가 높은 max queue
	//	{
	//		priority_queue<double> max_queue;
	//		// 위에서 double은 max_queue에 저장될 아이템들의 자료형

	//		for (auto v : vector<double>{ 3.5, 2.4, 8.3, 9.9, 1.2, 3.9 })
	//			max_queue.push(v);

	//		// 큰 값부터 출력
	//		while (!max_queue.empty())
	//		{
	//			cout << max_queue.top() << " ";
	//			max_queue.pop();
	//		}
	//		cout << endl;
	//	}

	//	// 작은 값의 우선순위가 높은 min queue
	//	{
	//		priority_queue<double, vector<double>, greater<double>> min_queue;
	//		// 위에서 double은 저장될 자료형
	//		// vector<double>은 pq에서 내부적으로 사용할 컨테이너
	//		// greater<double>는 우선순위를 결정할 때 사용할 비교
	//		// https://en.cppreference.com/w/cpp/container/priority_queue
	//		// 아래 예제코드에 min priority queue 부분 참고
	//		// std::greater<int> makes the max priority queue act as a min priority queue

	//		for (auto v : vector<double>{ 3.5, 2.4, 8.3, 9.9, 1.2, 3.9 })
	//			min_queue.push(v);

	//		// 작은 값부터 출력
	//		while (!min_queue.empty())
	//		{
	//			cout << min_queue.top() << " ";
	//			min_queue.pop();
	//		}
	//		cout << endl;
	//	}

	//	// std::pair와 함께 사용
	//	{
	//		priority_queue<pair<double, int>, vector<pair<double, int>>, greater<pair<double, int>>> pq;
	//		for (pair<double, int> v : vector<pair<double, int>>{ {3.5, 3}, {8.3, 1}, {3.5, 1}, {3.5, 2}, {2.4, 8}, {8.3, 5} })
	//			pq.push(v);
	//		// 작은 값부터 출력
	//		while (!pq.empty())
	//		{
	//			cout << "(" << pq.top().first << ", " << pq.top().second << ") ";
	//			pq.pop();
	//		}
	//		cout << endl;
	//	}
	//}
}
