#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include "terminalUtils.h"
#include "frameBuffer.h"

buffer_t screenBuffer;

int validateBuffer(buffer_t *buffer)
{
    if (buffer->height < 0 || buffer->width < 0 || buffer->frameData == NULL)
	return -1;

    return 0;
}

// Main screen functionality
void renderMainScreen()
{
    clearScreen();

    printf("1. Animate\r\n");
    printf("2. Play\r\n");
    printf("3. Quit\r\n");
}

void mainScreenInputHandler(const char input)
{
	switch (input)
	{
	    case '1':
		terminalInfo.screen = ANIMATE;
		break;
	    case '2':
		terminalInfo.screen = PLAYER;
		break;
	    case '3':
		exit(0);
		break;
	}
}

// Animate screen functionality
void renderAnimateScreen()
{
    clearScreen();
}

void animateScreenInputHandler(const char input)
{
	switch (input)
	{
	    case 'q':
		exit(0);
		break;
	}
}

// Play screen functionality
void renderPlayScreen()
{
    clearScreen();
}

void playScreenInputHandler(const char input)
{
	switch (input)
	{
	    case 'q':
		exit(0);
		break;
	}
}
void inputHandler()
{
    char c = '\0';
    while(1)
    {
	switch(terminalInfo.screen)
	{
	    case MAIN:
		renderMainScreen();
		break;
	    case ANIMATE:
		renderAnimateScreen();
		break;
	    case PLAYER:
		renderPlayScreen();
		break;
	}

        read(STDIN_FILENO, &c, 1);
	c = tolower(c);

	switch(terminalInfo.screen)
	{
	    case MAIN:
		mainScreenInputHandler(c);
		break;
	    case ANIMATE:
		animateScreenInputHandler(c);
		break;
	    case PLAYER:
		playScreenInputHandler(c);
		break;
	}
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
