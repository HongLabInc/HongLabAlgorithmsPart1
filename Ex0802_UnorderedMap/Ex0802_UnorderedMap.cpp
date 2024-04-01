#include <iostream>
#include <vector>
#include <random>
#include <limits>
#include <fstream>
#include <chrono>
#include <numeric>
#include <iomanip>
#include <list>
#include <map> // map
#include <unordered_map> // unordered_map 
using namespace std;

template<typename T_KEY, typename T_VALUE>
void Print(const unordered_map<T_KEY, T_VALUE>& map)
{
	for (int i = 0; i < map.bucket_count(); i++) // 버킷에 대해 반복
	{
		auto b = map.bucket(i);
		cout << i << ": ";
		for (auto i = map.begin(b); i != map.end(b); i++) // 버킷에 저장된 것들 출력
			cout << "(" << i->first << ", " << i->second << ")->";
		cout << endl;
	}
}

int main()
{
	// 기본적인 사용 방법
	{
		//unordered_map<string, int> map;
		map<string, int> map;

		// 새로운 키-값 추가
		map.insert({ "Orange", 1 });
		map.insert({ "Apple", 10 });
		map.insert({ "Strawberry", 7 });

		// 새로운 키-값 추가(배열처럼 인덱싱 연산자 사용)
		map["Kiwi"] = 5;   // map.insert({"Kiwi", 5});

		// 값 변경
		map.find("Kiwi")->second += 1; // 이터레이터 사용
		map["Kiwi"] += 1; // 인덱싱(더 편리)

		cout << map.count("Apple") << endl; // 1 아니면 0 반환 (중복허용X)

		// map은 내부적으로 정렬된 순서 유지 (unordered_map과 출력 순서가 다를 수 있음)
		for (auto i : map)
			cout << i.first << " " << i.second << endl;
	}

	// 난수 생성기
	random_device rd;
	mt19937 g(rd());
	uniform_int_distribution<int>  dist(1, 365);

	// 모인 인원 수
	int num_people = 23;

	std::unordered_map<int, int> map(num_people); // 버킷 수를 스스로 조절

	int num_try = 1000;
	int all_samebirthday_count = 0;

	for (int t = 0; t < num_try; t++)
	{
		int samebirthday_count = 0;

		for (int i = 0; i < num_people; i++)
		{
			int birthday = dist(g);

			// TODO:
		}

		if (samebirthday_count > 0)
			all_samebirthday_count += 1;

		//Print(map); // 디버깅용
		//exit(0);

		map.clear();
	}

	std::cout << (all_samebirthday_count * 100.0 / num_try) << " % " << endl;

	return 0;
}
