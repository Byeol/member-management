#ifndef __BINARYSEARCHTREE_H__
#define __BINARYSEARCHTREE_H__

#include "common.h"

#include "person.h"
typedef struct _NODEDATA {
	PERSON * member;
} NODEDATA;

typedef struct _NODE {
	int key;
	NODEDATA * value;
	struct _NODE * left;
	struct _NODE * right;
} NODE;

NODE * createNode(int key, NODEDATA * value);
NODE * findNode(NODE * rootNode, int key);
void insertNode(NODE * rootNode, int key, NODEDATA * value);
void deleteNode(NODE * rootNode, int key);
void traverseNode(NODE * rootNode, void(*callbackFunc)(NODEDATA *));

#endif