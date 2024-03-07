#include <vector>
#include <iostream>
#include <iomanip>
#include <numeric> // std::iota

using namespace std;

void Print(vector<int>& arr, int lo, int hi)
{
	// setfill(), setw()는 줄맞춤에 사용

	for (int i = 0; i < lo; i++)
		cout << "   ";
	for (int i = lo; i <= hi; i++)
		cout << setfill(' ') << setw(3) << arr[i];
	cout << endl;
}

bool CheckSorted(vector<int>& a)
{
	for (int i = 0; i < a.size() - 1; i++)
	{
		if (a[i] > a[i + 1])
			return false;
	}

	return true;
}

// Sedgewick p. 278
class BottomupMerge
{
public:
	void Sort(vector<int>& a)
	{
		aux.resize(a.size());

		int N = a.size();
		// TODO: 재귀호출 사용하지 않습니다.
	}

private:
	void Merge(vector<int>& a, int lo, int mid, int hi)
	{
		// TODO: Top-down과 동일
	}

	vector<int> aux; // 추가 메모리
};

int main()
{
	vector<int> my_vector(16);
	std::iota(my_vector.begin(), my_vector.end(), 0);
	std::reverse(my_vector.begin(), my_vector.end());

	cout << "        ";
	Print(my_vector, 0, my_vector.size() - 1);

	BottomupMerge merge;
	merge.Sort(my_vector);

	cout << "        ";
	Print(my_vector, 0, my_vector.size() - 1);
}
