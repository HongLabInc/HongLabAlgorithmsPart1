#include <vector>
#include <algorithm>
#include <string>
#include <iostream>
#include <iomanip>
using namespace std;

// LCS 문자열을 반환하는 함수
// 왼쪽부터 비교하는 구현 방식
string RecurLCSLeftFirst(const string& X, const string& Y, int i, int j)
{
	if (i == X.size() || j == Y.size())
		return string("");

	//if (X[i] == Y[j])
	//{
	//	return TODO;
	//}
	//else
	//{
	//	string s1 = TODO;
	//	string s2 = TODO;
	//	return s1.size() > s2.size() ? s1 : s2;
	//}

	return string(""); // TODO: 삭제
}

// 최대 길이만 반환하는 함수
// 오른쪽부터 비교하는 구현 방식
int RecurLengthLCS(const string& X, const string& Y, int m, int n)
{
	if (m == 0 || n == 0)
		return 0;

	//if (X[m - 1] == Y[n - 1])
	//{
	//	return TODO;
	//}
	//else
	//{
	//	return TODO;
	//}

	return 0; // TODO: 삭제
}

void PrintLCS(const vector<vector<char>>& prev, const string& X, int i, int j)
{
	if (i == 0 || j == 0)
		return;

	if (prev[i][j] == '\\') // 왼쪽 위로 올라가는 대각선 화살표를 위미
	{
		PrintLCS(prev, X, i - 1, j - 1);
		cout << X[i - 1]; // 주의: -1
	}
	else if (prev[i][j] == '|') // 위로 올라가는 화살표를 의미
	{
		PrintLCS(prev, X, i - 1, j);
	}
	else // '-'는 왼쪽으로 가는 화살표를 의미
	{
		PrintLCS(prev, X, i, j - 1);
	}
}

int BottomUpLCS(const string& X, const string& Y, int m, int n)
{
	vector<vector<int>> table(m + 1, vector<int>(n + 1, 0)); // LCS의 길이만 저장
	vector<vector<string>> lcs(m + 1, vector<string>(n + 1, "")); // LCS 문자열 저장

	vector<vector<char>> prev(m + 1, vector<char>(n + 1, ' '));
	// prev에는 화살표를 문자로 저장
	// PrintLCS() 참고

	for (int i = 1; i <= m; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			if (X[i - 1] == Y[j - 1]) // 주의: i - 1, j - 1
			{
				//table[i][j] = TODO;
				//prev[i][j] = '\\'; // [i-1][j-1] -> [i][j]라는 기록
				//lcs[i][j] = TODO;
			}
			else if (table[i - 1][j] >= table[i][j - 1])
			{
				//table[i][j] = TODO;
				//prev[i][j] = '|'; // [i-1][j] -> [i][j]라는 기록
				//lcs[i][j] = TODO;
			}
			else
			{
				//table[i][j] = TODO;
				//prev[i][j] = '-'; // [i][j - 1] -> [i][j]라는 기록
				//lcs[i][j] = TODO;
			}
		}
	}

	// 이하 표(tabulation) 확인용

	cout << table[m][n] << endl;
	for (int i = 1; i <= m; i++)
	{
		for (int j = 1; j <= n; j++)
			cout << left << setw(3) << table[i][j];
		cout << endl;
	}
	cout << endl;

	cout << lcs[m][n] << endl;
	for (int i = 1; i <= m; i++)
	{
		for (int j = 1; j <= n; j++)
			cout << setw(min(X.length(), Y.length())) << lcs[i][j];
		cout << endl;
	}
	cout << endl;

	PrintLCS(prev, X, m, n);
	cout << endl;

	for (int i = 1; i <= m; i++)
	{
		for (int j = 1; j <= n; j++)
			cout << setw(3) << prev[i][j];
		cout << endl;
	}
	cout << endl;

	return table[m][n];
}

int main()
{
	// CLRS 4th p.398 Fig 14.8 그림의 예제
	string X = "ABCBDAB";
	string Y = "BDCABA";

	// CLRS 4th p.393 Ch14.4 도입부 예시 (Recur 버전으로는 오래 걸려요)
	//string X = "ACCGGTCGAGTGCGCGGAAGCCGGCCGAA";
	//string Y = "GTCGTTCGGAATGCCGTTGCTCTGTAAA";
	// GTCGTCGGAAGCCGGCCGAA

	//위 예시의 일부
	//string X = "ACCGGTCGAGT";
	//string Y = "GTCGTTCGGAA";
	// CGTCGA
	//6

	cout << RecurLCSLeftFirst(X, Y, 0, 0) << endl;
	cout << RecurLengthLCS(X, Y, int(X.size()), int(Y.size())) << endl;
	cout << BottomUpLCS(X, Y, int(X.size()), int(Y.size())) << endl;

	return 0;
}
