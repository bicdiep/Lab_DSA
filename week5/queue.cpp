#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct NODE {
	int key;
	NODE* p_next;
};

struct Queue {
	NODE* head;
	NODE* tail;
};

Queue* initializeQueue() {
	Queue* q = new Queue;
	q->head = q->tail = nullptr;
	return q;
}

void enqueue(Queue& q, int key) {
	NODE* newNode = new NODE;
	newNode->key = key;
	newNode->p_next = nullptr;

	if (q.tail == nullptr) {
		q.head = q.tail = newNode;
	}
	else {
		q.tail->p_next = newNode;
		q.tail = newNode;
	}
}

int dequeue(Queue& q) {
	if (q.head == nullptr) {
		return -1;
	}
	NODE* temp = q.head;
	int value = temp->key;
	q.head = q.head->p_next;

	if (q.head == nullptr) q.tail = nullptr;
	delete temp;
	return value;
}

int size(Queue q) {
	int cnt = 0;
	NODE* temp = q.head;
	while (temp != nullptr) {
		cnt++;
		temp = temp->p_next;
	}
	return cnt;
}

bool isEmpty(Queue q) {
	return q.head == nullptr;
}

void display(Queue& q, ofstream& fout) {
	if (isEmpty(q)) {
		fout << "EMPTY" << endl;
		return;
	}

	NODE* temp = q.head;
	while (temp != nullptr) {
		fout << temp->key << " ";
		temp = temp->p_next;
	}
	fout << endl;
}

void process(const string& ip, const string& op) {
	ifstream fin(ip);
	ofstream fout(op);

	if (!fin.is_open() || !fout.is_open()) {
		cout << "cannot open file" << endl;
		return;
	}

	Queue* q = initializeQueue();
	string command;

	while (fin >> command) {
		if (command == "init") {
			if (q != nullptr) delete q;
			q = initializeQueue();
			fout << "EMPTY" << endl;
		}
		else if (command == "enqueue") {
			int value;
			fin >> value;
			enqueue(*q, value);
			display(*q, fout);
		}
		else if (command == "dequeue") {
			if (isEmpty(*q)) fout << "EMPTY" << endl;
			else {
				dequeue(*q);
				display(*q, fout);
			}
		}
	}
	if (q != nullptr) delete q;
}
int main() {
	process("input.txt", "output.txt");
	cout << "Done." << endl;
	return 0;
}