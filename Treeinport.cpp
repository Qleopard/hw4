#include <iostream>
#include <cmath>
#include <chrono>
#include <vector>
#include <list>
#include <algorithm>

using namespace std;

enum RBTColor { Black, Red };

template<class KeyType>
struct  RBTNode
{
	KeyType key;
	RBTColor color;
	RBTNode<KeyType> * left;
	RBTNode<KeyType> * right;
	RBTNode<KeyType> * parent;
	RBTNode(KeyType k, RBTColor c, RBTNode* p, RBTNode*l, RBTNode*r) :
		key(k), color(c), parent(p), left(l), right(r) { };
};

template<class T>
class  RBTree
{
public:
	RBTree();
	~RBTree();

	void insert(T key);    // Вставляем узел, key - это значение ключа, внешний интерфейс
	RBTNode<T>* search(T key);	//Алгоритм поиска в дереве
	


private:
	void leftRotate(RBTNode<T>* &root, RBTNode<T>* x);// Балансировка левой ветви
	void rightRotate(RBTNode<T>* &root, RBTNode<T>* y);// и правой ветви

	void insert(RBTNode<T>* &root, RBTNode<T>* node);// Вставляем узел, внутренний интерфейс
	void InsertFixUp(RBTNode<T>* &root, RBTNode<T>* node);
	void destroy(RBTNode<T>* &node);


	RBTNode<T>* search(RBTNode<T>*node, T key) const;
private:
	RBTNode<T>*root;
};

template<class T>		//Конструктор
RBTree<T>::RBTree() :root(NULL) {
	root = nullptr;
}
template<class T>		// Деструктор
RBTree<T>::~RBTree() {
	destroy(root);
}
template<class T>		//Левая балансировка
void RBTree<T>::leftRotate(RBTNode<T>* &root, RBTNode<T>* x) {
	RBTNode<T>*y = x->right;
	x->right = y->left;
	if (y->left != NULL)
		y->left->parent = x;

	y->parent = x->parent;
	if (x->parent == NULL)
		root = y;
	else {
		if (x == x->parent->left)
			x->parent->left = y;
		else
			x->parent->right = y;
	}
	y->left = x;
	x->parent = y;
};
template<class T>		//Правая балансировка
void RBTree<T>::rightRotate(RBTNode<T>*&root, RBTNode<T>*y) {
	RBTNode<T>*x = y->left;
	y->left = x->right;
	if (x->right != NULL)
		x->right->parent = y;

	x->parent = y->parent;
	if (y->parent == NULL)
		root = x;
	else {
		if  (y == y->parent->right)
			y->parent->right = x;
		else
			y->parent->left = x;
	}
	x->right = y;
	y->parent = x;
};
template<class T>		// Вставка
void RBTree<T>::insert(T key)
{
	RBTNode<T>*z = new RBTNode<T>(key, Red, NULL, NULL, NULL);
	insert(root, z);
};
template<class T>
void RBTree<T>::insert(RBTNode<T>* &root, RBTNode<T>* node)
{
	RBTNode<T> *x = root;
	RBTNode<T> *y = NULL;
	while (x != NULL)
	{
		y = x;
		if (node->key > x->key)
			x = x->right;
		else
			x = x->left;
	}
	node->parent = y;
	if(y!=NULL)
	{
		if (node->key > y->key)
			y->right = node;
		else
			y->left = node;
	}
	else 
		root = node;
	node->color = Red;
	InsertFixUp(root, node);
};
template<class T>
void RBTree<T>::InsertFixUp(RBTNode<T>* &root, RBTNode<T>* node)
{
	RBTNode<T>*parent;
	parent = node->parent;
	while (node != RBTree::root  && parent->color == Red)
	{
		RBTNode<T>*gparent = parent->parent;
		if (gparent->left == parent)
		{
			RBTNode<T>*uncle = gparent->right;
			if (uncle != NULL && uncle->color == Red)
			{
				parent->color = Black;
				uncle->color = Black;
				gparent->color = Red;
				node = gparent;
				parent = node->parent;
			}
			else
			{
				if (parent->right == node)
				{
					leftRotate(root, parent);
					swap(node, parent);
				}
				rightRotate(root, gparent);
				gparent->color = Red;
				parent->color = Black;
				break;
			}
		}
		else
		{
			RBTNode<T>*uncle = gparent->left;
			if (uncle != NULL && uncle->color == Red)
			{
				gparent->color = Red;
				parent->color = Black;
				uncle->color = Black;

				node = gparent;
				parent = node->parent;
			}
			else
			{
				if (parent->left == node)
				{
					rightRotate(root, parent);
					swap(parent, node);
				}
				leftRotate(root, gparent);
				parent->color = Black;
				gparent->color = Red;
				break;
			}
		}
	}
	root->color = Black;
}
template<class T>
// Разрушение системы
void RBTree<T>::destroy(RBTNode<T>* &node) 
{
	if (node == NULL)
		return;
	destroy(node->left);
	destroy(node->right);
	delete node;
	node = nullptr;
}

