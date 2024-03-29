// lab_5_3.cpp: определяет точку входа для консольного приложения.
#include "stdafx.h"
#include <iostream>
#include <thread>
#include <time.h>
#include <cassert>
using namespace std;

void merge(int *a, int low, int mid, int high)
{
	int* left = new int[mid - low + 1];
	int* right = new int[high - mid];

	int n1 = mid - low + 1, n2 = high - mid, i, j;

	for (i = 0; i < n1; i++)
		left[i] = a[i + low];

	for (i = 0; i < n2; i++)
		right[i] = a[i + mid + 1];

	int k = low;
	i = j = 0;

	while (i < n1 && j < n2) {
		if (left[i] <= right[j])
			a[k++] = left[i++];
		else
			a[k++] = right[j++];
	}

	while (i < n1) {
		a[k++] = left[i++];
	}

	while (j < n2) {
		a[k++] = right[j++];
	}
}

void merge_sort(int *a, int low, int high)
{
	int mid = low + (high - low) / 2;
	if (low < high) {
		merge_sort(a, low, mid);
		merge_sort(a, mid + 1, high);
		merge(a, low, mid, high);
	}
}

void merge_sort_t(int *a, int i, int len, int thread_max)
{
	int low = (i ) *(len / thread_max);
	int high = (i + 1) * (len / thread_max) - 1;

	int mid = low + (high - low) / 2;
	if (low < high) {
		merge_sort(a, low, mid);
		merge_sort(a, mid + 1, high);
		merge(a, low, mid, high);
	}
}

void merge_t(int *a, int i, int thread_max, int len)
{
	merge(a, i*(len / (thread_max / 2)), i*(len / (thread_max / 2)) + ((i + 1)*len / (thread_max / 2) - 1 - i * (len / (thread_max / 2))) / 2, (i + 1)*len / (thread_max / 2) - 1);
}

void merge_sort_thread(int*a, int len, int thread_max)
{
	thread *threads = new thread[thread_max];
	for (int i = 0; i < thread_max; i++)
		threads[i] = thread(&merge_sort_t, a, i, len, thread_max);
	for (int i = 0; i < thread_max; i++)
		threads[i].join();

	while (thread_max >= 2)
	{
		for (int i = 0; i < thread_max / 2; i++)
			threads[i] = thread(&merge_t, a, i, thread_max, len);
		for (int i = 0; i < thread_max / 2; i++)
			threads[i].join();
		thread_max /= 2;
	}
	
	/*while (thread_max >= 2)
	{
		for (int i = 0; i < thread_max; i++)
		{
			if (i % 2)
			{
				threads[i] = thread(&merge_t, a, i, thread_max, len);
				threads[i].join();
				threads[i - 1].join();
			}
			else
				threads[i] = thread(&merge_t, a, i, thread_max, len);
		}
		thread_max /= 2;
	}*/
	
	delete[] threads;
}

int main()
{
	const int size = 16;
	int a[size];
	for (int i = 0; i < size; i++)
		a[i] = rand() % 100;

	merge_sort_thread(a, size, 4);
	
	for (int i = 0; i < size; i++)
		cout << a[i] << " ";

	system("pause");
	return 0;
}
