#include "stdafx.h"
#include "CppUnitTest.h"
#include "../lab4_1/lab4_1.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{		
	bool int_less(int l, int r) {
		return l < r;
	}
	bool int_greater(int l, int r) {
		return l > r;
	}
	bool str_less(const std::string &l, const std::string &r) {
		return l < r;
	}
	bool str_greater(const std::string &l, const std::string &r) {
		return l > r;
	}
	bool double_less(double l, double r) {
		return l < r;
	}
	bool double_greater(double l, double r) {
		return l > r;
	}

	TEST_CLASS(UnitTest1)
	{
	public:
		TEST_METHOD(TestMethod1)
		{
			int arr[10] = { 1, 3, 7, 3, 5, 2, 65, 87, 34, 5 };
			int res[10] = { 1, 2, 3, 3, 5, 5, 7, 34, 65, 87 };
			merge_sort<int>(arr, 0, 9, int_less);
			for (int i = 0; i < 10; i++)
				Assert::AreEqual(arr[i], res[i]);
		}

		TEST_METHOD(TestMethod2)
		{
			int arr[10] = { 1, 3, 7, 3, 5, 2, 65, 87, 34, 5 };
			int res[10] = { 87, 65, 34, 7, 5, 5, 3, 3, 2, 1 };
			merge_sort<int>(arr, 0, 9, int_greater);
			for (int i = 0; i < 10; i++)
				Assert::AreEqual(arr[i], res[i]);
		}

		TEST_METHOD(TestMethod3)
		{
			double arr[10] = { 1.25, 3.65, 7.576, 3.89, 5.57, 2.325, 65.894, 87.2439, 34.457, 5.235 };
			double res[10] = { 1.25, 2.325, 3.65, 3.89, 5.235, 5.57, 7.576, 34.457, 65.894, 87.2439 };
			merge_sort<double>(arr, 0, 9, double_less);
			for (int i = 0; i < 10; i++)
				Assert::AreEqual(arr[i], res[i]);
		}

		TEST_METHOD(TestMethod4)
		{
			double arr[10] = { 1.25, 3.65, 7.576, 3.89, 5.57, 2.325, 65.894, 87.2439, 34.457, 5.235 };
			double res[10] = { 87.2439, 65.894, 34.457, 7.576, 5.57, 5.235, 3.89, 3.65, 2.325, 1.25 };
			merge_sort<double>(arr, 0, 9, double_greater);
			for (int i = 0; i < 10; i++)
				Assert::AreEqual(arr[i], res[i]);
		}

		TEST_METHOD(TestMethod5)
		{
			std::string arr[5];
			arr[0] = "12";
			arr[1] = "df";
			arr[2] = "1d";
			arr[3] = "d5";
			arr[4] = "1s";
			std::string res[5];
			res[0] = "12";
			res[1] = "1d";
			res[2] = "1s";
			res[3] = "d5";
			res[4] = "df";
			merge_sort<std::string>(arr, 0, 4, str_less);
			for (int i = 0; i < 5; i++)
				Assert::AreEqual(arr[i], res[i]);
		}
		TEST_METHOD(TestMethod6)
		{
			std::string arr[5];
			arr[0] = "12";
			arr[1] = "df";
			arr[2] = "1d";
			arr[3] = "d5";
			arr[4] = "1s";
			std::string res[5];
			res[0] = "df";
			res[1] = "d5";
			res[2] = "1s";
			res[3] = "1d";
			res[4] = "12";
			merge_sort<std::string>(arr, 0, 4, [](std::string a, std::string b) {return a > b; });
			for (int i = 0; i < 5; i++)
				Assert::AreEqual(arr[i], res[i]);
		}

		TEST_METHOD(TestMethod7)
		{
			int arr[10] = { 1, 3, 7, 3, 5, 2, 65, 87, 34, 5 };
			int res[10] = { 1, 2, 3, 3, 5, 5, 7, 34, 65, 87 };
			merge_sort<int>(arr, 0, 9);
			for (int i = 0; i < 10; i++)
				Assert::AreEqual(arr[i], res[i]);
		}

	};
}