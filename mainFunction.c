#include "common.h"

void printMemberList(PERSONLIST * members)
{
	int memberCnt;
	int pageOp;
	int startIdx = 0, endIdx = startIdx + printLineLength;

	memberCnt = members->memberCnt;
	if (endIdx > memberCnt)
		endIdx = memberCnt - 1;

	while ((pageOp = printMemberInRange(members, startIdx, endIdx, 0)) != -1)
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

int printMemberInRange(PERSONLIST * members, int startIdx, int endIdx, int isReturn)
{
	int memberIdx;
	PERSON * member;
	int nowPosition = 1;
	int movePosition;
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
		movePosition = 0;

		switch (keyInput)
		{
		case KEY_UP:
			movePosition = -1;
			break;
		case KEY_DOWN:
			movePosition = +1;
			break;
		case KEY_LEFT:
			return PAGE_LEFT;
		case KEY_RIGHT:
			return PAGE_RIGHT;
		case KEY_RETURN:
			if (isReturn)
				return nowPosition;
			break;
		default:
			break;
		}

		if (!(1 <= nowPosition + movePosition && nowPosition + movePosition <= endIdx - startIdx + 1))
		{
			playShortBeep();
			continue;
		}

		setCursorPosition(1, nowPosition);
		setTextColor(DEFAULT_TEXT_ATTRIBUTE);
		printMember(members->member[startIdx + nowPosition - 1]);

		nowPosition += movePosition;

		setCursorPosition(1, nowPosition);
		setTextColor(BACKGROUND_INTENSITY);
		printMember(members->member[startIdx + nowPosition - 1]);
		setTextColor(DEFAULT_TEXT_ATTRIBUTE);
	}

	return -1;
}

void printMember(PERSON * member)
{
	printf("%6d\t%-5s\t%-30s\t%-20s\n", member->memberId, member->name, member->address, member->phone);
}

int addMember(PERSON * member)
{
	insertMember(member);
	return 0;
}

int removeMember(PERSON * member)
{
	removeMemberById(member->memberId);
	return 0;
}

int editMember(PERSON * member)
{
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

	clearScreen();
	printf("%s", message_choiceInformationToChange);

	op = choiceFromList(string_list, sizeof(string_list) / sizeof(char *), 3);
	if (op == -1)
		return -1;
	opFunc = func_list[op];

	clearScreen();
	printf("%s%s%s%s%s\n", message_informationOfMember, string_list[op], message_is, destPointer_list[op], message_isB);
	printf("%s%s%s\n", message_informationToChange, string_list[op], message_enter);

	do
	{
		getString(changeString, sizeof(changeString), NULL);
		res = opFunc(member, changeString);

		if (res == WRONG_INPUT)
			printf("%s%s%s", message_informationToChange, string_list[op], message_enterAgain);

	} while (res);

	return 0;
}

PERSON * getMemberByInformation()
{
	int op;

	PERSON * member;
	char targetString[100];

	char * string_list[3] = {
		string_memberId,
		string_memberName,
		string_memberPhone
	};

	PERSON *(*func_list[3])(STRING) =
	{
		NULL,
		findMemberByName,
		findMemberByPhone
	};
	PERSON *(*opFunc)(STRING);

	printf("%s", message_choiceInformationToSearch);

	op = choiceFromList(string_list, sizeof(string_list) / sizeof(char *), 3);
	if (op == -1)
		return (PERSON *) -1;

	clearScreen();
	printf("%s%s%s\n", message_informationOfMemberToFind, string_list[op], message_enter);
	getString(targetString, sizeof(targetString), NULL);
	opFunc = func_list[op];

	if (op == 0)
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