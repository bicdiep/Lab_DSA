#include "sort_utils.h"

template <class T>
void HoanVi(T& a, T& b)
{
	T x = a;
	a = b;
	b = x;
}

//-------------------------------------------------

// Hàm phát sinh mảng dữ liệu ngẫu nhiên
void GenerateRandomData(int a[], int n)
{
	srand((unsigned int)time(NULL));

	for (int i = 0; i < n; i++)
	{
		a[i] = rand() % n;
	}
}

// Hàm phát sinh mảng dữ liệu có thứ tự tăng dần
void GenerateSortedData(int a[], int n)
{
	for (int i = 0; i < n; i++)
	{
		a[i] = i;
	}
}

// Hàm phát sinh mảng dữ liệu có thứ tự ngược (giảm dần)
void GenerateReverseData(int a[], int n)
{
	for (int i = 0; i < n; i++)
	{
		a[i] = n - 1 - i;
	}
}

// Hàm phát sinh mảng dữ liệu gần như có thứ tự
void GenerateNearlySortedData(int a[], int n)
{
	for (int i = 0; i < n; i++)
	{
		a[i] = i;
	}
	srand((unsigned int)time(NULL));
	for (int i = 0; i < 10; i++)
	{
		int r1 = rand() % n;
		int r2 = rand() % n;
		HoanVi(a[r1], a[r2]);
	}
}

void GenerateData(int a[], int n, int dataType)
{
	switch (dataType)
	{
	case 0:	// ngẫu nhiên
		GenerateRandomData(a, n);
		break;
	case 1:	// có thứ tự
		GenerateSortedData(a, n);
		break;
	case 2:	// có thứ tự ngược
		GenerateReverseData(a, n);
		break;
	case 3:	// gần như có thứ tự
		GenerateNearlySortedData(a, n);
		break;
	default:
		printf("Error: unknown data type\n");
	}
}

void readInputFile(const string& filename, int*& a, int& n) {
	ifstream fin(filename);
	if (!fin) {
		cout << "Cannot open file " << filename << "." << endl;
		exit(1);
	}
	fin >> n;
	a = new int[n];
	if (!a) {
		cout << "Memory allocation failed!\n";
		return;
	}
	for (int i = 0; i < n; i++) {
		fin >> a[i];
	}
}

void writeOutputFile(const string& filename, int*& a, int& n) {
	ofstream fout(filename);
	if (!fout) {
		cout << "Cannot open file " << filename << "." << endl;
		return;
	}
	fout << n << endl;
	for (int i = 0; i < n; i++) {
		fout << a[i] << " ";
	}

	fout.close();
}



void insertionSort(int a[], int n) {
	for (int i = 1; i < n; i++) {
		int key = a[i];
		int j = i - 1;
		while (j >= 0 && a[j] > key) {
			a[j + 1] = a[j];
			j = j - 1;
		}
		a[j + 1] = key;
	}
}

void heapify(int a[], int n, int i) {
	int largest = i;
	int left = 2 * i + 1;
	int right = 2 * i + 2;

	if (left < n && a[left] > a[largest]) {
		largest = left;
	}

	if (right < n && a[right] > a[largest]) {
		largest = right;
	}

	if (largest != i) {
		swap(a[i], a[largest]);
		heapify(a, n, largest);
	}
}

void heapSort(int a[], int n) {
	for (int i = n / 2 - 1; i >= 0; i--) {
		heapify(a, n, i);
	}

	for (int i = n - 1; i > 0; i--) {
		swap(a[0], a[i]);
		heapify(a, i, 0);
	}

}

void merge(int a[], int left, int mid, int right) {
	int* temp = new int[right - left + 1];
	if (!temp) {
		cout << "Memory allocation failed!\n";
		return;
	}
	int i = left, j = mid + 1, k = 0;
	while (i <= mid && j <= right) {

		if (a[i] <= a[j]) {
			temp[k++] = a[i++];
		}
		else temp[k++] = a[j++];
	}

	while (i <= mid) {
		temp[k++] = a[i++];
	}
	while (j <= right) {
		temp[k++] = a[j++];
	}

	for (int x = 0; x < k; x++) {
		a[left + x] = temp[x];
	}
	delete[] temp;
}

void mergeSort(int a[], int left, int right) {
	if (left < right) {
		int mid = left + (right - left) / 2;

		mergeSort(a, left, mid);
		mergeSort(a, mid + 1, right);
		merge(a, left, mid, right);
	}
}

