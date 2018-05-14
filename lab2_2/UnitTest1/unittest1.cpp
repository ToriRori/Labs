#include "stdafx.h"
#include "CppUnitTest.h"
#include "../lab2_2/lab2_2.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			//добавление в начало списка
			try {
				t_list<int> l;
				t_list<int>::t_iter it;
				int i;

				for (i = 0; i < 5; i++)
					l.add_front(i);
				i--;

				for (it = l.begin(); it != l.end(); ++it)
					Assert::AreEqual(*it, i--);
			}
			catch (t_list<int>::excp e)
			{
				e.print();
			}
		}
		TEST_METHOD(TestMethod2)
		{
			//добавление в конец списка
			try
			{
				t_list<int> l;
				t_list<int>::t_iter it;
				int i;

				for (i = 0; i < 5; i++)
					l.add_rear(i);
				i = 0;

				for (it = l.begin(); it != l.end(); ++it)
					Assert::AreEqual(*it, i++);
			}
			catch (t_list<int>::excp e)
			{
				e.print();
			}
		}
		TEST_METHOD(TestMethod3)
		{
			//удаление из начала списка
			try
			{
				t_list<int> l;
				t_list<int>::t_iter it;
				int i;

				for (i = 0; i < 5; i++)
					l.add_front(i);

				i = 2;
				l.remove_front();
				l.remove_front();

				for (it = l.begin(); it != l.end(); ++it)
					Assert::AreEqual(*it, i--);
			}
			catch (t_list<int>::excp e)
			{
				e.print();
			}
		}
		TEST_METHOD(TestMethod4)
		{
			//удаление из конца списка
			try
			{
				t_list<int> l;
				t_list<int>::t_iter it;
				int i;

				for (i = 0; i < 5; i++)
					l.add_front(i);

				i--;
				l.remove_rear();
				l.remove_rear();

				for (it = l.begin(); it != l.end(); ++it)
					Assert::AreEqual(*it, i--);
			}
			catch (t_list<int>::excp e)
			{
				e.print();
			}
		}
		TEST_METHOD(TestMethod5)
		{
			//вставка после i-ого элемента
			try
			{
				t_list<int> l;
				t_list<int>::t_iter it;
				int i;

				for (i = 0; i < 5; i++)
					l.add_front(i);

				i = 0;
				for (it = l.begin(); it != l.end(); ++it)
				{
					if (it.node->value == 3)
						l.insert_after(5, it);
					if (i == 2)
						Assert::AreEqual(*it, 5);
					i++;
				}
			}
			catch (t_list<int>::excp e)
			{
				e.print();
			}
		}
		TEST_METHOD(TestMethod6)
		{
			//удаление i-ого элемента
			try
			{
				t_list<int> l;
				t_list<int>::t_iter it;
				int i;

				for (i = 0; i < 5; i++)
					l.add_front(i);

				i--;
				for (it = l.begin(); it != l.end(); ++it)
					if (it.node->value == 3)
					{
						l.remove_it(it);
						break;
					}

				for (it = l.begin(); it != l.end(); ++it)
					if (i != 3)
						Assert::AreEqual(*it, i--);
			}
			catch (t_list<int>::excp e)
			{
				e.print();
			}
		}
		TEST_METHOD(TestMethod7)
		{
			//поиск элемента в списке
			try
			{
				t_list<int> l;
				t_list<int>::t_iter it;
				int i;

				for (i = 0; i < 5; i++)
					l.add_front(i);
				Assert::AreEqual(l.find(3), true);
				Assert::AreEqual(l.find(6), false);
			}
			catch (t_list<int>::excp e)
			{
				e.print();
			}
		}
		TEST_METHOD(TestMethod8)
		{
			//поиск по номеру элемента
			try
			{
				t_list<int> l;
				t_list<int>::t_iter it;
				int i;

				for (i = 0; i < 5; i++)
					l.add_front(i);

				Assert::AreEqual(*l.get_nth(3), 2);
			}
			catch (t_list<int>::excp e)
			{
				e.print();
			}
		}
		TEST_METHOD(TestMethod9)
		{
			//размерность списка
			try
			{
				t_list<int> l;
				t_list<int>::t_iter it;
				int i;

				for (i = 0; i < 5; i++)
					l.add_front(i);

				l.add_front(10);
				l.add_front(99);

				Assert::AreEqual(l.size(), (size_t)7);
			}
			catch (t_list<int>::excp e)
			{
				e.print();
			}
		}
	};
}