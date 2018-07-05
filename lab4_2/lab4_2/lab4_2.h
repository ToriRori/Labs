#include <iostream>

template<typename T>
struct t_tree {
	struct t_iter;
	struct t_node;
	friend struct t_iter;
	friend struct t_node;
public:
	struct t_node
	{
		friend struct t_tree::t_iter;
		T key;
		unsigned char height;
		t_node* left;
		t_node* right;
		t_node* parent;
		t_tree<T>::t_iter* iter = nullptr;
		int count = 0;
		t_node(T k) { count = 1; key = k; left = right = parent = nullptr; height = 1; }
	};

	struct t_iter {
		friend struct t_tree::t_node;
		t_iter() {}
		t_iter(t_node *t) : node(t), flag(false) { set(t); }
		t_iter(t_node *t, bool f) : flag(f), node(t) { set(t); }
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
			if ((node == it.node) && (!this->flag))
			{
				flag = true;
				return true;
			}
			return (node != it.node);
		}

		bool isValid() { return (node != nullptr); }

		t_iter& operator++()
		{
			if (flag)
				return *this;

			t_node *next_node;
			if (node->right != nullptr)
				if (node->right->left != nullptr)
				{
					t_node *n = node->right->left;
					while (n->left != nullptr)
						n = n->left;
					next_node = n;
				}
				else
					next_node = node->right;
			else
				if (node->parent != nullptr)
					if (node->key > node->parent->key)
					{
						t_node *n = node;
						while (n->key > n->parent->key)
							n = node->parent;
						next_node = n->parent;
					}
					else
						next_node = node->parent;
				else
				{
					std::cout << "Err";
					exit(1);
				}
			//t_node *next_node = node->next;
			off();
			if (next_node != nullptr)
				set(next_node);
			return *this;
		}

		t_iter& operator--()
		{
			if (flag)
				return *this;

			t_node *next_node;
			if (node->left != nullptr)
				if (node->left->right != nullptr)
				{
					t_node *n = node->left->right;
					while (n->right != nullptr)
						n = n->right;
					next_node = n;
				}
				else
					next_node = node->left;
			else
				if (node->parent != nullptr)
					if (node->key > node->parent->key)
					{
						t_node *n = node;
						while ((n->parent->parent != nullptr) && (n->key > n->parent->key))
							n = node->parent;
						next_node = n->parent;
					}
					else
						next_node = node->parent;
				else
				{
					std::cout << "Err";
					exit(1);
				}

			//t_node *prev_node = node->last;
			off();
			if (next_node != nullptr)
				set(next_node);
			return *this;
		}

		T operator*()
		{
			return node->key;
		}

		t_node *node = nullptr;
		t_iter *next = nullptr, *last = nullptr;
		bool flag;
	};

	t_node *head;

	t_tree(T k) { head = new t_node(k); }
private:
	unsigned char height(t_node* p)
	{
		return p ? p->height : 0;
	}

	int bfactor(t_node* p)
	{
		return height(p->right) - height(p->left);
	}

	void fixheight(t_node* p)
	{
		unsigned char hl = height(p->left);
		unsigned char hr = height(p->right);
		p->height = (hl>hr ? hl : hr) + 1;
	}

	t_node* rotateright(t_node* p)
	{
		t_node* q = p->left;
		p->left = q->right;
		q->right = p;
		fixheight(p);
		fixheight(q);
		return q;
	}

	t_node* rotateleft(t_node* q)
	{
		t_node* p = q->right;
		q->right = p->left;
		p->left = q;
		fixheight(q);
		fixheight(p);
		return p;
	}

	t_node* balance(t_node* p)
	{
		fixheight(p);
		if (bfactor(p) == 2)
		{
			if (bfactor(p->right) < 0)
				p->right = rotateright(p->right);
			return rotateleft(p);
		}
		if (bfactor(p) == -2)
		{
			if (bfactor(p->left) > 0)
				p->left = rotateleft(p->left);
			return rotateright(p);
		}
		head = p;
		return p;
	}
public:
	t_node* insert(t_node * p, T k)
	{
		if (p == nullptr) {
			p = new t_node(k);
			p = p;
			return p;
		}
		if (k == p->key)
		{
			p->count++;
			return p;
		}
		if (k < p->key)
		{
			if (p->left == nullptr)
			{
				p->left = new t_node(k);
				p->left->parent = p;
			}
			else
				p->left = insert(p->left, k);
		}
		else
		{
			if (p->right == nullptr)
			{
				p->right = new t_node(k);
				p->right->parent = p;
			}
			else
				p->right = insert(p->right, k);
		}
		return balance(p);
	}
private:
	t_node* findmin(t_node* p)
	{
		return p->left ? findmin(p->left) : p;
	}

	t_node* removemin(t_node* p)
	{
		if (p->left == nullptr)
			return p->right;
		p->left = removemin(p->left);
		return balance(p);
	}

	t_iter find_elem(T x, t_node* n)
	{
		if (x < n->key)
			return find_elem(x, n->left);
		else
			if (x > n->key)
				return find_elem(x, n->right);
			else
				return t_iter(n, false);
	}

public:
	t_node* remove(t_node* p, T k)
	{
		if (!p) return 0;
		if (k < p->key)
			p->left = remove(p->left, k);
		else if (k > p->key)
			p->right = remove(p->right, k);
		else
		{
			if (p->count > 1)
				p->count--;
			else
			{
				t_node* par = p->parent;
				t_node* q = p->left;
				t_node* r = p->right;
				delete p;
				if (par != nullptr)
					if ((r != nullptr) && (par->key > r->key))
						par->left = nullptr;
					else
						par->right = nullptr;
				if (!r) return q;
				t_node* min = findmin(r);
				min->right = removemin(r);
				min->left = q;
				return balance(min);
			}
		}
		return balance(p);
	}

	void del(t_iter &t)
	{
		remove(t.node, t.node->key);
		t.off();
	}

	t_iter find(T x)
	{
		return find_elem(x, head);
	}

	
	t_iter begin()
	{
		t_node *n = head;
		if (n->left == nullptr)
			return t_iter(n, false);
		while (n->left != nullptr)
			n = n->left;
		return t_iter(n, false);
	}

	t_iter end()
	{
		t_node *n = head;
		if (n->right == nullptr)
			return t_iter(n, false);
		while (n->right != nullptr)
			n = n->right;
		return t_iter(n, false);
	}
};