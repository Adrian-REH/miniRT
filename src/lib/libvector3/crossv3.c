#include "../../main.h"

double	sin_v3(Vector3 v1, Vector3 v2)
{
	const double	u = mod(v1);
	const double	v = mod(v2);
	const double	uv = mod(cross_v3(v1, v2));

	if (u && v)
		return (uv / (u * v));
	return (0);
}

Vector3	cross_v3(Vector3 v1, Vector3 v2)
{
	return ((Vector3){
		v1.y * v2.z - v1.z * v2.y,
		v1.z * v2.x - v1.x * v2.z,
		v1.x * v2.y - v1.y * v2.x
	});
}
