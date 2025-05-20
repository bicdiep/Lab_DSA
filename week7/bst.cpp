#include <iostream>
#include <vector>
using namespace std;

struct NODE {
	int key;
	NODE* p_left;
	NODE* p_right;
};

NODE* createNode(int data) {
	NODE* newNode = new NODE();
	if (!newNode) {
		cout << "Not enough memory.\n";
		return nullptr;
	}
	newNode->key = data;
	newNode->p_left = nullptr;
	newNode->p_right = nullptr;
	return newNode;
}

NODE* Search(NODE* pRoot, int x) {
	if (!pRoot) return nullptr;
	if (pRoot->key == x) return pRoot;
	if (x < pRoot->key) return Search(pRoot->p_left, x);
	else return Search(pRoot->p_right, x);
}

void Insert(NODE*& pRoot, int x) {
	if (!pRoot) {
		pRoot = createNode(x);
		return;
	}

	if (x < pRoot->key) Insert(pRoot->p_left, x);
	else Insert(pRoot->p_right, x);
}

void Remove(NODE*& pRoot, int x) {
	if (!pRoot) return;
	if (x < pRoot->key) Remove(pRoot->p_left, x);
	else if (x > pRoot->key) Remove(pRoot->p_right, x);
	else {
		if (!pRoot->p_left) {
			NODE* tmp = pRoot;
			pRoot = pRoot->p_right;
			delete tmp;
		}
		else if (!pRoot->p_right) {
			NODE* tmp = pRoot;
			pRoot = pRoot->p_left;
			delete tmp;
		}
		else {
			NODE* minNode = pRoot->p_right;
			while (minNode->p_left) minNode = minNode->p_left;
			pRoot->key = minNode->key;
			Remove(pRoot->p_right, minNode->key);
		}
	}
}

NODE* createTree(int a[], int n) {
	NODE* pRoot = nullptr;
	for (int i = 0; i < n; i++) {
		Insert(pRoot, a[i]);
	}
	return pRoot;
}

void removeTree(NODE*& pRoot) {
	if (!pRoot) return;
	removeTree(pRoot->p_left);
	removeTree(pRoot->p_right);
	delete pRoot;
	pRoot = nullptr;
}

int Height(NODE* pRoot) {
	if (!pRoot) return -1;
	int left = Height(pRoot->p_left);
	int right = Height(pRoot->p_right);
	if (left >= right) {
		return 1 + left;
	}
	else return 1 + right;
}

int countLess(NODE* pRoot, int x) {
	if (!pRoot) return 0;
	if (pRoot->key >= x) return countLess(pRoot->p_left, x);
	return 1 + countLess(pRoot->p_left, x) + countLess(pRoot->p_right, x);
}

int countGreater(NODE* pRoot, int x) {
	if (!pRoot) return 0;
	if (pRoot->key <= x) return countGreater(pRoot->p_right, x);
	return 1 + countGreater(pRoot->p_left, x) + countGreater(pRoot->p_right, x);
}

bool isBST(NODE* pRoot) {
	if (!pRoot) return true;

	if (pRoot->p_left) {
		NODE* tmp = pRoot->p_left;
		while (tmp->p_right) tmp = tmp->p_right;
		if (tmp->key >= pRoot->key) return false;
	}

	if (pRoot->p_right) {
		NODE* tmp = pRoot->p_right;
		while (tmp->p_left) tmp = tmp->p_left;
		if (tmp->key <= pRoot->key) return false;
	}
	return isBST(pRoot->p_left) && isBST(pRoot->p_right);

}

bool isFullBST(NODE* pRoot) {
	if (!pRoot) return true;
	if (!pRoot->p_left && !pRoot->p_right) return true;
	if (pRoot->p_left && pRoot->p_right) return isFullBST(pRoot->p_left) && isFullBST(pRoot->p_right);
	return false;
}

