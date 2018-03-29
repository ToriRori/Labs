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
		}

	};
}