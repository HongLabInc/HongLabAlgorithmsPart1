#include <iostream>
#include <vector>
#include <random>
#include <limits>
#include <fstream>
#include <chrono>
#include <numeric> // std::iota

using namespace std;
using namespace std::chrono;

void Print(vector<int>& arr)
{
	for (int i = 0; i < arr.size(); i++)
		cout << arr[i] << " ";
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

void InsertionSort1(vector<int>& a)
{
	int N = a.size();
	for (int i = 1; i < N; i++)
		for (int j = i; j > 0 && a[j - 1] > a[j]; j--)
			swap(a[j - 1], a[j]);
}

void InsertionSort2(vector<int>& a)
{
	int N = a.size();
	int i;
	for (i = 1; i < N; i++)
	{
		int key = a[i];
		int j = i;
		for (; j > 0 && a[j - 1] > key; j--)
			a[j] = a[j - 1];
		a[j] = key;
	}
}

struct Sample {
	int n;
	double duration;
};

int main()
{
	random_device rd;
	mt19937 gen(rd());

	vector<Sample> samples;
	samples.reserve(5000);

	for (int n = 1; n <= 5000; n += 1)
	{
		vector<int> my_vector(n);

		for (int r = 0; r < n; r += max(1, n / 100))
		{
			// 0 이상 n-1 이하의 정수가 균일한 확률로 생성되는 난수 (uniform distribution)
			//uniform_int_distribution<int> value_distribution(0, n - 1);
			//generate(my_vector.begin(), my_vector.end(), [&]() { return value_distribution(gen); });

			std::iota(my_vector.begin(), my_vector.end(), 0); // iota는 0, 1, 2, ... , n-1 까지 순서대로 채워주는 함수
			std::reverse(my_vector.begin(), my_vector.end()); // 최악의 경우를 만들기 위해 순서를 뒤집어주기
			std::random_shuffle(my_vector.begin(), my_vector.begin() + r); // 일부만 순서를 바꿔줌 (shuffle은 딜러가 카드 섞는 것 생각하면 됩니다.)

			// Print(my_vector);

			// Random case
			auto start = high_resolution_clock::now();

			InsertionSort2(my_vector);

			auto stop = high_resolution_clock::now();
			auto dur = double(duration_cast<nanoseconds>(stop - start).count()) / 1000000000.0;

			if (!CheckSorted(my_vector))
			{
				cout << "Failed." << endl;
				exit(-1);
			}

			samples.push_back({ n, dur });

			if (n % 1000 == 0 && r == 0)
			{
				cout << n << " : " << dur << endl;
			}
		}
	}

	ofstream ofile("result_insertion2_worstshuffle.txt");
	for (auto& s : samples)
		ofile << s.n << ", " << s.duration << endl;

	ofile.close();

	cout << "\a" << endl;
}
