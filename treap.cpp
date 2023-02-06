#include <iostream>
#include <cstdlib>
using namespace std;

typedef struct ctreenode *ctree;


struct ctreenode
{
	int key, fix;
	ctree left, right;
};
ctree nullnode, root;



class CTree
{
public:
	void initialize();
	void rl(ctree &);
	void rr(ctree &);
	void insert(ctree &, int);
	void remove(ctree &, int);
	void display(ctree, int);
	void inorder(ctree);
	bool find(ctree, int);
	CTree()
	{}
};


void CTree::initialize()
{
	nullnode = new ctreenode;
	nullnode->left = nullnode->right = nullnode;
	root = nullnode;
}



void CTree::rl(ctree& k1)
{
	ctree k2;
	k2 = k1->right;
	k1->right = k2->left;
	k2->left = k1;
	k1 = k2;
}



void CTree::rr(ctree& k1)
{
	ctree k2;
	k2 = k1->left;
	k1->left = k2->right;
	k2->right = k1;
	k1 = k2;
}


void CTree::insert(ctree& t, int x)
{
	if (t == nullnode)
	{
		t = new ctreenode;
		t->left = t->right = nullnode;
		t->key = x;
		t->fix = rand();
	}
	else
	{
		if (t->key == x)
		{
			return;
		}
		else
		{
			if (x < t->key)
			{
				insert(t->left, x);
				if (t->left->fix > t->fix)
					rr(t);
			}
			else
			{
				insert(t->right, x);
				if (t->right->fix > t->fix)
					rl(t);
			}
		}
	}
}



void CTree::remove(ctree& t, int x)
{
	if (t == nullnode)
		return;
	if (x > t->key)
		remove(t->right, x);
	else if (x < t->key)
		remove(t->left, x);
	else
	{
		if (t->left == nullnode && t->right == nullnode)
		{
			delete t;
			t = nullnode;
		}
		else if (t->left == nullnode)
		{
			ctree tmp = t;
			t = t->right;
			delete tmp;
		}
		else if (t->right == nullnode)
		{
			ctree tmp = t;
			t = t->left;
			delete tmp;
		}
		else
		{
			if (t->left->fix < t->right->fix)
			{
				rl(t);
				remove(t->left, x);
			}
			else
			{
				rr(t);
				remove(t->right, x);
			}
		}
	}
}


bool CTree::find(ctree t, int x)
{
	if (t == nullnode)
		return false;
	if (t->key == x)
		return true;
	else
	{
		if (x < t->key)
			return find(t->left, x);
		else
			return find(t->right, x);
	}
}


void CTree::display(ctree ptr, int level)
{
	int i;
	if (ptr == nullnode)
		return;
	if (ptr != NULL)
	{
		display(ptr->right, level + 1);
		cout << endl;
		if (ptr == root)
			cout << "Root->:  ";
		else
		{
			for (i = 0; i < level; i++)
				cout << "       ";
		}
		cout << ptr->key;
		display(ptr->left, level + 1);
	}
}


void CTree::inorder(ctree ptr)
{
	if (ptr == nullnode)
		return;
	if (ptr != NULL)
	{
		inorder(ptr->left);
		cout << ptr->key << "  ";
		inorder(ptr->right);
	}
}

int main()
{
	CTree ct;
	int choice, num;
	bool flag = false;
	ct.initialize();
	while (1)
	{
		cout << endl << "----------------------------" << endl;
		cout << endl << "Operations on Treap" << endl;
		cout << endl << "----------------------------" << endl;
		cout << "1.Darje onsor " << endl;
		cout << "2.Hazfe Onsor " << endl;
		cout << "3.Inorder Traversal" << endl;
		cout << "4.Namayesh" << endl;
		cout << "5.Khorooj" << endl;
		cout << "Gozine mored nazar ra vared konid : ";
		cin >> choice;
		switch (choice)
		{
		case 1:
			cout << "Adad ra baraye darj vared konid : ";
			cin >> num;
			ct.insert(root, num);
			break;
		case 2:
			if (root == nullnode)
			{
				cout << "Derakht khali ast, Chizi hazf nashod" << endl;
				continue;
			}
			cout << "Adad ra baraye hazf kardan vared konid : ";
			cin >> num;
			if (ct.find(root, num))
				flag = true;
			else
				cout << "Onsor peyda nashod" << endl;
			ct.remove(root, num);
			if (!ct.find(root, num) && flag)
				cout << "The element deleted" << endl;
			break;
		case 3:
			if (root == nullnode)
			{
				cout << "The tree is empty, enter the first element" << endl;
				continue;
			}
			cout << "Inorder Traversal:" << endl;
			ct.inorder(root);
			cout << endl;
			break;
		case 4:
			if (root == nullnode)
			{
				cout << "The tree is empty" << endl;
				continue;
			}
			cout << "Display Treap:" << endl;
			ct.display(root, 1);
			cout << endl;
			break;
		case 5:
			exit(1);
			break;
		default:
			cout << "Wrong choice" << endl;
		}
	}
} 
