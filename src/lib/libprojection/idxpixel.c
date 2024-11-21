#include "../../main.h"

int	idxpixel(int width, int x, int y)
{
	return ((y * width * 4) + (x * 4));
}
