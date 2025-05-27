#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

struct Buffer
{
    int width;
    int height;
    char frameData[][];
};

int initBuffer(int width, int height, struct Buffer *buffer);
int resizeBuffer(struct Buffer *buffer);

#endif
