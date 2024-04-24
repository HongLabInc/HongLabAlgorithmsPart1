#include <algorithm>
#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

template<typename T>
void Print(const vector<T>& items)
{
	for (auto v : items)
	{
		cout << setw(3) << v;
	}
	cout << endl;
}

int RecurUnboundedKnapsack(vector<int> weights, vector<int> values, int W, int n)
{
	// RecurZeroOneKnapsack()와 동일한 코드입니다.
	// Unbounded 버전으로 수정해보세요.
	// 힌트: n 번째 아이템을 여러 번 넣을 수 있다.

	cout << "W = " << W << ", n = " << n << endl;

	if (n == 0 || W == 0)
	{
		return 0;
	}

	if (weights[n - 1] > W)
	{
		return RecurUnboundedKnapsack(weights, values, W, n - 1);
	}
	else
	{
		return max(
			RecurUnboundedKnapsack(weights, values, W, n - 1), // Case 1
			RecurUnboundedKnapsack(weights, values, W - weights[n - 1], n - 1) + values[n - 1] // Case 2
		);
	}
}

// ZeroOneKnapsack()을 아주 약간만 수정한 버전
int BottomUpUnboundedKnapsack1(vector<int> weights, vector<int> values, int W)
{
	vector<vector<int> > table(W + 1, vector<int>(weights.size() + 1, 0)); // 모두 0으로 초기화 (아래 루프에서 w = 0 또는 n = 0인 경우 없음)
	vector<vector<vector<int>>> items(W + 1, vector<vector<int>>(weights.size() + 1, vector<int>(weights.size(), 0)));

	for (int w = 1; w <= W; w++)
	{
		for (int n = 1; n <= weights.size(); n++)
		{
			if (weights[n - 1] > w) // 아이템 n의 무게가 넣을 수 있는 무게인지
			{
				table[w][n] = table[w][n - 1];
				items[w][n] = items[w][n - 1];
			}
			else
			{
				// TODO: 아래는 ZeroOneKnapsack()와 동일합니다. 재귀버전과 비슷하게 수정해보세요.
				if (table[w][n - 1] > table[w - weights[n - 1]][n - 1] + values[n - 1])
				{
					table[w][n] = table[w][n - 1];
					items[w][n] = items[w][n - 1];
				}
				else
				{
					table[w][n] = table[w - weights[n - 1]][n - 1] + values[n - 1];
					items[w][n] = items[w - weights[n - 1]][n - 1];
					items[w][n][n - 1] += 1;
				}
			}
		}
	}

	using std::cout;

	cout << table[W][weights.size()] << endl;
	for (int i = 0; i <= weights.size(); i++)
	{
		cout << i << ": ";
		for (int w = 0; w <= W; w++)
			cout << right << setw(4) << table[w][i];
		cout << endl;
	}
	cout << endl;

	cout << "Weight:";
	for (int w = 0; w <= W; w++)
		cout << right << setw(4) << w;
	cout << endl << endl;

	cout << "Items count" << endl;
	for (int i = 0; i <= weights.size(); i++)
	{
		cout << "Item " << i << ": ";
		for (int w = 0; w <= W; w++) {
			for (int j = 0; j < weights.size(); j++)
				cout << items[w][i][j];
			cout << " ";
		}
		cout << endl;
	}
	cout << endl;

	cout << "Values per item" << endl;
	for (int i = 0; i <= weights.size(); i++)
	{
		cout << "Item " << i << ": ";
		for (int w = 0; w <= W; w++) {
			for (int j = 0; j < weights.size(); j++)
				cout << items[w][i][j] * values[j];
			cout << " ";
		}
		cout << endl;
	}
	cout << endl;

	cout << "Weights per item" << endl;
	for (int i = 0; i <= weights.size(); i++)
	{
		cout << "Item " << i << ": ";
		for (int w = 0; w <= W; w++) {
			for (int j = 0; j < weights.size(); j++)
				cout << items[w][i][j] * weights[j];
			cout << " ";
		}
		cout << endl;
	}
	cout << endl;

	return table[W][weights.size()];
}

int BottomUpUnboundedKnapsack2(vector<int> weights, vector<int> values, int W)
{
	vector<int> table(W + 1, 0); // 1차원 배열 (ZeroOne에서는 2차원)

	vector<vector<int>> items(W + 1, vector<int>(weights.size(), 0));

	for (int w = 1; w <= W; w++)
	{
		for (int n = 1; n <= weights.size(); n++)
		{
			if (weights[n - 1] <= w)
			{
				// TODO:
			}
		}

		cout << "Weight " << setw(2) << w << ", " << "Value " << setw(2) << table[w] << ", items: ";
		Print(items[w]);
	}

	cout << "Items  : ";
	Print(items[W]);
	int wsum = 0, vsum = 0;
	for (int i = 0; i < weights.size(); i++)
	{
		wsum += weights[i] * items[W][i];
		vsum += values[i] * items[W][i];
	}
	cout << wsum << " " << vsum << endl;

	return table[W]; // W만큼 채웠을 때 가격의 합
}

int main()
{
	//int W = 20; // 30
	//vector<int> weights = { 1, 2, 3 };
	//vector<int> values = { 1, 3, 2 };

	int W = 10; // 42
	vector<int> weights = { 6, 2,  4,  3, 11 };
	vector<int> values = { 20, 8, 14, 13, 35 };

	{
		cout << "Brute-force Recursion" << endl;
		cout << "W = " << W << endl;
		cout << "Weights: ";
		Print(weights);
		cout << "Values : ";
		Print(values);
		vector<int> result(weights.size(), 0);
		cout << RecurUnboundedKnapsack(weights, values, W, int(weights.size())) << endl;
		cout << endl;
	}

	{
		cout << "Bottom-up Tabulation" << endl;
		cout << "W = " << W << endl;
		cout << "Weights: ";
		Print(weights);
		cout << "Values : ";
		Print(values);

		cout << BottomUpUnboundedKnapsack1(weights, values, W) << endl;
		cout << endl;

		cout << BottomUpUnboundedKnapsack2(weights, values, W) << endl;
		cout << endl;
	}

	return 0;
}
