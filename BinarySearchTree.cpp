#include <iostream>
#include <memory>

using namespace::std;

using ElemType = int;

class Node
{
public:	
	Node() = default;
	
	ElemType key;
	Node* left = nullptr;
	Node* right = nullptr;
	Node* parent = nullptr;
};

class BinarySearchTree
{
	friend void Transplant(BinarySearchTree* T, Node* u, Node *v);
public:
	BinarySearchTree() = default;
	
	void InorderTreeWalk(Node *x);
	void PreorderTreeWalk(Node *x);
	void PostorderTreeWalk(Node *x);
	Node* Search(Node *x, ElemType k);
	Node* Minimun(Node *x);
	Node* Maximum(Node *x);
	Node* Successor(Node *x);
	Node* Predecessor(Node *x);
	void Insert(BinarySearchTree *T, ElemType z);
	void Delete(BinarySearchTree *T, Node *z);

	Node* root = nullptr;
};

int main()
{
	BinarySearchTree T;
	
	ElemType input;
	
	while (cin >> input)
	{
		T.Insert(&T, input);
	}
	
	T.InorderTreeWalk(T.root);
	cout << endl;
	
	T.PreorderTreeWalk(T.root);
	cout << endl;
	
	
	T.Delete(&T, T.root);
	
	T.InorderTreeWalk(T.root);
	cout << endl;
	
	T.PreorderTreeWalk(T.root);
	cout << endl;
	
	return 0;
}


void BinarySearchTree::InorderTreeWalk(Node *x)
{
	if (x != nullptr)
	{
		InorderTreeWalk(x->left);
		cout << x->key << " ";
		InorderTreeWalk(x->right);
	}
}

void BinarySearchTree::PreorderTreeWalk(Node *x)
{
	if (x != nullptr)
	{
		cout << x->key << " ";
		PreorderTreeWalk(x->left);
		PreorderTreeWalk(x->right);
	}
}

void BinarySearchTree::PostorderTreeWalk(Node *x)
{
	if (x != nullptr)
	{
		PostorderTreeWalk(x->left);
		PostorderTreeWalk(x->right);
		cout << x->key << " ";
	}
}

Node* BinarySearchTree::Search(Node *x, ElemType k)
{
	if (x == nullptr || k == x->key)
	{
		return x;
	}
	
	if (k < x->key)
	{
		Search(x->left, k);
	}
	else
	{
		Search(x->right, k);
	}
}

Node* BinarySearchTree::Minimun(Node *x)
{
	for (; x->left != nullptr; x = x->left)
	{
		
	}
	
	return x;
}

Node* BinarySearchTree::Maximum(Node *x)
{
	for (; x->right != nullptr; x = x->right)
	{
		
	}
	
	return x;
}

Node* BinarySearchTree::Successor(Node *x)
{
	if (x->right != nullptr)
	{
		return Minimun(x->right);
	}
	
	auto y = x->parent;
	
	for (; y != nullptr && x == y->right; x = y, y = y->parent)
	{
		
	}
	
	return y;
}

Node* BinarySearchTree::Predecessor(Node *x)
{
	if (x->left != nullptr)
	{
		return Maximum(x->left);
	}
	
	auto y = x->parent;
	
	for (; y != nullptr && x == y->left; x = y, y = y->parent)
	{
		
	}
	
	return y;
}

void BinarySearchTree::Insert(BinarySearchTree *T, ElemType z)
{
	auto node = new Node;
	Node* y = nullptr;
	auto x = root;
	
	while (x != nullptr)
	{
		y = x;
		
		if (z < x->key)
		{
			x = x->left;
		}
		else
		{
			x = x->right;
		}
	}
	
	node->parent = y;
	node->key = z;
	
	if (y == nullptr)
	{
		root = node;
	}
	else if (z < y->key)
	{
		y->left = node;
	}
	else
	{
		y->right = node;
	}
	
}

void BinarySearchTree::Delete(BinarySearchTree *T, Node *z)
{
	if (z->left == nullptr)
	{
		Transplant(T, z, z->right);
	}
	else if (z->right == nullptr)
	{
		Transplant(T, z, z->left);
	}
	else
	{
		auto y = Minimun(z->right);
		
		if (y->parent != z)
		{
			Transplant(T, y, y->right);
			
			y->right = z->right;
			y->right->parent = y;
		}
		
		Transplant(T, z, y);
		y->left = z->left;
		y->left->parent = y;
	}
	
	delete z;
	
}

void Transplant(BinarySearchTree *T, Node *u, Node *v)
{
	if (u->parent == nullptr)
	{
		T->root = v;
	}
	else if (u == u->parent->left)
	{
		u->parent->left = v;
	}
	else
	{
		u->parent->right = v;
	}
	
	if (v != nullptr)
	{
		v->parent = u->parent;
	}
}
