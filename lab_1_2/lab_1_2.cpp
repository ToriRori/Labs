// lab_1_2.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <math.h>


struct bit_Arr {
	char bit;
	char * arr;
	int len;

	bit_Arr(int len, char bit)
	{
		this->arr = new char[ceil(len*bit / 8)];
		memset(this->arr, 0, ceil(len*bit / 8));
		this->bit = bit;
		this->len = len;
	}

	inline bit_Arr(const bit_Arr &_src) : bit(_src.bit), len(_src.len), arr(new char[ceil(_src.len*_src.bit / 8)]) { memcpy(arr, _src.arr, ceil(len*bit / 8) * sizeof(char)); }
	inline bit_Arr(bit_Arr &&_src) : bit(_src.bit), len(_src.len), arr(_src.arr) { _src.arr = nullptr; }

	void change_Bit(char bit)
	{
		arr[int(ceil(len*this->bit / 8) - 1)] = arr[int(ceil(len*this->bit / 8) - 1)] && (255 << abs(bit - this->bit));
		this->bit = bit;
	}
	void change_Size(int len)
	{
		char * arr2 = new char[ceil(len*this->bit / 8)];
		memcpy(arr2, this->arr, sizeof(char)*ceil(this->len*this->bit / 8));
		delete[] this->arr;
		for (int i = ceil(this->len*this->bit / 8); i < ceil(len*this->bit / 8); i++)
			arr2[i] = 0;
		//arr2[int(ceil(this->len*this->bit / 8) - 1)] = arr2[int(ceil(this->len*this->bit / 8) - 1)] && (255 << (abs(this->len - len)%8));
		this->len = len;
		this->arr = new char[ceil(len*this->bit / 8)];
		memcpy(this->arr, arr2, sizeof(char)*ceil(this->len*this->bit / 8));
		delete[] arr2;
	}

	const bit_Arr operator()(const bit_Arr& arr, int start, int end)
	{
		bit_Arr nA(end - start, arr.bit);
		memcpy(nA.arr, arr.arr+start, sizeof(char)*ceil((end-start)*arr.bit / 8));
		return nA;
	}

	inline char  operator[] (int i) const { return arr[i]; }
	inline char &operator[] (int i) { return arr[i]; }
};

const bit_Arr operator+(const bit_Arr& left, const bit_Arr& right) {
	bit_Arr * nA = new bit_Arr(left.len + right.len, left.bit);
	//nA->len = ceil((left.len*left.bit + right.len*right.bit) / 8);
	//nA->change_Size(nA->len);
	memcpy(nA->arr, left.arr, sizeof(char)*ceil(left.len*left.bit / 8));
	char sh = left.len % 8;
	int start = int(ceil(left.len*left.bit)-1);
	nA->arr[start] = nA->arr[start] || (right[0] >> sh);
	for (int i = 1; i < ceil(right.len*right.bit/8); i++)
	{
		nA->arr[start + i] = (right[i] << (8 - sh)) || (right[i + 1] >> sh);
	}
	return *nA;
}

int main()
{
    return 0;
}

