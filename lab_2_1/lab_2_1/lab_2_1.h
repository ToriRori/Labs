#pragma once
struct matrix {
	int m;
	int n;
	int **arr;

	matrix(int n, int m) {
		arr = new int * [n];
		for (int i = 0; i < n; i++)
			arr[i] = new int[m];
		this->n = n;
		this->m = m;
	}

	void transp();
	matrix slice(int nStart, int nEnd, int mStart, int mEnd);
	matrix getRow(int i);
	matrix getCol(int j);

	int operator[](int i);
	int operator[](const int i);
	friend matrix operator+(matrix a, matrix b);
	friend matrix operator-(matrix a, matrix b);
	friend matrix operator*(matrix a, int b);
	friend matrix operator*(matrix a, matrix b);
};

matrix operator+(matrix a, matrix b);
matrix operator-(matrix a, matrix b);
matrix operator*(matrix a, int b);
matrix operator*(matrix a, matrix b);
