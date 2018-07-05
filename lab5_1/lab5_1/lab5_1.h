#pragma once
#include <iostream>
#include <ctime>
#include <windows.h>
#include <process.h>

struct Multiplyer
{
	static int m, n, q, r;
	static int **a, **b, **c;
	static int *from, *to;
	static const int numThread;

	Multiplyer(int **_a, int **_b, int _m, int _n, const int _numThread) 
	{
		m = _m;
		n = _n;
		a = _a;
		b = _b;
		numThread = _numThread;

		q = m / numThread; 
		r = m % numThread;
		from = new int[numThread];
		to = new int[numThread];
		from = { 0 };
		to = { 0 };

		c = new int *[m];
		for (int i = 0; i<n; i++)
			c[i] = new int[m];
	}

	static unsigned __stdcall ThreadFunctionMult(void *param)//, int* from, int* to, const int**matr_1, const int** matr_2, int ** matr_3, int m, int n)
	{
		int iNum = *(reinterpret_cast<int*>(param));
		for (int i = from[iNum]; i < to[iNum]; i++)
		{
			for (int j = 0; j < m; j++)
			{
				c[i][j] = 0;
				for (int z = 0; z < n; z++)
					c[i][j] += a[i][z] * b[z][j];
			}
		}
		return 0;
	}

	int **mult()
	{
		int q = m / numThread, r = m % numThread;
		int *from = new int[numThread], *to = new int[numThread];
		from = { 0 };
		to = { 0 };

		int **c = new int *[m];
		for (int i = 0; i<n; i++)
			c[i] = new int[m];

		HANDLE hThreads[numThread];
		unsigned id;
		int noms[numThread];

		for (int i = 0; i < numThread; i++) {
			to[i] = from[i] + q + (i < r ? 1 : 0);
			noms[i] = i;
			hThreads[i] = (HANDLE)_beginthreadex(NULL, 0, ThreadFunctionMult, (void *)(noms + i), 0, &id);
			if (i<numThread - 1)
				from[i + 1] = to[i];
		}

		WaitForMultipleObjects(numThread, hThreads, TRUE, INFINITE);
		for (int i = 0; i < numThread; i++)
			CloseHandle(hThreads[i]);

	}
};