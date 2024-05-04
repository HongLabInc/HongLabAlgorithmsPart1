#include <iostream> 
#include <vector>
#include <algorithm>
#include <iomanip>
#include <algorithm>
using namespace std;

// 용량 W를 n가지의 아이템으로 채운 경우 담을 수 있는 총 가치의 최대값 반환
// n가지의 아이템이라는 말의 의미는 아이템 1, 2, ..., n 을 넣을지 말지를 고려했다는 의미
// W가 더 작은 경우, n이 더 작은 경우에 대해 재귀호출하는 구조 -> 표 만들때는 반대 순서로 W이나 n이 더 작은 경우부터 채워나가면 된다는 의미

int RecurZeroOneKnapsack(const vector<int>& weights, const vector<int>& values, int W, int n)
{
	cout << "W = " << W << ", n = " << n << endl;

	// 인덱싱 주의
	// weights[n-1] n번째 아이템의 무게
	// values[n-1]  n번째 아이템의 가치(가격)

	if (n == 0 || W == 0)
	{
		return 0;
	}

	/*
	if ( TODO: 용량 W가 부족해서 weights[n - 1]를 넣을 수 없다면 )
	{
		return TODO: n번째 아이템을 넣지 않는 서브트리로 내려감 (용량은 그대로)
	}
	else
	{
		// n번째 아이템을 넣지 않는 경우와 넣는 경우 중 더 큰 값
		// Case 1. 넣지 않는 경우: n-1개의 아이템만 고려하는 경우에 대해 재귀호출
		// Case 2. 넣는 경우: n번째 아이템이 들어갈 용량을 미리 빼놓고 (확보해놓고) n-1개의 아이템만 고려하는 경우에 대해 재귀호출
		//                   재귀호출 결과를 그대로 사용하면 안되고 뭔가 더해줘야 합니다.

		return max(
			TODO, // Case 1
			TODO, // Case 2
		);
	}
	*/

	return 0; // TODO: 제거
}

int ZeroOneKnapsack(vector<int> weights, vector<int> values, int W)
{
	//주의: table에서는 1-based, weights와 values에서는 0-based 사용
	//     아이템 i의 무게는 weights[i - 1] 
	//     아이템 i의 가치는 values[i - 1]
	//     table[w][n] : 무게가 w이고 아이템을 n개까지 고려했을 때 가치의 합 (아이템 n만 고려했다는 것이 아니라 1, ..., n을 모두 고려했다는 의미)

	vector<vector<int> > table(W + 1, vector<int>(weights.size() + 1, 0)); // 모두 0으로 초기화 (아래 루프에서 w = 0 또는 n = 0인 경우 없음)
	vector<vector<vector<int>>> items(W + 1, vector<vector<int>>(weights.size() + 1, vector<int>(weights.size(), 0))); // 디버깅 도우미, 출력 예시 참고

	//힌트: RecurZeroOneKnapsack()하고 연관지어서 생각해보세요.

	for (int w = 1; w <= W; w++)
	{
		for (int n = 1; n <= weights.size(); n++)
		{
			// 힌트: 재귀호출 하는 대신에 먼저 계산되어서 table에 저장되어 있는 값 사용

			/*
			if ( TODO ) // 아이템 weights[n - 1]이 용량초과라서 넣을 수 없는 경우
			{
				table[w][n] = TODO
				items[w][n] = TODO
			}
			else
			{
				if (table[w][n - 1] > table[w - weights[n - 1]][n - 1] + values[n - 1]) // Case 1: 넣지 않는 경우
				{
					table[w][n] = table[w][n - 1];
					items[w][n] = items[w][n - 1];
				}
				else // Case 2: 넣는 경우
				{
					table[w][n] = TODO
					items[w][n] = items[w - weights[n - 1]][n - 1];
					items[w][n][n - 1] += 1; // 안내: 가장 오른쪽 [n-1]은 0-based indexing이라서 -1 추가
				}
			}
			*/
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

int main()
{
	vector<int> values = { 6, 5, 3 };
	vector<int> weights = { 3, 2, 1 };
	int W = 5;

	// 전체 용량 W에 대해 모든 아이템을 고려하는 n = weights.size()로 재귀호출 시작
	std::cout << RecurZeroOneKnapsack(weights, values, W, int(weights.size())) << endl;

	std::cout << ZeroOneKnapsack(weights, values, W) << endl;

	return 0;
}
