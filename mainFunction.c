#include "common.h"

void printMemberList(PERSONLIST * members)
{
	int memberCnt;
	int pageOp;
	int startIdx = 0, endIdx = startIdx + printLineLength;

	memberCnt = members->memberCnt;
	if (endIdx > memberCnt)
		endIdx = memberCnt - 1;

	while (pageOp = printMemberInRange(members, startIdx, endIdx))
	{
		switch (pageOp)
		{
		case PAGE_LEFT:
			if (startIdx <= 1)
			{
				playShortBeep();
				break;
			}

			startIdx -= printLineLength + 1;
			break;
		case PAGE_RIGHT:
			if (endIdx >= memberCnt - 1)
			{
				playShortBeep();
				break;
			}

			startIdx += printLineLength + 1;
			break;
		}

		endIdx = startIdx + printLineLength;
		if (endIdx > memberCnt)
			endIdx = memberCnt - 1;
	}
}

int printMemberInRange(PERSONLIST * members, int startIdx, int endIdx)
{
	int memberIdx;
	PERSON * member;
	int nowPosition = 1;
	int keyInput;
	setCursorPosition(1, nowPosition);
	
	if (endIdx > members->memberCnt)
		throwException(1);

	clearScreen();
	for (memberIdx = startIdx; memberIdx <= endIdx; memberIdx++)
	{
		member = members->member[memberIdx];
		printMember(member);
	}

	setCursorPosition(1, nowPosition);
	setTextColor(BACKGROUND_INTENSITY);
	printMember(members->member[startIdx + nowPosition - 1]);
	setTextColor(DEFAULT_TEXT_ATTRIBUTE);

	while (keyInput = getKeyInput())
	{
		switch (keyInput)
		{
		case KEY_UP:
			if (startIdx + nowPosition - 1 <= startIdx)
			{
				playShortBeep();
				break;
			}

			setCursorPosition(1, nowPosition);
			setTextColor(DEFAULT_TEXT_ATTRIBUTE);
			printMember(members->member[startIdx + nowPosition - 1]);

			nowPosition--;

			setCursorPosition(1, nowPosition);
			setTextColor(BACKGROUND_INTENSITY);
			printMember(members->member[startIdx + nowPosition - 1]);
			setTextColor(DEFAULT_TEXT_ATTRIBUTE);
			break;
		case KEY_DOWN:
			if (startIdx + nowPosition - 1 >= endIdx)
			{
				playShortBeep();
				break;
			}

			setCursorPosition(1, nowPosition);
			setTextColor(DEFAULT_TEXT_ATTRIBUTE);
			printMember(members->member[startIdx + nowPosition - 1]);

			nowPosition++;

			setCursorPosition(1, nowPosition);
			setTextColor(BACKGROUND_INTENSITY);
			printMember(members->member[startIdx + nowPosition - 1]);
			setTextColor(DEFAULT_TEXT_ATTRIBUTE);
			break;
		case KEY_LEFT:
			return PAGE_LEFT;
		case KEY_RIGHT:
			return PAGE_RIGHT;
		}
	}

	return 0;
}

void printMember(PERSON * member)
{
	printf("%6d\t%-5s\t%-30s\t%-20s\n", member->memberId, member->name, member->address, member->phone);
}

void addMember(PERSON * member)
{
	insertMember(member);
}

void removeMember(PERSON * member)
{
	removeMemberById(member->memberId);
}

void editMember(PERSON * member)
{
	int i;
	int op;
	int res;

	char changeString[100];
	STRING destPointer_list[3] =
	{
		member->name,
		member->address,
		member->phone
	};

	int (*func_list[3])(PERSON *, STRING) = 
	{
		changeMemberName,
		changeMemberAddress,
		changeMemberPhone
	};

	int (*opFunc)(PERSON *, STRING);

	char * string_list[3] = {
		string_memberName,
		string_memberAddress,
		string_memberPhone
	};

	printf("%s\n", message_choiceInformationToChange);
	for (i = 0; i < 3; i++)
		printf("%d. %s\n", i + 1, string_list[i]);
	scanf(" %d", &op);
	opFunc = func_list[op - 1];

	printf("%s%s%s%s%s\n", message_informationOfMember, string_list[op - 1], message_is, destPointer_list[op - 1], message_isB);
	printf("%s%s%s\n", message_informationToChange, string_list[op - 1], message_enter);

	do
	{
		getString(changeString, sizeof(changeString), NULL);
		res = opFunc(member, changeString);

		if (res == WRONG_INPUT)
			printf("%s%s%s", message_informationToChange, string_list[op - 1], message_enterAgain);

	} while (res);
}

PERSON * getMemberByInformation()
{
	int i;
	int op;

	PERSON * member;
	char targetString[100];

	char * information_string[3] = {
		string_memberId,
		string_memberName,
		string_memberPhone
	};

	PERSON *(*func_list[3])(STRING) =
	{
		findMemberById,
		findMemberByName,
		findMemberByPhone
	};
	PERSON *(*opFunc)(STRING);

	printf("%s\n", message_choiceInformationToSearch);
	for (i = 0; i < 3; i++)
		printf("%d. %s\n", i + 1, information_string[i]);

	scanf(" %d", &op);

	printf("%s%s%s\n", message_informationOfMemberToFind , information_string[op - 1], message_enter);
	scanf(" %[^\n]", targetString);
	opFunc = func_list[op - 1];

	if (op==1)
		member = findMemberById(atoi(targetString));
	else
		member = opFunc(targetString);

	return member;
}

void getMemberInformation(PERSON * member)
{
	int i;
	int res;
	char str[100];

	int(*func_list[3])(PERSON *, STRING) =
	{
		changeMemberName,
		changeMemberAddress,
		changeMemberPhone
	};
	int(*opFunc)(PERSON *, STRING);

	char * string_list[3] = {
		string_memberName,
		string_memberAddress,
		string_memberPhone
	};

	for (i = 0; i < 3; i++)
	{
		opFunc = func_list[i];
		printf("%s\n", string_list[i], message_enter);
		do
		{
			getString(str, sizeof(str), NULL);
			res = opFunc(member, str);
		} while (res);
	}
}