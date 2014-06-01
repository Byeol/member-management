#include "common.h"

void printMemberList()
{
	int memberCnt;
	int pageOp;
	int startIdx = 1, endIdx = startIdx + printLineLength;

	memberCnt = getMemberCount();
	
	while (pageOp = printMemberInRange(startIdx, endIdx))
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
			if (endIdx >= memberCnt)
			{
				playShortBeep();
				break;
			}

			startIdx += printLineLength + 1;
			break;
		}

		endIdx = startIdx + printLineLength;
		if (endIdx > memberCnt)
			endIdx = memberCnt;
	}
}

int printMemberInRange(int startIdx, int endIdx)
{
	int memberIdx;
	PERSON * member;
	int nowPosition = 1;
	int keyInput;
	setCursorPosition(1, nowPosition);
	
	clearScreen();
	for (memberIdx = startIdx; memberIdx <= endIdx; memberIdx++)
	{
		member = getMember(memberIdx);
		printMember(member);
	}

	setCursorPosition(1, nowPosition);
	setTextColor(BACKGROUND_INTENSITY);
	printMember(getMember(startIdx + nowPosition - 1));
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
			printMember(getMember(startIdx + nowPosition - 1));

			nowPosition--;

			setCursorPosition(1, nowPosition);
			setTextColor(BACKGROUND_INTENSITY);
			printMember(getMember(startIdx + nowPosition - 1));
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
			printMember(getMember(startIdx + nowPosition - 1));

			nowPosition++;

			setCursorPosition(1, nowPosition);
			setTextColor(BACKGROUND_INTENSITY);
			printMember(getMember(startIdx + nowPosition - 1));
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