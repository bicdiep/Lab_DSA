#include <iostream>;
using namespace std;

int LinearSearchWithSentinel(int a[], int n, int k) {
	int last = a[n - 1];
	a[n - 1] = k;
	int i = 0;
	
	while (a[i] != k) {
		i++;
	}

	a[n - 1] = last;
	if (i < n - 1 || a[n - 1] == k) {
		return i;
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
	cout << "key index: " << LinearSearchWithSentinel(a, n, k) << endl;
	return 0;
}