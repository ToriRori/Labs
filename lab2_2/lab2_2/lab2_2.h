#pragma once
// lab2_2.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>

template <typename T>
struct t_list
{
public:
	struct t_node;
	friend struct t_node;
	struct t_iter;
	friend struct t_iter;

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
		}
	};

	struct t_node
	{
		friend struct t_list;
		friend struct t_iter;
		t_node() {}
		t_node(int n) : value(n) {}
		~t_node() {}
		T value;
		t_node *last = nullptr, *next = nullptr;
		t_iter *iter = nullptr;
	};

	struct t_iter {
		friend struct t_list;
		friend struct t_iter;

		t_iter() {}
		t_iter(t_node *t) : node(t) { set(t); }
		t_iter(t_node *t, bool f): flag(f) { set(t); }
		~t_iter() { off(); }

		void off()
		{
			if (node == nullptr)
				return;
			if (last == nullptr)
				node->iter = next;
			else
				last->next = next;
			if (next != nullptr)
				next->last = last;
		}

		void set(t_node * new_node)
		{
			next = new_node->iter;
			new_node->iter = this;
			this->node = new_node;
		}

		t_iter& operator=(const t_iter &it)
		{
			if (*this == it)
				return *this;

			off();
			set(it.node);
			//node = it.node;
			//next = it.next;
			//last = it.last;
			return *this;
		}

		bool operator == (const t_iter &it) 
		{
			if ((node == it.node) && (!this->flag))
			{
				flag = true;
				return true;
			}

			return (node == it.node); 
		}

		bool operator != (const t_iter &it) 
		{ 
			if ((node == it.node)&&(!this->flag))
			{
				flag = true;
				return true;
			}
			return (node != it.node); 
		}

		bool isValid() { return (node != nullptr); }

		t_iter& operator++() throw (excp)
		{
			if (flag)
				return *this;

			if (node == nullptr)
				throw excp(1);

			t_node *next_node = node->next;
			off();
			if (next_node != nullptr)
				set(next_node);
			return *this;
		}

		t_iter& operator--()
		{
			if (flag)
				return *this;

			if (node == nullptr)
				throw excp(1);

			t_node *prev_node = node->last;
			off();
			if (prev_node != nullptr)
				set(prev_node);
			return *this;
		}

		T operator*() 
		{
			if (!isValid())
				throw 3;
			return node->value; 
		}

		friend t_list<T> operator+(t_list<T> a, t_list<T> b);
	
		t_node *node = nullptr;
		t_iter *next = nullptr, *last = nullptr;
		bool flag = false;
	};

	t_list() throw (std::bad_alloc)
	{
		//TODO: ...
		head = tail = nullptr;
	}

	t_list(T val) throw (std::bad_alloc)
	{
		head = tail = nullptr;
		next = nullptr;
		last = nullptr;
		add_front(val);
	}

	~t_list() throw (std::bad_alloc)
	{
		while (!empty()) 
		{
			remove_front();
		}
	}

	void add_front(T val) throw (std::bad_alloc)
	{
		if (empty())
		{
			t_node * add = new t_node(val);
			head = add;
			tail = add;
			list_size++;
			return ;
		}

		t_node * add = new t_node(val);
		add->next = head;
		add->last = nullptr;
		head->last = add;
		head = add;
		list_size++;
	}

	void add_rear(T val) throw (std::bad_alloc)
	{
		if (empty())
			add_front(val);
		else
		{
			t_node * add = new t_node(val);
			add->last = tail;
			add->next = nullptr;
			tail->next = add;
			tail = add;
		}
		list_size++;
	}

	bool insert_after(T node_val, t_iter &key_i) throw (std::bad_alloc)
	{
		for (t_node *dn = head; dn != tail; dn = dn->next)
		{
			if (dn == key_i.node)
			{
				t_node *node_to_add = new t_node(node_val);
				node_to_add->last = dn;
				node_to_add->next = dn->next;
				dn->next->last = node_to_add;
				dn->next = node_to_add;
				//key_i.set(node_to_add);
				list_size++;
				return true;
			}
		}
		return false;
	}

	T remove_front()
	{
		if (empty())
			throw excp(2);
	
		t_node *node_to_remove = head;
		T return_val = node_to_remove->value;
		head = node_to_remove->next;
		if (head != nullptr)
			head->last = nullptr;

		delete node_to_remove;
		list_size--;
		return return_val;
	}


	T remove_rear()
	{
		if (empty())
			throw excp(2);

		t_node *node_to_remove = tail;
		T return_val = node_to_remove->value;
		tail = node_to_remove->last;
		tail->next = nullptr;

		delete node_to_remove;
		list_size--;
		return return_val;
	}

	bool remove_it(t_iter &key_i)
	{
		for (t_node *dn = head; dn != tail; dn = dn->next)
		{
			if (dn == key_i.node)
			{
				dn->last->next = dn->next;
				dn->next->last = dn->last;
				delete dn;
				key_i.off();
				list_size--;
				return true;
			}
		}
		return false;
	}

	bool find(T node_val) const
	{
		for (t_node *dn = head; dn != tail; dn = dn->next)
		{
			if (dn->value == node_val)
				return true;
		}
		return false;
	}

	t_iter get_nth(const int element_num) const
	{
		if (element_num < 1)
			return NULL;

		int count = 1;
		for (t_node *dn = head; dn != tail; dn = dn->next)
		{
			if (count++ == element_num)
				return *(new t_iter(dn));
		}
		return NULL;
	}

	bool empty() {
		return head == nullptr;
	}

	size_t size() const
	{
		return list_size;
	}

	t_iter begin() { return t_iter(head, true); }
	t_iter end() { return t_iter(tail, true); }

private:
	t_node *head, *tail;
	size_t list_size = 0;
};


