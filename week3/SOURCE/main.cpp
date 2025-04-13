#include "sort_utils.h"

int main(int argc, char* argv[]) {
	string algo, inputFile, outputFile;
	int n;
	int* a;

	for (int i = 1; i < argc; i++) {
		string arg = argv[i];
		if (arg == "-a") algo = argv[++i];
		else if (arg == "-i") inputFile = argv[++i];
		else if (arg == "-o") outputFile = argv[++i];
	}

	readInputFile(inputFile, a, n);
	if (algo == "insertion-sort")
		insertionSort(a, n);
	else if (algo == "heap-sort")
		heapSort(a, n);
	else if (algo == "merge-sort")
		mergeSort(a, 0, n - 1);
	else if (algo == "flash-sort")
		flashSort(a, n);
	else if (algo == "selection-sort")
		selectionSort(a, n);
	else if (algo == "bubble-sort")
		bubbleSort(a, n);
	else if (algo == "shaker-sort")
		shakerSort(a, n);
	else if (algo == "shell-sort")
		shellSort(a, n);
	else if (algo == "quick-sort")
		quickSort(a, 0, n - 1);
	else if (algo == "counting-sort")
		countingSort(a, n);
	else if (algo == "radix-sort")
		radixSort(a, n);
	else return 1;
	writeOutputFile(outputFile, a, n);
	cout << "Done." << endl;
	delete[] a;

	return 0;
}

