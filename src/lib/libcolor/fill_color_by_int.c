
#include "../../main.h"

void	addint_to_color(Color *color, int src)
{
	if (color == NULL)
		return ;
	color->r = ((src >> 16) & 0xFF) / 255.0;
	color->g = ((src >> 8) & 0xFF) / 255.0;
	color->b = (src & 0xFF) / 255.0;
	color->color = src;
}

void	fillcolor_by_int(Color *color, int src)
{
	if (color == NULL)
		return ;
	color->r = ((src >> 16) & 0xFF) / 255.0;
	color->g = ((src >> 8) & 0xFF) / 255.0;
	color->b = (src & 0xFF) / 255.0;
	color->color = src;
}
