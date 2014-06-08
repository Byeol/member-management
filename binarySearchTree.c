#include "binarySearchTree.h"

NODE * createNode(int key, NODEDATA * value)
{
	NODE * node = malloc(sizeof(NODE));
	node->key = key;
	node->value = value;
	node->parent = NULL;
	node->left = NULL;
	node->right = NULL;
	return node;
}

NODE * findNode(NODE * rootNode, int key)
{
	if (rootNode == NULL)
		return NULL;

	if (key == rootNode->key)
		return rootNode;
	else if (key < rootNode->key)
		return findNode(rootNode->left, key);
	else if (key > rootNode->key)
		return findNode(rootNode->right, key);
}

void insertNode(NODE * rootNode, int key, NODEDATA * value)
{
	NODE * newNode = createNode(key, value);
	NODE * parentNode = findParentNode(rootNode, key);
	if (parentNode == NULL)
	{
		throwException(1);
		return;
	}
	newNode->parent = parentNode;

	if (key < parentNode->key && !parentNode->left)
		parentNode->left = newNode;
	else if (key > parentNode->key && !parentNode->right)
		parentNode->right = newNode;
	else
		throwException(2);
}

void deleteNode(NODE * rootNode, int key)
{
	NODE * targetNode = findNode(rootNode, key);
	NODE * successorNode;

	if (targetNode == NULL)
		return;

	if (targetNode->left && targetNode->right) // both children
	{
		successorNode = findMinNode(targetNode->right);
		targetNode->key = successorNode->key;
		targetNode->value = successorNode->value;
		deleteNode(successorNode, successorNode->key);
	}
	else if (targetNode->left) // only left child
		replaceNodeInParent(targetNode, targetNode->left);
	else if (targetNode->right) // only right child
		replaceNodeInParent(targetNode, targetNode->right);
	else // no children
		replaceNodeInParent(targetNode, NULL);
}

void traverseNode(NODE * rootNode, void(*callbackFunc)(NODEDATA *))
{
	if (rootNode == NULL)
		return;

	traverseNode(rootNode->left, callbackFunc);
	callbackFunc(rootNode->value);
	traverseNode(rootNode->right, callbackFunc);
}

static NODE * findParentNode(NODE * rootNode, int key)
{
	NODE ** targetPos = NULL;

	if (!rootNode)
		return NULL;

	if (key < rootNode->key)
		targetPos = &(rootNode->left);
	else if (key > rootNode->key)
		targetPos = &(rootNode->right);
	else if (key == rootNode->key)
		return NULL;

	if (*targetPos)
		return findParentNode(*targetPos, key);
	else
		return rootNode;
}

static NODE * findMinNode(NODE * rootNode)
{
	NODE * curNode = rootNode;

	while (curNode->left)
		curNode = curNode->left;

	return curNode;
}

static void replaceNodeInParent(NODE * node, NODE * destNode)
{
	NODE ** targetPos = NULL;

	if (node->parent)
	{
		if (node->parent->left == node)
			node->parent->left = destNode;
		else if (node->parent->right == node)
			node->parent->right = destNode;

		if (destNode)
			destNode->parent = node->parent;
	}
}