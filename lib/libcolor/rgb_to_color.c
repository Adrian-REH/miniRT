#include "libcolor.h"

Color *rgb_to_color(int r, int g, int b)
{
    Color *color = malloc(sizeof(Color));
    if (color == NULL) {
        return NULL;  // Manejo de error de asignación de memoria
    }
    color->r = (double)(r / 255.0);
    color->g = (double)(g / 255.0);
    color->b = (double)(b / 255.0);
    color->color = colornormal_to_int(*color);
    return color;
}