#include "libvector3.h"
double distance(Vector3 init, Vector3 end)
{
	return sqrt(pow(end.x - init.x, 2) + pow(end.y - init.y, 2) + pow(end.z - init.z, 2));
}
