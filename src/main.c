#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "terminalUtils.h"

int main(void)
{
    enterRawMode();
    
    int x;
    int y;
    int termWidth;
    int termHeight;

    setCursorPosition(30,30);
    getCursorPosition(&x, &y);
    getTerminalSize(&termWidth, &termHeight);
    setCursorPosition(0,0);
    printf("x: %d, y: %d\r\ntermWidth: %d, termHeight: %d\r\n", x, y, termWidth, termHeight);

    char c;
    while(1)
    {
        read(STDIN_FILENO, &c, 1);

        if (c == 'q') exit(0);
    }

    return 0;
}
