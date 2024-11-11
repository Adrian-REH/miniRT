#include "libcolor.h"

int get_color(char *buffer, int endian, int *alpha)
{
    int color = 0;

    if (endian == 1) // Big endian
    {
        color |= (buffer[1] & 0xFF) << 16;
        color |= (buffer[2] & 0xFF) << 8;
        color |= (buffer[3] & 0xFF);
    }
    else // Little endian
    {
        color |= (buffer[0] & 0xFF);
        color |= (buffer[1] & 0xFF) << 8;
        color |= (buffer[2] & 0xFF) << 16;
    }

    return color;
}

