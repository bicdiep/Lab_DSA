#include <iostream>
using namespace std;

bool twoSum(int nums[], int n, int target) {
	int left = 0, right = n - 1, sum = 0;
	
	while (left < right) {
		sum = nums[left] + nums[right];
		if (sum == target) return true;
		if (sum > target) right--;
		else left++;
	}
	return false;
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
	cout << "exist two numbers in the array: ";
	if (twoSum(nums, n, target)) cout << "YES" << endl;
	else cout << "NO" << endl;
	return 0;
}