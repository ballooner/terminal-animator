#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "terminalUtils.h"
#include "frameBuffer.h"

buffer_t screenBuffer;

void createMenuFrame(buffer_t *buffer)
{

}

void renderBuffer(buffer_t *buffer)
{

}

void inputHandler()
{
    

    char c;
    while(1)
    {
	

        read(STDIN_FILENO, &c, 1);

        if (c == 'q') 
	{
	    exit(0);
	} else if (c == 'g')
	{
	}

	//Clear c
	c = '\0';
    }   
}

int main(void)
{
    enterRawMode();


    inputHandler();

    return 0;
}
