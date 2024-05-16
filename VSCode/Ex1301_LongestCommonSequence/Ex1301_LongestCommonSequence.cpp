#include <vector>
#include <algorithm>
#include <string>
#include <iostream>
#include <iomanip>
using namespace std;

// X에서 첫 m글자, Y에서 첫 n글자에 대해 LCS를 찾는 함수
string RecurLCS(const string& X, const string& Y, int m, int n)
{
	if (m == 0 || n == 0)
		return string("");

	/*
	if (X[m - 1] == Y[n - 1])
	{
		return TODO:
	}
	else
	{
		string s1 = TODO:
		string s2 = TODO:

		return s1.size() >= s2.size() ? s1 : s2;
	}
	*/

	return string(""); // TODO: 불필요, 삭제
}

int RecurLengthLCS(const string& X, const string& Y, int m, int n)
{
	if (m == 0 || n == 0)
		return 0;

	/*
	if (X[m - 1] == Y[n - 1])
		return TODO
	else
		return max(TODO, TODO);
	*/

	return 0; // TODO: 불필요, 삭제
}

void PrintLCS(const vector<vector<char>>& prev, const string& X, int i, int j)
{
	if (i == 0 || j == 0)
		return;

	if (prev[i][j] == '\\')
	{
		PrintLCS(prev, X, i - 1, j - 1);
		cout << X[i - 1]; // 주의: -1
	}
	else if (prev[i][j] == '|')
	{
		PrintLCS(prev, X, i - 1, j);
	}
	else
	{
		PrintLCS(prev, X, i, j - 1);
	}
}

int BottomUpLCS(const string& X, const string& Y, int m, int n)
{
	// 주의: 문자열과 table의 인덱싱에 일관성이 없어서 헷갈릴 수 있습니다.
	//       table은 1-base 인덱싱, X와 Y는 0-base 인덱싱
	//       table[i][j]: X의 길이가 i이고 Y의 길이가 j인 경우를 의미
	//       table에서 1-base를 사용하는 이유는 i나 j가 0인 base case들도 포함시키기 위해서 입니다.

	// 문제풀이할때는 보통 table 채워서 최대 길이를 찾는 것이 목표입니다.
	// 추가적으로 prev와 lcs를 제공하는 이유는 이해를 돕기 위해서 입니다.
	vector<vector<int>> table(m + 1, vector<int>(n + 1, 0));
	vector<vector<char>> prev(m + 1, vector<char>(n + 1, ' '));

	vector<vector<string>> lcs(m + 1, vector<string>(n + 1, ""));
	// prev에는 강의 노트의 화살표를 문자로 저장, PrintLCS() 참고

	// 여기서 i, j는 X와 Y의 길이를 의미 (1-base)
	for (int i = 1; i <= m; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			/*
			if (X[i - 1] == Y[j - 1]) // 주의: i - 1, j - 1
			{
				table[i][j] = TODO;

				prev[i][j] = '\\'; // [i-1][j-1]에서 가져왔다는 의미
				lcs[i][j] = TODO;
			}
			else if (table[i - 1][j] >= table[i][j - 1])
			{
				table[i][j] = TODO;

				prev[i][j] = '|'; // [i-1][j]에서 가져왔다는 의미
				lcs[i][j] = TODO;
			}
			else
			{
				table[i][j] = TODO;

				prev[i][j] = '-'; // [i][j-1]에서 가져왔다는 의미
				lcs[i][j] = TODO;
			}
			*/
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

	return table[m][n]; // 결과
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

	//string X = "ACCGGTCGAGT";
	//string Y = "GTCGTTCGGAA";
	// CGTCGA
	//6

	cout << "RecurLCS()" << endl;
	cout << RecurLCS(X, Y, int(X.size()), int(Y.size())) << endl;
	cout << endl;

	cout << "RecurLengthLCS()" << endl;
	cout << RecurLengthLCS(X, Y, int(X.size()), int(Y.size())) << endl;
	cout << endl;

	cout << "BottomUpLCS()" << endl;
	cout << BottomUpLCS(X, Y, int(X.size()), int(Y.size())) << endl;
	cout << endl;

	return 0;
}
