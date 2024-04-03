#include <iostream>
#include <vector>
#include <random>
#include <limits>
#include <fstream>
#include <chrono>
#include <numeric>
#include <iomanip>
using namespace std;

void Print(vector<int>& arr)
{
	for (auto a : arr)
		if (a == -1)
			cout << "X ";
		else
			cout << a << " ";
	cout << endl;
}

// 입력은 0 이상 k 이하의 정수, CSLR 8.2
// 결과를 반환하는 구조 (In-place가 아님)
vector<int> CountingSort(const vector<int>& arr, int k)
{
	vector<int> count(k + 1, 0); // k + 1개를 0으로 초기화

	// TODO:

	cout << "Count: ";
	Print(count);

	vector<int> output(arr.size(), -1); // -1로 초기화하는 것은 디버깅용

	// 역순으로 복사
	for (int i = output.size() - 1; i >= 0; i--)
	{
		// TODO:

		cout << "Count: ";
		Print(count);

		cout << "Output: ";
		Print(output);
	}

	return output;
}

int main()
{
	vector<int> arr = { 2, 5, 3, 0, 2, 3, 0, 3 };

	Print(arr);

	int k = *std::max_element(arr.begin(), arr.end()); // 가장 큰 값 찾기
	// 가장 작은 값은 0이라고 고정

	vector<int> result = CountingSort(arr, k);

	Print(result);

	return 0;
}