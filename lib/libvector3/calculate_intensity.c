#include "libvector3.h"

double calculate_intensity(Vector3 normal, Vector3 light_dir)
{
//	double val = -(normal.x * light_dir.x + normal.y * light_dir.y + normal.z * light_dir.z);
	double val = -dot(normal, light_dir);

	return fmax(0, val);
}