#include <vector>
#include <iostream>
#include <iomanip>
using namespace std;

void Print(vector<int>& arr, int lo, int hi, string sep = "")
{
	//cout << "Index: ";
	//for (int i = 0; i < arr.size(); i++)
	//	cout << setfill(' ') << setw(3) << i;
	//cout << endl;

	cout << "Value: ";
	for (int i = 0; i < arr.size(); i++) {

		if (lo <= i && i <= hi)
			cout << setfill(' ') << setw(3) << arr[i] << sep;
		else
			cout << "   ";
	}
	cout << endl;
}

int Partition(vector<int>& arr, int lo, int hi)
{
	cout << "Pivot = " << arr[hi] << endl;

	int x = arr[hi];
	int i = lo - 1;
	for (int j = lo; j < hi; j++)
		if (arr[j] <= x)
		{
			i += 1;
			swap(arr[i], arr[j]);
		}

	swap(arr[i + 1], arr[hi]);

	Print(arr, lo, hi);

	return i + 1; // 피벗이 이동한 위치 반환
}

int RandomizedPartition(vector<int>& arr, int lo, int hi)
{
	int random = lo + rand() % (hi - lo + 1);
	swap(arr[random], arr[hi]);
	return Partition(arr, lo, hi);
}

void RandomizedQuicksort(vector<int>& arr, int lo, int hi)
{
	Print(arr, lo, hi);

	// TODO:
}

int main()
{
	srand(2);

	vector<int> arr = { 9, 8, 7, 6, 5, 4, 3, 2, 1, 0 };

	RandomizedQuicksort(arr, 0, arr.size() - 1);

	Print(arr, 0, arr.size() - 1);

	return 0;
}
