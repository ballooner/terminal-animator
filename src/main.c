#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "terminalUtils.h"
#include "frameBuffer.h"

buffer_t screenBuffer;

int validateBuffer(buffer_t *buffer)
{
    if (buffer->height < 0 || buffer->width < 0 || buffer->frameData == NULL)
	return -1;

    return 0;
}

void renderMainMenu()
{
    clearScreen();

    printf("1. Animate\r\n");
    printf("2. Play\r\n");
    printf("3. Quit\r\n");
}

void inputHandler()
{
    char c;
    while(1)
    {
	if (terminalInfo.screen == MAIN)
	    renderMainMenu();

        read(STDIN_FILENO, &c, 1);

        if (c == '3') 
	{
	    exit(0);
	}

	c = '\0';
    }   
}


int main(void)
{
    // Init
    enterRawMode();
    getTerminalSize();
    getCursorPosition(&terminalInfo.cursorX, &terminalInfo.cursorY);
    terminalInfo.screen = MAIN;

    inputHandler();

    return 0;
}
