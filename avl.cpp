/*
پیاده سازی و اجرای درخت AVL

*/
#include<iostream>
#include<cstdio>
#include<sstream>
#include<algorithm>
#define pow2(n) (1 << (n))
using namespace std;

/*
اعلان کلاس گره
*/
struct avl_node
{
	int data;
	struct avl_node *left;
	struct avl_node *right;
}*root;

/*
اعلان کلاس درخت avl
*/
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
		cout << "1.Afzoodane onsor be derakht " << endl;//قرار دادن عنصر به درخت
		cout << "2.Namayesh motavazene derakht" << endl;//نمایش متوازن درخت
		cout << "3.Peymayesh InOrder " << endl;//پیمایش میان ترتیب
		cout << "4. Peymayesh PreOrder " << endl;//پیمایش پس ترتیب
		cout << "5. Peymayesh PostOrder " << endl;//پیمایش پیش ترتیب
		cout << "6.Khorooj" << endl;//خروج
		cout << "Gozine morede nazar ra vared konid: ";
		cin >> choice;//وارد کردن گزینه مورد نظر
		switch (choice)
		{
		case 1:
			cout << "Onsore mored nazar ra vared konid: ";//اضافه کردن عنصر با انتخاب گزینه اول
			cin >> item;
			root = avl.insert(root, item);
			break;
		case 2://نمایش درخت با وارد کردن گزینه دوم
			if (root == NULL)
			{
				cout << "Derakht khali ast" << endl;
				continue;
			}
			cout << "Derakhte motavazen shode:" << endl;
			avl.display(root, 1);
			break;
		case 3://پیمایش میان ترتیب با انتخاب گزینه سوم
			cout << " Peymayesh Inorder:" << endl;
			avl.inorder(root);
			cout << endl;
			break;
		case 4:// پیمایش پس ترتیب با انتخاب گزینه چهارم
			cout << " Peymayesh Preorder:" << endl;
			avl.preorder(root);
			cout << endl;
			break;
		case 5:// پیمایش پیش ترتیب با انتخاب گزینه پنجم
			cout << " Peymayesh Postorder:" << endl;
			avl.postorder(root);
			cout << endl;
			break;
		case 6://خروج با گزینه ششم
			exit(1);
			break;
		default://انتخاب گزینه غیر مجاز
			cout << "Gozine vared shode eshtebah ast!" << endl;
		}
	}
	return 0;
}

/*
پیاده سازی متد ارتفاع درخت
*/
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

/*
پیاده سازی متد اختلاف ارتفاع زیر دخت چپ ریشه با زیر درخت راست ریشه
*/
int avlTree::diff(avl_node *temp)
{
	int l_height = height(temp->left);
	int r_height = height(temp->right);
	int e = l_height - r_height;
	return e;
}

/*
پیاده سازی متد چرخش راست راست
*/
avl_node *avlTree::rr_rotation(avl_node *parent)
{
	avl_node *temp;
	temp = parent->right;
	parent->right = temp->left;
	temp->left = parent;
	return temp;
}
/*
پیاده سازی متد چرخش چپ چپ
*/
avl_node *avlTree::ll_rotation(avl_node *parent)
{
	avl_node *e;
	e = parent->left;
	parent->left = e->right;
	e->right = parent;
	return e;
}

/*
پیاده سازی متد چرخش چپ راست
*/
avl_node *avlTree::lr_rotation(avl_node *parent)
{
	avl_node *e;
	e = parent->left;
	parent->left = rr_rotation(e);
	return ll_rotation(parent);
}

/*
پیاده سازی متد چرخش راست چپ
*/
avl_node *avlTree::rl_rotation(avl_node *parent)
{
	avl_node *e;
	e = parent->right;
	parent->right = ll_rotation(e);
	return rr_rotation(parent);
}

/*
پیاده سازی متد متعادل کردن درخت
*/
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

/*

پیاده سازی متد درج در درخت:
ابتدا بررسی میشود که نود جدید در سمت چپ ریشه درج شود و یا راست و این کار به صورت بازگشتی تکرار میشود تا مکان مناسب جدید پیدا شودو نود جدید در آنجا درج میشود .
سپس آنها را چک میکنیم که چه چرخشی باید انجام شود
*/
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

/*
پیاده سازی متد نمایش درخت
*/
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

/*
پیاده سازی متد پیمایش میان ترتیب درخت
*/
void avlTree::inorder(avl_node *tree)
{
	if (tree == NULL)
		return;
	inorder(tree->left);
	cout << tree->data << "  ";
	inorder(tree->right);
}
/*
پیاده سازی متد پیمایش پس ترتیب درخت */
void avlTree::preorder(avl_node *tree)
{
	if (tree == NULL)
		return;
	cout << tree->data << "  ";
	preorder(tree->left);
	preorder(tree->right);

}

/*
پیاده سازی متد پیمایش پیش ترتیب درخت */
void avlTree::postorder(avl_node *tree)
{
	if (tree == NULL)
		return;
	postorder(tree->left);
	postorder(tree->right);
	cout << tree->data << "  ";
}
ترتیب اعداد وارد شده: ۵ ۴ ۳ ۲ ۱ ۹ ۸// 
