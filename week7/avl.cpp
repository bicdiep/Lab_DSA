#include <iostream>
#include <vector>
using namespace std;

struct NODE {
	int key;
	NODE* p_left;
	NODE* p_right;
	int height;
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
	newNode->height = 0;
	return newNode;
}

int getHeight(NODE* pRoot) {
	return pRoot ? pRoot->height : -1;
}

void updateHeight(NODE* pRoot) {
	if (pRoot) {
		int left = getHeight(pRoot->p_left);
		int right = getHeight(pRoot->p_right);

		if (left >= right) pRoot->height = left + 1;
		else pRoot->height = right + 1;
	}
}

void rotateLeft(NODE* &pRoot) {
	NODE* newRoot = pRoot->p_right;
	NODE* childRL = newRoot->p_left;
	newRoot->p_left = pRoot;
	pRoot->p_right = childRL;
	
	updateHeight(pRoot);
	updateHeight(newRoot);

	pRoot = newRoot;
}

void rotateRight(NODE*& pRoot) {
	NODE* newRoot = pRoot->p_left;
	NODE* childLR = newRoot->p_right;
	newRoot->p_right = pRoot;
	pRoot->p_left = childLR;

	
	updateHeight(pRoot);
	updateHeight(newRoot);

	pRoot = newRoot;
}

void balance(NODE*& pRoot) {
	updateHeight(pRoot);
	int balFactor = getHeight(pRoot->p_left) - getHeight(pRoot->p_right);

	if (balFactor > 1) {
		int ll = getHeight(pRoot->p_left->p_left);
		int lr = getHeight(pRoot->p_left->p_right);

		if (ll >= lr) rotateRight(pRoot);
		else {
			rotateLeft(pRoot->p_left);
			rotateRight(pRoot);
		}
	}
	else if (balFactor < -1) {
		int rr = getHeight(pRoot->p_right->p_right);
		int rl = getHeight(pRoot->p_right->p_left);
		
		if (rr >= rl) rotateLeft(pRoot);
		else {
			rotateRight(pRoot->p_right);
			rotateLeft(pRoot);
		}
	}
}

void Insert(NODE*& pRoot, int x) {
	if (!pRoot) {
		pRoot = createNode(x);
		return;
	}

	if (x < pRoot->key) Insert(pRoot->p_left, x);
	else if (x > pRoot->key) Insert(pRoot->p_right, x);
	else return;

	updateHeight(pRoot);
	balance(pRoot);

}

void Remove(NODE*& pRoot, int x) {
	if (!pRoot) return;

	if (x < pRoot->key) Remove(pRoot->p_left, x);
	else if (x > pRoot->key) Remove(pRoot->p_right, x);
	else {
		if (!pRoot->p_left || !pRoot->p_right) {
			NODE* tmp = pRoot->p_left ? pRoot->p_left : pRoot->p_right;
			delete pRoot;
			pRoot = tmp;
		}
		else {
			NODE* childRight = pRoot->p_right;
			while (childRight->p_left) {
				childRight = childRight->p_left;
			}

			pRoot->key = childRight->key;
			Remove(pRoot->p_right, childRight->key);
		}
	}

	if (pRoot) {
		updateHeight(pRoot);
		balance(pRoot);
	};
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

bool isAVL(NODE* pRoot) {
	if (!pRoot) return true;

	if (!isBST(pRoot)) return false;
	int left = getHeight(pRoot->p_left);
	int right = getHeight(pRoot->p_right);

	if (abs(left - right) > 1) return false;
	return isAVL(pRoot->p_left) && isAVL(pRoot->p_right);
}

