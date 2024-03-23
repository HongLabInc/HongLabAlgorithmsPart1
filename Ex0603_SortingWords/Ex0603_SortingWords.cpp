#include <iostream>
#include <vector>
#include <random>
#include <limits>
#include <fstream>
#include <chrono>
#include <numeric>
#include <iomanip>
#include <string>
using namespace std;

template<typename T>
void Print(vector<T>& arr)
{
	for (auto& a : arr)
		cout << a << " ";
	cout << endl;
}

void CountingSort(vector<string>& arr, int k, int d)
{
	// vector<string> temp = arr; // 복사
	// std::fill(arr.begin(), arr.end(), "   "); // 디버깅 편의

	// TODO:
}

void RadixSort(vector<string>& arr)
{
	// TODO:
}

int main()
{
	// CLRS 8.3-1
	vector<string> arr = { "COW", "DOG", "SEA", "RUG",
		"ROW", "MOB", "BOX", "TAB", "BAR", "EAR", "TAR",
		"DIG", "BIG", "TEA", "NOW", "FOX" };

	Print(arr);

	RadixSort(arr);

	Print(arr);

	return 0;
}