#include <iostream>
using namespace std;

int findMin(int a[], int left, int right) {
	int mid = -1;
	while (left < right) {
		mid = left + (right - left) / 2;
		if (a[mid - 1] > a[mid]) return a[mid];
		if (a[mid + 1] < a[mid]) return a[mid + 1];
		if (a[mid] > a[right])
			left = mid + 1;
		else
			right = mid - 1;
	}
	return a[mid];
}

int main() {
	int a[100], n;
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
	cout << "min is: " << findMin(a, 0, n - 1);
	return 0;
}