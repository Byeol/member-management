#include "common.h"

void createNewMember();
void saveMemberDataToFile();
void exitProgram();

int isDataSaved = 0;

int main()
{
	int op;

	setConsolePreference();
	readMemberDataFromFile();

	while (1)
	{
		clearScreen();
		printf("%s\n\n", programName);

		printf("1. %s\n", string_printMemberList);
		printf("2. %s\n", string_addMember);
		printf("3. %s\n", string_removeMember);
		printf("4. %s\n", string_editMember);
		printf("5. %s\n", string_saveMemberData);
		printf("6. %s\n", string_searchMember);
		printf("7. %s\n", string_exitProgram);

		scanf(" %d", &op);

		clearScreen();
		switch (op)
		{
		case 1:
			printMemberList();
			break;
		case 2:
			createNewMember();
			break;
		case 5:
			saveMemberDataToFile();
			break;
		case 7:
			exitProgram();
			break;
		case 3: case 4: case 6:
			printf("not implemented yet!\n");
			getch();
			break;
		}
	}
}

void createNewMember()
{
	int res;

	PERSON * newMember;
	newMember = malloc(sizeof(PERSON));

	newMember->memberId = getMemberIdMax()+1;

	printf("회원 번호: %d\n", newMember->memberId);

	printf("이름: ");
	while (res = getString(newMember->name, name_maxchar, nameCheck))
	{
		switch (res)
		{
		case NAME_NOT_KOREAN:
			printf("%s\n", nameNotKorean);
			printf("%s\n", inputNameHelp);
			break;
		}
	}

	printf("주소: ");
	getString(newMember->address, address_maxchar, NULL);

	printf("전화번호: ");
	while (res = getString(newMember->phone, phone_maxchar, phoneCheck))
	{
		switch (res)
		{
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
	}

	addMember(newMember);
	isDataSaved = 0;
}

void saveMemberDataToFile()
{
	FILE * dataFile = openDataFile("w");
	fprintf(dataFile, "%s\t%s\t%s\t%s\n", string_memberId, string_memberName, string_memberAddress, string_memberPhone);

	int memberIdx;
	for (memberIdx = 1; memberIdx < getMemberCount(); memberIdx++)
		fprintf(dataFile, "%d\t%s\t%s\t%s\n", getMember(memberIdx)->memberId, getMember(memberIdx)->name, getMember(memberIdx)->address, getMember(memberIdx)->phone);

	isDataSaved = 1;

	printf("성공적으로 저장되었습니다!\n");
	getch();
}

void exitProgram()
{
	if (!isDataSaved)
	{
		printf("변경 내용이 있습니다!\n");
		printf("변경 내용을 저장하시겠습니까?\n");

		char * choiceList[] = { "예", "아니요" };	
		if (choiceFromList(choiceList, sizeof(choiceList) / sizeof(char *), 2) == 0)
			saveMemberDataToFile();
	}

	exit(0);
}