#pragma once
struct bit_Arr {
private:
	char bit;
	unsigned char * arr;
	int len;
public:
	bit_Arr(int len, unsigned char bit);

	inline bit_Arr(const bit_Arr &_src);
	inline bit_Arr(bit_Arr &&_src);

	void change_Bit(char bit);
	void change_Size(int len);

	bit_Arr operator()(const bit_Arr& arr, int start, int end);

	class t_proxy {
	public:
		inline t_proxy(int _ind, bit_Arr& _bA);
		t_proxy(const t_proxy &_src);	//Приватный copy-конструктор (запрет на копирование объекта);
		friend struct bit_Arr;	//Указанный класс имеет доступ к приватным полям t_proxy!
		inline t_proxy &operator = (int _val);
		inline operator int() const;
		int ind;
		bit_Arr &bA;
	};
	unsigned operator[] (int i) const;
	t_proxy operator[] (int i);
	friend bit_Arr operator+=(bit_Arr& left, bit_Arr& right);
};

bit_Arr operator+=(bit_Arr& left, bit_Arr& right);