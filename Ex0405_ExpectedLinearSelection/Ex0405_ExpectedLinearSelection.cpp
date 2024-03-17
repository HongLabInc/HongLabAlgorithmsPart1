#include <iostream>
#include <vector>
#include <random>
#include <limits>
#include <fstream>
#include <chrono>
#include <numeric>
#include <iomanip>
using namespace std;
using namespace std::chrono;

void Print(vector<int>& arr)
{
	int lo = 0, hi = arr.size() - 1;

	cout << "Index: ";
	for (int i = lo; i <= hi; i++)
		cout << setfill(' ') << setw(3) << i;
	cout << endl;

	cout << "Value: ";
	for (int i = lo; i <= hi; i++)
		cout << setfill(' ') << setw(3) << arr[i];
	cout << endl;
}

// CLRS p. 184
int Partition(vector<int>& arr, int lo, int hi)
{
	int x = arr[hi]; // 마지막 값을 피벗으로 사용
	int i = lo - 1;
	for (int j = lo; j < hi; j++)
		if (arr[j] <= x)
		{
			i += 1;
			swap(arr[i], arr[j]);
		}

	swap(arr[i + 1], arr[hi]);

	return i + 1; // 피벗이 이동한 위치 반환
}

// CLRS와 변수이름이 다릅니다.
// CLRS는 1-based 인덱스입니다.
// 매개변수 k는 1번째, 2번째, ..., k번째를 의미합니다. 0으로 시작하는 인덱스와 구분해야 합니다.
int RandomizedSelect(vector<int>& arr, int lo, int hi, int k)
{
	// TODO:

	return -1;
}

int SelectionBySorting(vector<int> arr, int k) // arr은 사본
{
	std::sort(arr.begin(), arr.end());
	return arr[k - 1];
}

struct Sample
{
	int n;
	double duration;
};

int main()
{
	vector<int> my_vector = { 6, 19, 4, 12, 14, 9, 15, 7, 8, 11, 3, 13, 2, 5, 10 };

	cout << RandomizedSelect(my_vector, 0, my_vector.size() - 1, 5) << endl;
	// 주의: k는 k번째를 의미, 인덱스 자리는 k - 1

	// 아래는 더 많은 경우에 대해 테스트

	//random_device rd;
	//mt19937 gen(rd());

	//vector<Sample> samples;
	//samples.reserve(5000);

	//for (int n = 1; n <= 10000; n += 1)
	//{
	//	vector<int> my_vector(n);

	//	uniform_int_distribution<int> value_distribution(0, (n - 1) / 2);
	//	generate(my_vector.begin(), my_vector.end(), [&]() { return value_distribution(gen); });
	//	//std::iota(my_vector.begin(), my_vector.end(), 0); // iota는 0, 1, 2, ... , n-1 까지 순서대로 채워주는 함수
	//	//std::random_shuffle(my_vector.begin(), my_vector.end()); // 일부만 순서를 바꿔줌 (shuffle은 딜러가 카드 섞는 것 생각하면 됩니다.)
	//	//std::reverse(my_vector.begin(), my_vector.end());

	//	vector<int> backup = my_vector;

	//	int k = int(my_vector.size() / 2) + 1;
	//	int expected_value = SelectionBySorting(my_vector, k);
	//	int selected_value = RandomizedSelect(my_vector, 0, my_vector.size() - 1, k);

	//	// Print(my_vector, 0, my_vector.size() - 1);
	//	// cout << expected_value << " " << selected_value << endl;

	//	if (expected_value != selected_value)
	//	{
	//		cout << "Incorrect. " << expected_value << " " << selected_value << endl;
	//		Print(backup);
	//		Print(my_vector);
	//		exit(-1);
	//	}
	//}

	// cout << "Good!" << endl;
}
