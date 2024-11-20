#include "../../main.h"

double calculate_intensity(Vector3 normal, Vector3 light_dir)
{
	double val = -dot(normal, light_dir);

	return fmax(0, val);
}