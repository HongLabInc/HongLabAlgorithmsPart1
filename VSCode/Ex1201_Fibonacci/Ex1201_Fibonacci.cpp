#include <vector>
#include <iostream>
#include <iomanip>
using namespace std;

int RecurFibonacci(int n)
{
	cout << "RecurFibonacci(" << setw(2) << n << ")" << endl;

	if (n == 0) return 0;
	if (n == 1) return 1;

	return RecurFibonacci(n - 2) + RecurFibonacci(n - 1);
}

// 메모에 vector 대신에 unordered_map을 사용하는 경우도 있습니다.
int MemoizedTopDownFibonacciHelper(int n, std::vector<int>& memo)
{
	// TODO:

	for (auto& t : memo) cout << setw(4) << t; cout << endl;

	return memo[n];
}

int MemoizedTopDownFibonacci(int n)
{
	vector<int> memo(n + 1, -1); // -1로 초기화
	memo[0] = 0;
	memo[1] = 1;

	return MemoizedTopDownFibonacciHelper(n, memo);
}

int BottomUpFibonacciTabulation(int n)
{
	if (n == 0) return 0;
	if (n == 1) return 1;

	vector<int> table(n + 1, -1);
	table[0] = 0;
	table[1] = 1;

	// for ( TODO )
	{
		// TODO:

		for (auto& t : table) cout << setw(4) << t; cout << endl;
	}

	return table[n]; // The N-th Fibonacci number
}

// 재미로 배열 없이 구현해보기
int BottomUpFibonacci(int n)
{
	if (n == 0 || n == 1)
		return n;

	int a = 0;
	int b = 1;

	// TODO:

	return b; // The N-th Fibonacci number
}

int main()
{
	int n = 7; // 숫자가 크면 단순 재귀 버전은 많이 느립니다.

	cout << RecurFibonacci(n) << endl;

	cout << MemoizedTopDownFibonacci(n) << endl;

	cout << BottomUpFibonacciTabulation(n) << endl;

	cout << BottomUpFibonacci(n) << endl;

	return 0;
}


