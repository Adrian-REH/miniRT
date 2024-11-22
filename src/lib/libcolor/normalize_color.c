#include "../../main.h"

void	normalize_color(Color *color)
{
	color->r = fmax(0.0, fmin(1.0, color->r / 255.0));
	color->g = fmax(0.0, fmin(1.0, color->g / 255.0));
	color->b = fmax(0.0, fmin(1.0, color->b / 255.0));
}
