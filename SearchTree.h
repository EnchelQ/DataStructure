#include<iostream>
using namespace std;
template <typename T>
//�ǽ�SearchTreeNode���ݳ�Ա�����public,���Ƕ����private,ͬʱ��SearchTree����Ϊ��Ԫ�ࣿ
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
	SearchTreeNode<T> *root;//����Ա��ΪĬ�ϲ�����ʹ��Ҫ��̬��Ա��
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
		//�޺��ӽڵ㣬�����ɾ����
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
	while (y != NULL && x == y->right)//���x��y���Һ��ӵĻ�����yΪ���������оͲ����ڴ���ڵ�ĺ�̽ڵ㡣
	{
		x = y;
		y = y->p;
	}
	return y;
}
//���x->keyΪ��Сֵ����ǰ��Ϊ�գ�����ǰ��һ�����ڡ�
template<typename T>
SearchTreeNode<T>* SearchTree<T>::predecessor(SearchTreeNode<T> * x)
{
	if (x->left != NULL)
		return _getMaximum(x->left);
	SearchTreeNode<T> *y = x->p;
	while (y!=NULL && x==y->left)//���x��y�����ӵĻ�����yΪ���������оͲ����ڴ���ڵ��ǰ�̽ڵ㡣
	{
		x = y;
		y = y->p;
	}
	return y;
}
//���������д�����i�Ĺؼ�����ȵĽڵ㣬�����ʧ�ܣ��������ɹ���
//��ʱ��д�������汾�����ڵݹ�汾���д�������
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

//�����ĵݹ�汾��
//�����ĵ����汾��Ҫ����������ʵ�֡�
template<typename T>
void SearchTree<T>::_preOrder(SearchTreeNode<T> *x)
{
	if��!x��
		return;
	std::cout << x->key << std::endl;//���������еĹ��ܺ�����
	_preOrder(x->left);
	_preOrder(x->right);
}
template<typename T>
void SearchTree<T>::_inOrder(SearchTreeNode<T> *x)
{
	if(!x)
		return;
	_inOrder(x->left);
	std::cout << x->key << std::endl;//���������еĹ��ܺ�����
	_inOrder(x->right);
}
template<typename T>
void SearchTree<T>::_postOrder(SearchTreeNode<T> *x)
{
	if��!x��
		return;
	_postOrder(x->left);
	_postOrder(x->right);
	std::cout << x->key << std::endl;//���������еĹ��ܺ�����
}
//transPlant�Ĺ���Ϊ��z�滻x��Ϊx��ĸ�ĺ��ӽڵ㡣,z����ΪNULL.
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
//ɾ���ڵ��ǽ��ڵ����������ɾ����
//ɾ���ڵ�����������1.x�޺��ӽڵ㣻2.xֻ��һ�����ӽڵ㣻3.x���������ӽڵ㡣1��2caseֱ���ú��ӽڵ��滻����3��Ҫ��Ѱ�Һ�̡�
//Ϊ�˱�д������ϸ������������������Եõ�3�ֲ��������1.�����ӽڵ���Һ��ӽڵ�ֱ���滻x��2.��Ѱ�����̽ڵ㣬����̽ڵ�Ϊ���Һ��ӣ�ֱ���滻��Ȼ�󲹳��̽ڵ�����ӣ�3.����̽ڵ㲻������Ů�����������滻��
//point:��̽ڵ������ӡ�
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