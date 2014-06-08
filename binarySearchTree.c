#include "binarySearchTree.h"

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

NODE * createNode(int key, NODEDATA * value)
{
	NODE * node = malloc(sizeof(NODE));
	node->key = key;
	node->value = value;
	node->left = NULL;
	node->right = NULL;
	return node;
}

NODE ** findPosition(NODE * rootNode, int key)
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
		return findPosition(*targetPos, key);
	else
		return targetPos;
}

void insertNode(NODE * rootNode, int key, NODEDATA * value)
{
	NODE * newNode = createNode(key, value);
	NODE ** newNodePos = findPosition(rootNode, key);

	if (newNodePos != NULL)
		*newNodePos = newNode;
	else
		throwException(2);
}

void deleteNode(NODE * rootNode, int key)
{
}

void traverseNode(NODE * rootNode, void(*callbackFunc)(NODEDATA *))
{
	if (rootNode == NULL)
		return;

	traverseNode(rootNode->left, callbackFunc);
	callbackFunc(rootNode->value);
	traverseNode(rootNode->right, callbackFunc);
}