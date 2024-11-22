#include "../../main.h"

double	calculate_intensity(Vector3 normal, Vector3 light_dir)
{
	return (fmax(0, -dot(normal, light_dir)));
}
