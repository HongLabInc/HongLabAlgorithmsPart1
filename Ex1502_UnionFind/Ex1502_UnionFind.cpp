#include "UnionFind.h"
#include <utility>
using namespace std;

int main()
{
	UnionFind uf(3);
	vector<pair<int, int>> tests =
	{
		{0, 1}, {1, 2}, {0, 2}
	};

	//UnionFind uf(9);
	//vector<pair<int, int>> tests =
	//{
	//	{6, 7}, {2, 8}, {5, 6}, {0, 1}, {2, 5}, {6, 8}, { 2, 3 }, {7, 8},
	//	{1, 2}, {0, 7}, {3, 4}, {4, 5}, {1, 7}, {3, 5}
	//};

	uf.Print();

	for (auto t : tests)
	{
		int u = t.first;
		int v = t.second;
		bool connected = uf.Connected(u, v);

		cout << u << " " << v << " " << std::boolalpha << connected << endl;
		cout << "Union " << u << " " << v << endl;

		uf.Union(u, v);

		uf.Print();
	}

	// Quick-Find와 Quick-Union의 차이: Find()를 빠르게 할지 Union()을 빠르게 할지
}
