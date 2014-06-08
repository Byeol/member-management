#ifndef __DATASTRUCTURE_BST_H__
#define __DATASTRUCTURE_BST_H__

#include "binarySearchTree.h"
#include "person.h"
#include "common.h"

void initTree();

typedef char * STRING;

PERSONLIST getMemberList();
PERSON * findMemberById(int memberId);
PERSON * findMemberByName(STRING name);
PERSON * findMemberByPhone(STRING phone);

void insertMember(PERSON * member);
void removeMemberById(int memberId);

int getMemberIdMax();
#endif