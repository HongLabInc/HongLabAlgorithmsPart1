#include <iostream> 
#include <vector>
#include <algorithm>
#include <iomanip>
#include <algorithm>
using namespace std;

// W는 남은 무게
// i는 아이템의 1-based index
int RecurZeroOneKnapsack(const vector<int>& weights, const vector<int>& values, int W, int i)
{
	cout << "W = " << W << ", i = " << i << endl;

	// weights[i - 1] : 아이템 i의 무게 

	if (i == 0 || W == 0)
		return 0;

	//if ( TODO )
	//{
	// // 더 넣을 수 있는 무게 w가 부족해서 못 넣는 경우
	// // i를 넣지 않는다는 것은 0 ~ i-1 까지만 넣는다는 의미
	// return RecurZeroOneKnapsack(weights, values, TODO, TODO);
	//}
	//else
	//{
	// // 넣을 수 있는 상황
	// // 넣었을 때와 넣지 않았을 때를 비교
	//	return max(
	//		RecurZeroOneKnapsack(weights, values, TODO, TODO),
	//		RecurZeroOneKnapsack(weights, values, TODO, TODO) + values[i - 1]
	//	);
	// }

	return 0; // TODO: 제거
}

int ZeroOneKnapsack(vector<int> weights, vector<int> values, int W)
{
	// table에서는 1-based, weights와 values에서는 0-based 사용

	// table[w][i] : 가치의 합
	vector<vector<int> > table(W + 1, vector<int>(weights.size() + 1, 0));
	vector<vector<vector<int>>> items(W + 1, vector<vector<int>>(weights.size() + 1, vector<int>(weights.size(), 0)));

	// 아이템 i의 무게는 weights[i - 1] 
	// 아이템 i의 가치는 values[i - 1]

	for (int w = 1; w <= W; w++)
	{
		// 무게가 w일 때 어떤 아이템 i를 추가하는 것이 좋은지 아닌지 따져보기
		for (int i = 1; i <= weights.size(); i++)
		{
			//if (i == 0 || w == 0)
			//{
			//	table[w][i] = 0; // 불필요
			//}

			//if ( TODO ) // 아이템 i의 무게가 넣을 수 있는 무게인지
			//{
			//	// 아이템 i를 넣는 것이 좋은지 아니면 넣지 않는 것이 좋은지 비교
			//	// 힌트: table[w - weights[i - 1]][i - 1] 아이템 i를 넣을 여유가 있는 상태의 총 가치
			//	//       table[w - weights[i - 1]][i - 1] + values[i - 1] 아이템 i를 넣어서 무게를 w로 맞췄을 때의 가치
			//	if ( TODO )
			//	{
			//		// 아이템 i를 넣지 않았을 때

			//		table[w][i] = TODO;

			//		items[w][i] = TODO; // 복사만
			//	}
			//	else
			//	{
			//		// 아이템 i를 넣었을 때

			//		table[w][i] = TODO;

			//		items[w][i] = TODO;
			//		items[w][i][i - 1] += 1; // 아이템 i 하나 증가
			//	}
			//}
			//else
			//{
			//	table[w][i] = table[w][i - 1];
			//	items[w][i] = items[w][i - 1];
			//}
		}
	}

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

int main()
{
	vector<int> values = { 6, 5, 3 };
	vector<int> weights = { 3, 2, 1 };
	int W = 5;

	cout << RecurZeroOneKnapsack(weights, values, W, int(weights.size())) << endl;
	cout << ZeroOneKnapsack(weights, values, W) << endl;

	return 0;
}
