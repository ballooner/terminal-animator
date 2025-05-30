#ifndef TERMINALUTILS_H
#define TERMINALUTILS_H

#include <termios.h>

enum ScreenState
{
    MAIN = 1,
    ANIMATE = 2,
    PLAYER = 3
};

struct TerminalInfo
{
    struct termios defaultSettings;
    int terminalWidth;
    int terminalHeight;
    int cursorX;
    int cursorY;
    enum ScreenState screen;
};

extern struct TerminalInfo terminalInfo;

int  clearScreen();
void enterRawMode();
void leaveRawMode();
void updateTerminalSize();
void setupResizeHandler();
int  setCursorPosition(int x, int y);
int  getCursorPosition(int *x, int *y);
int  getTerminalSize();

#endif
