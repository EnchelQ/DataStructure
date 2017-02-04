#include<iostream>
using namespace std;
template <typename T>
//是将SearchTreeNode数据成员定义成public,还是定义成private,同时将SearchTree定义为友元类？
class SearchTreeNode
{
public:
	T key;
	SearchTreeNode<T> *left, *right, *p;
	SearchTreeNode(T k) :key(k), left(NULL), right(NULL), p(NULL){}
};
template<typename T>
class SearchTree
{
public:
	SearchTree() : root(NULL){}
	void deleNode(){ _deleNode(root); }
	SearchTreeNode<T>* search(T k){ _search(root, k); }
	SearchTreeNode<T>* iterSearch(T k);
	SearchTreeNode<T>* getMinimum(){ _getMinimum(root); }
	SearchTreeNode<T>* getMaximum() {_getMinimum(root); }
	SearchTreeNode<T> * successor(SearchTreeNode<T> *x);
	SearchTreeNode<T> * predecessor(SearchTreeNode<T> *x);
	bool insertNode(SearchTreeNode<T> *i);
	void deleteNode(SearchTreeNode<T> *i);
	void preOrder(){ _preOrder(root); }
	void inOrder(){ _inOrder(root); }
	void postOrder(){ _postOrder(root); }

private:
	SearchTreeNode<T> *root;//将成员作为默认参数是使用要求静态成员。
	SearchTreeNode<T> *_search(SearchTreeNode<T> *x, T k);
	void _preOrder(SearchTreeNode<T> *x);
	void _inOrder(SearchTreeNode<T> *x);
	void _postOrder(SearchTreeNode<T> *x);
	SearchTreeNode<T>* _getMinimum(SearchTreeNode<T> *x);
	SearchTreeNode<T>* _getMaximum(SearchTreeNode<T> *x);
	void transPlant(SearchTreeNode<T> *x,SearchTreeNode<T> *z);
	void _deleNode(SearchTreeNode<T> *x)
	{
		if (!x)
			return;
		//无孩子节点，则放心删除。
		_deleNode(x->left);
		_deleNode(x->right);
		delete x;
	}
};

template<typename T>
SearchTreeNode<T>* SearchTree<T>::_search(SearchTreeNode<T> *x,T k)
{
	if (x.key == NULL || x.key == k)
		return x;
	if (x.key < k)
		return _search(x->right,k);
	else
		return _search(x->left,k);
}
template<typename T>
SearchTreeNode<T> * SearchTree<T>::iterSearch(T k)
{
	SearchTree<T> *x = root;
	while (x != NULL && x.key != k)
	{
		if (x->key < k)
			x = x->right;
		else
			x = x->left;
	}
	return x;
}
template<typename T>
SearchTreeNode<T> *SearchTree<T>::_getMinimum(SearchTreeNode<T> *x)
{
	if (x == NULL)
		return x;
	while (x->left != NULL)
		x = x->left;
	return x;
}
template<typename T>
SearchTreeNode<T> *SearchTree<T>::_getMaximum(SearchTreeNode<T> *x)
{
	if (x == NULL)
		return x;
	while (x->right != NULL)
		x = x->right;
	return x;
}
template<typename T>
SearchTreeNode<T>* SearchTree<T>::successor(SearchTreeNode<T> * x)
{
	if (x->right != NULL)
		return _getMinimum(x->right);
	SearchTreeNode<T>* y = x->p;
	while (y != NULL && x == y->right)//如果x是y的右孩子的话，以y为根的子树中就不存在待求节点的后继节点。
	{
		x = y;
		y = y->p;
	}
	return y;
}
//如果x->key为最小值，则前驱为空，否则前驱一定存在。
template<typename T>
SearchTreeNode<T>* SearchTree<T>::predecessor(SearchTreeNode<T> * x)
{
	if (x->left != NULL)
		return _getMaximum(x->left);
	SearchTreeNode<T> *y = x->p;
	while (y!=NULL && x==y->left)//如果x是y的左孩子的话，以y为根的子树中就不存在待求节点的前继节点。
	{
		x = y;
		y = y->p;
	}
	return y;
}
//若搜索树中存在与i的关键字相等的节点，则插入失败，否则插入成功。
//暂时能写出迭代版本，至于递归版本，有待考量。
template<typename T>
bool SearchTree<T>::insertNode(SearchTreeNode<T> *i)
{
	SearchTreeNode<T> *x = root;
	if (!x)
	{
		root = i;
		return true;
	}
	T k = i->key;
	SearchTreeNode<T> *y = NULL;
	while (x != NULL)
	{
		y = x;
		if (x->key < k)
			x = x->right;
		else if (x->key>k)
			x = x->left;
		else
			return false;
	}
	if (y->key > k)
		y->left = i;
	else
		y->right = i;
	i->p = y;
	return true;
}

//遍历的递归版本。
//遍历的迭代版本需要借助队列来实现。
template<typename T>
void SearchTree<T>::_preOrder(SearchTreeNode<T> *x)
{
	if（!x）
		return;
	std::cout << x->key << std::endl;//遍历过程中的功能函数。
	_preOrder(x->left);
	_preOrder(x->right);
}
template<typename T>
void SearchTree<T>::_inOrder(SearchTreeNode<T> *x)
{
	if(!x)
		return;
	_inOrder(x->left);
	std::cout << x->key << std::endl;//遍历过程中的功能函数。
	_inOrder(x->right);
}
template<typename T>
void SearchTree<T>::_postOrder(SearchTreeNode<T> *x)
{
	if（!x）
		return;
	_postOrder(x->left);
	_postOrder(x->right);
	std::cout << x->key << std::endl;//遍历过程中的功能函数。
}
//transPlant的功能为：z替换x成为x父母的孩子节点。,z可是为NULL.
template<typename T>
void SearchTree<T>::transPlant(SearchTreeNode<T> *x, SearchTreeNode<T> *z)
{
	if (x->p == NULL)
		root = z;
	else if (x->p->left == x)
		x->p->left = z;
	else
		x->p->right = z;
	if (z != NULL)
		z->p = x->p;
}
//删除节点是将节点从搜索树中删除。
//删除节点分三种情况：1.x无孩子节点；2.x只有一个孩子节点；3.x有两个孩子节点。1，2case直接用孩子节点替换，而3需要先寻找后继。
//为了编写程序，仔细分析这三种情况，可以得到3种操作情况：1.将左孩子节点或右孩子节点直接替换x；2.先寻找其后继节点，若后继节点为其右孩子，直接替换，然后补充后继节点的左孩子；3.若后继节点不是其子女，则经历两次替换。
//point:后继节点无左孩子。
template<typename T>
void SearchTree<T>::deleteNode(SearchTreeNode<T> *x)
{
	if (x->left == NULL)
		transPlant(x, x->right);
	else if (x->right == NULL)
		transPlant(x, x->right);
	else
	{
		SearchTreeNode<T> *y = _getMinimum(x->right);
		if (y->p!=x)
		{
			transPlant(y,y->right);
			y->right = x->right;
			y->right->p = y;
		}
		transPlant(x, y);
		y->left = x->left;
		y->left->p = y;
	}
}