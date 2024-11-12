
#include "../../main.h"
int colornormal_to_int(Color color)
{
    int r = (int)(color.r * 255.0);
    int g = (int)(color.g * 255.0);
    int b = (int)(color.b * 255.0);
    return (r << 16) | (g << 8) | b;
}
