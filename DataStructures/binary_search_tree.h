#ifndef __BST_H__
#define __BST_H__

// Binary Tree Node
typedef struct BTNode
{
	int data;
	BTNode *left;
	BTNode *right;
};

class BST
{
	BTNode *root;
public:
	BST();
	void add(int data);
};

#endif // __BST_H__

// pre order : 1 2 4 5 3 6 7
// in order  : 4 2 5 1 6 3 7
// post order: 4 5 2 6 7 3 1