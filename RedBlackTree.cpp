#include <iostream>
#include <memory>

using namespace::std;

using ElemType = int;
enum color{RED, BLACK};

class Node
{
public:	
	Node() = default;
	
	ElemType key;
	Node *left = nullptr;
	Node *right = nullptr;
	Node *parent = nullptr;
	color color;
};

class RedBlackTree
{
	friend void LeftRotate(RedBlackTree *T, Node *x);
	friend void RightRotate(RedBlackTree *T, Node *y);
public:
	RedBlackTree() = default;
	
	Node* Minimun(Node *x);
	Node* Maximum(Node *x);
	void Insert(ElemType z);
	void InsertFixup(Node *x);
	void Transplant(Node *u, Node *v);
	void Delete(Node *z);
	void DeleteFixup(Node *x);
	
	Node *root = nullptr;
	const Node* const nil = nullptr;
};


int main()
{
	
}

void LeftRotate(RedBlackTree *T, Node *x)
{
	auto y = x->right;
	x->right = y->left;
	
	if (y->left != T->nil)
	{
		y->left->parent = x;
	}
	
	y->parent = x->parent;
	
	if (x->parent == T->nil)
	{
		T->root = y;
	}
	else if (x == x->parent->left)
	{
		x->parent->left = y;
	}
	else
	{
		x->parent->right = y;
	}
	
	y->left = x;
	x->parent = y;
}

void RightRotate(RedBlackTree *T, Node *y)
{
	auto x = y->left;
	y->left = x->right;
	
	if (x->right != T->nil)
	{
		x->right->parent = y;
	}
	
	x->parent = y->parent;
	
	if (y->parent == T->nil)
	{
		T->root = x;
	}
	else if (y == y->parent->left)
	{
		y->parent->left = x;
	}
	else
	{
		y->parent->right = x;
	}
	
	x->right = y;
	y->parent = x;
}

Node* RedBlackTree::Minimun(Node *x)
{
	for (; x->left != nullptr; x = x->left)
	{
		
	}
	
	return x;
}

Node* RedBlackTree::Maximum(Node *x)
{
	for (; x->right != nullptr; x = x->right)
	{
		
	}
	
	return x;
}

void RedBlackTree::Insert(ElemType z)
{
	auto node = new Node;
	auto y = const_cast<Node*> (nil);
	auto x = root;
	
	for (; x != nil;)
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
	
	if (y == nil)
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
	
	node->left = const_cast<Node*> (nil);
	node->right = const_cast<Node*> (nil);
	node->color = RED;
	
	InsertFixup(node);
}

void RedBlackTree::InsertFixup(Node *x)
{
	for (; x->parent->color == RED;)
	{
		if (x->parent == x->parent->parent->left)
		{
			auto y = x->parent->parent->right;
			
			if (y->color == RED)
			{
				x->parent->color = BLACK;
				y->color = BLACK;
				x->parent->parent->color = RED;
				x = x->parent->parent;
			}
			else if (x == x->parent->right)
			{
				x = x->parent;
				
				LeftRotate(this, x);
			}
			else
			{
				x->parent->color = BLACK;
				x->parent->parent->color = RED;
				
				RightRotate(this, x->parent->parent);
			}
		}
		else
		{
			auto y = x->parent->parent->left;
			
			if (y->color == RED)
			{
				x->parent->color = BLACK;
				y->color = BLACK;
				x->parent->parent->color = RED;
				x = x->parent->parent;
			}
			else if (x == x->parent->left)
			{
				x = x->parent;
				
				RightRotate(this, x);
			}
			else
			{
				x->parent->color = BLACK;
				x->parent->parent->color = RED;
				
				LeftRotate(this, x->parent->parent);
			}
		}
	}
	
	root->color = BLACK;
}

void RedBlackTree::Transplant(Node *u, Node *v)
{
	if (u->parent == nil)
	{
		root = v;
	}
	else if (u == u->parent->left)
	{
		u->parent->left = v;
	}
	else
	{
		u->parent->right = v;
	}
	
	v->parent = u->parent;
}

void RedBlackTree::Delete(Node *z)
{
	auto y = z;
	auto y_original_color = y->color;
	Node* x = nullptr;
	
	if (z->left == nil)
	{
		x = z->right;
		
		Transplant(z, z->right);
	}
	else if (z->right == nil)
	{
		x = z->left;
		
		Transplant(z, z->left);
	}
	else
	{
		y = Minimun(z->right);
		x = y->right;
		
		if (y->parent == z)
		{
			x->parent = y;
		}
		else
		{
			Transplant(y, y->right);
			y->right = z->right;
			y->right->parent = y;
		}
		
		Transplant(z, y);
		y->left = z->left;
		y->left->parent = y;
		y->color = z->color;
	}
	
	if (y_original_color == BLACK)
	{
		DeleteFixup(x);
	}
	
	delete z;
}

void RedBlackTree::DeleteFixup(Node *x)
{
	for (; x != root && x->color == BLACK;)
	{
		if (x == x->parent->left)
		{
			auto w = x->parent->right;
			
			if (w->color == RED)
			{
				w->color = BLACK;
				x->parent->color = RED;
				LeftRotate(this, x->parent);
				w = x->parent->right;
			}
			
			if (w->left->color == BLACK && w->right->color == BLACK)
			{
				w->color = RED;
				x = x->parent;
			}
			else if (w->right->color == BLACK)
			{
				w->left->color = BLACK;
				w->color = RED;
				RightRotate(this, w);
				w = w->parent->right;
			}
			else
			{
				w->color = w->parent->color;
				x->parent->color = BLACK;
				w->right->color = BLACK;
				LeftRotate(this, x->parent);
				x = root;
			}
		}
		else
		{
			auto w = x->parent->left;
			
			if (w->color == RED)
			{
				w->color = BLACK;
				x->parent->color = RED;
				RightRotate(this, x->parent);
				w = x->parent->left;
			}
			
			if (w->left->color == BLACK && w->right->color == BLACK)
			{
				w->color = RED;
				x = x->parent;
			}
			else if (w->left->color == BLACK)
			{
				w->right->color = BLACK;
				w->color = RED;
				LeftRotate(this, w);
				w = w->parent->left;
			}
			else
			{
				w->color = w->parent->color;
				x->parent->color = BLACK;
				w->left->color = BLACK;
				RightRotate(this, x->parent);
				x = root;
			}
		}
	}
	
	x->color = BLACK;
}
