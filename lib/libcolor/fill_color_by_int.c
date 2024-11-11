#include "libcolor.h"
void addint_to_color(Color *color, int src)
{
    if (color == NULL) {
        return NULL;  // Manejo de error de asignación de memoria
    }
    color->r = ((src >> 16) & 0xFF) / 255.0;
    color->g = ((src >> 8) & 0xFF) / 255.0;
    color->b = (src & 0xFF) / 255.0;
    color->color = src;
    return color;
}

void fillcolor_by_int(Color *color, int src)
{
    if (color == NULL) {
        return NULL;  // Manejo de error de asignación de memoria
    }
    color->r = ((src >> 16) & 0xFF) / 255.0;
    color->g = ((src >> 8) & 0xFF) / 255.0;
    color->b = (src & 0xFF) / 255.0;
    color->color = src;
    return color;
}

