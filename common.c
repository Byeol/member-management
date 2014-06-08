#include "common.h"

void throwException(int exception)
{
	assert(exception);
}

int getChoice(char * string_list[], int listCount)
{
	int i, op;

	for (i = 0; i < listCount; i++)
		printf("%d. %s\n", i + 1, string_list[i]);

	scanf(" %d", &op);

	if (!(1 <= op && op <= listCount))
		return -1;

	else return op;
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

	setCursorPosition(1, nowPosition);
	setTextColor(BACKGROUND_INTENSITY);
	printf("%s\n", choiceList[0]);
	setTextColor(DEFAULT_TEXT_ATTRIBUTE);
	for (i = 1; i < choiceCount; i++)
		printf("%s\n", choiceList[i]);

	while (keyInput = getKeyInput())
	{
		switch (keyInput)
		{
		case KEY_UP:
			if (nowPosition <= startPosition)
			{
				playShortBeep();
				break;
			}

			setCursorPosition(1, nowPosition);
			setTextColor(DEFAULT_TEXT_ATTRIBUTE);
			printf("%s\n", choiceList[nowPosition - startPosition]);

			nowPosition--;

			setCursorPosition(1, nowPosition);
			setTextColor(BACKGROUND_INTENSITY);
			printf("%s\n", choiceList[nowPosition - startPosition]);
			setTextColor(DEFAULT_TEXT_ATTRIBUTE);
			break;
		case KEY_DOWN:
			if (nowPosition > startPosition)
			{
				playShortBeep();
				break;
			}

			setCursorPosition(1, nowPosition);
			setTextColor(DEFAULT_TEXT_ATTRIBUTE);
			printf("%s\n", choiceList[nowPosition - startPosition]);

			nowPosition++;

			setCursorPosition(1, nowPosition);
			setTextColor(BACKGROUND_INTENSITY);
			printf("%s\n", choiceList[nowPosition - startPosition]);
			setTextColor(DEFAULT_TEXT_ATTRIBUTE);
			break;
		case KEY_RETURN:
			return nowPosition - startPosition;
			break;
		}
	}
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

	int i;
	for (i = 0; i < strlen(str); i++)
	{
		if ((str[i] & 0x80) != 0x80)
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
	int i;

	printf("%s\n", message_matchedManyMembers);

	for (i = 0; i < personList.memberCnt; i++)
		printf("%d. %d\n", i + 1, personList.member[i]->memberId);
	scanf(" %d", &choice);

	return personList.member[choice - 1];
}