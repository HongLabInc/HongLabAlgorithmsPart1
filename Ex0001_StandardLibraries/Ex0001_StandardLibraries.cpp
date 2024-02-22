#include <string> // std::string
#include <vector> // std::vector
#include <list>   // std::list
#include <iostream>

using namespace std;

int main()
{
	// 자료구조에서는 여러가지 자료구조들을 만들어보는 프로그래밍 연습에 집중했습니다.
	// 여기에서부터는 자료구조는 표준라이브러리를 활용하고 
	// 대신에 조금 더 높은 차원에서 알고리듬에 집중하겠습니다.
	// 기본적인 사용방법들을 아래에 정리해두었으니까 쭉 훑어보세요.

	// 편리하게 사용할 수 있는 문자열 std::string
	// #include <string>
	{
		std::string my_string = "Hello, World"; // 위에서 using namespace를 선언했기 때문에 std:: 생략 가능
		// string my_string("Hello, World"); // 생성자로 초기값 지정

		cout << my_string << endl;

		// int i = my_string.size(); // 경고 발생: conversion from 'size_t' to 'int', possible loss of data
		// size_t는 부호 없는 정수입니다. x86에서는 32bit, x64에서는 64bit 입니다.
		// 여기서는 편의상 size_t 대신에 int를 사용하고 경고는 무시합니다.

		for (int i = 0; i < my_string.size(); i++) // size()는 글자 수
			cout << my_string[i]; // 배열처럼 인덱싱 가능
		cout << endl;

		for (int i = 0; i < my_string.size(); i++)
		{
			char c = my_string[i]; // 한 글자는 char 자료형
			cout << c;
		}
		cout << endl;

		// for-each 문법을 사용하면 편리합니다. my_string에서 한 글자씩 c에 들어갑니다.
		for (char c : my_string)
			cout << c;
		cout << endl;

		// 자료형 추론(type inference)
		// auto i = 123; // 명확한 자료형 대신에 auto를 사용하면 등호 오른쪽을 보고 자료형을 추론해서 결정해줍니다.
		// auto i = my_string.begin(); // 여기서 i는 이터레이터(std::string::iterator) 자료형입니다. 
		// std::string::iterator를 매번 타이핑하는 것은 번거롭고 가독성도 떨어지는데 auto를 사용하면 간결해집니다.

		// iterator 사용법 (내부적으로는 파이썬 추월코스에 나오는 이터레이터와 같은 원리입니다.)
		for (auto i = my_string.begin(); i != my_string.end(); i++)
		{
			char c = *i;
			cout << c;
		}
		cout << endl;
	}

	// 문자열의 일부(substring)만 가져오고 싶을 때 substr()
	{
		string temp("1234567890");
		int mid = 5; // 바꿔가면서 테스트 해보세요.
		string a = temp.substr(0, temp.size() - mid);
		string b = temp.substr(temp.size() - mid, mid);

		cout << a << " " << b << endl; // 12345 67890
	}

	// stoi 문자열을 정수로 변환할 때 사용
	{
		auto i = stoi(string("123")); // stoi("123") 가능
		cout << i * stoi("456") << endl; // 56088
	}

	// std::vector (동적 배열)
	{
		vector<int> my_vector = { 1, 2, 3, 4, 5 }; // 정수형 배열처럼 사용할 수 있습니다. 내부적으로 동적 메모리를 사용합니다.

		for (int i = 0; i < my_vector.size(); i++)
		{
			int a = my_vector[i];
			cout << a << " ";
		}
		cout << endl;

		for (int a : my_vector)
			cout << a << " ";
		cout << endl;

		for (int& a : my_vector) // <- int의 reference 사용
			a *= 10;

		for (int a : my_vector)
			cout << a << " "; // <- 변경된 값이 출력
		cout << endl;

		for (auto a : my_vector) // auto는 자동으로 자료형을 결정하기 때문에 편합니다. auto 위에 마우스를 갖다 대어보면 int로 나옵니다.
			cout << a << " ";
		cout << endl;

		my_vector.push_back(1000); // 맨 뒤에 값 추가
		for (auto a : my_vector)
			cout << a << " ";
		cout << endl;
	}

	// std::list (linked list)
	// #include <list>
	{
		list<double> my_list; // double 자료형들을 담을 수 있는 linked list
		my_list.push_back(1);
		my_list.push_back(2);
		my_list.push_front(0);

		for (auto v : my_list)
			cout << v << " ";
		cout << endl;
	}

	// 그 외에 stack, queue, priority_queue 등이 있는데 사용법은 비슷비슷하기 때문에 뒤에 나올때마다 안내해드리겠습니다.

	return 0;
}