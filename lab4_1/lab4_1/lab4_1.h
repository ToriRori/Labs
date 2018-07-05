#pragma once
#include <functional>
template<typename T>

void merge(T tmp[], T arr[], int l, int mid, int r, std::function<bool(T, T)>F)
{
	int i = l, j = mid + 1;
	int k = 0;
	while (i <= mid && j <= r) {
		if (F(arr[i], arr[j]))
			tmp[k++] = arr[i++];
		else
			tmp[k++] = arr[j++];
	}

	while (i <= mid)
		tmp[k++] = arr[i++];

	while (j <= r)
		tmp[k++] = arr[j++];

	for (k = 0, i = l; i <= r; ++i, ++k)
		arr[i] = tmp[k];
}


template <typename T>
void merge_sort(T arr[], int first, int last, std::function<bool(T,T)>F = std::less<T>())
{
	T *tmp = new T[last - first + 1];
	int mid;
	if (first < last) {
		mid = (first + last) / 2;
		merge_sort( arr, first, mid, F);
		merge_sort( arr, mid + 1, last, F);

		merge(tmp, arr, first, mid, last, F);
	}
	delete[] tmp;
}