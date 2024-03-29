#include <iostream>
#include <string>
#include <assert.h>
#include <iomanip>
#include <vector>

using namespace std;

// Sedgewick 교재의 자바 구현 예시
// https://algs4.cs.princeton.edu/33balanced/RedBlackBST.java.html

using Key = string; // 구현 단순화(템플릿 미사용)
using Value = int;  // 구현 단순화(템플릿 미사용)

enum Color { kRed, kBlack };
// C-style로 구현한다면
// #define kRed true
// #define kBlack false

class Node
{
public:
	Key key;
	Value val;
	Node* left;
	Node* right;
	int size; // Number of nodes in this subtree
	Color color;

	Node(Key key, Value val, int N, Color color)
		: key(key), val(val), size(N), color(color),
		left(nullptr), right(nullptr) // 널 포인터로 초기화
	{}
};

class RedBlackBST
{
public:
	Node* root = nullptr;

	bool IsEmpty() { return root == nullptr; }

	bool IsRed(Node* x)
	{
		if (x == nullptr) return false; // 널노드는 블랙
		return x->color == Color::kRed;
	}

	int Size() { return Size(root); }
	int Size(Node* x)
	{
		if (x == nullptr) return 0;
		else return x->size;
	}

	// 이진트리 복습
	Value Search(Key key) { return Search(root, key); }
	Value Search(Node* x, Key key)
	{
		if (x == nullptr) return -1; // 편의상 못 찾았을 경우 -1 반환

		// if (key < x->key) TODO:
		// else if (key > x->key) TODO:
		// else return x->val;
		return -1; // TODO: 삭제
	}

	// 이진트리 복습
	bool Contains(Key key) { return Contains(root, key); }
	bool Contains(Node* x, Key key)
	{
		if (x == nullptr) return false;

		// if (key < x->key) TODO:
		// else if (key > x->key) TODO:
		// else return true;
		return false; // 삭제
	}

	// 키(key)가 가장 작은 노드 찾기 (이진트리 복습)
	Key Min() {
		assert(!IsEmpty());
		return Min(root)->key;
	}
	Node* Min(Node* x)
	{
		// return TODO:
		return nullptr; // 삭제
	}

	// 키(key)가 가장 큰 노드 찾기 (이진트리 복습)
	Key Max() {
		assert(!IsEmpty());
		return Max(root)->key;
	}
	Node* Max(Node* x)
	{
		// return TODO:
		return nullptr; // 삭제
	}

	// AVL과 비슷
	Node* RotateLeft(Node* h)
	{
		Node* x = h->right; // 회전 후에 부모 자리로 올라갈 노드
		// h->right = TODO
		// x->left = TODO
		x->color = h->color;
		h->color = Color::kRed; // 일단 레드로 설정 후 나중에 수정
		x->size = h->size;
		h->size = 1 + Size(h->left) + Size(h->right);
		return x;
	}

	// AVL과 비슷
	Node* RotateRight(Node* h)
	{
		Node* x = h->left; // 회전 후에 부모 자리로 올라갈 노드
		// h->right = TODO
		// x->left = TODO
		x->color = h->color;
		h->color = Color::kRed; // 일단 레드로 설정 후 나중에 수정
		x->size = h->size;
		h->size = 1 + Size(h->left) + Size(h->right);
		return x;
	}

	void FlipColor(Color& c)
	{
		if (c == Color::kRed)
			c = Color::kBlack;
		else
			c = Color::kRed;
	}

	void FlipColors(Node* h)
	{
		FlipColor(h->color);
		FlipColor(h->left->color);
		FlipColor(h->right->color);
	}

	// 균형을 맞춰주는 함수
	Node* Balance(Node* h) 	// restore red-black tree invariant
	{
		assert(h != nullptr);

		// 아래 힌트
		// 1. IsRed()에서 널노드는 블랙으로 간주(false 반환)
		// 2. else-if가 아니라 if  

		// 오른쪽이 레드이고 왼쪽은 레드가 아니면?
		// if (TODO) h = TODO

		// 왼쪽과 왼쪽의 왼쪽이 둘 다 레드이면?
		// if (TODO) h = TODO

		// 왼쪽, 오른쪽이 둘 다 레드이면? 
		// if (TODO) TODO

		h->size = Size(h->left) + Size(h->right) + 1;

		return h;
	}

