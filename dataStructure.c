#include "common.h"

static PERSON * members[personMaxCount];
static int memberCount = 0;
static int memberIdMax = 0;

PERSON * insertMember(PERSON * newPerson)
{
	members[++memberCount] = newPerson;

	if (memberIdMax < newPerson->memberId)
		memberIdMax = newPerson->memberId;

	return members[memberCount];
}

PERSON * getMember(int personIdx)
{
	return members[personIdx];
}

int getMemberCount()
{
	return memberCount;
}

int getMemberIdMax()
{
	return memberIdMax;
}