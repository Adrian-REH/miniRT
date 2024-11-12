#include "../../main.h"

int idxpixel(int x, int y)
{
	return (y * WINX * 4) + (x * 4);
}
