// lab2_2.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "lab2_2.h"

int main()
{
	t_list<int> l;
	t_list<int>::t_iter it;
	
	for (int i = 0; i < 5; i++)
		l.add_front(i);

	std::cout << *l.get_nth(3) << " ";
	
	for (it = l.begin(); it != l.end(); ++it)
		std::cout << it.node->value << " ";

	system("pause");
    return 0;
}