template<class T>
RBTNode<T>* RBTree<T>::search(T key) 
{
	return search(root, key);
}
template<class T>
RBTNode<T>* RBTree<T>::search(RBTNode<T>*node, T key) const
{
	if (node == NULL || node->key == key)
		return node;
	else
		if (key > node->key)
			return search(node->right, key);
		else
			return search(node->left, key);
}


template<typename Cont> Cont filling(Cont cont) { //Заполнитель контейнеров (точно работает на последовательных контейнерах)
    srand(time(0));
    while (cont.size() != 500) {
        int x = rand() % 10000 + 1;
        bool found = std::find(cont.begin(), cont.end(), x) != cont.end();
        if (!found) {
            cont.push_back(x);
        }
    }
    return cont;
}

void search(std::vector<std::list<int>> codes, int fi, int x) {
    int j = -1;
    for(int i = 0; i < x; i++) {
        for(int num : codes[i]) {
            if (num == fi) {
                j = i;
            }
        }
    }
    if (j == -1) {
        std::cout << "Not found";
    }  
    else {
        std::cout << "Index: " << j;
    }
}

int main()  
{
    std::vector<int> nums;
    nums.reserve(500);

    auto start4 = std::chrono::high_resolution_clock::now();
    nums = filling(nums); //Создаём и заполняем вектор
    auto end4 = std::chrono::high_resolution_clock::now();
    auto time4 = std::chrono::duration_cast<std::chrono::milliseconds>(end4 - start4);

    RBTree<int> tree;

    auto start3 = std::chrono::high_resolution_clock::now();
	for (auto num : nums)
		tree.insert(num);
    auto end3 = std::chrono::high_resolution_clock::now();
    auto time3 = std::chrono::duration_cast<std::chrono::milliseconds>(end3 - start3);
    
    int y = 642;

    auto start1 = std::chrono::high_resolution_clock::now();
    tree.search(y);
    auto end1 = std::chrono::high_resolution_clock::now();
    auto time1 = std::chrono::duration_cast<std::chrono::milliseconds>(end1 - start1);

    auto start2 = std::chrono::high_resolution_clock::now();
    bool found = std::find(nums.begin(), nums.end(), y) != nums.end();
    auto end2 = std::chrono::high_resolution_clock::now();
    auto time2 = std::chrono::duration_cast<std::chrono::milliseconds>(end2 - start2); 

    if (time1 < time2) {
        std::cout << "Search in a tree is faster. Result: " << time1.count() << " milliseconds. " << "Vector showed the result: " << \
        time2.count() << " milliseconds.\n"; 
    }
    else if (time1 > time2) {
        std::cout << "Search in a vector is faster. Result: " << time2.count() << " milliseconds. " << "Tree showed the result: " << \
        time2.count() << " milliseconds.\n";
    }
    else {
        std::cout << "Both have similar time in search: " << time2.count() << " milliseconds.\n";
    }

    if (time3 < time4) {
        std::cout << "Insert in a tree is faster. Result: " << time3.count() << " milliseconds. " << "Vector showed the result: " << \
        time4.count() << " milliseconds."; 
    }
    else if (time3 > time4) {
        std::cout << "Insert in a vector is faster. Result: " << time4.count() << " milliseconds. " << "Tree showed the result: " << \
        time3.count() << " milliseconds.";
    }
    else {
        std::cout << "Both have similar time in insert: " << time4.count() << " milliseconds.";
    }   
    return 0;
}