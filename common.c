#include "common.h"

void throwException(int exception)
{
	assert(exception);
}

void printNotification(STRING message)
{
	clearScreen();
	printf("%s\n", message);
	getch();
}

int getString(char * str, int size, int (checkFunc)(char *))
{
	int res;
	res = scanf_s(" %[^\n]", str, size);

	if (res == EOF || checkFunc == NULL)
		return res;

	return checkFunc(str);
}

int choiceFromList(char * choiceList[], int choiceCount, int startPosition)
{
	int i;
	int nowPosition = startPosition;
	int keyInput;
	int movePosition;

	setCursorPosition(1, nowPosition);
	setTextColor(BACKGROUND_INTENSITY);
	printf("%s\n", choiceList[0]);
	setTextColor(DEFAULT_TEXT_ATTRIBUTE);
	for (i = 1; i < choiceCount; i++)
		printf("%s\n", choiceList[i]);

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
		case KEY_RETURN:
			return nowPosition - startPosition;
			break;
		default:
			break;
		}

		if (!(startPosition <= nowPosition + movePosition && nowPosition + movePosition <= startPosition + choiceCount - 1))
		{
			playShortBeep();
			continue;
		}

		setCursorPosition(1, nowPosition);
		setTextColor(DEFAULT_TEXT_ATTRIBUTE);
		printf("%s\n", choiceList[nowPosition - startPosition]);

		nowPosition += movePosition;

		setCursorPosition(1, nowPosition);
		setTextColor(BACKGROUND_INTENSITY);
		printf("%s\n", choiceList[nowPosition - startPosition]);
		setTextColor(DEFAULT_TEXT_ATTRIBUTE);
	}

	return -1;
}

FILE * openDataFile(char *opt)
{
	return fopen(data_filename, opt);
}

void readMemberDataFromFile()
{
	FILE * dataFile = openDataFile("r");

	if (!dataFile)
		return;

	char temp[dataLineMaxLength];
	fscanf(dataFile, "%[^\n]\n", temp);

	while (!feof(dataFile)) {
		PERSON * newMember = malloc(sizeof(PERSON));

		fscanf(dataFile, "%d\t", &newMember->memberId);
		fscanf(dataFile, "%[^\t]\t", newMember->name);
		fscanf(dataFile, "%[^\t]\t", newMember->address);
		fscanf(dataFile, "%[^\n]\n", newMember->phone);

		insertMember(newMember);
	}

	fclose(dataFile);
}

int checkNameValid(char * str)
{
	// rule: korean character

	unsigned int idx;
	for (idx = 0; idx < strlen(str); idx++)
	{
		if ((str[idx] & 0x80) != 0x80)
			return NAME_NOT_KOREAN;
	}

	return 0;
}

int checkPhoneValid(char * str)
{
	// rule: [0-9]{3}-[0-9]{4}-[0-9]{4}

	char * token, *destPtr;

	int cnt;
	int delim = '-';
	int form[] = { 3, 4, 4 };
	int tokenCnt = 0;

	token = strtok(str, "-");
	destPtr = str;

	while (token)
	{
		cnt = 0;
		while (*token != '\0')
		{
			if (!isdigit((unsigned char) *token))
				return PHONE_NOT_DIGIT;

			*(destPtr++) = *(token++);
			cnt++;
		}

		if (tokenCnt >= (sizeof(form) / sizeof(int)) || cnt != form[tokenCnt++])
			return WRONG_INPUT;

		token = strtok(NULL, "-");
		if (!token)
			delim = '\0';
		*(destPtr++) = delim;
	}

	if (tokenCnt != (sizeof(form) / sizeof(int)))
		return WRONG_INPUT;

	// check duplicated

	if (findMemberByPhone(str) != NULL)
		return PHONE_DUPLICATED;

	return 0;
}

int changeMemberName(PERSON * member, STRING str)
{
	// check name is valid
	int res;
	res = checkNameValid(str);
	
	switch (res)
	{
	case 0:
		strcpy(member->name, str);
		return 0;
	case NAME_NOT_KOREAN:
		printf("%s\n", nameNotKorean);
		printf("%s\n", inputNameHelp);
		break;
	}

	return -1;
}

int changeMemberAddress(PERSON * member, STRING str)
{
	strcpy(member->address, str);
	return 0;
}

int changeMemberPhone(PERSON * member, STRING str)
{
	// check phone is valid
	int res;
	res = checkPhoneValid(str);

	switch (res)
	{
	case 0:
		strcpy(member->phone, str);
		return 0;
	case WRONG_INPUT:
		printf("%s\n", wrongInput);
		printf("%s\n", inputPhoneHelp);
		break;
	case PHONE_NOT_DIGIT:
		printf("%s\n", phoneNotDigit);
		printf("%s\n", inputPhoneHelp);
		break;
	case PHONE_DUPLICATED:
		printf("%s\n", phoneDuplicated);
		break;
	}

	return -1;
}

PERSON * choiceDuplicatedOne(PERSONLIST personList)
{
	// choice one in personList
	int choice = 0;

	printNotification(message_matchedManyMembers);

	choice = printMemberInRange(&personList, 0, personList.memberCnt-1, 1);
	if (choice == -1)
		return (PERSON *) -1;

	return personList.member[choice - 1];
}