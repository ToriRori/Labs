#pragma once
#include <iostream>
#include <cstdlib>
#include <omp.h>

void mult(int **a, int **b, int **c, int n, int m, const int numThread)
{
	int i, j, k;
	omp_set_num_threads(numThread);
#pragma omp parallel for shared(a, b, c) private(i, j, k)
	for (i = 0; i < n; i++) {
		for (j = 0; j < m; j++) {
			c[i][j] = 0;
			for (k = 0; k < m; k++) {
				c[i][j] += (a[i][k] * b[k][j]);
			}
		}
	}
}