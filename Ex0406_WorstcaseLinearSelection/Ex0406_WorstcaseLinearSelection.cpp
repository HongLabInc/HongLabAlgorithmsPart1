#include <iostream>
#include <vector>
#include <random>
#include <limits>
#include <fstream>
#include <chrono>
#include <numeric>
#include <iomanip>
using namespace std;

void Print(vector<int>& arr, int lo, int hi, string sep = "")
{
	cout << "Index: ";
	for (int i = 0; i < arr.size(); i++)
		cout << setfill(' ') << setw(3) << i;
	cout << endl;

	cout << "Value: ";
	for (int i = 0; i < arr.size(); i++) {

		if (lo <= i && i <= hi)
			cout << setfill(' ') << setw(3) << arr[i] << sep;
		else
			cout << "   ";
	}
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
	return i + 1;
}

void SelectionSortPass(vector<int>& arr, int lo, int hi, int stride = 1)
{
	for (int i = lo + stride; i <= hi; i += stride)
		if (arr[i] < arr[lo])
			swap(arr[i], arr[lo]);
}

void PrintGroups(vector<int>& arr, int lo, int hi)
{
	for (int j = lo; j <= lo + hi - 1; j++)
	{
		cout << "Group " << j - lo + 1 << " : ";
		for (int l = 0; l < 5; l++)
			cout << arr[j + l * hi] << " ";
		cout << endl;
	}
}

struct Pair
{
	int index;
	int value;
};

Pair Select(vector<int>& arr, int lo, int hi, int k)
{
	// TODO:

	return Pair{ -1, -1 };
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
	//vector<int> my_vector = { 6, 19, 4, 12, 14, 9, 15, 7, 8, 11, 3, 13, 2, 5, 10 };
	//vector<int> my_vector = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	//vector<int> my_vector = { 10, 9, 8, 7, 6, 5, 4, 3, 2, 1 };
	//vector<int> my_vector = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23 };

	vector<int> my_vector = { 11,  7, 14,  6, 20,  4,  0, 10, 23,  5,  8, 17,  9, 21, 12, 22, 19, 15,  3, 13, 18,  1,  2, 16 };
	cout << my_vector.size() << endl;
	cout << Select(my_vector, 0, my_vector.size() - 1, 13).value << endl;
	// 주의: k는 k번째를 의미, 인덱스 자리는 k - 1

	// 아래는 더 많은 경우에 대한 테스트

	//random_device rd;
	//mt19937 gen(rd());

	//vector<Sample> samples;
	//samples.reserve(5000);

	//for (int n = 1; n <= 10000; n += 1)
	//{
	//	vector<int> my_vector(n);

	//	uniform_int_distribution<int> value_distribution(0, (n - 1) / 2); // 중복 발생
	//	generate(my_vector.begin(), my_vector.end(), [&]() { return value_distribution(gen); });
	//	//std::iota(my_vector.begin(), my_vector.end(), 0); // iota는 0, 1, 2, ... , n-1 까지 순서대로 채워주는 함수
	//	//std::random_shuffle(my_vector.begin(), my_vector.end()); // 일부만 순서를 바꿔줌 (shuffle은 딜러가 카드 섞는 것 생각하면 됩니다.)
	//	//std::reverse(my_vector.begin(), my_vector.end());

	//	vector<int> backup = my_vector;

	//	int k = int(my_vector.size() / 2) + 1;
	//	int expected_value = SelectionBySorting(my_vector, k);
	//	int selected_value = Select(my_vector, 0, my_vector.size() - 1, k).value;

	//	// Print(my_vector, 0, my_vector.size() - 1);
	//	// cout << expected_value << " " << selected_value << endl;

	//	if (expected_value != selected_value)
	//	{
	//		cout << "Incorrect. " << expected_value << " " << selected_value << endl;

	//		Print(backup, 0, backup.size(), ",");

	//		Print(my_vector, 0, my_vector.size() - 1);
	//		exit(-1);
	//	}
	//}

	//cout << "Good!" << endl;
}