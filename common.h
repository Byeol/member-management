#ifndef __COMMON_H__
#define __COMMON_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <ctype.h>
#include <assert.h>
#include <Windows.h>

#include "person.h"
#include "constants.h"
#include "messages_ko-KR.h"

#include "dataStructure_BST.h"
#include "mainFunction.h"
#include "consoleFunction.h"

#pragma warning (disable:4996)

typedef void(*funcPointer)();
typedef char * STRING;

void throwException(int exception);
void printNotification(STRING message);
int getString(char * str, int size, int (checkFunc)(char *));
int choiceFromList(char * choiceList[], int choiceCount, int startPosition);
FILE * openDataFile(char *opt);
void readMemberDataFromFile();
int checkNameValid(char * str);
int checkAddressValid(char * str);
int checkPhoneValid(char * str);
int changeMemberName(PERSON * member, STRING str);
int changeMemberAddress(PERSON * member, STRING str);
int changeMemberPhone(PERSON * member, STRING str);
PERSON * choiceDuplicatedOne(PERSONLIST personList);

#endif