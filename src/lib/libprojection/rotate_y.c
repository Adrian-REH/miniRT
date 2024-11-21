#include "../../main.h"

Vector3	rotate_y(Vector3 v, double angle)
{
	const double	radians = angle * M_PI / 180.0;
	const double	cos_theta = cos(radians);
	const double	sin_theta = sin(radians);
	Vector3			result;

	result.x = v.x * cos_theta + v.z * sin_theta;
	result.y = v.y;
	result.z = -v.x * sin_theta + v.z * cos_theta;
	return (result);
}
