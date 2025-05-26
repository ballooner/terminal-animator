#include <termios.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <stdlib.h>
#include <stdio.h>
#include "terminalUtils.h"

static struct termios defaultTermSettings;

// Clear screen
// return
// 0 on success
// -2 on failure to write
int clearScreen()
{
    if (write(STDIN_FILENO, "\x1b[2J", 4) != 4) return -2;

    return 0;
}

void enterRawMode()
{
    clearScreen();
    // Make sure we have original settings so we can reset when leaving raw mode
    tcgetattr(STDIN_FILENO, &defaultTermSettings);

    struct termios rawSettings = defaultTermSettings;

    // Set all the raw settings
    rawSettings.c_iflag &= ~(IGNBRK | BRKINT | PARMRK | ISTRIP | INLCR | IGNCR 
                             | ICRNL | IXON);
    rawSettings.c_oflag &= ~OPOST;
    rawSettings.c_lflag &= ~(ECHO | ECHONL | ICANON | ISIG | IEXTEN);
    rawSettings.c_cflag &= ~(CSIZE | PARENB);
    rawSettings.c_cflag |= CS8;

    // Set terminal to raw settings
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &rawSettings);
    atexit(leaveRawMode);
}

void leaveRawMode()
{
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &defaultTermSettings);
}

// Set cursor position to (x,y)
// return 
// 0 on success
// -1 on failure to format
// -2 on failure to write
int setCursorPosition(int x, int y)
{
    // 4 char constants + size of x/y vars
    unsigned int bufferSize = 4 + sizeof(x) + sizeof(y);

    char buffer[bufferSize];

    if (snprintf(buffer, bufferSize, "\x1b[%d;%dH", y, x) < 0) return -1;
    if (write(STDIN_FILENO, buffer, bufferSize) != bufferSize) return -2;

    return 0;
}

// Get cursor position and put them into x and y
// return
// 0 on success
// -1 on failure to receive correct report
// -2 on failure to write
int getCursorPosition(int *x, int *y)
{
    // Request VT100 Cursor Report
    if (write(STDIN_FILENO, "\x1b[6n", 4) != 4) return -2;

    // Read VT100 Cursor Report
    char buffer[32];
    int i = 0;
    while (read(STDIN_FILENO, buffer + i, 1) == 1 && buffer[i] != 'R' && i++ < sizeof(buffer) - 1);
    buffer[i] = '\0';

    // Verify that we read a VT100 report
    if (buffer[0] != '\x1b' && buffer[1] != '[') return -1;
    sscanf(buffer, "\x1b[%d;%dR", y, x);

    return 0;
}

// Get the terminal's size
// return
// 0 on success
// -2 on failure to write
int getTerminalSize(int *height, int *width)
{
    struct winsize ws;

    if (ioctl(STDIN_FILENO, TIOCGWINSZ, &ws) == -1) // If ioctl doesn't work we 
    {                                               // use VT100 commands
        if (write(STDIN_FILENO, "\x1b[999C\x1b[999B", 12) != 12) return -2;

        getCursorPosition(height, width);
    } else
    {
        *width = ws.ws_col;
        *height = ws.ws_row;
    }
}
