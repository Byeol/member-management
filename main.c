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

	while (1)
	{
		clearScreen();
		printf("%s\n\n", programName);

		op = getChoice(string_list, sizeof(string_list) / sizeof(char *));
		if (op == -1)
			continue;

		void(*opFunc)() = func_list[op - 1];
		clearScreen();
		opFunc();
	}
}

void printAllMember()
{
	PERSONLIST members = getMemberList();

	if (!members.memberCnt)
	{
		printf("%s\n", message_nobodyExist);
		getch();
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
	addMember(newMember);
	isDataSaved = 0;
}

void removeMemberByInformation()
{
	PERSON * member = getMemberByInformation();

	if (!member)
	{
		printf("%s\n", message_nobodyMatched);
		getch();
		return;
	}

	removeMember(member);
}

void editMemberByInformation()
{
	PERSON * member = getMemberByInformation();

	if (!member)
	{
		printf("%s\n", message_nobodyMatched);
		getch();
		return;
	}

	editMember(member);
}

void searchMember()
{
	PERSON * member = getMemberByInformation();

	if (!member)
	{
		printf("%s\n", message_nobodyMatched);
		getch();
		return;
	}

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

	printf("%s\n", message_savedSuccessfully);
	getch();
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

	clearScreen();
	printf("%s\n", message_exitProgram);
	exit(0);
}