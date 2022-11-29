#include <stdio.h>
#include "binary_search_tree.h"

BST::BST()
{
	root = nullptr;
}

BST::add(int data)
{
	if (root == nullptr)
	{
		root = new BTNode();
		root->data = data;
		root->left = nullptr;
		root->right = nullptr;
	}
	else
	{

	}
}