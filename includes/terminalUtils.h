#ifndef TERMINALUTILS_H
#define TERMINALUTILS_H

int clearScreen();
void enterRawMode();
void leaveRawMode();
int  setCursorPosition(int x, int y);
int getCursorPosition(int *x, int *y);
int getTerminalSize(int *height, int *width);

#endif
