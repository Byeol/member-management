#ifndef __MAINFUNCTION_H__
#define __MAINFUNCTION_H__

#include "common.h"

void printMemberList(PERSONLIST * members);
int printMemberInRange(PERSONLIST * members, int startIdx, int endIdx, int isReturn);
void printMember(PERSON * member);
int addMember(PERSON *);
int removeMember(PERSON *);
int editMember(PERSON *);
PERSON * getMemberByInformation();
void getMemberInformation(PERSON * member);

#endif