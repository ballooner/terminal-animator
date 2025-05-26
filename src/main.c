#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "terminalUtils.h"

int main(void)
{
    enterRawMode();
    getTerminalSize();
    
    char c;
    while(1)
    {
        read(STDIN_FILENO, &c, 1);

        if (c == 'q') 
	{
	    exit(0);
	} else if (c == 'g')
	{
	    printf("height: %d, width: %d\r\n", terminalInfo.terminalHeight, terminalInfo.terminalWidth);
	}

	//Clear c
	c = '\0';
    }

    return 0;
}
