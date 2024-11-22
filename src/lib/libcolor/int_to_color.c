
#include "../../main.h"

Color	*int_to_color(int src)
{
	Color	*color;

	color = malloc(sizeof(Color));
	if (color == NULL)
		return (NULL);
	color->r = ((src >> 16) & 0xFF) / 255.0;
	color->g = ((src >> 8) & 0xFF) / 255.0;
	color->b = (src & 0xFF) / 255.0;
	color->color = src;
	return (color);
}
