#ifndef __MAINFUNCTION_H__
#define __MAINFUNCTION_H__

#include "common.h"

void printMemberList(PERSONLIST * members);
int printMemberInRange(PERSONLIST * members, int startIdx, int endIdx);
void printMember(PERSON * member);
void addMember(PERSON *);
void removeMember(PERSON *);
void editMember(PERSON *);
PERSON * getMemberByInformation();
void getMemberInformation(PERSON * member);

#endif