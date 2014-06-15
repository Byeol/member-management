#include "main.h"

static int isDataSaved = 0;

int main()
{
	funcPointer func_list[7] =
	{
		printAllMember,
		createNewMember,
		removeMemberByInformation,
		editMemberByInformation,
		saveMemberDataToFile,
		searchMember,
		exitProgram
	};

	char * string_list[7] =
	{
		string_printMemberList,
		string_addMember,
		string_removeMember,
		string_editMember,
		string_saveMemberData,
		string_searchMember,
		string_exitProgram
	};

	int op;

	setConsolePreference();
	readMemberDataFromFile();
	isDataSaved = 1;

	while (1)
	{
		clearScreen();
		printf("%s", programName);

		op = choiceFromList(string_list, sizeof(string_list) / sizeof(char *), 3);

		if (op == -1)
			continue;

		void(*opFunc)() = func_list[op];
		clearScreen();
		opFunc();
	}
}

void printAllMember()
{
	PERSONLIST members = getMemberList();

	if (!members.memberCnt)
	{
		printNotification(message_nobodyExist);
		return;
	}

	printMemberList(&members);
}

void createNewMember()
{
	PERSON * newMember;
	newMember = malloc(sizeof(PERSON));

	newMember->memberId = getMemberIdMax()+1;
	printf("%s: %d\n", string_memberId, newMember->memberId);

	getMemberInformation(newMember);

	if (addMember(newMember) == 0)
	{
		isDataSaved = 0;
		printNotification(message_createdSuccessfully);
	}
}

void removeMemberByInformation()
{
	PERSON * member = getMemberByInformation();
	if (member == (PERSON *) -1)
		return;

	if (!member)
	{
		printNotification(message_nobodyMatched);
		return;
	}

	if (removeMember(member) == 0)
	{
		isDataSaved = 0;
		printNotification(message_removedSuccessfully);
	}
}

void editMemberByInformation()
{
	PERSON * member = getMemberByInformation();
	if (member == (PERSON *) -1)
		return;

	if (!member)
	{
		printNotification(message_nobodyMatched);
		return;
	}

	if (editMember(member) == 0)
	{
		isDataSaved = 0;
		printNotification(message_editedSuccessfully);
	}
}

void searchMember()
{
	PERSON * member = getMemberByInformation();
	if (member == (PERSON *) -1)
		return;

	if (!member)
	{
		printNotification(message_nobodyMatched);
		return;
	}

	clearScreen();
	printMember(member);
	getch();
}

void saveMemberDataToFile()
{
	FILE * dataFile = openDataFile("w");
	fprintf(dataFile, "%s\t%s\t%s\t%s\n", string_memberId, string_memberName, string_memberAddress, string_memberPhone);

	PERSONLIST members = getMemberList();

	int memberIdx;
	for (memberIdx = 0; memberIdx < members.memberCnt; memberIdx++)
		fprintf(dataFile, "%d\t%s\t%s\t%s\n", members.member[memberIdx]->memberId, members.member[memberIdx]->name, members.member[memberIdx]->address, members.member[memberIdx]->phone);

	isDataSaved = 1;

	printNotification(message_savedSuccessfully);
}

void exitProgram()
{
	if (!isDataSaved)
	{
		printf("%s\n", message_changeExist);
		printf("%s\n", message_saveChangeQuestion);

		char * choiceList[] = { string_yes, string_no };	
		if (choiceFromList(choiceList, sizeof(choiceList) / sizeof(char *), 3) == 0)
			saveMemberDataToFile();
	}

	printNotification(message_exitProgram);
	exit(0);
}