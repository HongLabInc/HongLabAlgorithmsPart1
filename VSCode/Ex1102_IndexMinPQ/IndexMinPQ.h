#pragma once

#include <cassert>
#include <iostream>
#include <iomanip>
#include <utility>
#include <vector>

// https://algs4.cs.princeton.edu/code/edu/princeton/cs/algs4/IndexMinPQ.java.html

template<typename Key>
class IndexMinPQ
{
public:
	IndexMinPQ(int cap)
	{
		capacity = cap;
		size = 0;
		keys.resize(capacity + 1);
		pq.resize(capacity + 1); // heap[0]은 비워둡니다.
		qp.resize(capacity + 1, -1); // -1로 초기화(아직 추가되지 않았다는 의미)
	}

	bool Empty()
	{
		return size == 0;
	}

	bool Contains(int i)
	{
		assert(i >= 0 && i < capacity);
		return qp[i] != -1;
	}

	int Size() { return size; }

	void Insert(int i, Key key)
	{
		assert(i >= 0 && i < capacity);
		assert(!Contains(i));

		size += 1;
		qp[i] = size;
		pq[size] = i;
		keys[i] = key;
		Swim(size); // pq[size]를 자기 위치로 올려보냄
	}

	int MinIndex()
	{
		return pq[1]; // 1번 인덱스 자리
	}

	Key MinKey()
	{
		assert(size > 0);
		return keys[pq[1]];
	}

	int DelMin()
	{
		assert(size != 0);

		int m = pq[1];
		Exch(1, size--);
		Sink(1);

		assert(m == pq[size + 1]);

		qp[m] = -1; // 삭제했다는 의미
		keys[m] = 0.0; // 삭제했다는 의미, 디버깅용
		pq[size + 1] = -1; // 삭제했다는 의미, 디버깅용

		return m;
	}

	Key keyOf(int i)
	{
		assert(i >= 0 && i < capacity);
		assert(Contains(i));

		return keys[i];
	}

	void ChangeKey(int i, Key key)
	{
		assert(i >= 0 && i < capacity);
		assert(Contains(i));

		keys[i] = key;
		Swim(qp[i]);
		Sink(qp[i]);
	}

	void DecreaseKey(int i, Key key)
	{
		assert(i >= 0 && i < capacity);
		assert(Contains(i));
		assert(key < keys[i]); // 새로운 키가 더 작아야 함

		keys[i] = key;
		Swim(qp[i]);
	}

	void IncreaseKey(int i, Key key)
	{
		assert(i >= 0 && i < capacity);
		assert(Contains(i));
		assert(key > keys[i]); // 새로운 키가 더 작아야 함

		keys[i] = key;
		Sink(qp[i]);
	}

	void Delete(int i)
	{
		assert(i >= 0 && i < capacity);
		assert(Contains(i));

		int index = qp[i];
		Exch(index, size--);
		Swim(index);
		Sink(index);
		keys[i] = 0.0; // 삭제됐다는 의미, 디버깅용
		qp[i] = -1; // 삭제됐다는 의미
	}

	void Exch(int i, int j)
	{
		int swap = pq[i];
		pq[i] = pq[j];
		pq[j] = swap;
		qp[pq[i]] = i;
		qp[pq[j]] = j;
	}

	bool Greater(int i, int j)
	{
		return keys[pq[i]] > keys[pq[j]];
	}

	void Swim(int k)
	{
		// TODO: 우선순위가 높은 것을 수영해서 수면위로 올라가듯 위로 올리는 과정
		// 힌트: Greater(), Exch() 사용
	}

	void Sink(int k)
	{
		// TODO: 우선순위가 낮은 것을 밑으로 가라앉히는 과정
		// 힌트: Greater(), Exch() 사용
	}

	void Print()
	{
		using namespace std;
		cout << "Index: ";
		for (int i = 1; i <= size; i++)
			cout << setw(5) << i;
		cout << endl;

		cout << "Key:   ";
		for (int i = 1; i <= size; i++)
			cout << setw(5) << keyOf(pq[i]);
		cout << endl;

		cout << "Value: ";
		for (int i = 1; i <= size; i++)
			cout << setw(5) << pq[i];
		cout << endl << endl;
	}

private:
	int size = 0;
	int capacity = 0;
	std::vector<int> pq; // 이진힙
	std::vector<int> qp; // qp[pq[i]] = pq[qp[i]] = i
	std::vector<Key> keys; // keys[i]가 index i의 우선순위
};

