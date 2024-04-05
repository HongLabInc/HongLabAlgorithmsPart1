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

int SelectionBySorting(vector<int> arr, int k) // arr은 사본, 정답 확인용
{
	std::sort(arr.begin(), arr.end());
	return arr[k - 1];
}

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

// CLRS p. 184
int Partition(vector<int>& arr, int lo, int hi)
{
	int x = arr[hi]; // 마지막 값을 피벗으로 사용
	int i = lo - 1;
	for (int j = lo; j < hi; j++)
	{
		if (arr[j] <= x)
		{
			i += 1;
			swap(arr[i], arr[j]);
		}

		//cout << "i = " << i << ", j = " << j << endl;
		//Print(arr);
	}

	swap(arr[i + 1], arr[hi]);

	return i + 1; // 피벗이 이동한 위치 반환
}

int g_level = -1; // 경우에 따라 최대 몇 레벨까지 내려가는지 확인하는 용도

// CLRS와 변수이름이 다릅니다.
// CLRS는 1-based 인덱스입니다.
// 매개변수 k는 1번째, 2번째, ..., k번째를 의미합니다. 0으로 시작하는 인덱스와 구분해야 합니다.
int RandomizedSelect(vector<int>& arr, int lo, int hi, int k)
{
	g_level++; // 확인용

	cout << "level = " << g_level << ", n = " << hi - lo + 1 << ", lo = " << lo << ", hi = " << hi << ", k= " << k << endl;
	Print(arr, lo, hi);

	if (lo == hi) return arr[lo]; // 하나만 남았을 경우

	// 난수사용하는 경우와 아닌 경우 비교해보세요.
	//int random = lo + rand() % (hi - lo + 1);
	//참고: uniform_int_distribution<int> vd(lo, hi)도 사용 가능
	//swap(arr[random], arr[hi]);

	int index = Partition(arr, lo, hi); // pivot index

	//if (index - lo == k - 1) TODO;
	//else if (k - 1 < index - lo) TODO;
	//else TODO;

	return -1; // 임시구현
}

int main()
{
	srand(1); // 랜덤 피벗을 사용할 때는 숫자를 바꿔가면서 테스트해보세요.

	//vector<int> my_vector = { 6, 19, 4, 12, 14, 9, 15, 7, 8, 11, 3, 13, 2, 5, 10 };
	//vector<int> my_vector = { 4, 19, 4, 12, 2, 9, 15, 2, 8, 11, 3, 1, 2, 1, 10 };
	vector<int> my_vector = { 9, 8, 7, 6, 5, 4, 3, 2, 1, 0 };

	Print(my_vector, 0, my_vector.size() - 1);

	cout << RandomizedSelect(my_vector, 0, my_vector.size() - 1, std::ceil(my_vector.size() / 2.0)) << endl;
	// 주의: k는 k번째를 의미, 인덱스는 0부터 시작하기 때문에 인덱스로는 k - 1 자리

	return 0; // 아래 테스트 실행하려면 제거

	// 아래는 더 많은 경우에 대한 테스트
	random_device rd;
	mt19937 gen(rd());

	for (int n = 1; n <= 10000; n += 1)
	{
		vector<int> my_vector(n);

		uniform_int_distribution<int> value_distribution(0, (n - 1) / 2);
		generate(my_vector.begin(), my_vector.end(), [&]() { return value_distribution(gen); });
		//std::iota(my_vector.begin(), my_vector.end(), 0); // iota는 0, 1, 2, ... , n-1 까지 순서대로 채워주는 함수
		//std::random_shuffle(my_vector.begin(), my_vector.end()); // 일부만 순서를 바꿔줌 (shuffle은 딜러가 카드 섞는 것 생각하면 됩니다.)
		//std::reverse(my_vector.begin(), my_vector.end());

		vector<int> backup = my_vector;

		int k = int(my_vector.size() / 2) + 1;
		int expected_value = SelectionBySorting(my_vector, k);
		int selected_value = RandomizedSelect(my_vector, 0, my_vector.size() - 1, k);

		// Print(my_vector, 0, my_vector.size() - 1);
		// cout << expected_value << " " << selected_value << endl;

		if (expected_value != selected_value)
		{
			cout << "Incorrect. " << expected_value << " " << selected_value << endl;
			Print(backup, 0, backup.size() - 1);
			Print(my_vector, 0, backup.size() - 1);
			exit(-1);
		}
	}

	cout << "Good!" << endl;
}
