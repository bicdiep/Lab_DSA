#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct NODE {
	int key;
	NODE* p_next;
};

struct Stack {
	NODE* top;
};

Stack* initializeStack();
void push(Stack& s, int key);
int pop(Stack& s);
int size(Stack s);
bool isEmpty(Stack s);

Stack* initializeStack() {
	Stack* s = new Stack;
	s->top = nullptr;
	return s;
}

void push(Stack& s, int key) {
	NODE* newNode = new NODE;
	newNode->key = key;
	newNode->p_next = s.top;
	s.top = newNode;
}

int pop(Stack& s) {
	if (s.top == nullptr) {
		return -1;
	}
	NODE* temp = s.top;
	int first = temp->key;
	s.top = s.top->p_next;
	delete temp;
	return first;
}

int size(Stack s) {
	int cnt = 0;
	NODE* temp = s.top;
	while (temp != nullptr) {
		cnt++;
		temp = temp->p_next;
	}
	return cnt;
}

bool isEmpty(Stack s) {
	return s.top == nullptr;
}

void display(Stack& s, ofstream& fout) {
	if (isEmpty(s)) {
		fout << "EMPTY" << endl;
		return;
	}

	const int MAX = 100;
	int a[MAX];
	int n = 0;

	NODE* temp = s.top;
	while (temp != nullptr && n < MAX) {
		a[n++] = temp->key;
		temp = temp->p_next;
	}

	for (int i = n - 1; i >= 0; i--) {
		fout << a[i] << " ";
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
	Stack* s = initializeStack();
	string command;
	while (fin >> command) {
		if (command == "init") {
			if (s != nullptr) {
				delete s;
			}
			s = initializeStack();
			fout << "EMPTY" << endl;
		}
		else if (command == "push") {
			int value;
			fin >> value;
			push(*s, value);
			display(*s, fout);
		}
		else if (command == "pop") {
			pop(*s);
			display(*s, fout);
		}
	}
	if (s != nullptr) {
		delete s;
	}
}


int main() {
	process("input.txt", "output.txt");
	cout << "Done." << endl;
	return 0;
}