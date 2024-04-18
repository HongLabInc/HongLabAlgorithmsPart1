#include <iostream>
#include <math.h>
#include <vector>
#include <iomanip>
using namespace std;

int RecurCutRod(const vector<int>& prices, int length)
{
	// TODO:

	int max_price = numeric_limits<int>::min();

	for (int i = 1; i <= length; i++)
	{
		// TODO:
	}

	return max_price;
}

int MemoizedCutRodHelper(const vector<int>& prices, int length, vector<int>& memo)
{
	// TODO:

	return memo[length];
}

int MemoizedCutRod(const vector<int>& prices, int length)
{
	vector<int> memo(length + 1, -1);
	memo[0] = 0;

	return MemoizedCutRodHelper(prices, length, memo);
}

int ButtomUpCutRod(const vector<int>& prices, int length)
{
	vector<int> table(length + 1, -1); // 가격은 음수가 될 수 없으니까 디버깅 편의를 위해 -1로 초기화
	table[0] = 0; // length* prices[0];

	// TODO:

	return table[length];
}

int main()
{
	vector<int> price_table = { 0, 1, 5, 8, 9, 10, 17, 17, 20, 24, 30 };

	cout << "Naive recursion" << endl;
	for (int length = 0; length < price_table.size(); length++)
	{
		int revenue = RecurCutRod(price_table, length);
		cout << "Optimal revenue for length " << length << ": " << revenue << endl;
	}
	cout << endl;

	cout << "TopDown with Memoization" << endl;
	for (int length = 0; length < price_table.size(); length++)
	{
		int revenue = MemoizedCutRod(price_table, length);
		cout << "Optimal revenue for length " << length << ": " << revenue << endl;
	}
	cout << endl;

	cout << "BottomUp" << endl;
	for (int length = 0; length < price_table.size(); length++)
	{
		int revenue = ButtomUpCutRod(price_table, length);
		cout << "Optimal revenue for length " << length << ": " << revenue << endl;
	}
	cout << endl;

	return 0;
}
