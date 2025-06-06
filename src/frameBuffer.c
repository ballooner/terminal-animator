#include <stdlib.h>
#include "frameBuffer.h"

// Allocate frameData memory based on width and height
// of buffer struct
// return:
// -2 on failure to allocate memory
// -1 on invalid height/width
// 0 on success
int allocateFrameBuffer(buffer_t *buffer)
{
    int height = buffer->height;
    int width = buffer->width;

    // See if dimensions are possible
    if (height < 0 || width < 0)
	return -1;

    // If frameData is already allocated, free it
    if (buffer->frameData != NULL)
	freeBuffer(buffer);

    // Allocate the rows 
    if ((buffer->frameData = malloc(sizeof(char *) * height)) == NULL)
	return -2;

    // Allocate the columns
    for (int i = 0; i < height; i++)
    {
	// If we fail return -1 and free the previous allocations
	if ((buffer->frameData[i] = malloc(sizeof(char) * width)) == NULL)
	{
	    freeBuffer(buffer);

	    return -2;
	}
    }

    return 0;
}

// Deallocate all the frameData memory
void freeBuffer(buffer_t *buffer)
{
    // Return if already empty
    if (buffer->frameData == NULL)
	return;
    
    // Free memory and set to NULL
    for (int i = 0; i < buffer->height; i++)
    {
	free(buffer->frameData[i]);
    }
    free(buffer->frameData);

    buffer->frameData = NULL;
}

// Resize the frameData array and change size of buffer
// to new height/width
// return:
// -1 on bad height/width
// 0 on success
int resizeBuffer(int height, int width, buffer_t *buffer)
{
    //Make sure height and width are > 0
    if (height < 0 || width < 0)
	return -1;

    buffer_t *oldBuffer = buffer;
    buffer->height = height;
    buffer->width = width;

    // Allocate new array 
    allocateFrameBuffer(buffer);

    // Write old frameData information into new buffer
    int minHeight = oldBuffer->height < height ? oldBuffer->height : height;
    int minWidth = oldBuffer->width < width ? oldBuffer->width : width;

    for (int i = 0; i < height; i++)
    {
	for (int j = 0; j < width; j++)
	{
	    buffer->frameData[i][j] = oldBuffer->frameData[i][j];
	}
    }

    return 0;
}

// Replace a buffer with a new buffer
// return:
// -1 on invalid newBuffer contents
// 0 on success
int replaceBuffer(const buffer_t *newBuffer, buffer_t *oldBuffer)
{
    if (newBuffer->height < 0 || newBuffer->width < 0 || newBuffer->frameData == NULL)
	return -1;

    freeBuffer(oldBuffer);

    oldBuffer->height = newBuffer->height;
    oldBuffer->width = newBuffer->width;

    allocateFrameBuffer(oldBuffer);

    for (int i = 0; i < oldBuffer->height; i++)
    {
	for (int j = 0; j < oldBuffer->width; j++)
	{
	    oldBuffer->frameData[i][j] = newBuffer->frameData[i][j];
	}
    }

    return 0;
}


