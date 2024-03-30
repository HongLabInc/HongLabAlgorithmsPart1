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
// #define RED true
// #define BLACK false

class Node
{
public:
	Key key;
	Value val;
	Node* left;
	Node* right;
	int size; // 서브트리 노드수, 여기서는 사용안함
	Color color;

	Node(Key key, Value val, int N, Color color)
		: key(key), val(val), size(N), color(color),
		left(nullptr), right(nullptr) // 널 포인터로 초기화
	{}

	// 자바로 구현할 때는 널포인터 대신에 
	// 가상의 널 오브젝트를 하나 만들어서 가리키도록 구현할 수 있습니다.
	// C++에서 굳이 그렇게 구현할 필요가 없기 때문에
	// 여기서는 자식이 없으면 널포인터(nullptr)를 대입해놓습니다.
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

	// 삭제할 때 사용됨 (실행 예시 설명 참고)
	Node* MoveRedLeft(Node* h)
	{
		cout << "MoveRedLeft() " << h->key << endl;

		FlipColors(h);

		// 오른쪽 자식의 왼쪽 자식이 레드라면 (오른쪽 자식이 3-노드라면)
		//if (...)
		//{
		//	// 그 중에서 가장 작은 것을 h의 왼쪽으로 옮김 
		//	// 삭제 후 남을 여분을 하나 가져오는 것
		//	// 왼쪽을 3/4-노드로 만들어서 쉽게 삭제하기 위함 
		//	TODO: 
		//	TODO:
		// 
		//	FlipColors(h);
		//}

		return h;
	}

	// 삭제할 때 사용됨 (MoveRedLeft와 좌우대칭)
	Node* MoveRedRight(Node* h)
	{
		cout << "MoveRedRight() " << h->key << endl;

		// TODO:

		return h;
	}

	// 가장 작은 키(key)를 찾아서 삭제
	void DeleteMin()
	{
		assert(!IsEmpty());

		// 루트가 가운데인 4-노드로 임시 변경
		if (!IsRed(root->left) && !IsRed(root->right))
			root->color = Color::kRed;

		root = DeleteMin(root);

		// 루트는 항상 블랙
		if (!IsEmpty())
			root->color = Color::kBlack;
	}

	Node* DeleteMin(Node* h)
	{
		cout << "DeleteMin() " << h->key << endl;

		// h가 가장 작은 노드라면 삭제하고 반환
		//if ( TODO )
		//{
		//	cout << "Delete node " << h->key << endl;
		//	delete h; // 자바에서는 가비지 컬렉터 사용
		//	return nullptr;
		//}

		// 왼쪽자식이 블랙이고, 왼쪽-왼쪽 자식도 블랙이면
		// 삭제하기 어렵기 때문에 MoveRedLeft()에서 3-노드로 변경
		//if ( TODO )
		//{
		//	TODO:
		// 
		//	Print2D(h);
		//}

		// 계속 찾아 내려감
		h->left = DeleteMin(h->left);

		return Balance(h);
	}

	// 가장 큰 키(key)를 찾아서 삭제 (DeleteMin과 대칭)
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
		// 삭제하려는 키를 가진 노드가 존재하는지 미리 확인
		if (!Contains(key)) return;

		if (!IsRed(root->left) && !IsRed(root->right))
			root->color = Color::kRed;

		root = Delete(root, key);

		if (!IsEmpty()) root->color = Color::kBlack;
	}

	Node* Delete(Node* h, Key key)
	{
		//if ( TODO ) // 왼쪽으로 찾아 내려가서 지우는 경우
		//{
		//	// 힌트: DeleteMin()과 비슷함

		//	if ( TODO )
		//		h = TODO

		//	h->left = TODO
		//}
		//else // 오른쪽으로 찾아 내려가거나 바로 삭제하는 경우
		//{
		//	// DeleteMax()와 비슷한 경우
		//	if ( TODO )
		//		h = TODO

		//	// 키가 일치하고 오른쪽 서브트리가 없으면 삭제
		//	// 왼쪽 서브트리에 대한 처리는 바로 위의 RotateRight()에 해줬음
		//	if ((TODO) && (TODO))
		//	{
		//		delete h; // 자바는 가비지 컬렉터 사용
		//		return nullptr;
		//	}

		//	if (!IsRed(h->right) && !IsRed(h->right->left))
		//		h = MoveRedRight(h);

		//	// 삭제하는 경우
		//	if (key == h->key)
		//	{
		//		// 오른쪽 서브트리에서 가장 작은 것을 h로 복사한 후에
		//		// DeleteMin()으로 그것을 삭제
		//      
		//		// TODO: Min() 사용, 4줄 정도 됩니다.
		//	}
		//	else {
		//		// 오른쪽으로 계속 찾아가기
		//		h->right = Delete(h->right, key);
		//	}
		//}

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
	void Print2D() { Print2D(root); }
	void Print2D(Node* root) {
		if (!root) cout << "Empty" << endl;
		else {
			int h = Height(root) + 1, w = 4 * int(pow(2, h - 1));
			screen.clear();
			screen.resize(h * 2, string(w, ' '));
			Print2D(root, w / 2 - 2, 0, h - 1);
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
	// SEARCHXMPL 순서로 추가
	{
		RedBlackBST bst;

		string keys = string("SEARCHXMPL");

		for (char c : keys)
		{
			cout << "Insert: " << string(1, c) << endl;
			bst.Insert(string(1, c), int(c));
			//bst.Print2D();

		}

		//// Search 테스트
		//for (char c : keys)
		//{
		//	cout << c << " " << int(c) << " " << bst.Search(string(1, c)) << endl;
		//}

		bst.Print2D();

		//for (char c : keys)
		//{
		//	cout << "Delete: " << string(1, c) << endl;
		//	bst.Delete(string(1, c));
		//	bst.Print2D();

		//}
		//return 0;

		//while (!bst.IsEmpty())
		//{
		//	cout << "DeleteMin: " << bst.Min() << endl;
		//	bst.DeleteMin();
		//	bst.Print2D();
		//}
		//cout << endl;

		//while (!bst.IsEmpty())
		//{
		//	cout << "DeleteMax: " << bst.Max() << endl;
		//	bst.DeleteMax();
		//	bst.Print2D();
		//}
		//cout << endl;
	}

	// ACEHLMPRSX 순서로 추가
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

