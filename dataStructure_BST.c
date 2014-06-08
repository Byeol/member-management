#include "dataStructure_BST.h"

static PERSONLIST personList;
static STRING matchString;

static int memberCount = 0;
static int memberIdMax = 0;

static NODE * rootNode = NULL;

PERSON * findMemberById(int memberId)
{
	NODE * node = findNode(rootNode, memberId);
	if (node == NULL)
		return NULL;

	return node->value->member;
}

static void addMemberToList(PERSON * member)
{
	personList.member[personList.memberCnt++] = member;
}

static int checkStringMatch(STRING string)
{
	return !strcmp(string, matchString);
}

void getMemberListByAll(NODEDATA * value)
{
	addMemberToList(value->member);
}

PERSONLIST getMemberList()
{
	personList.memberCnt = 0;
	traverseNode(rootNode, getMemberListByAll);
	return personList;
}

void getMemberListByName(NODEDATA * value)
{
	if (checkStringMatch(value->member->name))
		addMemberToList(value->member);
}

void getMemberListByPhone(NODEDATA * value)
{
	if (checkStringMatch(value->member->phone))
		addMemberToList(value->member);
}

PERSON * findMemberByName(STRING name)
{
	personList.memberCnt = 0;
	matchString = name;
	traverseNode(rootNode, getMemberListByName);

	if (personList.memberCnt == 0)
		return NULL;
	else if (personList.memberCnt == 1)
		return personList.member[0];
	else
		return choiceDuplicatedOne(personList);
}

PERSON * findMemberByPhone(STRING phone)
{
	personList.memberCnt = 0;
	matchString = phone;
	traverseNode(rootNode, getMemberListByPhone);

	if (personList.memberCnt == 0)
		return NULL;
	else if (personList.memberCnt == 1)
		return personList.member[0];
	else
		return choiceDuplicatedOne(personList);
}

void insertMember(PERSON * member)
{
	NODEDATA * nodeData = malloc(sizeof(NODEDATA));
	nodeData->member = member;

	if (memberIdMax < member->memberId)
		memberIdMax = member->memberId;

	if (rootNode == NULL)
	{
		rootNode = createNode(member->memberId, nodeData);
		return;
	}

	insertNode(rootNode, member->memberId, nodeData);
}

void removeMemberById(int memberId)
{
	NODE * node = findNode(rootNode, memberId);

	if (node == rootNode)
	{
		node->parent = createNode(-1, NULL);
		node->parent->right = rootNode;
		deleteNode(rootNode, memberId);
		rootNode = node->parent->right;
	}

	deleteNode(rootNode, memberId);
}

int getMemberIdMax()
{
	return memberIdMax;
}