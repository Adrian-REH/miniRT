
#include "../../main.h"

int	colornormal_to_int(Color color)
{
	const int	r = (int)(color.r * 255.0);
	const int	g = (int)(color.g * 255.0);
	const int	b = (int)(color.b * 255.0);

	return ((r << 16) | (g << 8) | b);
}
