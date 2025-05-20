#include <iostream>
#include <vector>
#include <queue>
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

vector<int> NLR(NODE* pRoot) {

	if (!pRoot) return {};

	vector<int> nlr;

	nlr.push_back(pRoot->key);
	vector<int> left = NLR(pRoot->p_left);
	vector<int> right = NLR(pRoot->p_right);

	nlr.insert(nlr.end(), left.begin(), left.end());
	nlr.insert(nlr.end(), right.begin(), right.end());

	return nlr;
}

vector<int> LNR(NODE* pRoot) {

	if (!pRoot) return {};

	vector<int> lnr;
	vector<int> left = LNR(pRoot->p_left);
	lnr.insert(lnr.end(), left.begin(), left.end());

	lnr.push_back(pRoot->key);

	vector<int> right = LNR(pRoot->p_right);
	lnr.insert(lnr.end(), right.begin(), right.end());

	return lnr;
}

vector<int> LRN(NODE* pRoot) {

	if (!pRoot) return {};

	vector<int> lrn;
	vector<int> left = LRN(pRoot->p_left);
	lrn.insert(lrn.end(), left.begin(), left.end());

	vector<int> right = LRN(pRoot->p_right);
	lrn.insert(lrn.end(), right.begin(), right.end());

	lrn.push_back(pRoot->key);

	return lrn;
}

vector<vector<int>> LevelOrder(NODE* pRoot) {

	if (!pRoot) return {};

	vector<vector<int>> res;
	queue<NODE*> q;
	q.push(pRoot);

	while (!q.empty()) {
		vector<int> level;
		int len = q.size();
		for (int i = 0; i < len; i++) {
			NODE* curr = q.front();
			q.pop();
			level.push_back(curr->key);

			if (curr->p_left) q.push(curr->p_left);
			if (curr->p_right) q.push(curr->p_right);
		}
		res.push_back(level);
	}
	return res;
}

int countNode(NODE* pRoot) {
	if (!pRoot) return 0;
	return 1 + countNode(pRoot->p_left) + countNode(pRoot->p_right);
}

int sumNode(NODE* pRoot) {
	if (!pRoot) return 0;
	return pRoot->key + sumNode(pRoot->p_left) + sumNode(pRoot->p_right);
}

int height(NODE* p) {
	
	if (p == nullptr) return -1;
	
	int left = height(p->p_left);
	int right = height(p->p_right);
	
	if (left >= right) {
		return 1 + left;
	}
	else return 1 + right;
}


int heightNode(NODE* pRoot, int value) {
	
	if (pRoot == nullptr) return -1;
	if (pRoot->key == value) return height(pRoot);
	
	int left = heightNode(pRoot->p_left, value);
	if (left != -1) return left;
	
	return heightNode(pRoot->p_right, value);
}

int Level(NODE* pRoot, NODE* p) {
	
	if (!pRoot) return -1;
	if (pRoot == p) return 0;

	int left = Level(pRoot->p_left, p);
	if (left != -1) return left + 1;

	int right = Level(pRoot->p_right, p);
	if (right != -1) return right + 1;

	return -1;
}

int countLeaf(NODE* pRoot) {
	if (pRoot == nullptr) return 0;
	if (pRoot->p_left == nullptr && pRoot->p_right == nullptr) return 1;
	return countLeaf(pRoot->p_left) + countLeaf(pRoot->p_right);
}


