#include <iostream>
#include <map>
#include <vector>

using namespace std;

struct Node
{
public:
	int value = 0;
	int memo = 0; // <- Memoization에 사용
	Node* left = nullptr;
	Node* right = nullptr;

	// 꼭 이진 트리가 아니라 싸이클이 없는 트리 구조면 다 가능합니다.
};

int RecurLIS(Node* root)
{
	if (root == nullptr)
		return 0;

	// Root 노드가 포함 되지 않는 경우: 자식들 포함 가능
	int case1 = RecurLIS(root->left) + RecurLIS(root->right);

	// Root 노드가 포함되는 경우는 하나 건너서 자식들의 자식들만 포함 가능합니다.
	int case2 = 1;
	if (root->left)
		case2 += RecurLIS(root->left->left) + RecurLIS(root->left->right);
	if (root->right)
		case2 += RecurLIS(root->right->left) + RecurLIS(root->right->right);

	// 두 가지 경우 중 큰 경우 반환
	return max(case1, case2);
}

int MemoLIS(Node* root)
{
	// TODO:

	return 0;
}

Node* MakeNode(int data)
{
	Node* temp = new Node();
	temp->value = data;
	temp->left = temp->right = nullptr;
	return temp;
}

int main()
{
	// 이진 트리 만들기
	Node* root = MakeNode(1);
	root->left = MakeNode(2);
	root->left->left = MakeNode(4);
	root->left->right = MakeNode(5);
	root->left->right->left = MakeNode(7);
	root->left->right->right = MakeNode(8);
	root->right = MakeNode(3);
	root->right->right = MakeNode(6);

	cout << RecurLIS(root) << endl;
	cout << MemoLIS(root) << endl;

	return 0;
}

// GeeksForGeeks 예제를 약간 변형하였습니다.
// https://www.geeksforgeeks.org/largest-independent-set-problem-using-dynamic-programming/
