#include "../main.h"

int line_solution_point(Ray ray, Vector3 point)
{

	if ( !ray.direction.x && point.x != ray.origin.x)
		return 0;
	if ( !ray.direction.y && point.y != ray.origin.y)
		return 0;
	if ( !ray.direction.z && point.z != ray.origin.z)
		return 0;

   double tx = (ray.direction.x != 0) ? (point.x - ray.origin.x) / ray.direction.x : 0;
   double ty = (ray.direction.y != 0) ?(point.y - ray.origin.y) / ray.direction.y : 0;
   double tz = (ray.direction.z != 0) ?(point.z - ray.origin.z) / ray.direction.z : 0;

	if ((ray.direction.x && ray.direction.y && tx != ty) ||
	(ray.direction.x && ray.direction.z && tx != tz)||
	(ray.direction.y && ray.direction.z && ty != tz)
	)
		return 0;
	return tx;
}