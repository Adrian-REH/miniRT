
#include "../../main.h"

Vector3	*hit_point(Ray ray, double t)
{
	Vector3 *hit_point = malloc(sizeof(Vector3));
	 hit_point->x = ray.origin.x + t * ray.direction.x;
	hit_point->y = ray.origin.y + t * ray.direction.y;
	hit_point->z = ray.origin.z + t * ray.direction.z;
	return hit_point;
}

Vector3	resolve_hit_point(Ray ray, double t)
{
	Vector3 hit_point;

	hit_point.x = ray.origin.x + t * ray.direction.x;
	hit_point.y = ray.origin.y + t * ray.direction.y;
	hit_point.z = ray.origin.z + t * ray.direction.z;
	return (hit_point);
}
