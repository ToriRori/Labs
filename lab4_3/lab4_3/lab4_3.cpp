// lab4_3.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include <thread>
#include "windows.h"
#include "process.h"
#include <iomanip>

#define SIZE 9

void f(double a[SIZE][SIZE], int start, int end, int count, int len)
{
	for (start, end; start <= len, end <= len; start += (end - start + 1) * count, end += (end - start + 1) * count + (start == len - (end - start) ? 0 : 1))
	{
		for (int k = start; k < end; k++)
		{
			for (int j = k + 1; j < end; j++)
			{
				double d = a[j][(k - 1) % SIZE] / a[(k - 1) % SIZE][(k - 1) % SIZE];
				for (int i = (k - 1) % SIZE; i < end; i++)
				{
					a[j][i] = a[j][i] - d * a[(k - 1) % SIZE][i];
				}
			}
		}
		if (count == 0)
			break;
	}
}

void merge(double a[SIZE][SIZE], int num, int size, int len, int count)
{
	for (num; num <= len; num += size * count)
	{
		for (int i = 0 ; i < size - 1; i++)
		{
			double d = a[num][num - size + i + (num == size - 1 ? 1 : 0)] / a[num - size + i + 1][num - size + i + (num == size - 1 ? 1 : 0)];
			for (int j = ((num - size) < 0) ? 0 : (num - size); j <= num; j++)
			{
				a[num][j] = a[num][j] - d * a[num - size + i + 1][j];
			}
		}

		for (int i = 0; i < size - 1 + (num == len-size-1?1:0); i++)
		{
			double d = a[num][num+i] / a[num + i + 1][num+i];
			for (int j = num; j <= num + size; j++)
			{
				a[num][j] = a[num][j] - d * a[num + i + 1][j];
			}
		}
		if (count == 0)
			break;
	}
}

int main()
{
	double a[9][9];
	for (int i = 0; i < 9; i++)
		for (int j = 0; j < 9; j++)
			if (((i > 2) && (j < 2)) || ((j > 2) && (i < 2)) || ((i > 5) && (j < 5)) || ((i < 5) && (j > 5)))
				a[i][j] = 0;
			else
				a[i][j] =  rand() % 10;
	
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
			std::cout << a[i][j] << " ";
		std::cout << "\n";
	}
	std::cout << "\n";
	std::cout << "\n";
	int thread_max = 4;

	std::thread * t = new std::thread[thread_max];
	if (thread_max >= 9 / 3)
		thread_max = 9 / 3;

	for (int i = 0; i < thread_max; i ++)
		t[i] = std::thread(f, std::ref(a), i*3, i*3 + 3 - (i*3==9-3?0:1), 9/3-thread_max, 9);
	for (int i = 0; i < thread_max; i ++)
		t[i].join();

	/*for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
			std::cout << std::setw(10) << a[i][j] << " ";
		std::cout << "\n";
	}
	std::cout << "\n";
	std::cout << "\n";*/

	for (int i = 0; i < thread_max-1; i++)
		t[i] = std::thread(&merge, std::ref(a),(i+1)*3 - 1, 3, 9, 9/3-thread_max);
	for (int i = 0; i < thread_max-1; i++)
		t[i].join();

	 delete[] t;

	 for (int i = 0; i < 9; i++)
	 {
		 for (int j = 0; j < 9; j++)
			 std::cout << std::setw(10) << a[i][j] << " ";
		 std::cout << "\n";
	 }
	
	system("pause");
	return 0;
}