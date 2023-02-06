
#include<iostream>
#include<cstdio>
#include<sstream>
#include<algorithm>
#define pow2(n) (1 << (n))
using namespace std;


struct avl_node
{
	int data;
	struct avl_node *left;
	struct avl_node *right;
}*root;


class avlTree
{
public:
	int height(avl_node *);
	int diff(avl_node *);
	avl_node *rr_rotation(avl_node *);
	avl_node *ll_rotation(avl_node *);
	avl_node *lr_rotation(avl_node *);
	avl_node *rl_rotation(avl_node *);
	avl_node* balance(avl_node *);
	avl_node* insert(avl_node *, int);
	void display(avl_node *, int);
	void inorder(avl_node *);
	void preorder(avl_node *);
	void postorder(avl_node *);
	avlTree()
	{
		root = NULL;
	}
};

int main()
{
	int choice, item;
	avlTree avl;
	while (1)
	{
		cout << "\n---------------------" << endl;
		cout << "AVL Tree Implementation" << endl;
		cout << "\n---------------------" << endl;
		cout << "1.Afzoodane onsor be derakht " << endl;//
		cout << "2.Namayesh motavazene derakht" << endl;//
		cout << "3.Peymayesh InOrder " << endl;//
		cout << "4. Peymayesh PreOrder " << endl;//
		cout << "5. Peymayesh PostOrder " << endl;//
		cout << "6.Khorooj" << endl;//
		cout << "Gozine morede nazar ra vared konid: ";
		cin >> choice;//
		switch (choice)
		{
		case 1:
			cout << "Onsore mored nazar ra vared konid: ";//
			cin >> item;
			root = avl.insert(root, item);
			break;
		case 2://
			if (root == NULL)
			{
				cout << "Derakht khali ast" << endl;
				continue;
			}
			cout << "Derakhte motavazen shode:" << endl;
			avl.display(root, 1);
			break;
		case 3://
			cout << " Peymayesh Inorder:" << endl;
			avl.inorder(root);
			cout << endl;
			break;
		case 4:// 
			cout << " Peymayesh Preorder:" << endl;
			avl.preorder(root);
			cout << endl;
			break;
		case 5:// 
			cout << " Peymayesh Postorder:" << endl;
			avl.postorder(root);
			cout << endl;
			break;
		case 6://
			exit(1);
			break;
		default://
			cout << "Gozine vared shode eshtebah ast!" << endl;
		}
	}
	return 0;
}


int avlTree::height(avl_node *temp)
{
	int h = 0;
	if (temp != NULL)
	{
		int l_height = height(temp->left);
		int r_height = height(temp->right);
		int max_height = max(l_height, r_height);
		h = max_height + 1;
	}
	return h;
}


int avlTree::diff(avl_node *temp)
{
	int l_height = height(temp->left);
	int r_height = height(temp->right);
	int e = l_height - r_height;
	return e;
}


avl_node *avlTree::rr_rotation(avl_node *parent)
{
	avl_node *temp;
	temp = parent->right;
	parent->right = temp->left;
	temp->left = parent;
	return temp;
}

avl_node *avlTree::ll_rotation(avl_node *parent)
{
	avl_node *e;
	e = parent->left;
	parent->left = e->right;
	e->right = parent;
	return e;
}


avl_node *avlTree::lr_rotation(avl_node *parent)
{
	avl_node *e;
	e = parent->left;
	parent->left = rr_rotation(e);
	return ll_rotation(parent);
}


avl_node *avlTree::rl_rotation(avl_node *parent)
{
	avl_node *e;
	e = parent->right;
	parent->right = ll_rotation(e);
	return rr_rotation(parent);
}


avl_node *avlTree::balance(avl_node *temp)
{
	int bal_factor = diff(temp);
	if (bal_factor > 1)
	{
		if (diff(temp->left) > 0)
			temp = ll_rotation(temp);
		else
			temp = lr_rotation(temp);
	}
	else if (bal_factor < -1)
	{
		if (diff(temp->right) > 0)
			temp = rl_rotation(temp);
		else
			temp = rr_rotation(temp);
	}
	return temp;
}



avl_node *avlTree::insert(avl_node *root, int value)
{
	if (root == NULL)
	{
		root = new avl_node;
		root->data = value;
		root->left = NULL;
		root->right = NULL;
		return root;
	}
	else if (value < root->data)
	{
		root->left = insert(root->left, value);
		root = balance(root);
	}
	else if (value >= root->data)
	{
		root->right = insert(root->right, value);
		root = balance(root);
	}
	return root;
}



void avlTree::display(avl_node *ptr, int level)
{
	int i;
	if (ptr != NULL)
	{
		display(ptr->right, level + 1);
		printf("\n");
		if (ptr == root)
			cout << "Root -> ";
		for (i = 0; i < level && ptr != root; i++)
			cout << "        ";
		cout << ptr->data;
		display(ptr->left, level + 1);
	}
}



void avlTree::inorder(avl_node *tree)
{
	if (tree == NULL)
		return;
	inorder(tree->left);
	cout << tree->data << "  ";
	inorder(tree->right);
}


void avlTree::preorder(avl_node *tree)
{
	if (tree == NULL)
		return;
	cout << tree->data << "  ";
	preorder(tree->left);
	preorder(tree->right);

}


void avlTree::postorder(avl_node *tree)
{
	if (tree == NULL)
		return;
	postorder(tree->left);
	postorder(tree->right);
	cout << tree->data << "  ";
}
