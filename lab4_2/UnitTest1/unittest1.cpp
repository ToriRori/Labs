#include "stdafx.h"
#include "CppUnitTest.h"
#include "../lab4_2/lab4_2.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			t_tree<int> *Tree = new t_tree<int>(12);
			Tree->insert(Tree->head, 12);
			Tree->insert(Tree->head, 5);
			Tree->insert(Tree->head, 15);
			Tree->insert(Tree->head, 1);
			int i = 0;
			int mas[4] = { 1, 5, 12, 15 };
			for (t_tree<int>::t_iter it = Tree->begin(); it != Tree->end(); ++it)
				Assert::AreEqual(*it, mas[i++]);
		}
		TEST_METHOD(TestMethod2)
		{
			t_tree<int> *Tree = new t_tree<int>(12);
			Tree->insert(Tree->head, 12);
			Tree->insert(Tree->head, 5);
			Tree->insert(Tree->head, 15);
			Tree->insert(Tree->head, 1);
			int i = 0;
			int mas[4] = { 15, 12, 5, 1 };
			for (t_tree<int>::t_iter it = Tree->end(); it != Tree->begin(); --it)
				Assert::AreEqual(*it, mas[i++]);
		}
		TEST_METHOD(TestMethod3)
		{
			t_tree<int> *Tree = new t_tree<int>(12);
			Tree->insert(Tree->head, 12);
			Tree->insert(Tree->head, 15);
			Tree->insert(Tree->head, 1);
			int i = 0;
			int mas[4] = { 1, 12 };
			for (t_tree<int>::t_iter it = Tree->begin(); it != Tree->end(); ++it)
				if (*it == 15)
				{
					Tree->del(it);
					break;
				}
			for (t_tree<int>::t_iter it = Tree->begin(); it != Tree->end(); ++it)
				Assert::AreEqual(*it, mas[i++]);
		}

		TEST_METHOD(TestMethod4)
		{
			t_tree<int> *Tree = new t_tree<int>(12);
			Tree->insert(Tree->head, 12);
			Tree->insert(Tree->head, 5);
			Tree->insert(Tree->head, 15);
			Tree->insert(Tree->head, 1);
			int i = 0;
			int mas[4] = { 5, 12, 15 };
			for (t_tree<int>::t_iter it = Tree->find(5); it != Tree->end(); ++it)
				Assert::AreEqual(*it, mas[i++]);
		}
	};
}