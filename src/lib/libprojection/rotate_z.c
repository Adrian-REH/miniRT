#include "../../main.h"

Vector3	rotate_z(Vector3 v, double angle)
{
	const double	radians = angle * M_PI / 180.0;
	const double	cos_theta = cos(radians);
	const double	sin_theta = sin(radians);
	Vector3			result;

	result.x = v.x * cos_theta - v.y * sin_theta;
	result.y = v.x * sin_theta + v.y * cos_theta;
	result.z = v.z;
	return (result);
}
