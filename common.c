#include "common.h"

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
			if (nowPosition <= 2)
			{
				playShortBeep();
				break;
			}

			setCursorPosition(1, nowPosition);
			setTextColor(DEFAULT_TEXT_ATTRIBUTE);
			printf("%s\n", choiceList[nowPosition - 2]);

			nowPosition--;

			setCursorPosition(1, nowPosition);
			setTextColor(BACKGROUND_INTENSITY);
			printf("%s\n", choiceList[nowPosition - 2]);
			setTextColor(DEFAULT_TEXT_ATTRIBUTE);
			break;
		case KEY_DOWN:
			if (nowPosition >= 3)
			{
				playShortBeep();
				break;
			}

			setCursorPosition(1, nowPosition);
			setTextColor(DEFAULT_TEXT_ATTRIBUTE);
			printf("%s\n", choiceList[nowPosition - 2]);

			nowPosition++;

			setCursorPosition(1, nowPosition);
			setTextColor(BACKGROUND_INTENSITY);
			printf("%s\n", choiceList[nowPosition - 2]);
			setTextColor(DEFAULT_TEXT_ATTRIBUTE);
			break;
		case KEY_RETURN:
			return nowPosition - 2;
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

int nameCheck(char * str)
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

int phoneCheck(char * str)
{
	// rule: [0-9]{3}-[0-9]{4}-[0-9]{4}

	int memberIdx;
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

	for (memberIdx = 1; memberIdx < getMemberCount(); memberIdx++)
	{
		if (!strcmp(getMember(memberIdx)->phone, str))
			return PHONE_DUPLICATED;
	}

	return 0;
}