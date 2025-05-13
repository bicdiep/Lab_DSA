#include <iostream>
#include <fstream>
#include <string>
using namespace std;

void equalLen(string& a, string& b) {
	while (a.length() < b.length()) {
		a = "0" + a;
	}
	while (b.length() < a.length()) {
		b = "0" + b;
	}
}

bool isSmaller(string a, string b) {
	equalLen(a, b);
	return a < b;
}

string addBigInt(string a, string b) {
	string sum;
	int carry = 0;
	equalLen(a, b);
	for (int i = a.length() - 1; i >= 0; i--) {
		int d = (a[i] - '0') + (b[i] - '0') + carry; //tinh tong cua tung hang + bien nho truoc do
		carry = d / 10; //bien nho bang tong tung hang chia 10
		sum = (char)(d % 10 + '0') + sum; //lay hang don vi cua tong tung hang roi dua vao dau chuoi tong
	}
	if (carry != 0) {
		sum = "1" + sum;
	}
	return sum;
}

string minusBigInt(string a, string b) {
	string diff;
	int carry = 0;
	equalLen(a, b);
	for (int i = a.length() - 1; i >= 0; i--) {
		int d = (a[i] - '0') - (b[i] - '0') - carry;
		if (d < 0) {
			carry = 1;
			d = 10 + d;
			diff = (char)(d + '0') + diff;
		}
		else {
			carry = 0;
			diff = (char)(d + '0') + diff;
		}
	}

	int j = 0;
	while (j < diff.length() && diff[j] == '0') {
		j++;
	}

	diff.erase(0, j);
	if (diff.empty()) diff = "0";
	return diff;
}

string calculateAdd(string a, string b) {
	bool signA = false, signB = false;

	if (a[0] == '-') {
		signA = true;
		a = a.substr(1);
	}

	if (b[0] == '-') {
		signB = true;
		b = b.substr(1);
	}

	if (!signA && !signB) {
		return addBigInt(a, b);
	}
	else if (signA && signB) {
		return "-" + addBigInt(a, b);
	}
	else if (signA && !signB) {
		if (isSmaller(a, b)) return minusBigInt(b, a);
		else return "-" + minusBigInt(a, b);
	}
	else {
		if (isSmaller(a, b)) return "-" + minusBigInt(b, a);
		else return minusBigInt(a, b);
	}
}

string calculateMinus(string a, string b) {
	bool signA = false, signB = false;

	if (a[0] == '-') {
		signA = true;
		a = a.substr(1);
	}

	if (b[0] == '-') {
		signB = true;
		b = b.substr(1);
	}

	if (!signA && !signB) {
		return minusBigInt(a, b);
	}
	else if (signA && signB) {
		if (isSmaller(a, b)) return minusBigInt(b, a);
		return "-" + minusBigInt(a,b);
	}
	else if (signA && !signB) {
		return "-" + addBigInt(a, b);
	}
	else {
		return addBigInt(a, b);
	}

}

//ham nhan mot so voi so nguyen lon
string multiply(string a, char b) {
	string res;
	int carry = 0;
	if (b == '0') return "0";
	for (int i = a.length() - 1; i >= 0; i--) {
		int d = (a[i] - '0') * (b - '0') + carry;
		carry = d / 10;
		res = (char)(d % 10 + '0') + res;
	}
	if (carry != 0) {
		res = (char)(carry + '0') + res;
	}
	return res;
}

string multiplyBigInt(string a, string b) {
	string product;

	bool sign = false;
	if (a[0] == '-') {
		sign = !sign;
		a = a.substr(1);
	}
	if (b[0] == '-') {
		sign = !sign;
		b = b.substr(1);
	}

	if (a == "0" || b == "0") return product = "0";
	int cnt = -1;
	for (int i = b.length() - 1; i >= 0; i--) {
		cnt++;
		string res1 = multiply(a, b[i]);
		res1 = res1 + string(cnt, '0');
		product = addBigInt(product, res1);
	}
	if (sign && product != "0") product = "-" + product;
	return product;
}

string divisionBigInt(string a, string b) {
	string quotient = "0";
	string cur = "0";

	bool sign = false;
	if (a[0] == '-') {
		sign = !sign;
		a = a.substr(1); 
	}
	if (b[0] == '-') {
		sign = !sign;
		b = b.substr(1);
	}
	if (b == "0") return "Error: Division by zero.\n";

	if (isSmaller(a, b)) return quotient;
	for (int i = 0; i < a.length(); i++) {
		cur = cur + a[i];

		if (isSmaller(cur, b)) {
			quotient = quotient + "0";
			continue;
		}

		int lo = 0, hi = 9, x = 0;
		while (lo <= hi) {
			int mid = (lo + hi) / 2;
			string prod = multiply(b, mid + '0');
			if (!isSmaller(cur, prod)) {
				x = mid;
				lo = mid + 1;
			}
			else {
				hi = mid - 1;
			}
		}
		quotient = quotient + (char)(x + '0');
		cur = minusBigInt(cur, multiply(b, x + '0'));

	}
	int j = 0;
	while (j < quotient.length() && quotient[j] == '0') {
		j++;
	}
	quotient.erase(0, j);
	if (quotient.empty()) quotient = "0";

	if (sign && quotient != "0") quotient = "-" + quotient;
	return quotient;	
}

