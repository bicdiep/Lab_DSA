#include <iostream>
using namespace std;

int canShip(int weights[], int n, int capacity) {
	int day = 1;
	int countWeight = 0;

	for (int i = 0; i < n; i++) {
		if (countWeight + weights[i] > capacity) {
			day++;
			countWeight = 0;
		}
		countWeight += weights[i];
	}
	
	return day;
}

int minCapacity(int weights[], int n, int days) {
	int left = weights[n - 1];
	int right = 0;

	for (int i = 0; i < n; i++) {
		right += weights[i];
	}

	while (left < right) {
		int mid = (left + right) / 2;
		if (canShip(weights, n, mid) <= days) {
			right = mid;
		}
		else {
			left = mid + 1;
		}
	}
	return right;
}

int main() {
	int weights[100], n, days;
	cout << "enter the number of packages: ";
	cin >> n;
	cout << "enter the weights of " << n << " packages: ";
	for (int i = 0; i < n; i++) {
		cin >> weights[i];
	}
	cout << "enter the max number of days for ship: ";
	cin >> days;
	cout << "Minimum required ship capacity: " << minCapacity(weights, n, days) << endl;
	return 0;
}