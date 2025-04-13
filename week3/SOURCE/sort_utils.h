#pragma once
#include <iostream>
#include <fstream>
#include <cmath>
#include <time.h>
#include <chrono>
#include <iomanip>
using namespace std;

template <class T>
void HoanVi(T& a, T& b);
void GenerateRandomData(int a[], int n);
void GenerateSortedData(int a[], int n);
void GenerateReverseData(int a[], int n);
void GenerateNearlySortedData(int a[], int n);
void GenerateData(int a[], int n, int dataType);
void readInputFile(const string& filename, int*& a, int& n);
void writeOutputFile(const string& filename, int*& a, int& n);
void insertionSort(int a[], int n);
void heapify(int a[], int n, int i);
void heapSort(int a[], int n);
void merge(int a[], int left, int mid, int right);
void mergeSort(int a[], int left, int right);
void flashSort(int a[], int n);
void selectionSort(int a[], int n);
void bubbleSort(int a[], int n);
void shakerSort(int a[], int n);
void shellSort(int a[], int n);
int quick(int a[], int l, int r);
void quickSort(int a[], int l, int r);
void countingSort(int a[], int n);
int getMax(int a[], int n);
void countSortForRadix(int a[], int n, int exp);
void radixSort(int a[], int n);



