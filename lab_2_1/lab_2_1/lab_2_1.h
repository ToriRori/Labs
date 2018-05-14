#pragma once
#include <iostream>;

struct t_string {
	int m;
	int n;
	int * arr;
	size_t ref_count;
	friend struct matrix;

	t_string(int len)
	{
		this->arr = new int [len];
		this->ref_count = 1;
	}

	~t_string() throw(std::bad_alloc)
	{
	}

	t_string(const t_string &_src)
	{
		this->ref_count = 1;
		this->m = _src.m;
		this->n = _src.n;
		this->arr = new int[_src.m*_src.n];
		memcpy(this->arr, _src.arr, sizeof(int) * _src.m*_src.n);
	}
};

struct matrix {
private:
	t_string * matr;

	void str_off() throw(std::bad_alloc)
	{
		if (matr == NULL)
			return;
		if (--(matr->ref_count) == 0)
			delete[]((matr)->arr);
		matr = NULL;
	}

	void str_mov(t_string *src)
	{
		if (matr == src)
			return;
		str_off();
		if (src == NULL)
			return;
		src->ref_count++;
		matr = src;
	}

	void str_cpy(t_string *src, int len)
	{
		if (matr == src)
		{
			return;
		}
		t_string * tmp = new t_string(len);
		tmp->m = matr->m;
		tmp->n = matr->n;
		memcpy(tmp->arr, src->arr, sizeof(int) * len);
		str_off();
		matr = tmp;
	}

	struct excp :public std::exception
	{
		int code;
	public:
		excp(int _code)
		{
			code = _code;
		}
		virtual void print() {
			std::cerr << "Err " << code << "\n";
		}
	};

public:
	matrix(int n, int m) throw (std::bad_alloc) {
		matr = new t_string(n*m);
		this->matr->n = n;
		this->matr->m = m;
	}

	~matrix()
	{
		if ((--matr->ref_count) < 0)
			delete[](matr->arr);
	}
	void transp();
	
	class t_proxy {
	private:
		inline t_proxy(int _i, int _j, matrix &_m) : i(_i), j(_j), m(_m) { if ((_i > _m.matr->n) || (_j > _m.matr->m)) throw excp(1); }
		t_proxy(const t_proxy &_src) : m(_src.m) {}
		friend struct matrix;
	public:
		inline operator int() const {
			return m.matr->arr[i*m.matr->m + j];
		}
		t_proxy &operator = (int _val);
	private:
		int i, j;
		matrix &m;
	};

	t_proxy operator()(int i, int j);
	int operator() (int i, int j) const;
	
	class t_slice {
	private:
		inline t_slice(int _i1, int _i2,  int _step1,int _j1, int _j2, int _step2, matrix * _m) : i1(_i1), j1(_j1), i2(_i2), j2(_j2), step1(_step1), step2(_step2), m(_m) {
			if ((_i1 >= _m->matr->n) || (_i1 >= _m->matr->n) || (_j1 >= _m->matr->m) || (_j2 >= _m->matr->m))
				throw matrix::excp(1);
		}
		inline t_slice(int _i1, int _i2, int _step1, matrix * _m) : i1(_i1), j1(0), i2(_i2), j2(_m->matr->n-1), step1(_step1), step2(1), m(_m) {
			if ((_i1 >= _m->matr->n) || (_i1 >= _m->matr->n))
				throw matrix::excp(1);
		}
		inline t_slice(int _i1, int _i2, matrix * _m) : i1(_i1), j1(0), i2(_i2), j2(_m->matr->n-1), step1(1), step2(1), m(_m) {
			if ((_i1 >= _m->matr->n) || (_i1 >= _m->matr->n))
				throw matrix::excp(1);
		}
	public:
		t_slice transp();
		t_slice getRow(int i);
		t_slice getCol(int j);

		friend struct matrix;
		t_slice& operator=(t_slice s);
		t_slice& operator=(matrix m);
		matrix * getM() { return m; };
		int getI1() { return i1; }
		int getI2() { return i2; }
		int getJ1() { return j1; }
		int getJ2() { return j2; }
		int getS1() { return step1; }
		int getS2() { return step2; }


	private:
		int i1, j1, i2, j2, step1,  step2;
		matrix * m;
	};
	
	t_slice getRow(int i);
	t_slice getCol(int j);

	matrix& operator=(t_slice t);
	
	t_slice slice(int _i1, int _i2, int _step1, int _j1, int _j2, int _step2);
	t_slice slice(int _i1, int _i2, int _step1);
	t_slice slice(int _i1, int _i2); 
	
	friend matrix operator+(matrix::t_slice a, matrix::t_slice b);
	friend matrix operator-(matrix::t_slice a, matrix::t_slice b);
	friend matrix operator*(matrix::t_slice a, matrix::t_slice b);
	friend matrix operator*(matrix::t_slice a, int b);
	friend matrix operator+(matrix a, matrix::t_slice b);
	friend matrix operator-(matrix a, matrix::t_slice b);

	friend matrix operator+(matrix a, matrix b);
	friend matrix operator-(matrix a, matrix b);
	friend matrix operator*(matrix a, int b);
	friend matrix operator*(matrix a, matrix b);
	friend matrix operator*(matrix::t_slice a, matrix::t_slice b);
};

matrix operator+(matrix::t_slice a, matrix::t_slice b);
matrix operator-(matrix::t_slice a, matrix::t_slice b);
matrix operator*(matrix::t_slice a, matrix::t_slice b);
matrix operator+(matrix a, matrix::t_slice b);
matrix operator-(matrix a, matrix::t_slice b);
matrix operator*(matrix::t_slice a, int b);

matrix operator+(matrix a, matrix b);
matrix operator-(matrix a, matrix b);
matrix operator*(matrix a, int b);
matrix operator*(matrix a, matrix b);
