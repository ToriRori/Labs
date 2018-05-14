#include "stdafx.h"
#include "CppUnitTest.h"
#include "..\lab_2_1\lab_2_1.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			// обращение к элементу
			matrix m(5, 4);
			for (int i = 0; i < 5; i++)
				for (int j = 0; j < 4; j++)
					m(i, j) = i * 2 + j;

			Assert::AreEqual(int(m(0, 0)), 0);
			Assert::AreEqual(int(m(1, 2)), 4);
			Assert::AreEqual(int(m(4, 3)), 11);
			Assert::AreEqual(int(m(0, 2)), 2);
		}
		TEST_METHOD(TestMethod2)
		{
			//транспонирование
			matrix m(2, 5);
			for (int i = 0; i < 2; i++)
				for (int j = 0; j < 5; j++)
					m(i, j) = i + j * 2;

			m.transp();
			Assert::AreEqual(int(m(0, 0)), 0);
			Assert::AreEqual(int(m(4, 1)), 9);
			Assert::AreEqual(int(m(3, 0)), 6);
			Assert::AreEqual(int(m(1, 1)), 3);
		}
		TEST_METHOD(TestMethod3)
		{
			//срез со сложением
			matrix m(2, 5);
			for (int i = 0; i < 2; i++)
				for (int j = 0; j < 5; j++)
					m(i, j) = i + j * 2;

			matrix n(2, 3);
			for (int i = 0; i < 2; i++)
				for (int j = 0; j < 3; j++)
					n(i, j) = i + j * 3;

			matrix res(2, 3);
			res = n + m.slice(0, 1, 1, 0, 4, 2);
			Assert::AreEqual(int(res(0, 0)), 0);
			Assert::AreEqual(int(res(0, 1)), 7);
			Assert::AreEqual(int(res(0, 2)), 14);
			Assert::AreEqual(int(res(1, 0)), 2);
		}
		TEST_METHOD(TestMethod4)
		{
			//получить строку
			matrix m1(5, 5);
			for (int i = 0; i < 5; i++)
				for (int j = 0; j < 5; j++)
					m1(i, j) = i * j;

			matrix m2(1, 5);
			m2 = m1.getRow(3);

			Assert::AreEqual(int(m2(0, 2)), 6);
			Assert::AreEqual(int(m2(0, 3)), 9);
			Assert::AreEqual(int(m2(0, 4)), 12);
		}
		TEST_METHOD(TestMethod5)
		{
			//получить столбец
			matrix m1(5, 5);
			for (int i = 0; i < 5; i++)
				for (int j = 0; j < 5; j++)
					m1(i, j) = i * j;

			matrix m2(5, 1);
			m2 = m1.getCol(4);

			Assert::AreEqual(int(m2(2, 0)), 8);
			Assert::AreEqual(int(m2(3, 0)), 12);
			Assert::AreEqual(int(m2(4, 0)), 16);
		}
		TEST_METHOD(TestMethod6)
		{
			//сложение матриц
			matrix m1(3, 3);
			matrix m2(3, 3);
			for (int i = 0; i < 3; i++)
				for (int j = 0; j < 3; j++)
				{
					m1(i, j) = i * 2 + j;
					m2(i, j) = i * 3 + j;
				}

			matrix m3(3, 3);
			m3 = m1 + m2;

			Assert::AreEqual(int(m3(0, 0)), 0);
			Assert::AreEqual(int(m3(1, 1)), 7);
			Assert::AreEqual(int(m3(2, 2)), 14);
		}
		TEST_METHOD(TestMethod7)
		{
			//вычитание матриц
			matrix m1(3, 3);
			matrix m2(3, 3);
			for (int i = 0; i < 3; i++)
				for (int j = 0; j < 3; j++)
				{
					m2(i, j) = i * 2 + j;
					m1(i, j) = i * 3 + j;
				}

			matrix m3(3, 3);
			m3 = m1 - m2;

			Assert::AreEqual(int(m3(0, 0)), 0);
			Assert::AreEqual(int(m3(1, 1)), 1);
			Assert::AreEqual(int(m3(2, 2)), 2);
		}
		TEST_METHOD(TestMethod8)
		{
			//умножение матрицы на число
			matrix m(4, 4);
			for (int i = 0; i < 4; i++)
				for (int j = 0; j < 4; j++)
					m(i, j) = i * j;

			m = m * 3;
			Assert::AreEqual(int(m(0, 0)), 0);
			Assert::AreEqual(int(m(1, 1)), 3);
			Assert::AreEqual(int(m(2, 2)), 12);
			Assert::AreEqual(int(m(3, 3)), 27);
		}
		TEST_METHOD(Test_Method9)
		{
			//умножение матриц
			matrix m(2, 4);
			m(0,0) = 2;
			m(0,1) = 0;
			m(0,2) = 4;
			m(0,3) = -1;
			m(1,0) = 1;
			m(1,1) = -1;
			m(1,2) = 1;
			m(1,3) = 0;

			matrix m1(4, 1);
			m1(0,0) = 2;
			m1(1,0) = 1;
			m1(2,0) = 0;
			m1(3,0) = -2;

			matrix res(2, 1);
			res = m * m1;

			Assert::AreEqual(int(res(0, 0)), 6);
			Assert::AreEqual(int(res(1, 0)), 1);
		}
		TEST_METHOD(TestMethod10)
		{
			//срез с вычитанием
			matrix m(2, 5);
			for (int i = 0; i < 2; i++)
				for (int j = 0; j < 5; j++)
					m(i, j) = i + j * 2;

			matrix n(2, 3);
			for (int i = 0; i < 2; i++)
				for (int j = 0; j < 3; j++)
					n(i, j) = i + j * 3;

			matrix res = n - m.slice(0, 1, 1, 0, 4, 2);
			Assert::AreEqual(int(res(0, 0)), 0);
			Assert::AreEqual(int(res(0, 1)), -1);
			Assert::AreEqual(int(res(0, 2)), -2);
			Assert::AreEqual(int(res(1, 0)), 0);
		}
		TEST_METHOD(TestMethod11)
		{
			//срез с умножением
			matrix m(2, 5);
			for (int i = 0; i < 2; i++)
				for (int j = 0; j < 5; j++)
					m(i, j) = i + j * 2;

			matrix n(1, 3);
			n = m.slice(0, 0, 1, 0, 4, 2) * 5;

			Assert::AreEqual(int(n(0, 0)), 0);
			Assert::AreEqual(int(n(0, 1)), 20);
			Assert::AreEqual(int(n(0, 2)), 40);
		}
		TEST_METHOD(TestMethod12)
		{
			//вычитание срезов
			matrix m(2, 5);
			for (int i = 0; i < 2; i++)
				for (int j = 0; j < 5; j++)
					m(i, j) = i + j * 2;

			matrix n(2, 5);
			for (int i = 0; i < 2; i++)
				for (int j = 0; j < 5; j++)
					n(i, j) = i + j * 3;

			matrix res(1, 3);
			res = n.slice(0, 0, 1, 0, 4, 2) - m.slice(0, 0, 1, 0, 4, 2);

			Assert::AreEqual(int(res(0, 0)), 0);
			Assert::AreEqual(int(res(0, 1)), 2);
			Assert::AreEqual(int(res(0, 2)), 4);
		}
		TEST_METHOD(TestMethod13)
		{
			//сложение срезов
			matrix m(2, 5);
			for (int i = 0; i < 2; i++)
				for (int j = 0; j < 5; j++)
					m(i, j) = i + j * 2;

			matrix n(2, 5);
			for (int i = 0; i < 2; i++)
				for (int j = 0; j < 5; j++)
					n(i, j) = i + j * 3;

			matrix res(1, 3);
			res = n.slice(0, 0, 1, 0, 4, 2) + m.slice(0, 0, 1, 0, 4, 2);

			Assert::AreEqual(int(res(0, 0)), 0);
			Assert::AreEqual(int(res(0, 1)), 10);
			Assert::AreEqual(int(res(0, 2)), 20);
		}
		TEST_METHOD(TestMethod14)
		{
			//умножение срезов
			matrix m(2, 5);
			for (int i = 0; i < 2; i++)
				for (int j = 0; j < 5; j++)
					m(i, j) = i + j * 2;

			matrix n(2, 5);
			for (int i = 0; i < 2; i++)
				for (int j = 0; j < 5; j++)
					n(i, j) = i + j * 3;

			matrix res(1, 1);
			res = n.slice(1, 1, 1, 0, 4, 3) * m.slice(0, 1, 1, 0, 0, 1);
			
			Assert::AreEqual(int(res(0, 0)), 10);
		}
		TEST_METHOD(TestMethod15)
		{
			//транспонирование среза
			matrix m(3, 3);
			for (int i = 0; i < 3; i++)
				for (int j = 0; j < 3; j++)
					m(i, j) = i + j * 2;

			matrix res = m.slice(0, 0, 1, 0, 2, 2).transp() * 3;
			
			Assert::AreEqual(int(res(1, 0)), 12);
		}
		TEST_METHOD(TestMethod16)
		{
			//строка среза
			matrix m(3, 3);
			for (int i = 0; i < 3; i++)
				for (int j = 0; j < 3; j++)
					m(i, j) = i + j * 2;

			matrix res = m.slice(0, 2, 1, 0, 2, 2).getRow(1) * 2;

			Assert::AreEqual(int(res(0, 0)), 2);
			Assert::AreEqual(int(res(0, 1)), 6);
		}
		TEST_METHOD(TestMethod17)
		{
			matrix m(3, 3);
			for (int i = 0; i < 3; i++)
				for (int j = 0; j < 3; j++)
					m(i, j) = i + j * 2;
			matrix _m(3, 3);
			for (int i = 0; i < 3; i++)
				for (int j = 0; j < 3; j++)
					_m(i, j) = i + j * 3;

			m.slice(0, 2, 1, 0, 2, 2) = _m.slice(0, 2, 1, 1, 2, 1);

			Assert::AreEqual(int(m(0, 0)), 3);
			Assert::AreEqual(int(m(0, 2)), 6);
			Assert::AreEqual(int(m(1, 0)), 4);
			Assert::AreEqual(int(m(1, 2)), 7);
			Assert::AreEqual(int(m(2, 0)), 5);
			Assert::AreEqual(int(m(2, 2)), 8);
		}
	};
}