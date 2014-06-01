#ifndef __COMMON_H__
#define __COMMON_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <Windows.h>

#include "person.h"
#include "constants.h"
#include "messages_ko-KR.h"

#include "dataStructure.h"
#include "mainFunction.h"
#include "consoleFunction.h"

#pragma warning (disable:4996)

int getString(char * str, int size, int (checkFunc)(char *));
int choiceFromList(char * choiceList[], int choiceCount, int startPosition);
FILE * openDataFile(char *opt);
void readMemberDataFromFile();
int nameCheck(char * str);
int addressCheck(char * str);
int phoneCheck(char * str);

#endif