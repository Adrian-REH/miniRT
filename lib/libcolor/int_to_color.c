#include "libcolor.h"

Color *int_to_color(int src)
{
    Color *color = malloc(sizeof(Color));
    if (color == NULL) {
        return NULL;  // Manejo de error de asignación de memoria
    }
    color->r = ((src >> 16) & 0xFF) / 255.0;
    color->g = ((src >> 8) & 0xFF) / 255.0;
    color->b = (src & 0xFF) / 255.0;
    color->color = src;
    return color;
}
