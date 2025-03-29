#include <iostream>
using namespace std;

void sortArray(int nums[], int n) {
	for (int i = 0; i < n; i++) {
		int key = nums[i];
		int j = i - 1;
		while (j >= 0 && nums[j] > key) {
			nums[j + 1] = nums[j];
			j = j - 1;
		}
		nums[j + 1] = key;
	}
}

void threeSum(int nums[], int n) {
	sortArray(nums, n);
	
	for (int i = 0; i < n - 2; i++) {
		int left = i + 1, right = n - 1;

		while (left < right) {
			int sum = nums[i] + nums[left] + nums[right];

			if (sum == 0) {
				cout << "[" << nums[i] << ", " << nums[left] << ", " << nums[right] << "]";
				left++;
				right--;
			}
			else if (sum < 0) {
				left++;
			}
			else right--;
		}
	}

}

int main() {
	int nums[100], n;
	cout << "enter length of array: ";
	cin >> n;
	cout << "enter elements: ";
	for (int i = 0; i < n; i++) {
		cin >> nums[i];
	}
	cout << "Triplets with sum equal to zero: ";
	threeSum(nums, n);
	return 0;
}