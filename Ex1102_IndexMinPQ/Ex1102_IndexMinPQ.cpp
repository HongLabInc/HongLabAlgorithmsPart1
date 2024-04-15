#include "IndexMinPQ.h"
#include <iostream>
using namespace std;

int main()
{
	IndexMinPQ<double> pq(10);

	for (pair<double, int> p : vector<pair<double, int>>{ {3.5, 3}, {8.3, 1}, {1.5, 1}, {1.6, 3}, {0.5, 8}, {0.1, 5} })
	{
		if (!pq.Contains(p.second)) pq.Insert(p.second, p.first);
		else pq.ChangeKey(p.second, p.first);

		pq.Print();
	}

	while (!pq.Empty())
	{
		cout << "(" << pq.MinKey() << ", " << pq.MinIndex() << ") ";

		pq.DelMin();
	}
	cout << endl;
}
