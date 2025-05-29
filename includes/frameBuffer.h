#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

typedef struct Buffer
{
    int width;
    int height;
    char **frameData;
} buffer_t;

// Allocate frameData memory
// return:
// -2 on failure to allocate memory
// -1 on invalid height/width
// 0 on success
int allocateFrameBuffer(buffer_t *buffer);

// Deallocate all the frameData memory
// return:
// -1 if buffer is empty
// 0 on success
int freeBuffer(buffer_t *buffer);

// Resize the frameData array and change size of buffer
// to new height/width
// return:
// -1 on bad height/width
// 0 on success
int resizeBuffer(int height, int width, buffer_t *buffer);

// Replace a buffer with a new buffer
int replaceBuffer(const buffer_t *newBuffer, buffer_t *oldBuffer);

#endif
