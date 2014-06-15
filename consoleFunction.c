#include "common.h"

void setTitle()
{
	SetConsoleTitle(TEXT(programName));
}

void clearScreen()
{
	system("cls");
}

void setConsoleSize(int cols, int lines)
{
	char command[100];
	sprintf(command, "MODE CON COLS=%d LINES=%d", cols, lines);
	system(command);
}

void hideCursor()
{
	CONSOLE_CURSOR_INFO ConCurInf;

	ConCurInf.dwSize = 10;
	ConCurInf.bVisible = FALSE;

	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &ConCurInf);
}

void setConsolePreference()
{
	setTitle();
	setConsoleSize(consoleCols, consoleLines);
	hideCursor();
}

void setCursorPosition(int x, int y)
{
	COORD Pos = { x - 1, y - 1 };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

void setTextColor(int Color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Color);
}

int getKeyInput()
{
	int input;
	while ((input = getch()) != 27)
	{
		if (input == 224)
		{
			input = getch();

			if (input == 72)
				return KEY_UP;
			else if (input == 75)
				return KEY_LEFT;
			else if (input == 77)
				return KEY_RIGHT;
			else if (input == 80)
				return KEY_DOWN;
		}
		else if (input == 13)
			return KEY_RETURN;
	}

	return 0;
}

void playShortBeep()
{
	Beep(523, 500);
}