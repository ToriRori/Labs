#include "stdafx.h"
#include "CppUnitTest.h"
#include "..\lab_1_2\lab_1_2.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			//изначально занулены элементы
			bit_Arr bA(4, 3);
			Assert::AreEqual(int(bA[0]), 0);
			Assert::AreEqual(int(bA[1]), 0);
			Assert::AreEqual(int(bA[2]), 0);
			Assert::AreEqual(int(bA[3]), 0);
		}
		TEST_METHOD(TestMethod2)
		{
			//изменение битности
			bit_Arr bA(2, 6);
			bA[0] = 12;
			bA.change_Bit(3);
			bA[0] = 6;
			Assert::AreEqual(int(bA[1]), 4);
		}
		TEST_METHOD(TestMethod3)
		{
			//присваивание
			bit_Arr bA(14, 3);
			bA[0] = 0;
			bA[1] = 1;
			bA[2] = 3;
			bA[3] = 7;
			Assert::AreEqual(int(bA[0]), 0);
			Assert::AreEqual(int(bA[1]), 1);
			Assert::AreEqual(int(bA[2]), 3);
			Assert::AreEqual(int(bA[3]), 7);
		}
		TEST_METHOD(TestMethod4)
		{
			//конструктор копирования
			bit_Arr bA1(5, 2);
			bA1[0] = 3;
			bA1[2] = 1;
			bit_Arr bA2(bA1);
			Assert::AreEqual(int(bA2[0]), 3);
			Assert::AreEqual(int(bA2[2]), 1);
		}
		TEST_METHOD(TestMethod5)
		{
			//подмассив c нулевого
			bit_Arr bA1(3, 3);
			bit_Arr bA2(2, 3);
			bA1[0] = 3;
			bA1[2] = 7;
			bA2(bA1, 0, 1);
			Assert::AreEqual(int(bA2[0]), 3);
			Assert::AreEqual(int(bA2[1]), 0);
		}
		TEST_METHOD(TestMethod6)
		{
			//подмассив не с нулевого
			bit_Arr bA1(7, 3);
			bit_Arr bA2(3, 3);
			bA1[0] = 3;
			bA1[2] = 7;
			bA1[5] = 6;
			bA2(bA1, 4, 6);
			Assert::AreEqual(int(bA2[0]), 0);
			Assert::AreEqual(int(bA2[1]), 6);
			Assert::AreEqual(int(bA2[2]), 0);
		}
		TEST_METHOD(TestMethod7)
		{
			//изменение длины - уменьшение
			bit_Arr bA(4, 3);
			bA[0] = 3;
			bA[2] = 7;
			bA[3] = 2;
			bA.change_Size(3);
			Assert::AreEqual(int(bA[0]), 3);
			Assert::AreEqual(int(bA[1]), 0);
			Assert::AreEqual(int(bA[2]), 7);
		}
		TEST_METHOD(TestMethod8)
		{
			//изменение длины - увеличение
			bit_Arr bA(4, 3);
			bA[0] = 3;
			bA[2] = 7;
			bA[3] = 2;
			bA.change_Size(7);
			Assert::AreEqual(int(bA[0]), 3);
			Assert::AreEqual(int(bA[2]), 7);
			Assert::AreEqual(int(bA[3]), 2);
			Assert::AreEqual(int(bA[4]), 0);
			Assert::AreEqual(int(bA[5]), 0);
			Assert::AreEqual(int(bA[6]), 0);
		}
	};
}