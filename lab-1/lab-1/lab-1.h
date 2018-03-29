#pragma once
#ifndef lab1

struct Calendar {
private:
	int year;
	int month;
	int day;
	static std::string formatDate;

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
			exit(code);
		}
	};
public:
	static void setFormat(std::string str);

	Calendar(int year, int month, int day);

	Calendar(std::string str);

	operator std::string();

	bool isLeap(int year);

	int getWeekDay();

	friend Calendar operator+=(Calendar& left, int days);
	friend Calendar operator-=(Calendar& left, int days);
	friend std::istream& operator >> (std::istream& is, Calendar & obj);
	friend std::ostream& operator <<(std::ostream& os, Calendar& obj);
	friend int operator-(Calendar left, Calendar right);
};

Calendar operator+=(Calendar& left, int per);
Calendar operator-=(Calendar& left, int per);
int operator-(Calendar left, Calendar right);
std::istream& operator >> (std::istream& is, Calendar & obj);
std::ostream& operator <<(std::ostream& os, Calendar& obj);

#endif // !lab-1