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
	short isEscPress = 0;
	short isReturnPress;

	while (!isEscPress)
	{
		isEscPress = GetAsyncKeyState(VK_ESCAPE);
		isReturnPress = abs(GetKeyState(VK_RETURN)) % 2;

		if (GetAsyncKeyState(VK_UP) & SHRT_MAX)
			return KEY_UP;
		else if (GetAsyncKeyState(VK_DOWN) & SHRT_MAX)
			return KEY_DOWN;
		else if (GetAsyncKeyState(VK_LEFT) & SHRT_MAX)
			return KEY_LEFT;
		else if (GetAsyncKeyState(VK_RIGHT) & SHRT_MAX)
			return KEY_RIGHT;
		else if (isReturnPress != abs(GetKeyState(VK_RETURN)) % 2)
			return KEY_RETURN;
	}

	return 0;
}

void playShortBeep()
{
	Beep(523, 500);
}