#include "../../main.h"

void	normalize(Vector3 *v)
{
	const double	magnitude = sqrt(v->x * v->x + v->y * v->y + v->z * v->z);

	if (magnitude > 0)
	{
		v->x /= magnitude;
		v->y /= magnitude;
		v->z /= magnitude;
	}
}

Vector3	*invnormal(Vector3 *normal)
{
	normal->x = -normal->x;
	normal->y = -normal->y;
	normal->z = -normal->z;
	return (normal);
}

Vector3	subtract(Vector3 init, Vector3 end)
{
	Vector3	direction;

	direction.x = end.x - init.x;
	direction.y = end.y - init.y;
	direction.z = end.z - init.z;
	return (direction);
}

Vector3	norm_subtract(Vector3 init, Vector3 end)
{
	Vector3	direction;

	direction.x = end.x - init.x;
	direction.y = end.y - init.y;
	direction.z = end.z - init.z;
	normalize(&direction);
	return (direction);
}
