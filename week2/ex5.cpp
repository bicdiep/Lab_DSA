#include <iostream>
#include <climits>
using namespace std;

int minLength(int nums[], int n, int target) {
	int minLength = INT_MAX, left = 0, right, sum = 0;

	for (right = 0; right < n; right++) {
		sum += nums[right];

		while (sum >= target) {
			if (minLength > right - left + 1) {
				minLength = right - left + 1;
			}
			sum -= nums[left];
			left++;
		}
	}
	if (minLength == INT_MAX) return 0;
	else return minLength;
}

int main() {
	int nums[100], n, target;
	cout << "enter length of array: ";
	cin >> n;
	cout << "enter elements: ";
	for (int i = 0; i < n; i++) {
		cin >> nums[i];
	}
	cout << "enter target: ";
	cin >> target;
	cout << "the minimal length of subarray whose sum is greater than or equal to targer is: " << minLength(nums, n, target) << endl;
	return 0;
}