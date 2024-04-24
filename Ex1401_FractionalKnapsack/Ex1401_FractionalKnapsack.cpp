#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

struct Item
{
	double value;
	double weight;
};

void Print(Item i)
{
	cout << "(" << i.value / i.weight << ", " << i.value << ", " << i.weight << ") ";
}

void Print(vector<Item>& items)
{
	for (auto i : items)
		Print(i);
	cout << endl;
}

bool Compare(struct Item a, struct Item b)
{
	double ratio_a = a.value / a.weight;
	double ratio_b = b.value / b.weight;

	return ratio_a > ratio_b; // ratio가 큰 쪽이 앞으로 오도록 정렬
}

double FractionalKnapsack(vector<Item> items, double W)
{
	sort(items.begin(), items.end(), Compare); // Compare() 함수를 이용해서 정렬

	cout << "W = " << W << endl;
	Print(items);

	double vsum = 0.0;

	for (auto& i : items)
	{
		// TODO:
	}

	return vsum;
}

int main()
{
	double W = 6.0;

	vector<Item> items = { { 10, 1 }, { 28, 4 }, { 12, 2 }, { 12, 3 } };

	cout << FractionalKnapsack(items, W) << endl;

	return 0;
}
