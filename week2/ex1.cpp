#include <iostream>
using namespace std;

int LinearSearch(int a[], int n, int k) {
	for (int i = 0; i < n; i++) {
		if (a[i] == k) return i;
	}
	return -1;
}

int main() {
	int a[100], n, k;
	cout << "enter length of array: ";
	cin >> n;
	while (n < 0) {
		cout << "please enter positive integer. enter again: ";
		cin >> n;
	}
	cout << "enter elements: ";
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}
	cout << "enter key: ";
	cin >> k;
	cout << "key index: " << LinearSearch(a, n, k) << endl;
	return 0;
}