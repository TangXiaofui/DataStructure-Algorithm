#include <iostream>
using namespace std;

struct TreeNode
{
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int v = 0) :val(v), left(nullptr), right(nullptr) {}
	~TreeNode()
	{
		cout << "~~~~~~~~~~~~~" << val << endl;
	}
};


class BinaryTree
{
public:
	BinaryTree() :root(nullptr) {}
	~BinaryTree();
	void Insert(int val);
	void Delete(int val);
	bool Search(int val);
	void inOrder();
	TreeNode* findMin(TreeNode *root);


private:
	void inOrder(TreeNode* root);
	bool find(TreeNode* root, int val);
	void clear(TreeNode *root);
	void remove(TreeNode *&root, int val);

	TreeNode *insert(TreeNode *root, int val);
	TreeNode *root;
};

BinaryTree::~BinaryTree()
{
	clear(root);
}

void BinaryTree::clear(TreeNode *root)
{
	if (root == nullptr)
		return;
	clear(root->left);
	clear(root->right);
	delete root;
}

void BinaryTree::Insert(int val)
{
	if (root == nullptr)
	{
		root = new TreeNode(val);
	}
	else
	{
		insert(root, val);
	}
}

TreeNode* BinaryTree::insert(TreeNode *root, int val)
{
	if (root == nullptr)
	{
		return new TreeNode(val);
	}
	if (root->val > val)
	{
		root->left = insert(root->left, val);
	}
	else
	{
		root->right = insert(root->right, val);
	}
	return root;
}

void BinaryTree::Delete(int val)
{
	remove(root, val);
}

void BinaryTree::remove(TreeNode * &root, int val)
{
	if (root == nullptr)
	{
		return;
	}
	if (val < root->val)
	{
		remove(root->left, val);
	}
	else if (val > root->val)
	{
		remove(root->right, val);
	}
	else if (root->left != nullptr && root->right != nullptr)
	{
		root->val = findMin(root->right)->val;
		remove(root->right, root->val);
	}
	else
	{
		TreeNode *old = root;
		root = (root->left != nullptr) ? root->left : root->right;
		delete old;
	}
}
bool BinaryTree::Search(int val)
{
	return find(root, val);
}

TreeNode* BinaryTree::findMin(TreeNode *root)
{
	if (root == nullptr)
	{
		return nullptr;
	}
	if (root->left == nullptr)
		return root;
	return findMin(root->left);
}

bool BinaryTree::find(TreeNode* root, int val)
{
	if (root == nullptr)
	{
		return false;
	}
	if (root->val == val)
	{
		return true;
	}
	else if (root->val > val)
	{
		return find(root->left, val);
	}
	else
	{
		return find(root->right, val);
	}
}
void BinaryTree::inOrder()
{
	inOrder(root);
}


void BinaryTree::inOrder(TreeNode* root)
{
	if (root == nullptr)
		return;
	inOrder(root->left);
	cout << root->val << endl;
	inOrder(root->right);

}

int main()
{
	BinaryTree s;
	s.Insert(3);
	s.Insert(1);
	s.Insert(2);
	s.Insert(5);
	s.inOrder();
	cout << "--------------------" << endl;
	s.Delete(3);
	s.inOrder();
	cout << "--------------------" << endl;
	cout << s.Search(4) << endl;
	cout << s.Search(1) << endl;
	cout << s.Search(2) << endl;
	cout << "----------------" << endl;


}