	void Insert(Key key, Value val)
	{
		root = Insert(root, key, val);
		root->color = Color::kBlack; // 루트는 블랙
	}

	Node* Insert(Node* h, Key key, Value val)
	{
		// 새 노드는 일단 레드
		if (h == nullptr)
			return new Node(key, val, 1, Color::kRed);

		// key를 비교해서 재귀호출 (키가 같으면 val 업데이트)
		// 이진트리와 동일
		if (key < h->key) h->left = Insert(h->left, key, val);
		else if (key > h->key) h->right = Insert(h->right, key, val);
		else h->val = val;

		// Insert()는 재귀호출됩니다.
		// 여기서 반환되면 트리를 거슬러 올라가면서 
		// 추가로 자식들의 색을 보고 수정합니다.

		return Balance(h); // <- Balance() 구현
	}

	// 삭제할 때 사용됨
	Node* MoveRedLeft(Node* h)
	{
		// TODO:
		return nullptr;
	}

	// 삭제할 때 사용됨
	Node* MoveRedRight(Node* h)
	{
		assert(h != null);
		assert(IsRed(h) && !IsRed(h->right) && !IsRed(h->right->left));

		// TODO:
		return nullptr;
	}

	// 가장 작은 키(key)를 찾아서 삭제
	void DeleteMin()
	{
		assert(!IsEmpty());

		// TODO:
	}

	Node* DeleteMin(Node* h)
	{
		// TODO:
		return nullptr;
	}

	// 가장 큰 키(key)를 찾아서 삭제
	void DeleteMax()
	{
		// TODO:
	}

	Node* DeleteMax(Node* h)
	{
		// TODO:
		return nullptr;
	}

	// 임의의 키(key)를 찾아서 삭제
	void Delete(Key key)
	{
		// TODO:
	}

	Node* Delete(Node* h, Key key)
	{
		assert(Contains(key) == true);

		// TODO:

		return Balance(h);
	}

	// 루트만 있을 경우 높이 0
	// https://en.wikipedia.org/wiki/Tree_(data_structure)
	int Height() { return Height(root); }
	int Height(Node* node)
	{
		if (!node) return -1;
		return 1 + std::max(Height(node->left), Height(node->right));
	}

	// 디버깅 편의 도구
	vector<string> screen;
	void PrintLine(int x, string s, string& line) {
		for (const auto c : s) line[x++] = c;
		//cout << line << endl;
	}
	void Print2D() {
		if (!root) cout << "Empty" << endl;
		else {
			int h = Height() + 1, w = 4 * int(pow(2, h - 1));
			screen.clear();
			screen.resize(h * 2, string(w, ' '));
			Print2D(root, w / 2 - 2, 0, h - 1);
			//cout << "DEBUG" << endl;
			for (const auto& l : screen) cout << l << endl;
		}
	}
	void Print2D(Node* n, int x, int level, int s)
	{
		//cout << x << " " << level << " " << s << endl;
		PrintLine(x, (IsRed(n) ? "*" : " ") + n->key, screen[2 * level]);
		x -= int(pow(2, s));
		if (n->left) {
			PrintLine(x, "  /", screen[2 * level + 1]);
			Print2D(n->left, x, level + 1, s - 1);
		}
		if (n->right)
		{
			PrintLine(x + 2 * int(pow(2, s)), "\\", screen[2 * level + 1]);
			Print2D(n->right, x + 2 * int(pow(2, s)), level + 1, s - 1);
		}
	}
};

int main()
{
	{
		RedBlackBST bst;

		for (char c : string("SEARCHXMPL"))
		{
			cout << "Insert: " << string(1, c) << endl;
			bst.Insert(string(1, c), int(c));
			bst.Print2D();

		}
	}

	//{
	//	RedBlackBST bst;

	//	for (char c : string("ACEHLMPRSX"))
	//	{
	//		cout << "Insert: " << string(1, c) << endl;
	//		bst.Insert(string(1, c), int(c));
	//		bst.Print2D();
	//	}
	//}

	return 0;
}

