#ifndef __MAINFUNCTION_H__
#define __MAINFUNCTION_H__

#include "common.h"

void printMemberList();
int printMemberInRange(int startIdx, int endIdx);
void printMember(PERSON * member);
void addMember(PERSON *);
void removeMember(PERSON *);
void editMember(PERSON *);

#endif