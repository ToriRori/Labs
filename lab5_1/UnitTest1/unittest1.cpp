#include "stdafx.h"
#include "CppUnitTest.h"
#include "../lab5_1/lab5_1_2.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			int **a = new int *[2];
			int **b = new int *[3];
			int **c = new int *[2];
			for (int i = 0; i<2; i++)
				a[i] = new int[3];
			for (int i = 0; i<3; i++)
				b[i] = new int[2];
			for (int i = 0; i<2; i++)
				c[i] = new int[2];
			a[0][0] = -1;
			a[0][1] = 0;
			a[0][2] = 2;
			a[1][0] = 3;
			a[1][1] = 1;
			a[1][2] = -4;
			b[0][0] = -3;
			b[0][1] = 7;
			b[1][0] = 4;
			b[1][1] = 0;
			b[2][0] = 5;
			b[2][1] = -2;
			mult(a, b, c, 2, 3, 2);
			Assert::AreEqual(c[0][0], 13);
			Assert::AreEqual(c[0][1], -11);
			Assert::AreEqual(c[1][0], -25);
			Assert::AreEqual(c[1][1], 29);
		}

	};
}