#ifndef __CONSOLEFUNCTION_H__
#define __CONSOLEFUNCTION_H__

#define KEY_UP 1
#define KEY_DOWN 2
#define KEY_LEFT 3
#define KEY_RIGHT 4
#define KEY_RETURN 5

#define PAGE_LEFT 1
#define PAGE_RIGHT 2

#define DEFAULT_TEXT_ATTRIBUTE 7

void setTitle();
void clearScreen();
void hideCursor();
void setConsolePreference();
void setCursorPosition(int x, int y);
void setTextColor(int Color);
int getKeyInput();
void playShortBeep();

#endif