bool isOperator(char c) {
	return c == '+' || c == '-' || c == '*' || c == '/';
}
int precedence(char o) {
	if (o == '+' || o == '-') return 1;
	if (o == '*' || o == '/') return 2;
	return 0;
}

const int MAX = 100;
string stack[MAX];
int top = -1;

bool isEmpty() {
	return top == -1;
}

bool isFull() {
	return top == MAX - 1;
}

void push(string a) {
	if (isFull()) {
		cout << "Stack overflow.\n";
		return;
	}
	stack[++top] = a;
}

string pop() {
	if (isEmpty()) {
		return "";
	}
	return stack[top--];
}

string peek() {
	if (isEmpty()) return "";
	return stack[top];
}

string infixToPostfix(string infix) {
	string postfix;
	for (int i = 0; i < infix.length(); i++) {
		char ch = infix[i];
		if (ch == ' ') continue;

		if ((ch >= '0' && ch <= '9') || (ch == '-' && (i == 0 || infix[i - 1] == '('))) {
			string num;
			if (ch == '-') {
				num += ch;
				i++;
			}
			while (i < infix.length() && infix[i] >= '0' && infix[i] <= '9') {
				num += infix[i];
				i++;
			}
			i--;
			postfix += num + " ";
		}
		else if (ch == '(') {
			push(string(1, ch));
		}
		else if (ch == ')') {
			while (!isEmpty() && peek() != "(") {
				postfix += pop();
				postfix += " ";
			}
			if (!isEmpty() && peek() == "(") pop();
			else return "Syntax error.\n";
		}
		else if (isOperator(ch)) {
			while (!isEmpty() && precedence(peek()[0]) >= precedence(ch)) {
				postfix += pop();
				postfix += " ";
			}
			push(string(1,ch));
		}
		else {
			cout << "Syntax error!" << endl;
			return "";
		}
	}

	while (!isEmpty()) {
		if (peek() == "(") return "Syntax error.\n";
		postfix += pop();
		postfix += " ";
	}

	return postfix;
}

string caculatePostfix(string postfix) {
	int i = 0;
	while (i < postfix.length()) {
		while (postfix[i] == ' ') i++;
		if (i >= postfix.length()) break;

		if (isOperator(postfix[i]) && (postfix[i + 1] == ' ')) {
			if (top < 1) return "Syntax error.";
			string b = pop();
			string a = pop();
			string res;

			if (postfix[i] == '+') {
				res = calculateAdd(a, b);
			} 
			else if (postfix[i] == '-') {
				res = calculateMinus(a, b);
			}
			else if (postfix[i] == '*') {
				res = multiplyBigInt(a, b);
			}
			else if (postfix[i] == '/') {
				res = divisionBigInt(a, b);
				if (res == "Error: Division by zero.\n") return res;
			}
			push(res);
			i++;
		}
		else {
			string num;
			if (postfix[i] == '-') {
				num += postfix[i];
				i++;
			}
			while (i < postfix.length() && postfix[i] >= '0' && postfix[i] <= '9') {
				num += postfix[i];
				i++;
			}
			push(num);
		}
	}
	if (top != 0) return "Syntax error";
	return pop();
}

void process(const string& ip, const string& op) {
	ifstream fin(ip);
	ofstream fout(op);
	string infix;

	if (!fin.is_open() || !fout.is_open()) {
		cout << "Cannot open file !";
		return;
	}

	while (getline(fin, infix)) {
		if (infix.empty()) break;
		string cleanInfix;
		for (int i = 0; i < infix.length(); i++) {
			if (infix[i] != ' ') {
				cleanInfix += infix[i];
			}
		}
		string postfix = infixToPostfix(cleanInfix);
		if (postfix == "") {
			fout << "Syntax error.\n";
			cout << "Syntax error.\n";
			continue;
		}
		string res = caculatePostfix(postfix);
		if (res == "Error: Division by zero.\n") {
			fout << "Division by zero error.\n";
			cout << "Division by zero error.\n";
			continue;
		}
		if (res.empty()) {
			fout << "Error\n";
			cout << "Error\n";
			continue;
		}
		fout << res << endl;
		cout << res << endl;
	}
	fin.close();
	fout.close();
}
int main(int argc, char* argv[]) {
	string x = argv[1];
	string y = argv[2];
	if (argc != 3) {
		return 1;
	}
	process(x, y);
	return 0;
}