void flashSort(int a[], int n) {
	if (n <= 1) return;
	int m = static_cast<int>(0.45 * n);

	int* l = new int[m]();
	if (!l) {
		cout << "Memory allocation failed!\n";
		return;
	}
	int max = 0, min = a[0];

	for (int i = 1; i < n; i++) {
		if (a[i] < min) min = a[i];
		if (a[i] > a[max]) max = i;
	}
	if (min == a[max]) return;

	double b = static_cast<double>(m - 1) / (a[max] - min);

	for (int j = 0; j < n; j++) {
		++l[static_cast<int>(b * (a[j] - min))];
	}

	for (int x = 1; x < m; x++) {
		l[x] += l[x - 1];
	}

	swap(a[max], a[0]);

	int move = 0, t, flash;
	int i = 0;
	int k = m - 1;

	while (move < n - 1) {
		while (i > (l[k] - 1)) {
			++i;
			k = static_cast<int>(b * (a[i] - min));
		}
		if (k < 0) break;
		flash = a[i];
		while (i != l[k]) {
			k = static_cast<int>(b * (flash - min));
			t = --l[k];
			swap(a[t], a[i]);
			flash = a[i];
			++move;
		}
	}
	delete[] l;
	insertionSort(a, n);

}

void selectionSort(int a[], int n) {
	for (int i = 0; i < n; i++) {
		int min = i;
		for (int j = i + 1; j < n; j++) {
		
			if (a[j] < a[min]) {
				min = j;
			}
		}
		swap(a[i], a[min]);
	}
}
void bubbleSort(int a[], int n) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n - 1 - i; j++) {
			
			if (a[j] > a[j + 1]) {
				swap(a[j], a[j + 1]);
			}
		}
	}
}
void shakerSort(int a[], int n) {
	int l = 0;
	int r = n - 1;
	while (l < r) {
		for (int i = l;+ i < r; i++) {
			
			if (a[i] > a[i + 1]) {
				swap(a[i], a[i + 1]);
			}
		}
		r--;
		for (int j = r; j > l; j--) {
	
			if (a[j] < a[j - 1]) {
				swap(a[j], a[j - 1]);
			}
		}
		l++;
	}
}
void shellSort(int a[], int n) {
	for (int d = n / 2; d > 0; d /= 2) {
		for (int i = d; i < n; i++) {
			int j = i;
			int value = a[i];
			while (j >= d && value < a[j - d]) {
				a[j] = a[j - d];
				j -= d;
			}
			a[j] = value;
		}
	}
}
int quick(int a[], int l, int r) {
	int randIndex = l + rand() % (r - l + 1);
	int pivot = a[randIndex];
	swap(a[randIndex], a[r]);
	int i = l - 1;
	for (int j = l; j < r; j++) {
		
		if (a[j] < pivot) {
			i++;
			swap(a[i], a[j]);
		}
	}
	i++;
	swap(a[i], a[r]);
	return i;
}
void quickSort(int a[], int l, int r) {
	if (l >= r)return;
	else {
		int p = quick(a, l, r);
		quickSort(a, l, p - 1);
		quickSort(a, p + 1, r);
	}
}
void countingSort(int a[], int n) {
	int valmax = a[0];
	int valmin = a[0];
	for (int i = 0; i < n; i++) {
		if (a[i] > valmax)valmax = a[i];
		if ( a[i] < valmin)valmin = a[i];
	}
	int h = valmax - valmin + 1;
	int* dem = new int[h] {};
	for (int i = 0;  i < n; i++) {
		dem[a[i] - valmin]++;
	}
	int idex = 0;
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < dem[i]; j++) {
			a[idex++] = i + valmin;
		}
	}
}
int getMax(int a[], int n) {
	int mx = a[0];
	for (int i = 1; i < n; ++i)
		if (a[i] > mx) mx = a[i];
	return mx;
}

void countSortForRadix(int a[], int n, int exp) {
	int* output = new int[n], count[10] = {};

	for (int i = 0; i < n; ++i)
		++count[(a[i] / exp) % 10];
	for (int i = 1; i < 10; ++i)
		count[i] += count[i - 1];
	for (int i = n - 1; i >= 0; --i)
		output[--count[(a[i] / exp) % 10]] = a[i];
	for (int i = 0; i < n; ++i)
		a[i] = output[i];

	delete[] output;
}

void radixSort(int a[], int n) {
	int m = getMax(a, n);
	for (int exp = 1; m / exp > 0; exp *= 10)
		countSortForRadix(a, n, exp);
}

